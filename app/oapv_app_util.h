/*
 * Copyright (c) 2022 Samsung Electronics Co., Ltd.
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

#ifndef _OAPV_APP_UTIL_H_
#define _OAPV_APP_UTIL_H_

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <ctype.h>
#if LINUX
#include <signal.h>
#include <unistd.h>
#endif

#define VERBOSE_NONE   0
#define VERBOSE_ERROR  1
#define VERBOSE_SIMPLE 2
#define VERBOSE_FRAME  3

/* logging functions */
static void log_msg(char *filename, int line, const char *fmt, ...)
{
    char str[1024] = { '\0' };
    if(filename != NULL && line >= 0)
        sprintf(str, "[%s:%d] ", filename, line);
    va_list args;
    va_start(args, fmt);
    vsprintf(str + strlen(str), fmt, args);
    va_end(args);
    printf("%s", str);
}

static void log_line(char *pre)
{
    int       i, len;
    char      str[128] = { '\0' };
    const int chars = 80;
    for(i = 0; i < 3; i++) {
        str[i] = '=';
    }
    str[i] = '\0';

    len = (pre == NULL) ? 0 : (int)strlen(pre);
    if(len > 0) {
        sprintf(str + 3, " %s ", pre);
        len = (int)strlen(str);
    }

    for(i = len; i < chars; i++) {
        str[i] = '=';
    }
    str[chars] = '\0';
    printf("%s\n", str);
}

