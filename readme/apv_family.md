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

|Resolution | Frame Rate | APV 422 LQ | | APV 422 SQ | | APV 422 HQ | | APV 444 HQ | |
|:---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| |  | Mb/s | GB/h | Mb/s | GB/h | Mb/s | GB/h | Mb/s | GB/h|
|qHD     1280x720 | 24p | 28 | 13 | 42 | 19 | 56 | 25 | 84 | 38|
| | 25p | 29 | 13 | 44 | 20 | 58 | 26 | 88 | 39|
| | 30p | 35 | 16 | 53 | 24 | 70 | 32 | 105 | 47|
| | 50p | 58 | 26 | 88 | 39 | 117 | 53 | 175 | 79|
| | 60p | 70 | 32 | 105 | 47 | 140 | 63 | 210 | 95|
| | 120p | 140 | 63 | 210 | 95 | 280 | 126 | 420 | 189|
|HD     1280x720 | 24p | 40 | 18 | 60 | 27 | 80 | 36 | 120 | 54|
| | 25p | 42 | 19 | 63 | 28 | 83 | 38 | 125 | 56|
| | 30p | 50 | 23 | 75 | 34 | 100 | 45 | 150 | 68|
| | 50p | 83 | 38 | 125 | 56 | 167 | 75 | 250 | 113|
| | 60p | 100 | 45 | 150 | 68 | 200 | 90 | 300 | 135|
| | 120p | 200 | 90 | 300 | 135 | 400 | 180 | 600 | 270|
|FHD     1920x1080 | 24p | 86 | 39 | 129 | 58 | 173 | 78 | 259 | 116|
| | 25p | 90 | 40 | 135 | 61 | 180 | 81 | 270 | 121|
| | 30p | 108 | 49 | 162 | 73 | 216 | 97 | 323 | 146|
| | 50p | 180 | 81 | 270 | 121 | 359 | 162 | 539 | 243|
| | 60p | 216 | 97 | 323 | 146 | 431 | 194 | 647 | 291|
| | 120p | 431 | 194 | 647 | 291 | 863 | 388 | 1,294 | 582|
|2K     2048x1080 | 24p | 92 | 41 | 138 | 62 | 184 | 83 | 276 | 124|
| | 25p | 96 | 43 | 144 | 65 | 192 | 86 | 288 | 129|
| | 30p | 115 | 52 | 173 | 78 | 230 | 104 | 345 | 155|
| | 50p | 192 | 86 | 288 | 129 | 383 | 173 | 575 | 259|
| | 60p | 230 | 104 | 345 | 155 | 460 | 207 | 690 | 311|
| | 120p | 460 | 207 | 690 | 311 | 920 | 414 | 1,380 | 621|
|UHD   4K     3840x2160 | 24p | 300 | 135 | 450 | 203 | 600 | 270 | 900 | 405|
| | 25p | 313 | 141 | 469 | 211 | 625 | 281 | 938 | 422|
| | 30p | 375 | 169 | 563 | 253 | 750 | 338 | 1,125 | 506|
| | 50p | 625 | 281 | 938 | 422 | 1,250 | 563 | 1,875 | 844|
| | 60p | 750 | 338 | 1,125 | 506 | 1,500 | 675 | 2,250 | 1,013|
| | 120p | 1,500 | 675 | 2,250 | 1,013 | 3,000 | 1,350 | 4,500 | 2,025|
|4K     4096x2160 | 24p | 312 | 140 | 468 | 211 | 624 | 281 | 936 | 421|
| | 25p | 325 | 146 | 488 | 219 | 650 | 293 | 975 | 439|
| | 30p | 390 | 176 | 585 | 263 | 780 | 351 | 1,170 | 527|
| | 50p | 650 | 293 | 975 | 439 | 1,300 | 585 | 1,950 | 878|
| | 60p | 780 | 351 | 1,170 | 527 | 1,560 | 702 | 2,340 | 1,053|
| | 120p | 1,560 | 702 | 2,340 | 1,053 | 3,120 | 1,404 | 4,680 | 2,106|
|UHD   8K     7680x4320 | 24p | 1,125 | 506 | 1,688 | 759 | 2,250 | 1,013 | 3,375 | 1,519|
| | 25p | 1,172 | 527 | 1,758 | 791 | 2,344 | 1,055 | 3,516 | 1,582|
| | 30p | 1,406 | 633 | 2,109 | 949 | 2,813 | 1,266 | 4,219 | 1,898|
| | 50p | 2,344 | 1,055 | 3,516 | 1,582 | 4,688 | 2,109 | 7,031 | 3,164|
| | 60p | 2,813 | 1,266 | 4,219 | 1,898 | 5,625 | 2,531 | 8,438 | 3,797|
| | 120p | 5,625 | 2,531 | 8,438 | 3,797 | 11,250 | 5,063 | 16,875 | 7,594|
|8K     8192x4320 | 24p | 1,248 | 562 | 1,872 | 842 | 2,496 | 1,123 | 3,744 | 1,685|
| | 25p | 1,300 | 585 | 1,950 | 878 | 2,600 | 1,170 | 3,900 | 1,755|
| | 30p | 1,560 | 702 | 2,340 | 1,053 | 3,120 | 1,404 | 4,680 | 2,106|
| | 50p | 2,600 | 1,170 | 3,900 | 1,755 | 5,200 | 2,340 | 7,800 | 3,510|
| | 60p | 3,120 | 1,404 | 4,680 | 2,106 | 6,240 | 2,808 | 9,360 | 4,212|
| | 120p | 6,240 | 2,808 | 9,360 | 4,212 | 12,480 | 5,616 | 18,720 | 8,424|


< table: Typical bitrates (Mb/s, GB/h) >


