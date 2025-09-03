/*
 * Copyright (c) 2025 Samsung Electronics Co., Ltd.
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * - Neither the name of the copyright owner, nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <oapv.h>
#include "oapv_port.h"

#define CLIP_VAL(n, min, max) (((n) > (max)) ? (max) : (((n) < (min)) ? (min) : (n)))
#define ALIGN_VAL(val, align) ((((val) + (align) - 1) / (align)) * (align))

/* assert function */
#include <assert.h>

/* Function for atomic increment:
   This function might need to modify according to O/S or CPU platform
*/
static int atomic_inc(volatile int *pcnt)
{
    int ret;
    ret = *pcnt;
    ret++;
    *pcnt = ret;
    return ret;
}

/* Function for atomic decrement:
   This function might need to modify according to O/S or CPU platform
*/
static int atomic_dec(volatile int *pcnt)
{
    int ret;
    ret = *pcnt;
    ret--;
    *pcnt = ret;
    return ret;
}

/* Function to allocate memory for picture buffer:
   This function might need to modify according to O/S or CPU platform
*/
static void *picbuf_alloc(int size)
{
    return oapv_malloc(size);
}

/* Function to free memory allocated for picture buffer:
   This function might need to modify according to O/S or CPU platform
*/
static void picbuf_free(void *p)
{
    if(p) {
        oapv_mfree(p);
    }
}

static int imgb_addref(oapv_imgb_t *imgb)
{
    oapv_assert_rv(imgb, OAPV_ERR_INVALID_ARGUMENT);
    return atomic_inc(&imgb->refcnt);
}

static int imgb_getref(oapv_imgb_t *imgb)
{
    oapv_assert_rv(imgb, OAPV_ERR_INVALID_ARGUMENT);
    return imgb->refcnt;
}

static int imgb_release(oapv_imgb_t *imgb)
{
    int refcnt, i;
    oapv_assert_rv(imgb, OAPV_ERR_INVALID_ARGUMENT);
    refcnt = atomic_dec(&imgb->refcnt);
    if(refcnt == 0) {
        for(i = 0; i < OAPV_MAX_CC; i++) {
            if(imgb->baddr[i])
                picbuf_free(imgb->baddr[i]);
        }
        oapv_mfree(imgb);
    }
    return refcnt;
}

static void imgb_cpy_plane(oapv_imgb_t *dst, oapv_imgb_t *src)
{
    int            i, j;
    unsigned char *s, *d;
    int            numbyte = OAPV_CS_GET_BYTE_DEPTH(src->cs);

    for(i = 0; i < src->np; i++) {
        s = (unsigned char *)src->a[i];
        d = (unsigned char *)dst->a[i];

        for(j = 0; j < src->ah[i]; j++) {
            oapv_mcpy(d, s, numbyte * src->aw[i]);
            s += src->s[i];
            d += dst->s[i];
        }
    }
}

static void imgb_cpy_shift_left_8b(oapv_imgb_t *dst, oapv_imgb_t *src, int shift)
{
    int            i, j, k;

    unsigned char *s;
    short         *d;

    for(i = 0; i < dst->np; i++) {
        s = (unsigned char *)src->a[i];
        d = (short *)dst->a[i];

        for(j = 0; j < src->ah[i]; j++) {
            for(k = 0; k < src->aw[i]; k++) {
                d[k] = (short)(s[k] << shift);
            }
            s = s + src->s[i];
            d = (short *)(((unsigned char *)d) + dst->s[i]);
        }
    }
}

static void imgb_cpy_shift_right_8b(oapv_imgb_t *dst, oapv_imgb_t *src, int shift)
{
    int            i, j, k, t0, add;

    short         *s;
    unsigned char *d;

    if(shift)
        add = 1 << (shift - 1);
    else
        add = 0;

    for(i = 0; i < dst->np; i++) {
        s = (short *)src->a[i];
        d = (unsigned char *)dst->a[i];

        for(j = 0; j < src->ah[i]; j++) {
            for(k = 0; k < src->aw[i]; k++) {
                t0 = ((s[k] + add) >> shift);
                d[k] = (unsigned char)(CLIP_VAL(t0, 0, 255));
            }
            s = (short *)(((unsigned char *)s) + src->s[i]);
            d = d + dst->s[i];
        }
    }
}

static void imgb_cpy_shift_left(oapv_imgb_t *dst, oapv_imgb_t *src, int shift)
{
    int             i, j, k;

    unsigned short *s;
    unsigned short *d;

    for(i = 0; i < dst->np; i++) {
        s = (unsigned short *)src->a[i];
        d = (unsigned short *)dst->a[i];

        for(j = 0; j < src->h[i]; j++) {
            for(k = 0; k < src->w[i]; k++) {
                d[k] = (unsigned short)(s[k] << shift);
            }
            s = (unsigned short *)(((unsigned char *)s) + src->s[i]);
            d = (unsigned short *)(((unsigned char *)d) + dst->s[i]);
        }
    }
}

