APV Family
==============

# Introduction

This document details the standard configurations of the APV codec, collectively termed the 'APV family'. Although the APV family is not formally defined in the APV specification, it provides a useful framework for defining typical setups and ensures uniform communication practices.

The choice of which APV family to use depends on factors like file size requirements, desired quality, and the specific editing environment. For example, 422 HQ might be preferred for preserving the high quality video, while 422 LT might be used for lower file sizes and bandwidth usage, making it suitable for situations where storage space or network transfer is a concern.

# Description of APV family

| Usage | Family | Color Sampling |
|:-------------|:--------------:|:------:|
| Finishing                                | APV 422 UQ | 4:2:2 | 
|                                          | APV 444 UQ | 4:4:4 | 
| High quality mezzanine                   | APV 422 HQ | 4:2:2 | 
|                                          | APV 444 HQ | 4:4:4 | 
| Standard quality mezzanine               | APV 422 SQ | 4:2:2 | 
|                                          | APV 444 SQ | 4:4:4 | 
| Editing-friendly low-data-rate workflows | APV 422 LQ | 4:2:2 | 
|                                          | APV 444 LQ | 4:4:4 | 


## Target bitrates of APV family

Following table is the typical bitrates of APV family.
Actual compressed bitrate may have about 10% variations according to complexity of video signal.

|Resolution | Frame Rate | APV 422 LQ | | APV 422 SQ | | APV 422 HQ | | APV 444 HQ | |
|:---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| |  | Mb/s | GB/h | Mb/s | GB/h | Mb/s | GB/h | Mb/s | GB/h|
|HD     1280x720 | 24p | 33 | 15 | 43 | 20 | 65 | 29 | 98 | 44|
| | 25p | 34 | 15 | 45 | 20 | 68 | 30 | 102 | 46|
| | 30p | 41 | 18 | 54 | 24 | 81 | 37 | 122 | 55|
| | 60p | 81 | 37 | 122 | 55 | 163 | 73 | 244 | 110|
| | 120p | 163 | 73 | 217 | 98 | 325 | 146 | 488 | 219|
|FHD     1920x1080 | 24p | 73 | 33 | 98 | 44 | 146 | 66 | 219 | 99|
| | 25p | 76 | 34 | 102 | 46 | 152 | 69 | 229 | 103|
| | 30p | 91 | 41 | 122 | 55 | 183 | 82 | 274 | 123|
| | 60p | 183 | 82 | 274 | 123 | 366 | 165 | 548 | 247|
| | 120p | 366 | 165 | 488 | 219 | 731 | 329 | 1,097 | 494|
|2K     2048x1080 | 24p | 78 | 35 | 104 | 47 | 156 | 70 | 234 | 105|
| | 25p | 81 | 37 | 108 | 49 | 163 | 73 | 244 | 110|
| | 30p | 98 | 44 | 130 | 59 | 195 | 88 | 293 | 132|
| | 60p | 195 | 88 | 293 | 132 | 390 | 176 | 585 | 263|
| | 120p | 390 | 176 | 520 | 234 | 780 | 351 | 1,170 | 527|
|UHD   4K     3840x2160 | 24p | 293 | 132 | 390 | 176 | 585 | 263 | 878 | 395|
| | 25p | 305 | 137 | 406 | 183 | 609 | 274 | 914 | 411|
| | 30p | 366 | 165 | 488 | 219 | 731 | 329 | 1,097 | 494|
| | 60p | 731 | 329 | 1,097 | 494 | 1,463 | 658 | 2,194 | 987|
| | 120p | 1,463 | 658 | 1,950 | 878 | 2,925 | 1,316 | 4,388 | 1,974|
|4K     4096x2160 | 24p | 312 | 140 | 416 | 187 | 624 | 281 | 936 | 421|
| | 25p | 325 | 146 | 433 | 195 | 650 | 293 | 975 | 439|
| | 30p | 390 | 176 | 520 | 234 | 780 | 351 | 1,170 | 527|
| | 60p | 780 | 351 | 1,170 | 527 | 1,560 | 702 | 2,340 | 1,053|
| | 120p | 1,560 | 702 | 2,080 | 936 | 3,120 | 1,404 | 4,680 | 2,106|
|UHD   8K     7680x4320 | 24p | 1,170 | 527 | 1,560 | 702 | 2,340 | 1,053 | 3,510 | 1,580|
| | 25p | 1,219 | 548 | 1,625 | 731 | 2,438 | 1,097 | 3,656 | 1,645|
| | 30p | 1,463 | 658 | 1,950 | 878 | 2,925 | 1,316 | 4,388 | 1,974|
| | 60p | 2,925 | 1,316 | 4,388 | 1,974 | 5,850 | 2,633 | 8,775 | 3,949|
| | 120p | 5,850 | 2,633 | 7,800 | 3,510 | 11,700 | 5,265 | 17,550 | 7,898|
|8K     8192x4320 | 24p | 1,248 | 562 | 1,664 | 749 | 2,496 | 1,123 | 3,744 | 1,685|
| | 25p | 1,300 | 585 | 1,733 | 780 | 2,600 | 1,170 | 3,900 | 1,755|
| | 30p | 1,560 | 702 | 2,080 | 936 | 3,120 | 1,404 | 4,680 | 2,106|
| | 60p | 3,120 | 1,404 | 4,680 | 2,106 | 6,240 | 2,808 | 9,360 | 4,212|
| | 120p | 6,240 | 2,808 | 8,320 | 3,744 | 12,480 | 5,616 | 18,720 | 8,424|


< table: Typical bitrates (Mb/s, GB/h) >


