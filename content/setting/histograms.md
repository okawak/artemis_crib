---
title: "Histograms"
date: 2023-11-02T17:03:45+09:00
draft: false
author: "Kodai Okawa"
weight: 7
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

In the online analysis, it is important to have immediate access to data.
The artemis can produce **TTree** object but long commands are needed to access, for example,

```shell { wrap="false" }
artemis [1] fcd 0  # move to the created rootfile
artemis [2] zone 2 2  # make a "artemis" 2x2 canvas
artemis [3] tree->Draw("ssd_cal.fCharge:ssd_cal.fTiming>(100,0.,100., 100,0.,100)","ssd_cal.fCharge > 1.0","colz")
```

This would take time if there was a diagram that you wanted to display immediately...

Therefore, if you know in advance the diagram you want to see, it is useful to predefine its histogram!
The processor used is `TTreeProjectionProcessor`.
I would like to explain how to use this one.


## 1. Steering file

Let's look at how histograms are defined when looking at SSD data.
First, let's prepare the steering file as follows!
please see previous section for omissions.

```yaml { wrap="false" title="chkssd.yaml" hl_lines="9" }
# -- snip --

  - include: ssd/ssd_single.yaml

# Histogram
  - name: projection_ssd
    type: art::TTreeProjectionProcessor
    parameter:
      FileName: hist/ssd/ssd.yaml
      Type:     art::TTreeProjection
      OutputFilename: *histout


# output root file
  - name: outputtree
    type: art::TOutputTreeProcessor
    parameter:
      FileName:
        - *output
```

The histogram is created based on the **TTree** object, 
so describe the processing of the histogram after the part that represents the data processing and before the part that outputs the TTree (`TOutputTreeProcessor`).

There are three points to note here.

1. It is possible to create a root file containing only a histogram as well as a root file containing a TTree.
(Look at the node part of the OutputFilename.)
2. The histogram itself is defined in a separate file to this one, written on the highlighted line above.
3. The file paths are relative to the working directory.

Therefore, I would now like to show the histogram definition file.


## 2. Histogram file

First please look at this example.

```yaml { lineNos="true" wrap="false" title="hist/ssd/ssd.yaml" }
anchor: 
  - &energy ["ssd_cal.fCharge",100,0.,100.]
  - &timing ["ssd_cal.fTiming",100,0.,100.]
alias:
  energy_cut: ssd_cal.fCharge>1.0;
group:
  - name: ssd_test
    title: ssd_test
    contents:
      - name: ssd_energy
        title: ssd_energy
        x: *energy

      - name: ssd_timing
        title: ssd_timing
        x: *timing

      - name: ssd_energy and timing
        title: ssd_energy and timing
        x: *timing
        y: *energy
        cut: energy_cut

```

This definition file consists of three parts.

### 2.1 anchor
The actual core part is the "**2.3 group**", but "**2.1 anchor**" and "**2.2 alias**" are often used to make this part easier to write.
The anchor defines the first argument of `tree->Draw("ssd_cal.fCharge>(100,0.,100.)","ssd_cal.fCharge > 1.0")`

The array stored in the variable named "energy" in the second line looks like `[str, int, float, float]` and has the following meanings

1. str: Name of the object (need double quote "")
2. int: Number of bins of histogram
3. float: Minimum value of histogram range
4. float: Maximum value of histogram range

As you might imagine, inside the first argument you can also add operations such as `TMath::Sqrt(ssd_cal.fCharge)` or `ssd_cal.fCharge-ssd_cal.fTiming`, because it is the same with "tree->Draw".

Note, however, that the definition here is for one-dimensional histograms.
Two-dimensional histograms will be presented in Section 2.3. It is very simple to write!


### 2.2 alias

This part is used when applying gates to events (often we call it as "cut" or "selection").
For example, if you only want to see events with energies above 1.0 MeV, you would write something like `tree->Draw("energy","energy>1.0")`.

The alias node is used to define the part of `energy>1.0`

