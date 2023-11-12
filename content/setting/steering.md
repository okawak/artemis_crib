---
title: "Steering"
date: 2023-11-02T17:03:39+09:00
draft: false
author: "Kodai Okawa"
weight: 5
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

The `steering` file (yaml format) is a file that directs the process of how the obtained data is to be processed.
The `artemis` is an object-oriented program whose components are called `processors`, which are combined to process data.

The main role of the "processor" is to process data from an input data called `InputCollection` and create an output data called `OutputCollection`.
This "OutputCollection" will be stored into the root file as a "tree".
Complex processing can be performed by using "processor" in multiple steps.

I will explain how to create this "steering" file using Si detector data as an example.

{{< mermaid >}}
---
title: example of the data process structure
---
graph TD;
    subgraph event loop
    A-->B(mapping processor<br></br>InputCollection: decoded data\nOutputCollection: Si raw data)
    B-->C(calibration processor<br></br>InputCollection: Si raw data\nOutputCollection: Si calibrated data)
    C-->X((event end))
    X-->A
    end
    subgraph DAQ
    D(Raw binary data)-->A(decode processor<br></br>InputCollection: raw data\nOutputCollection: decoded data)
    end
{{< /mermaid >}}


## Steering file: Silicon data case

First, I describe what is the `Anchor` and how to use command line arguments.
See example here.

```yaml { wrap="false" title="chkssd.yaml"}
Anchor:
 - &input ridf/@NAME@@NUM@.ridf
 - &output output/@NAME@/@NUM@/chkssd@NAME@@NUM@.root
 - &histout output/@NAME@/@NUM@/chkssd@NAME@@NUM@.hist.root
```

You can use variables from elsewhere in the steering file by declaring them as such.
For example if you write:

```yaml { wrap="false"}
something: *input
```

This unfolds as follows:

```yaml { wrap="false"}
something: ridf/@NAME@@NUM@.ridf
```

Variables enclosed in `@` can also be specified by command line arguments.
For example, If you command like the following in the artemis console,

```shell { wrap="false" }
artemis [1] add steering/chkssd.yaml NAME=run NUM=0000
```

it is considered as

```yaml { wrap="false" title="chkssd.yaml"}
Anchor:
 - &input ridf/run0000.ridf
 - &output output/run/0000/chkssdrun0000.root
 - &histout output/run/0000/chkssdrun0000.hist.root
```

### 1. General processor
When using the "Babirl", the data file will be in the form of "ridf".
In this case, the beginning and end of the steering file is usually as follows.

```yaml { wrap="false" title="chkssd.yaml"}
Processor:
  - name: timer
    type: art::TTimerProcessor

  - name: ridf
    type: art::TRIDFEventStore
    parameter:
      OutputTransparency: 1
      InputFiles:
        - *input
      SHMID: 0

  - name: mapper
    type: art::TMappingProcessor
    parameter:
      OutputTransparency: 1

# -- snip --

  - name: outputtree
    type: art::TOutputTreeProcessor
    parameter:
      FileName:
        - *output
```
- TTimerProcessor: measure the time taken to process data
- TRIDFEventStore: decode the ridf file and store the value in `EventStore` (see below)
- TMappingProcessor: read mapper.conf for mapping
- TOutputTreeProcessor: writes data to the root file

`OutputTransparency` is set to 1, indicating that "OutputCollection" is not exported to the root file.

### 2. Mapping processor

The "mapping processor" puts the data stored in the "EventStore" into a certain data class based on "mapper.conf".
Assume the following map file is used.
```txt { wrap="false" }
# map for SSD
# [category] [id] [[device] [focus] [detector] [geo] [ch]] ....
#
# Map: energy, timing
#
#--------------------------------------------------------------------
   1,   0,  12,   1,  6,   0,   0,  12,   2,  7,   0,   0
```


In this case, since we are assuming data from the Si detector, let's consider putting it in a data class that stores energy and timing data, "TTimingChargeData"!
The processor mapping to this data class is "TTimingChargeMappingProcessor".