static void imgb_cpy_shift_right(oapv_imgb_t *dst, oapv_imgb_t *src, int shift)
{
    int             i, j, k, t0, add;

    int             clip_min = 0;
    int             clip_max = 0;

    unsigned short *s;
    unsigned short *d;

    if(shift)
        add = 1 << (shift - 1);
    else
        add = 0;

    clip_max = (1 << (OAPV_CS_GET_BIT_DEPTH(dst->cs))) - 1;

    for(i = 0; i < dst->np; i++) {
        s = (unsigned short *)src->a[i];
        d = (unsigned short *)dst->a[i];

        for(j = 0; j < src->h[i]; j++) {
            for(k = 0; k < src->w[i]; k++) {
                t0 = ((s[k] + add) >> shift);
                d[k] = (CLIP_VAL(t0, clip_min, clip_max));
            }
            s = (unsigned short *)(((unsigned char *)s) + src->s[i]);
            d = (unsigned short *)(((unsigned char *)d) + dst->s[i]);
        }
    }
}

void oapv_imgb_cpy(oapv_imgb_t *dst, oapv_imgb_t *src)
{
    int i, bd_src, bd_dst;
    bd_src = OAPV_CS_GET_BIT_DEPTH(src->cs);
    bd_dst = OAPV_CS_GET_BIT_DEPTH(dst->cs);

    if(src->cs == dst->cs) {
        imgb_cpy_plane(dst, src);
    }
    else if(bd_src == 8 && bd_dst > 8) {
        imgb_cpy_shift_left_8b(dst, src, bd_dst - bd_src);
    }
    else if(bd_src > 8 && bd_dst == 8) {
        imgb_cpy_shift_right_8b(dst, src, bd_src - bd_dst);
    }
    else if(bd_src < bd_dst) {
        imgb_cpy_shift_left(dst, src, bd_dst - bd_src);
    }
    else if(bd_src > bd_dst) {
        imgb_cpy_shift_right(dst, src, bd_src - bd_dst);
    }
    else {
        oapv_trace("ERROR: unsupported image copy\n");
        return;
    }
    for(i = 0; i < OAPV_MAX_CC; i++) {
        dst->x[i] = src->x[i];
        dst->y[i] = src->y[i];
        dst->w[i] = src->w[i];
        dst->h[i] = src->h[i];
        dst->ts[i] = src->ts[i];
    }
}

oapv_imgb_t *oapv_imgb_create(int w, int h, int cs)
{
    int          i, bd;
    oapv_imgb_t *imgb;

    imgb = (oapv_imgb_t *)oapv_malloc(sizeof(oapv_imgb_t));
    if(imgb == NULL)
        goto ERR;
    oapv_mset(imgb, 0, sizeof(oapv_imgb_t));

    bd = OAPV_CS_GET_BYTE_DEPTH(cs); /* byte unit */

    imgb->w[0] = w;
    imgb->h[0] = h;
    switch(OAPV_CS_GET_FORMAT(cs)) {
    case OAPV_CF_YCBCR400:
        imgb->w[1] = imgb->w[2] = w;
        imgb->h[1] = imgb->h[2] = h;
        imgb->np = 1;
        break;
    case OAPV_CF_YCBCR420:
        imgb->w[1] = imgb->w[2] = (w + 1) >> 1;
        imgb->h[1] = imgb->h[2] = (h + 1) >> 1;
        imgb->np = 3;
        break;
    case OAPV_CF_YCBCR422:
        imgb->w[1] = imgb->w[2] = (w + 1) >> 1;
        imgb->h[1] = imgb->h[2] = h;
        imgb->np = 3;
        break;
    case OAPV_CF_YCBCR444:
        imgb->w[1] = imgb->w[2] = w;
        imgb->h[1] = imgb->h[2] = h;
        imgb->np = 3;
        break;
    case OAPV_CF_YCBCR4444:
        imgb->w[1] = imgb->w[2] = imgb->w[3] = w;
        imgb->h[1] = imgb->h[2] = imgb->h[3] = h;
        imgb->np = 4;
        break;
    case OAPV_CF_PLANAR2:
        imgb->w[1] = w;
        imgb->h[1] = h;
        imgb->np = 2;
        break;
    default:
        oapv_trace("unsupported color format\n");
        goto ERR;
    }

    for(i = 0; i < imgb->np; i++) {
        // width and height need to be aligned to macroblock size
        imgb->aw[i] = ALIGN_VAL(imgb->w[i], OAPV_MB_W);
        imgb->s[i] = imgb->aw[i] * bd;
        imgb->ah[i] = ALIGN_VAL(imgb->h[i], OAPV_MB_H);
        imgb->e[i] = imgb->ah[i];

        imgb->bsize[i] = imgb->s[i] * imgb->e[i];
        imgb->a[i] = imgb->baddr[i] = picbuf_alloc(imgb->bsize[i]);
        oapv_assert_g(imgb->a[i] != NULL, ERR);
        oapv_mset(imgb->a[i], 0, imgb->bsize[i]);
    }
    imgb->cs = cs;
    imgb->addref = imgb_addref;
    imgb->getref = imgb_getref;
    imgb->release = imgb_release;

    imgb->addref(imgb); /* increase reference count */
    return imgb;

ERR:
    oapv_trace("cannot create image buffer\n");
    if(imgb) {
        for(int i = 0; i < OAPV_MAX_CC; i++) {
            if(imgb->a[i])
                picbuf_free(imgb->a[i]);
        }
        oapv_mfree(imgb);
    }
    return NULL;
}