{{% notice style="note" %}}
A semicolon ";" at the end of the sentence may be needed...?
please check [the source](https://github.com/artemis-dev/artemis/blob/develop/sources/loop/hist/TTreeProjection.cc).
{{% /notice %}}


### 2.3 group

The histogram is defined here and the object is stored in a directory in artemis (ROOT, TDirectory).
In the example shown above, the directory structure would look like this:

(It is not actually displayed in this way).
```shell { wrap="false" }
# in artemis
.
└── ssd_test
    ├── ssd_energy (1D hist)
    ├── ssd_timing (1D hist)
    └── ssd_energy and timing (2D hist)
```

The first "name" and "title" nodes are arguments of TDirectory instance.
Also the second "name" and "title" nodes are arguments of instance of TH1 or TH2 object. 
The other "x", "y" and "cut" is the important node!

1. If there are only "x" nodes -> 1D histogram
2. If there are both "x" and "y" nodes -> 2D histogram
3. In any case, it can be gated by adding a "cut" node.

## 3. Commands for histograms

There are many useful command for checking the histogram objects.
These are similar to the [ANAPAW](https://ribf.riken.go.jp/RIBFDAQ/index.php?Tools/Analysis/ANAPAW) commands.

1. ls : check the artemis directory

```shell { wrap="false" }
> artlogin (username)
> a

artemis [0] add steering/chkssd.yaml NAME=hoge NUM=0000
artemis [1] res
artemis [2] sus
artemis [3] ls # check the artemis directory

 artemis
>   0 art::TTreeProjGroup ssd_test        ssd_test
    1 art::TAnalysisInfo analysisInfo

```

2. cd [ID] : move to the directory of the ID
```shell { wrap="false" }
artemis [4] cd 0
artemis [5] ls

 ssd_test
>   0 art::TH1FTreeProj ssd_energy      ssd_energy
    1 art::TH1FTreeProj ssd_timing      ssd_timing
    2 art::TH2FTreeProj ssd_energy and timing ssd_energy and timing

```

3. ht [ID] [option] : draw the histogram of the ID
```shell { wrap="false" }
artemis [6] ht 0
artemis [7] ht 2 colz
```

4. hn : draw the next ID histogram
5. hb : draw the prev ID histogram

## 4. Template hist file

When setting up several detectors of the same type and wanting to set up a histogram with the same content, it is tedious to create several files with only the names of the objects changed.
In such cases, it is useful to allow the histogram definition file to have arguments.

Please look here first.

```yaml { wrap="false" title="chkssd.yaml" hl_lines="12 13" }
# -- snip --

  - include: ssd/ssd_single.yaml

# Histogram
  - name: projection_ssd
    type: art::TTreeProjectionProcessor
    parameter:
      FileName: hist/ssd/ssd.yaml
      Type:     art::TTreeProjection
      OutputFilename: *histout
      Replace: |
        name: ssd_cal

# -- snip --
```

We add the highlighted lines.
Then the "name" can be used at hist file by `@name@`!
The "name" can be freely set. 

```yaml { wrap="false" title="hist/ssd/ssd.yaml" }
anchor: 
  - &energy ["@name@.fCharge",100,0.,100.]
  - &timing ["@name@.fTiming",100,0.,100.]
alias:
  energy_cut: @name@.fCharge>1.0;
group:
  - name: ssd_test
    title: ssd_test
    contents:
      - name: ssd_energy
        title: ssd_energy
        x: *energy

      - name: ssd_timing
        title: ssd_timing
        x: *timing

      - name: ssd_energy and timing
        title: ssd_energy and timing
        x: *timing
        y: *energy
        cut: energy_cut

```

This is useful when there are more objects to check!

```yaml { wrap="false" title="chkssd.yaml" }
# -- snip --

  - include: ssd/ssd_single.yaml

# Histogram
  - name: projection_ssd
    type: art::TTreeProjectionProcessor
    parameter:
      FileName: hist/ssd/ssd.yaml
      Type:     art::TTreeProjection
      OutputFilename: *histout
      Replace: |
        name: ssd_cal

  - name: projection_ssd
    type: art::TTreeProjectionProcessor
    parameter:
      FileName: hist/ssd/ssd.yaml
      Type:     art::TTreeProjection
      Replace: |
        name: ssd_raw
  # and so on!

# -- snip --
```





















