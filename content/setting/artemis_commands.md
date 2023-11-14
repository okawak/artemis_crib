---
title: "artemis commands"
date: 2023-11-14T11:23:31+09:00
draft: false
author: "Kodai Okawa"
weight: 4
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

Before configuring the settings according to your experiment, let's check that artemis is working!

```shell { wrap="false" }
> artlogin (username)
> a # start the artemis!
```

Then the prompt change to the `artemis [0]`.
This means you are in artemis console!

Analysis using artemis use event loop.
It is therefore necessary to load a file that specifies what kind of analysis is to be performed.
This file is called the `steering file`.
As an example, let's check the operation using a steering file that only generates random numbers!

The command to load the steering file is `add`.

```shell { wrap="false" }
artemis [0] add steering/example/example.tmpl.yaml NUM=0001 MAX=10
```

This means that 10000 random numbers from 0 to MAX=10 are generated (10000 event loops).
NUM=0001 is the ID, so any number is okay (related to outputed file name).

And the command to start the event loop is `resume`.
(Often abbreviated as "resume" or "re". 
The abbreviated form will also run without problems if there are no conflicts with other commands.)

```shell { wrap="true" }
artemis [1] res
artemis [2] Info in <art::TTimerProcessor::PostLoop>: real = 0.02, cpu = 0.02 sec, total 10000 events, rate 500000.00 evts/sec
```

When the time taken for such an analysis is displayed, it means that all event loops have been completed.
If you are doing a time-consuming analysis and want to suspend the event loop in the middle, `suspend` command is used. (Often "sus" or "su" is used.)


```shell { wrap="false" }
artemis [2] sus
```

This event loop creates histogram objects (inherit from TH1 or TH2) and a TTree object.
Let's look at how to access each of these.

## Histogram

Details are given in the [Histograms section](https://okawak.github.io/artemis_crib/setting/histograms/index.html), but histograms are created in an internal directory.
To access it, you need to use the same commands as for the linux command, such as "ls" or "cd", to get to that directory.

```shell { wrap="false" }
artemis [2] ls

 artemis
>   0 art::TTreeProjGroup test2           test (2) # the first ">" means your current position
    1 art::TTreeProjGroup test            test
    2 art::TAnalysisInfo analysisInfo

# then let's move to the "test" directory!

artemis [3] cd 1
artemis [4] ls

 test
>   0 art::TH1FTreeProj hRndm           random value

```

You can use the command `ht [ID]` to display a histogram.
The ID can be omitted if it is already represented by >.

```shell { wrap="false" }
artemis [5] zone # make artemis canvas
artemis [6] ht 0
```

{{< figure src="example_test_hist.png" width=600 >}}


Next, let's also check the histogram in "test2" directory and display two histograms vertically at the same time!

```shell { wrap="false" }
artemis [7] zone 2 1 # row=2, column=1
artemis [8] ht 0 # show the current hist 
artemis [9] cd ..
artemis [10] ls

 artemis
>   0 art::TTreeProjGroup test2           test (2)
    1 art::TTreeProjGroup test            test
    2 art::TAnalysisInfo analysisInfo

artemis [11] cd 0

 test2
>   0 art::TH1FTreeProj hRndm2          random number

artemis [12] ht 0
```

{{< figure src="example_test_hist2.png" width=600 >}}


## TTree

Now consider displaying a diagram from a TTree object.
The file is created at here.

```shell { wrap="false" }
artemis [13] fls
 files
    0 TFile output/0001/example_0001.tree.root            (CREATE)
```

We use the `fcd` command to navigate to this root file.

```shell { wrap="false" }
artemis [14] fcd 0
artemis [15] ls

 output/0001/example_0001.tree.root
>   0 art::TAnalysisInfo analysisInfo
    1 art::TArtTree tree            tree

```

The command `branchinfo` ("br") displays a list of the branches stored in this tree.

```shell { wrap="false" }
artemis [16] br
random               art::TSimpleData
```

At the same time, the ROOT command can be used.

```shell { wrap="false" }
artemis [17] tree->Print()
******************************************************************************
*Tree    :tree      : tree                                                   *
*Entries :    10000 : Total =          600989 bytes  File  Size =      86144 *
*        :          : Tree compression factor =   7.00                       *
******************************************************************************
*Br    0 :random    : art::TSimpleData                                       *
*Entries :    10000 : Total  Size=     600582 bytes  File Size  =      85732 *
*Baskets :        1 : Basket Size=    3200000 bytes  Compression=   7.00     *
*............................................................................*
```

{{% notice style="info" %}}
What is stored in the branch is not the usual type like "double" or "int", but a class defined in artemis.
Therefore, the "artemis" root file cannot be opened by usual ROOT.
{{% /notice %}}

Accessing data in a branch's data class requires the use of public variables and methods, which can be examined by providing arguments to `branchinfo [branch name]` or `classinfo [class name]`.

```shell { wrap="false" hl_lines="24" }
artemis [18] br random

 art::TSimpleData

 Data Members


 Methods

                   Bool_t   CheckTObjectHashConsistency
             TSimpleData&   operator=
             TSimpleData&   operator=

 See also

     art::TSimpleDataBase<double>

artemis [19] cl art::TSimpleDataBase<double>

 art::TSimpleDataBase<double>

 Data Members

                   double   fValue

 Methods

                     void   SetValue
                   double   GetValue
                   Bool_t   CheckTObjectHashConsistency
     TSimpleDataBase<double>&   operator=

 See also

     art::TDataObject       base class for data object
```

Therefore, it can be seen that it can be accessed by the value `fValue`.

```shell { wrap="false" }
artemis [20] zone
artemis [21] tree->Draw("random.fValue>>(100,0.,10.)")
```


## Other useful commands

```shell { wrap="false" }
artemis [*] help # show the commands we can use
artemis [*] save # save the current canvas
artemis [*] print # print the current canvas (send to the printer, need to configure)
artemis [*] unzoom
artemis [*] lgy, lgz, lny, lnz # linear or log scale
```

