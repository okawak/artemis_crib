---
title: "Analysis example"
date: 2024-07-30T17:28:14+09:00
draft: false
author: "Kodai Okawa"
weight: 100
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

A brief example of an analysis flow using artemis_crib is given below.
This is just the method recommended by okawak,
so you can proceed with the analysis as you like.

I hope this page will give you some ideas.

---

0. Get calibration paramters
1. Concentrate on one RUN (one or two hours data) for analysis.
2. Briefly check other RUNs to see if the trend is the same.
3. Determine the appropriate gate (like remove noise, not precisely).
4. Create ROOT files for all RUNs with appropriate Gate.
5. Merging the ROOT files to one file.
6. Determine further detailed gates (essensial gate like selecting proton).
7. Create a ROOT file with only selected events from the original ROOT file.
8. Repeat steps 6 and 7.
9. Create a histogram that gives the physical quantity you want.
10. If necessary, create a simulation and produce a histogram you want.
11. Manipulate the histograms using macros (.C file) or pyROOT to produce the final result.

---

##### **1. Concentrate on one RUN (one or two hours data) for analysis**

The acquired data contains a lot of noise and other data that is not absolutely necessary for analysis,
and if you use `artemis` to do an event loop for all events, it will take a long time.
Therefore, a root file should only be created for a specific RUN (data file) to save time.
(It is tempting to look at the data using with a lot of statistics,
but we believe that this is done by online-analysis and concentrate on reducing useless data.)

```shell { wrap="false" }
$ artlogin (user)
$ a

artemis [] a steering/hoge.yaml NAME=run NUM=0000
artemis [] .q
```

As you want to look at a variety of data I think,
it is convenient to create a canvas each time with ‘tree->Draw()’, instead of defining a histogram.
Not defining a histogram also has the advantage that the event loop is faster.

Once the root file has been created, it can be read directly from that file, eliminating the waiting time.

```shell { wrap="false" }
$ a output/created_rootfile_path.root

artemis [] tree->Draw("hoge")
```

<u>It is good idea to make a ".C" macro file to record and reproduce the analysis process.</u>

Here are some points I think would be good to check:

- reproduce the online-analysis
- check if the calibration parameter is correct
- check multiplicity of the beam tracking detector (PPAC or MWDC)
- proper timing of PPACa/b or MWDCa/b (because we may be using multihit TDC, V1190)
- check the beam properties difference between "beam_single" trigger and "SSD_coin" trigger
- RF timing with "beam_single" and "SSD_coin" trigger should be different, so need to check the offset value.
- check RF timing and contamination of the beam with "beam_single" trigger

If there are problems during the experiment, there may be many other things to check.

##### **2. Briefly check other RUNs to see if the trend is the same**

It is possible that some parameter is different for each RUN.
There are many possibilities, for example, a trouble may have occurred and the conditions of the detector have changed.
In such cases, it is necessary to take action, for example, to prepare several calibration parameters.

While some of these changes in parameters can be predicted in advance, unforeseen changes can also occur.

- RF timing sometime change (relatie value)
  - -> need to modify the PID parameters
- MUX position parameter sometimes shift
  - -> need to modify position calibration parameter

These are the problems I have encountered, but others with different tendencies may exist.

If you can anticipate it, it is good to have a plan for dealing with it at this point and move on to the next step.
However, there is no need to waste time here as it can be noticed after merging the overall measurements in the following step.

##### 3. Determine the appropriate gate (like remove noise, not precisely)

##### 4. Create ROOT files for all RUNs with appropriate Gate

##### 5. Merging the ROOT files to one file

##### 6. Determine further detailed gates (essensial gate like selecting proton)

##### 7. Create a ROOT file with only selected events from the original ROOT file

##### 8. Repeat steps 6 and 7

##### 9. Create a histogram that gives the physical quantity you want

##### 10. If necessary, create a simulation and produce a histogram you want

##### 11. Manipulate the histograms using macros (.C file) or pyROOT to produce the final result