```yaml { wrap="false" title="chkssd.yaml" hl_lines="10" }
Processor:
  - name: proc_ssd_raw
    type: art::TTimingChargeMappingProcessor
    parameter:
      CatID:         1
      ChargeType:    1
      ChargeTypeID:  0
      TimingTypeID:  1
      Sparse:        1
      OutputCollection: ssd_raw
```

1. CatID: enter here the same number as the cid (category ID) in the map file.
2. ChargeType: there are various ways to store energy (charge) and timing using this processor, but this time "1" is specified to use the processing method using ADC and TDC.
3. Charge/TimingTypeID: The map file has two sets of five parameters that specify the DAQ ID. Which of these parameters specifies which represents the energy (charge) and timing. (it start from "0")
4. Sparse: parameter for the output data structure
5. OutputCollection: name of the data class to be output

Then, you can access the ssd_raw data by using like `tree->Draw("ssd_raw.fCharge")`


### 3. Calibration processor

While the data in the "ssd_raw" are raw channel of the ADC and TDC, it is important to see the data calibrated to energy and time.
I will explain the details in [Example: preparation/macro](), but here I will discuss the calibration processors assuming that the following appropriate calibration files have been created.

- prm/ssd/ch2MeV.dat
- prm/ssd/ch2ns.dat

Now, let's load these files.

```yaml { wrap="false" title="chkssd.yaml" hl_lines="5 13" }
Processor:
  - name: proc_ssd_ch2MeV
    type: art::TParameterArrayLoader
    parameter:
      Name: prm_ssd_ch2MeV
      Type: art::TAffineConverter
      FileName: prm/ssd/ch2MeV.dat
      OutputTransparency: 1

  - name: proc_ssd_ch2ns
    type: art::TParameterArrayLoader
    parameter:
      Name: prm_ssd_ch2ns
      Type: art::TAffineConverter
      FileName: prm/ssd/ch2ns.dat
      OutputTransparency: 1
```

To calibrate data contained in a `TTimingChargeData` class, a `TTimingChargeCalibrationProcessor` processor is used.

```yaml { wrap="false" title="chkssd.yaml" hl_lines="5 7 8" }
Processor:
  - name: proc_ssd
    type: art::TTimingChargeCalibrationProcessor
    parameter:
      InputCollection:      ssd_raw
      OutputCollection:     ssd_cal
      ChargeConverterArray: prm_ssd_ch2MeV
      TimingConverterArray: prm_ssd_ch2ns
```

Note here that "InputCollection", "ChargeConverterArray", and "TimingConverterArray" use the same names as the highlighted lines in the code block above.

{{% notice style="info" %}}
The arguments to be used will vary depending on the processor used, so please check and write them according to the situation.
If you want to check from artemis console, you can use "processordescription" command like this 
```shell { wrap="false" }
> artlogin (username)
> a
artemis [0] processordescription art::TTimingChargeCalibrationProcessor
Processor:
  - name: MyTTimingChargeCalibrationProcessor
    type: art::TTimingChargeCalibrationProcessor
    parameter:
      ChargeConverterArray: no_conversion  # [TString] normally output of TAffineConverterArrayGenerator
      InputCollection: plastic_raw  # [TString] array of objects inheriting from art::ITiming and/or art::ICharge
      InputIsDigital: 1  # [Bool_t] whether input is digital or not
      OutputCollection: plastic  # [TString] output class will be the same as input
      OutputTransparency: 0  # [Bool_t] Output is persistent if false (default)
      TimingConverterArray: no_conversion  # [TString] normally output of TAffineConverterArrayGenerator
      Verbose: 1  # [Int_t] verbose level (default 1 : non quiet)
```
{{% /notice %}}


### 4. Split files

If you want to analyse a large number of detectors, not just Si detectors, 
writing everything in one steering file will result in a large amount of content that is difficult to read.

In that case, we can use "include" node!

In the examples we have written so far, let's only use a separate file for the part related to the analysis of the Si detector.

```yaml { wrap="false" title="chkssd.yaml" }
# -- snip --

Processor:

# -- snip --

  - include: ssd/ssd_single.yaml

# -- snip --
```

