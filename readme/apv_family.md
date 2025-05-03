APV Family
==============

# Introduction

This document details the standard configurations of the APV codec, collectively termed the 'APV family'. Although the APV family is not formally defined in the APV specification, it provides a useful framework for defining typical setups and ensures uniform communication practices.

The choice of which APV family to use depends on factors like file size requirements, desired quality, and the specific editing environment. For example, 422 HQ might be preferred for preserving the high quality video, while 422 LT might be used for lower file sizes and bandwidth usage, making it suitable for situations where storage space or network transfer is a concern.

# Description of APV family

| Family       | Color Sampling | Usage |
|:------------:|:--------------:|:------|
| APV 422 UQ   | 4:2:2          | Finishing |
| APV 422 HQ   | 4:2:2          | High quality mezzanine |
| APV 422 SQ   | 4:2:2          | Standard quality mezzanine |
| APV 422 LQ   | 4:2:2          | Editing-friendly low-data-rate workflows |


## Target bitrates of 4:2:2 color sampling

Following table is the typical bitrates of 4:2:2 color sampling video signal.
Actual compressed bitrate may have about 10% variations according to complexity of video signal.

| Resolution | Frame Rate | APV 422 LQ | APV 422 SQ | APV 422 HQ | APV 422 UQ |
|:----------:|:----------:|:----------:|:----------:|:----------:|:----------:|
| HD<br>1280x720 | 24p | xxx | xxx | xxx | xxx |
|  | 25p | xxx | xxx | xxx | xxx |
|  | 30p | xxx | xxx | xxx | xxx |
|  | 60p | xxx | xxx | xxx | xxx |
| FHD<br>1920x1080 | 24p | xxx | xxx | xxx | xxx |
|  | 25p | xxx | xxx | xxx | xxx |
|  | 30p | xxx | xxx | xxx | xxx |
|  | 60p | xxx | xxx | xxx | xxx |
| 2K<br>2048x1080 | 24p | xxx | xxx | xxx | xxx |
|  | 25p | xxx | xxx | xxx | xxx |
|  | 30p | xxx | xxx | xxx | xxx |
|  | 60p | xxx | xxx | xxx | xxx |
| UHD 4K<br>3840x2160| 24p | xxx | xxx | xxx | xxx |
|  | 25p | xxx | xxx | xxx | xxx |
|  | 30p | xxx | xxx | xxx | xxx |
|  | 60p | xxx | xxx | xxx | xxx |
| 4K<br>4096x2160| 24p | xxx | xxx | xxx | xxx |
|  | 25p | xxx | xxx | xxx | xxx |
|  | 30p | xxx | xxx | xxx | xxx |
|  | 60p | xxx | xxx | xxx | xxx |
| UHD 8K<br>7680x4320| 24p | xxx | xxx | xxx | xxx |
|  | 25p | xxx | xxx | xxx | xxx |
|  | 30p | xxx | xxx | xxx | xxx |
|  | 60p | xxx | xxx | xxx | xxx |
| 8K<br>8192x4320| 24p | xxx | xxx | xxx | xxx |
|  | 25p | xxx | xxx | xxx | xxx |
|  | 30p | xxx | xxx | xxx | xxx |
|  | 60p | xxx | xxx | xxx | xxx |

< table: Typical bitrates (Mbps) of 4:2:2 color sampling >

## Target bitrates of 4:4:4 color sampling

| Resolution | Frame Rate | APV 444 LQ | APV 444 SQ | APV 444 HQ | APV 444 UQ |
|:----------:|:----------:|:----------:|:----------:|:----------:|:----------:|
| HD<br>1280x720 | 24p | xxx | xxx | xxx | xxx |
|  | 25p | xxx | xxx | xxx | xxx |
|  | 30p | xxx | xxx | xxx | xxx |
|  | 60p | xxx | xxx | xxx | xxx |
| FHD<br>1920x1080 | 24p | xxx | xxx | xxx | xxx |
|  | 25p | xxx | xxx | xxx | xxx |
|  | 30p | xxx | xxx | xxx | xxx |
|  | 60p | xxx | xxx | xxx | xxx |
| 2K<br>2048x1080 | 24p | xxx | xxx | xxx | xxx |
|  | 25p | xxx | xxx | xxx | xxx |
|  | 30p | xxx | xxx | xxx | xxx |
|  | 60p | xxx | xxx | xxx | xxx |
| UHD 4K<br>3840x2160| 24p | xxx | xxx | xxx | xxx |
|  | 25p | xxx | xxx | xxx | xxx |
|  | 30p | xxx | xxx | xxx | xxx |
|  | 60p | xxx | xxx | xxx | xxx |
| 4K<br>4096x2160| 24p | xxx | xxx | xxx | xxx |
|  | 25p | xxx | xxx | xxx | xxx |
|  | 30p | xxx | xxx | xxx | xxx |
|  | 60p | xxx | xxx | xxx | xxx |
| UHD 8K<br>7680x4320| 24p | xxx | xxx | xxx | xxx |
|  | 25p | xxx | xxx | xxx | xxx |
|  | 30p | xxx | xxx | xxx | xxx |
|  | 60p | xxx | xxx | xxx | xxx |
| 8K<br>8192x4320| 24p | xxx | xxx | xxx | xxx |
|  | 25p | xxx | xxx | xxx | xxx |
|  | 30p | xxx | xxx | xxx | xxx |
|  | 60p | xxx | xxx | xxx | xxx |