#if defined(__GNUC__)
#define __FILENAME__ \
    (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define logerr(args...)                   \
    {                                     \
        if(op_verbose >= VERBOSE_ERROR) { \
            log_msg(NULL, -1, args);      \
        }                                 \
    }
#define logv2(args...)                     \
    {                                      \
        if(op_verbose >= VERBOSE_SIMPLE) { \
            log_msg(NULL, -1, args);       \
        }                                  \
    }
#define logv3(args...)                    \
    {                                     \
        if(op_verbose >= VERBOSE_FRAME) { \
            log_msg(NULL, -1, args);      \
        }                                 \
    }
#else
#define __FILENAME__ \
    (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define logerr(args, ...)                         \
    {                                             \
        if(op_verbose >= VERBOSE_ERROR) {         \
            log_msg(NULL, -1, args, __VA_ARGS__); \
        }                                         \
    }
#define logv2(args, ...)                          \
    {                                             \
        if(op_verbose >= VERBOSE_SIMPLE) {        \
            log_msg(NULL, -1, args, __VA_ARGS__); \
        }                                         \
    }
#define logv3(args, ...)                          \
    {                                             \
        if(op_verbose >= VERBOSE_FRAME) {         \
            log_msg(NULL, -1, args, __VA_ARGS__); \
        }                                         \
    }
#endif
#define logv2_line(pre)                    \
    {                                      \
        if(op_verbose >= VERBOSE_SIMPLE) { \
            log_line(pre);                 \
        }                                  \
    }
#define logv3_line(pre)                   \
    {                                     \
        if(op_verbose >= VERBOSE_FRAME) { \
            log_line(pre);                \
        }                                 \
    }

/* assert function */
#include <assert.h>
#define assert_r(x)    \
    {                  \
        if(!(x)) {     \
            assert(x); \
            return;    \
        }              \
    }
#define assert_rv(x, r) \
    {                   \
        if(!(x)) {      \
            assert(x);  \
            return (r); \
        }               \
    }
#define assert_g(x, g) \
    {                  \
        if(!(x)) {     \
            assert(x); \
            goto g;    \
        }              \
    }
#define assert_gv(x, r, v, g) \
    {                         \
        if(!(x)) {            \
            assert(x);        \
            (r) = (v);        \
            goto g;           \
        }                     \
    }

static int op_verbose = VERBOSE_SIMPLE;

/* Clocks */
#if defined(_WIN64) || defined(_WIN32)
#include <windows.h>

typedef DWORD oapv_clk_t;
#define OAPV_CLK_PER_SEC  (1000)
#define OAPV_CLK_PER_MSEC (1)
#define OAPV_CLK_MAX      ((oapv_clk_t)(-1))
#define oapv_clk_get()    GetTickCount()

#elif __linux__ || __CYGWIN__ || __APPLE__
#include <time.h>
#include <sys/time.h>
typedef unsigned long oapv_clk_t;
#define OAPV_CLK_MAX      ((oapv_clk_t)(-1))
#define OAPV_CLK_PER_SEC  (10000)
#define OAPV_CLK_PER_MSEC (10)
static oapv_clk_t     oapv_clk_get(void)
{
    oapv_clk_t     clk;
    struct timeval t;
    gettimeofday(&t, NULL);
    clk = t.tv_sec * 10000L + t.tv_usec / 100L;
    return clk;
}

#else
#error THIS PLATFORM CANNOT SUPPORT CLOCK
#endif

static __inline oapv_clk_t oapv_clk_diff(oapv_clk_t t1, oapv_clk_t t2)
{
    return (((t2) >= (t1)) ? ((t2) - (t1)) : ((OAPV_CLK_MAX - (t1)) + (t2)));
}

static __inline oapv_clk_t oapv_clk_from(oapv_clk_t from)
{
    oapv_clk_t now = oapv_clk_get();
    return oapv_clk_diff(from, now);
}

static __inline oapv_clk_t oapv_clk_msec(oapv_clk_t clk)
{
    return ((oapv_clk_t)((clk + (OAPV_CLK_PER_MSEC / 2)) / OAPV_CLK_PER_MSEC));
}

static __inline oapv_clk_t oapv_clk_sec(oapv_clk_t clk)
{
    return ((oapv_clk_t)((clk + (OAPV_CLK_PER_SEC / 2)) / OAPV_CLK_PER_SEC));
}


static int imgb_read(FILE *fp, oapv_imgb_t *img, int width, int height, int is_y4m)
{
    int            f_w, f_h;
    unsigned char *p8;

    /* handling Y4M frame header */
    char           t_buf[10];
    if(is_y4m) {
        if(6 != fread(t_buf, 1, 6, fp))
            return -1;
        if(memcmp(t_buf, "FRAME", 5)) {
            logerr("Loss of framing in Y4M input data\n");
            return -1;
        }
        if(t_buf[5] != '\n') {
            logerr("Error parsing Y4M frame header\n");
            return -1;
        }
    }

    /* reading YUV format */
    int chroma_format = OAPV_CS_GET_FORMAT(img->cs);
    int bit_depth = OAPV_CS_GET_BIT_DEPTH(img->cs);
    int w_shift = (chroma_format == OAPV_CF_YCBCR420) || ((chroma_format == OAPV_CF_YCBCR422) || (chroma_format == OAPV_CF_PLANAR2)) ? 1 : 0;
    int h_shift = chroma_format == OAPV_CF_YCBCR420 ? 1 : 0;

    if(bit_depth == 8) {
        f_w = width;
        f_h = height;
    }
    else if(bit_depth >= 10 && bit_depth <= 14) {
        f_w = width * sizeof(short);
        f_h = height;
    }
    else {
        logerr("unsupported bit-depth (%d)\n", bit_depth);
        return -1;
    }

    p8 = (unsigned char *)img->a[0];
    for(int j = 0; j < f_h; j++) {
        if(fread(p8, 1, f_w, fp) != (unsigned)f_w) {
            return -1;
        }
        p8 += img->s[0];
    }

    if(chroma_format == OAPV_CF_PLANAR2) {
        p8 = (unsigned char *)img->a[1];
        for(int j = 0; j < f_h; j++) {
            if(fread(p8, 1, f_w, fp) != (unsigned)f_w) {
                return -1;
            }
            p8 += img->s[1];
        }
    }
    else if(chroma_format != OAPV_CF_YCBCR400) {
        f_w = f_w >> w_shift;
        f_h = f_h >> h_shift;

        p8 = (unsigned char *)img->a[1];
        for(int j = 0; j < f_h; j++) {
            if(fread(p8, 1, f_w, fp) != (unsigned)f_w) {
                return -1;
            }
            p8 += img->s[1];
        }

        p8 = (unsigned char *)img->a[2];
        for(int j = 0; j < f_h; j++) {
            if(fread(p8, 1, f_w, fp) != (unsigned)f_w) {
                return -1;
            }
            p8 += img->s[2];
        }
    }

    if(chroma_format == OAPV_CF_YCBCR4444) {
        f_w = f_w >> w_shift;
        f_h = f_h >> h_shift;

        p8 = (unsigned char *)img->a[3];
        for(int j = 0; j < f_h; j++) {
            if(fread(p8, 1, f_w, fp) != (unsigned)f_w) {
                return -1;
            }
            p8 += img->s[3];
        }
    }

    return 0;
}

static int imgb_write(char *fname, oapv_imgb_t *imgb)
{
    unsigned char *p8;
    int            i, j, bd;
    FILE          *fp;

    int            chroma_format = OAPV_CS_GET_FORMAT(imgb->cs);
    int            bit_depth = OAPV_CS_GET_BIT_DEPTH(imgb->cs);

    fp = fopen(fname, "ab");
    if(fp == NULL) {
        logerr("cannot open file = %s\n", fname);
        return -1;
    }
    if(bit_depth == 8 && (chroma_format == OAPV_CF_YCBCR400 || chroma_format == OAPV_CF_YCBCR420 || chroma_format == OAPV_CF_YCBCR422 ||
                          chroma_format == OAPV_CF_YCBCR444 || chroma_format == OAPV_CF_YCBCR4444)) {
        bd = 1;
    }
    else if(bit_depth >= 10 && bit_depth <= 14 && (chroma_format == OAPV_CF_YCBCR400 || chroma_format == OAPV_CF_YCBCR420 || chroma_format == OAPV_CF_YCBCR422 || chroma_format == OAPV_CF_YCBCR444 || chroma_format == OAPV_CF_YCBCR4444)) {
        bd = 2;
    }
    else if(bit_depth >= 10 && chroma_format == OAPV_CF_PLANAR2) {
        bd = 2;
    }
    else {
        logerr("cannot support the color space\n");
        fclose(fp);
        return -1;
    }

    for(i = 0; i < imgb->np; i++) {
        p8 = (unsigned char *)imgb->a[i] + (imgb->s[i] * imgb->y[i]) + (imgb->x[i] * bd);

        for(j = 0; j < imgb->h[i]; j++) {
            fwrite(p8, imgb->w[i] * bd, 1, fp);
            p8 += imgb->s[i];
        }
    }

    fclose(fp);
    return 0;
}

static void measure_psnr(oapv_imgb_t *org, oapv_imgb_t *rec, double psnr[4], int bit_depth)
{
    double sum[4], mse[4];

    if(bit_depth == 8) {
        unsigned char *o, *r;
        int            i, j, k;

        for(i = 0; i < org->np; i++) {
            o = (unsigned char *)org->a[i];
            r = (unsigned char *)rec->a[i];
            sum[i] = 0;

            for(j = 0; j < org->h[i]; j++) {
                for(k = 0; k < org->w[i]; k++) {
                    sum[i] += (o[k] - r[k]) * (o[k] - r[k]);
                }

                o += org->s[i];
                r += rec->s[i];
            }
            mse[i] = sum[i] / (org->w[i] * org->h[i]);
            psnr[i] = (mse[i] == 0.0) ? 100. : fabs(10 * log10(((255 * 255) / mse[i])));
        }
    }
    else {
        /* more than 8bit, ex) 10bit */
        unsigned short *o, *r;
        int             i, j, k;
        int             factor = 1 << (bit_depth - 8);
        factor *= factor;
        for(i = 0; i < org->np; i++) {
            o = (unsigned short *)org->a[i];
            r = (unsigned short *)rec->a[i];
            sum[i] = 0;
            for(j = 0; j < org->h[i]; j++) {
                for(k = 0; k < org->w[i]; k++) {
                    if(OAPV_CS_GET_FORMAT(org->cs) == OAPV_CF_PLANAR2) {
                        sum[i] += (((int)o[k] - (int)r[k]) >> 6) * (((int)o[k] - (int)r[k]) >> 6);
                    }
                    else {
                        sum[i] += (o[k] - r[k]) * (o[k] - r[k]);
                    }
                }
                o = (unsigned short *)((unsigned char *)o + org->s[i]);
                r = (unsigned short *)((unsigned char *)r + rec->s[i]);
            }
            mse[i] = sum[i] / (org->w[i] * org->h[i]);
            psnr[i] = (mse[i] == 0.0) ? 100. : fabs(10 * log10(((255 * 255 * factor) / mse[i])));
        }
    }
}

static int write_data(char *fname, unsigned char *data, int size)
{
    FILE *fp;

    fp = fopen(fname, "ab");
    if(fp == NULL) {
        logerr("cannot open the output file=%s\n", fname);
        return -1;
    }
    fwrite(data, 1, size, fp);
    fclose(fp);
    return 0;
}

static int clear_data(char *fname)
{
    FILE *fp;
    fp = fopen(fname, "wb");
    if(fp == NULL) {
        logerr("cannot remove file (%s)\n", fname);
        return -1;
    }
    fclose(fp);
    return 0;
}
static unsigned char char_to_hex(char a)
{
    unsigned char ret;

    switch(a) {
    case 'a':
    case 'A':
        ret = 10;
        break;
    case 'b':
    case 'B':
        ret = 11;
        break;
    case 'c':
    case 'C':
        ret = 12;
        break;
    case 'd':
    case 'D':
        ret = 13;
        break;
    case 'e':
    case 'E':
        ret = 14;
        break;
    case 'f':
    case 'F':
        ret = 15;
        break;
    default:
        ret = (unsigned char)a - '0';
        break;
    }
    return ret;
}

#endif /* _OAPV_APP_UTIL_H_ */
