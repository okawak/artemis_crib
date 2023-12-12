---
title: "New commands"
date: 2023-12-12T13:53:50+09:00
draft: false
author: "Kodai Okawa"
weight: 4
tags: ["CRIB"]
---

{{% badge %}}{{< signature >}}{{% /badge %}}

Various commands (mainly the same with ANAPAW commands) have been developed for CRIB experiment. 
For more information, please click [here (art-work-dir/src-crib/commands)](https://github.com/okawak/artemis_crib/tree/main/src-crib/commands).
These commands are registered in userlogon.C. (See previous section.)

This section explains how to use them.

- start
- stop
- xfitg
- xblow
- xyblow
- xstatus
- tcutg
- erase
- draw

the default figures:
{{< figure src="default.png" width=1000 >}}

### start
This is exactly the same as the `resume` command, because ANAPAW starts the event loop with `start` instead of resume.

### stop
This is exactly the same as the `suspend` command, because ANAPAW stops the event loop with `stop` instead of suspend.

### xfitg
For `1D` histograms, by selecting the two ends of two points, the peak between them is fitted with a Gaussian.

```shell { wrap="false" }
artemis [7] xf
Info in <art::TCmdXfitg::Cmd>: click on the lowest edge:
Info in <art::TCmdXfitg::Cmd>: click on the highest edge:
Info in <art::TCmdXfitg::Cmd>: X1: -1437.56, X2: -1419.11
 FCN=81.6642 FROM MIGRAD    STATUS=CONVERGED      71 CALLS          72 TOTAL
                     EDM=3.35095e-09    STRATEGY= 1      ERROR MATRIX ACCURATE
  EXT PARAMETER                                   STEP         FIRST
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE
   1  Constant     1.16439e+03   2.43862e+01   8.08454e-02   9.04256e-07
   2  Mean        -1.43081e+03   4.54001e-02   6.82262e-04  -1.74034e-03
   3  Sigma        2.81435e+00   4.07888e-02   1.55351e-05  -3.15946e-03
artemis [8]
```

{{< figure src="xfitg.png" width=600 >}}



### xblow
For `1D` histograms, select both ends and crop the histogram between them.

```shell { wrap="false" }
artemis [10] xblo
Info in <art::TCmdXblow::Run>: click on the lowest edge: 
Info in <art::TCmdXblow::Run>: click on the highest edge: 
Info in <art::TCmdXblow::Run>: X1: -1439.3, X2: -1417.37
Info in <art::TCmdXblow::Run>: id = 2 hist is created
artemis [11]
```

{{< figure src="xblow.png" width=600 >}}

### xyblow
For `2D` histograms, select both corners and crop the histogram between them.

```shell { wrap="false" }
artemis [60] xyblo
Info in <art::TCmdXYblow::Run>: click on one corner: 
Info in <art::TCmdXYblow::Run>: X1: 9.2154, Y1: 46.6159
Info in <art::TCmdXYblow::Run>: click on the other corner: 
Info in <art::TCmdXYblow::Run>: X2: 21.7032, Y2: 23.952
Info in <art::TCmdXYblow::Run>: id = 6 hist is created
artemis [61]
```

{{< figure src="xyblow.png" width=600 >}}

### xstatus
For `2D` histograms, select both corners and determine the ratio of the total number of events.

```shell { wrap="false" }
artemis [8] xs
Info in <art::TCmdXstatus::Cmd>: click on one corner: 
Info in <art::TCmdXstatus::Cmd>: X1: 14.1496, Y1: 41.4826
Info in <art::TCmdXstatus::Cmd>: click on the other corner: 
Info in <art::TCmdXstatus::Cmd>: X2: 21.0941, Y2: 31.9909
------------------
selected = 976, total = 7526
ratio  = 0.129684 (12.9684%)
artemis [9]
```

{{< figure src="xstatus.png" width=600 >}}

---
## ---under development---

### tcutg

### erase

### draw
