APV Family
==============

# Introduction

This document details the standard configurations of the APV codec, collectively termed the 'APV family'. Although the APV family is not formally defined in the APV specification, it provides a useful framework for defining typical setups and ensures uniform communication practices.

The choice of which APV family to use depends on factors like file size requirements, desired quality, and the specific editing environment. For example, 422 HQ might be preferred for preserving the high quality video, while 422 LT might be used for lower file sizes and bandwidth usage, making it suitable for situations where storage space or network transfer is a concern.

# Description of APV family

| Usage | Family | Color Sampling |
|:-------------|:--------------:|:------:|
| High quality mezzanine                   | APV 422 HQ | 4:2:2 | 
| Standard quality mezzanine               | APV 422 SQ | 4:2:2 | 
| Editing-friendly low-data-rate workflows | APV 422 LQ | 4:2:2 | 
| Finishing                                | APV 444 UQ | 4:4:4 | 


## Target bitrates of APV family

Following table is the typical bitrates of APV family.
Actual compressed bitrate may have about 10% variations according to complexity of video signal.

|Resolution | Frame Rate | APV 422 LQ | | APV 422 SQ | | APV 422 HQ | | APV 444 UQ | |
|:---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| |  | Mb/s | GB/h | Mb/s | GB/h | Mb/s | GB/h | Mb/s | GB/h|
|qHD     960x540 | 24p | 29 | 13 | 41 | 18 | 57 | 26 | 85 | 38|
| | 25p | 31 | 14 | 42 | 19 | 59 | 27 | 89 | 40|
| | 30p | 37 | 17 | 51 | 23 | 71 | 32 | 107 | 48|
| | 50p | 61 | 28 | 85 | 38 | 118 | 53 | 178 | 80|
| | 60p | 73 | 33 | 101 | 46 | 142 | 64 | 213 | 96|
| | 120p | 147 | 66 | 203 | 91 | 284 | 128 | 426 | 192|
|HD     1280x720 | 24p | 40 | 18 | 55 | 25 | 78 | 35 | 116 | 52|
| | 25p | 42 | 19 | 58 | 26 | 81 | 36 | 121 | 55|
| | 30p | 50 | 23 | 69 | 31 | 97 | 44 | 146 | 65|
| | 50p | 84 | 38 | 115 | 52 | 162 | 73 | 243 | 109|
| | 60p | 100 | 45 | 139 | 62 | 194 | 87 | 291 | 131|
| | 120p | 201 | 90 | 277 | 125 | 388 | 175 | 582 | 262|
|FHD     1920x1080 | 24p | 81 | 36 | 111 | 50 | 156 | 70 | 234 | 105|
| | 25p | 84 | 38 | 116 | 52 | 163 | 73 | 244 | 110|
| | 30p | 101 | 45 | 139 | 63 | 195 | 88 | 293 | 132|
| | 50p | 168 | 76 | 232 | 104 | 325 | 146 | 488 | 219|
| | 60p | 202 | 91 | 279 | 125 | 390 | 176 | 585 | 263|
| | 120p | 404 | 182 | 557 | 251 | 780 | 351 | 1,170 | 527|
|2K     2048x1080 | 24p | 86 | 39 | 119 | 53 | 166 | 75 | 250 | 112|
| | 25p | 90 | 40 | 124 | 56 | 173 | 78 | 260 | 117|
| | 30p | 108 | 48 | 149 | 67 | 208 | 94 | 312 | 140|
| | 50p | 179 | 81 | 248 | 111 | 347 | 156 | 520 | 234|
| | 60p | 215 | 97 | 297 | 134 | 416 | 187 | 624 | 281|
| | 120p | 431 | 194 | 594 | 267 | 832 | 374 | 1,248 | 562|
|UHD   4K     3840x2160 | 24p | 323 | 145 | 446 | 201 | 624 | 281 | 936 | 421|
| | 25p | 336 | 151 | 464 | 209 | 650 | 293 | 975 | 439|
| | 30p | 404 | 182 | 557 | 251 | 780 | 351 | 1,170 | 527|
| | 50p | 673 | 303 | 929 | 418 | 1,300 | 585 | 1,950 | 878|
| | 60p | 807 | 363 | 1,114 | 501 | 1,560 | 702 | 2,340 | 1,053|
| | 120p | 1,615 | 727 | 2,229 | 1,003 | 3,120 | 1,404 | 4,680 | 2,106|
|4K     4096x2160 | 24p | 345 | 155 | 475 | 214 | 666 | 300 | 998 | 449|
| | 25p | 359 | 161 | 495 | 223 | 693 | 312 | 1,040 | 468|
| | 30p | 431 | 194 | 594 | 267 | 832 | 374 | 1,248 | 562|
| | 50p | 718 | 323 | 990 | 446 | 1,387 | 624 | 2,080 | 936|
| | 60p | 861 | 388 | 1,189 | 535 | 1,664 | 749 | 2,496 | 1,123|
| | 120p | 1,723 | 775 | 2,377 | 1,070 | 3,328 | 1,498 | 4,992 | 2,246|
|UHD   8K     7680x4320 | 24p | 1,292 | 581 | 1,783 | 802 | 2,496 | 1,123 | 3,744 | 1,685|
| | 25p | 1,346 | 606 | 1,857 | 836 | 2,600 | 1,170 | 3,900 | 1,755|
| | 30p | 1,615 | 727 | 2,229 | 1,003 | 3,120 | 1,404 | 4,680 | 2,106|
| | 50p | 2,692 | 1,211 | 3,714 | 1,671 | 5,200 | 2,340 | 7,800 | 3,510|
| | 60p | 3,230 | 1,453 | 4,457 | 2,006 | 6,240 | 2,808 | 9,360 | 4,212|
| | 120p | 6,460 | 2,907 | 8,914 | 4,011 | 12,480 | 5,616 | 18,720 | 8,424|
|8K     8192x4320 | 24p | 1,378 | 620 | 1,902 | 856 | 2,662 | 1,198 | 3,994 | 1,797|
| | 25p | 1,435 | 646 | 1,981 | 891 | 2,773 | 1,248 | 4,160 | 1,872|
| | 30p | 1,723 | 775 | 2,377 | 1,070 | 3,328 | 1,498 | 4,992 | 2,246|
| | 50p | 2,871 | 1,292 | 3,962 | 1,783 | 5,547 | 2,496 | 8,320 | 3,744|
| | 60p | 3,445 | 1,550 | 4,754 | 2,139 | 6,656 | 2,995 | 9,984 | 4,493|
| | 120p | 6,890 | 3,101 | 9,509 | 4,279 | 13,312 | 5,990 | 19,968 | 8,986|

< table: Typical bitrates (Mega bits/sec, Giga Bytes/hour) >


