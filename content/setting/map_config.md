---
title: "Map configuration"
date: 2023-11-02T15:31:58+09:00
draft: false
author: "Kodai Okawa"
weight: 5
tags: ["CRIB"]
---

{{% badge %}}{{< signature >}}{{% /badge %}}

From this section, we start to configure the settings according to the actual experimental setup.
The setting files are followings:

```txt { wrap="false" }
> tree
.
├── mapper.conf
├── conf
│   ├── map
│   │   ├── ppac
│   │   │   ├── dlppac.map

-- snip --

│   └── seg
│       ├── modulelist.yaml
│       └── seglist.yaml

-- snip --

```

### 1. What is the map file?

The data obtained from an ADC/TDC is in the form of, for example, 
"The data coming into channel 10 of an ADC with an ID of 1 is 100".

{{< mermaid >}}
---
title: Data flow example
---
graph LR;
    A{detector} -->|signal| B(TDC/ADC<br></br>ID=1, ch=10)
    B -->|value=100| C[<strong>Data build</strong>\nridf file]
{{< /mermaid >}}

The role of the map file is to map this value of "100" to an ID that is easy to analyse. 
An ID that is easy to analyse means, for example, 
that even if signals from the same detector are acquired with different ADCs/TDCs, 
the same ID is easier to handle in the analysis.

{{< mermaid >}}
---
title: Data flow example
---
graph LR;
    A(TDC/ADC<br></br>ID=1, ch=10) -->|value=100| B[<strong>Data build</strong>\nridf file]
    B -->|value=100 mapping to| C(analysis<br></br>ID=2, ch=20)
{{< /mermaid >}}

After mapping, we can check the data of this "100" from ID=2 and ch=20.
This ID and channel (2, 20) are provided for convenience, so you can freely set them.

So, in summary, the map file role is like this:

{{< mermaid >}}
---
title: role of the map file
---
graph LR;
    A(DAQ ID<br></br>ID=1, ch=10) <-->|mapping| B(analysis ID<br></br>ID=2, ch=20)
{{< /mermaid >}}


### 2. map files

CRIB is using [Babirl](https://ribf.riken.jp/RIBFDAQ/index.php?FrontPage) for the DAQ system.
In this system, the DAQ ID represented in the example is determined by five parameters.

- device ID (dev)
- focal plane (fp)
- detector ID (det)
- geometry ID (geo)
- channel (ch)

The dev, fp, det and geo parameters can be set from DAQ setting.
For the CRIB experiment, conventionally we set dev=12, fp=0--2 (for each MPV), det=6,7 (6=energy, 7=timing) and geo=from 0.
But you can change it freely.

And analysis ID represented in the example is determined by two parameters.

- Category ID (CatID, cid)
- id (fID)

Of cource you can also set the value freely. 

The format of the map file is followings:
```txt { wrap="false" }
# [category] [id] [[device] [focus] [detector] [geo] [ch]] ....
   1,   0,  12,   1,  6,   0,   0
```

{{% notice style="note" %}}
- The id should start from "0".
- The ADC/TDC channel start from "0".
- The leading "#" is treated as a comment statement.
- you can set several "DAQ ID" to one "analysis ID" like this:

```txt { wrap="false" }
# map for SSD
# [category] [id] [[device] [focus] [detector] [geo] [ch]] ....
#
# Map: energy, timing
#
#--------------------------------------------------------------------
   1,   0,  12,   1,  6,   0,   0,  12,   2,  7,   0,   0
```
{{% /notice %}}

Please create map files for all detectors like this!


### 3. mapper.conf

You can select the map file to be loaded with this file.
This is especially useful when separating map files for testing from map files for the experiment.

The format is followings: (`path/to/the/map/file number`)

```txt { wrap="false" }
# file path for configuration, relative to the working directory
# (path to the map file) (Number of columns)

# cid = 1: rf
conf/map/rf/rf.map 1
```
In the note example above, the number is 2.

Please do not forget to add to the mapper.conf after you add some map files.


### 4. (option) segment files

This conf files are used when you use "chkseg.yaml" steering file.
This steering file create raw data 2D histograms.
I will describe in the [Example: online_analysis/Check raw data](https://okawak.github.io/artemis_crib/example/online_analysis/check_rawdata/) in detail.