```yaml { wrap="false" title="ssd/ssd_single.yaml" }
Processor:
# parameter files
  - name: proc_ssd_ch2MeV
    type: art::TParameterArrayLoader
    parameter:
      Name: prm_ssd_ch2MeV
      Type: art::TAffineConverter
      FileName: prm/ssd/ch2MeV.dat
      OutputTransparency: 1

  - name: proc_ssd_ch2ns
    type: art::TParameterArrayLoader
    parameter:
      Name: prm_ssd_ch2ns
      Type: art::TAffineConverter
      FileName: prm/ssd/ch2ns.dat
      OutputTransparency: 1

# data process
  - name: proc_ssd_raw
    type: art::TTimingChargeMappingProcessor
    parameter:
      CatID:         1
      ChargeType:    1
      ChargeTypeID:  0
      TimingTypeID:  1
      Sparse:        1
      OutputCollection: ssd_raw

  - name: proc_ssd
    type: art::TTimingChargeCalibrationProcessor
    parameter:
      InputCollection:      ssd_raw
      OutputCollection:     ssd_cal
      ChargeConverterArray: prm_ssd_ch2MeV
      TimingConverterArray: prm_ssd_ch2ns
```
In this way, the contents of "chkssd.yaml" can be kept concise, while the same process is carried out.
Note that the file paths here are relative to the paths from the steering directory.
Parameter files, for example, are relative paths from the working directory (one level down).

Utilising file splitting also makes it easier to check the steering files that analyse a large number of detectors like this.

```yaml { wrap="false" title="chkall.yaml" }
# -- snip --

Processor:

# -- snip --

  - include: rf/rf.yaml
  - include: ppac/f1ppac.yaml
  - include: ppac/dlppac.yaml
  - include: mwdc/mwdc.yaml
  - include: ssd/ssd_all.yaml

# -- snip --
```

{{% notice style="info" %}}
When you include other files, you can set arguments. This can be used, for example, to share variables.
Details will be introduced in the example section.
{{% /notice %}}


---

### Summary

The whole steering file is as follows:

```yaml { wrap="false" title="chkssd.yaml"}
Anchor:
 - &input ridf/@NAME@@NUM@.ridf
 - &output output/@NAME@/@NUM@/chkssd@NAME@@NUM@.root
 - &histout output/@NAME@/@NUM@/chkssd@NAME@@NUM@.hist.root

Processor:
  - name: timer
    type: art::TTimerProcessor

  - name: ridf
    type: art::TRIDFEventStore
    parameter:
      OutputTransparency: 1
      InputFiles:
        - *input
      SHMID: 0

  - name: mapper
    type: art::TMappingProcessor
    parameter:
      OutputTransparency: 1

  - include: ssd/ssd_single.yaml

# output root file
  - name: outputtree
    type: art::TOutputTreeProcessor
    parameter:
      FileName:
        - *output
```

```yaml { wrap="false" title="ssd/ssd_single.yaml" }
Processor:
# parameter files
  - name: proc_ssd_ch2MeV
    type: art::TParameterArrayLoader
    parameter:
      Name: prm_ssd_ch2MeV
      Type: art::TAffineConverter
      FileName: prm/ssd/ch2MeV.dat
      OutputTransparency: 1

  - name: proc_ssd_ch2ns
    type: art::TParameterArrayLoader
    parameter:
      Name: prm_ssd_ch2ns
      Type: art::TAffineConverter
      FileName: prm/ssd/ch2ns.dat
      OutputTransparency: 1

# data process
  - name: proc_ssd_raw
    type: art::TTimingChargeMappingProcessor
    parameter:
      CatID:         1
      ChargeType:    1
      ChargeTypeID:  0
      TimingTypeID:  1
      Sparse:        1
      OutputCollection: ssd_raw

  - name: proc_ssd
    type: art::TTimingChargeCalibrationProcessor
    parameter:
      InputCollection:      ssd_raw
      OutputCollection:     ssd_cal
      ChargeConverterArray: prm_ssd_ch2MeV
      TimingConverterArray: prm_ssd_ch2ns
```

```shell { wrap="false" }
> acd
> a
artemis [0] add steering/chkssd.yaml NAME=run NUM=0000
```
