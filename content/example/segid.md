---
title: "Segment ID"
date: 2024-01-11T22:08:49+09:00
draft: false
author: "Kodai Okawa"
weight: 1
tags: []
hidden: true
---

{{% badge %}}{{< signature >}}{{% /badge %}}

This is from ANAROOT source (https://rnc.riken.go.jp/RIBFDAQ/index.php?Tools%2FAnalysis%2FANAROOT%2FInstallation)

```cpp { wrap="false" title="anaroot/sources/Core/include/segidlist.h" }
// Module  0--255
static const int C16        = 0;
static const int C24        = 1;
static const int AD413AC    = 2;   // AD413A + w/o Zero supp.   (CAMAC read)
static const int AD413ACZ   = 3;    // AD413A + Zero suppression (CAMAC read)
static const int AD413AM    = 4;    // AD413A + w/o Zero supp.   + Memory
static const int AD413A     = 5;    // AD413A + Zero suppression + Memory
static const int AD413AMZ   = 5;    // AD413A + Zero suppression + Memory
static const int L3377      = 6;    // LeCroy 3377 Double word (CAMAC read)
static const int L3377CW    = 6;    // LeCroy 3377 Double word (CAMAC read)
static const int L3377CS    = 7;    // LeCroy 3377 Single word (CAMAC read)
static const int C32        = 8;    // C32 such as SIS32XX series
static const int P7166      = 9;    // Philips 7166 + w/o Zero supp.
static const int P716X      = 9;    // Philips 7166 + w/o Zero supp.
static const int P716XZ     = 10;    // Philips 7166 + Zero suppression
static const int CTM405     = 11;
static const int L4300BC    = 11;    // LeCroy 4300B + w/o Zero supp.   (CAMAC read)
static const int L4300BCZ   = 12;    // LeCroy 4300B + Zero suppression (CAMAC read)
static const int L4300BM    = 13;    // LeCroy 4300B + w/o Zero supp.   + Memory
static const int L4300BMZ   = 14;    // LeCroy 4300B + Zero suppression + Memory
static const int UNDEFINE15 = 15;
static const int L3377MW    = 16;    // LeCroy 3377 Double word   + Memory
static const int L3377MS    = 17;    // LeCroy 3377 Single word   + Memory
static const int UNDEFINE18 = 18;
static const int MDPP19     = 19;    // Mesytech MDPP-19
static const int UNDEFINE20 = 20;
static const int V775       = 21;
static const int V785       = 21;
static const int V792       = 21;
static const int V550       = 22;
static const int V767       = 23;
static const int V1190      = 24;
static const int V1190A     = 24;
static const int V1190B     = 24;
static const int V1290      = 25;
static const int V1190C     = 26;
static const int V7XXBIGEND = 27;
static const int NEULANDTS  = 28;
static const int DSP        = 29;
static const int V1740      = 30;
static const int A3100      = 31;
static const int MADC32     = 32;    // Mesytech ADC
static const int MQDC32     = 33;    // Mesytech QDC
static const int MTDC32     = 34;    // Mesytech TDC
static const int UNDEFINE35 = 35;
static const int AMTTDC     = 36;
static const int SIS3301    = 37;
static const int LUPOIO     = 41;
static const int LUPOTS     = 42;
static const int LUPOMTS    = 43;  // for dead time monitor
static const int MUST2VXI   = 50;
static const int MINOS      = 53;
static const int TACQUILA   = 54;
static const int A3400      = 55;
```
