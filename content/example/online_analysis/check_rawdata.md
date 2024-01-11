---
title: "Check raw data"
date: 2023-11-05T14:57:50+09:00
draft: false
author: "Kodai Okawa"
weight: 12
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

Artemis produces mainly `TArtTree` and the branches are `TClonesArray(art::hoge)`.
It means that all objects rely on the artemis library, and we cannot open and check the data by using normal ROOT.

Also, sometimes it is necessary top check the raw data obtained by ADC and TDC as it is.
Of course, the real raw data is binary and therefore difficult to read, so we will check the raw data after the decoders.

Related processors;
- [TSegmentOutputProcessor.cc](https://github.com/okawak/artemis_crib/blob/main/src-crib/TSegmentOutputProcessor.cc)
- [TModuleData.cc](https://github.com/okawak/artemis_crib/blob/main/src-crib/TModuleData.cc)
- [TSegmentCheckProcessor.cc](https://github.com/artemis-dev/artemis/blob/develop/sources/loop/TSegmentCheckProcessor.cc) (in original artemis source)


## How to check the raw data

### 1. prepare conf files

We already prepared `conf/map` files, but in this case, we need to prepare `conf/seg` files.
There are two files.
This is an example, so please change it according to the experimental conditions.

```yaml { wrap="false" title="conf/seg/modulelist.yaml"}
#modulename:
#  id: module id (it is module-specific)
#  ch: channel number
#  values:
#    - name1: [Nbin: int, min: double, max: double] it is for 2D histogram (these values vs. ch)
#    - name2: [Nbin: int, min: double, max: double] <= somehow two line needed...?

MADC32:
  id: 32
  ch: 32
  values:
    - adc: [4000, 0., 4000.]
    - tdc: [4000, 0., 4000.] # no use, but seems it needed...

V1190A:
  id: 24
  ch: 128
  values:
    - tdcL: [300, -5000., 300000.]
    - tdcT: [300, -5000., 300000.]
```
The module id list is [here](../../../example/segid).

```yaml { wrap="false" title="conf/seg/seglist.yaml"}
#segment_name:
# segid: [[dev], [fp], [det]] <= same as a map file
# type: V7XX <= defined type in modulelist.yaml
# modules:
#   - id: geo1
#   - id: geo2

V1190:
  segid: [12, 0, 7]
  type: V1190A
  modules:
    - id: 0
    - id: 1

MADC:
  segid: [12, 1, 6]
  type: MADC32
  modules:
    - id: 0
    - id: 1
    - id: 2
```

### 2. use "steering/chkseg.yaml"

Based on these two conf file, the `steering/chkseg.yaml` file produce rawdata histograms and TTree object.
We can use [steering/chkseg.yaml](https://github.com/okawak/artemis_crib/blob/main/steering/chkseg.yaml) without any change I think.

This is an example from one CRIB experiment.

```shell { wrap="false" }
$ a
artemis [0] add steering/chkseg.yaml NAME=hoge NUM=0000
artemis [1] res
artemis [2] sus
artemis [3] ls

 artemis
>   0 TDirectory SegmentHistogram art::TSegmentCheckProcessor

artemis [4] cd 0
artemis [5] ls

 SegmentHistogram
>   0 TDirectory E7_V1190        E7_V1190
    1 TDirectory J1_V785         J1_V785
    2 TDirectory J1_MADC         J1_MADC
    3 TDirectory J1_V1190        J1_V1190

artemis [6] cd 0
artemis [7] ls


 E7_V1190
>   0 TH2F E7_V1190_0_tdcL E7_V1190_0_tdcL
    1 TH2F E7_V1190_0_tdcT E7_V1190_0_tdcT
    2 TH2F E7_V1190_1_tdcL E7_V1190_1_tdcL
    3 TH2F E7_V1190_1_tdcT E7_V1190_1_tdcT

# we can check these histograms by ht command

artemis [8] fcd 0
artemis [9] br
E7_V1190_0           vector<vector<int> >
E7_V1190_1           vector<vector<int> >
J1_V785_0            vector<int>
J1_V785_1            vector<int>
J1_V785_2            vector<int>
J1_MADC_3            vector<int>
J1_MADC_4            vector<int>
J1_MADC_5            vector<int>
J1_V1190_0           vector<vector<int> >
```
{{% notice style="info" %}}
If the module ID = 24 or 25, it is multihit TDC, so the branch become 2D vector.
When you want to use std::vector<T> method, you can use by "@" like
```shell { wrap="false" }
artemis [*] tree->Draw("J1_V785_0@.size()")
```
{{% /notice %}}

Of course we can open this output ROOT file from normal ROOT.

