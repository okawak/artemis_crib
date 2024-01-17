---
title: "Gate"
date: 2023-12-15T17:30:58+09:00
draft: false
author: "Kodai Okawa"
weight: 8
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

It is very important to select events for online analysis as well.
There are several options to do so, and I will cover all of them.
If you know other useful way, please let me know.

- Histogram definition
- TCutG object
- TGateStopProcessor

For clearer understanding, we will use this figure, and we call this as default figure:

{{< figure src="default.png" width=600 >}}



## Histogram definition

We explained in the [Histograms](../../../setting/histograms) page, but again we describe about histogram definition focus on the `cut` part.

The default figure defined like this:

```yaml { wrap="false" title="hist/f2/f2.yaml" }
anchor:
  - &f2ppacx ["f2ppac.fX",200,-50.,50.]
  - &f2ppacy ["f2ppac.fY",200,-50.,50.]
alias:
group:
  - name: f2check
    title: f2_check
    contents:
      - name: f2PPAC X vs Y
        title: f2ppac X vs Y
        x: *f2ppacx
        y: *f2ppacy
```

For example, let's add the gate to select only "-10.0 < X < 10.0".
We can use alias node to define that.

```yaml { wrap="false" title="hist/f2/f2.yaml" hl_lines="5 14" }
anchor:
  - &f2ppacx ["f2ppac.fX",200,-50.,50.]
  - &f2ppacy ["f2ppac.fY",200,-50.,50.]
alias:
  centerx: abs(f2ppac.fX) < 10.0;
group:
  - name: f2check
    title: f2_check
    contents:
      - name: f2PPAC X vs Y{centerx}
        title: f2ppac X vs Y{centerx}
        x: *f2ppacx
        y: *f2ppacy
        cut: centerx
```

Then the following histogram is created.

{{< figure src="yaml_gate.png" width=600 >}}

Also, multiple conditions can be specified at the same time.

```yaml { wrap="false" title="hist/f2/f2.yaml" hl_lines="6 15" }
anchor:
  - &f2ppacx ["f2ppac.fX",200,-50.,50.]
  - &f2ppacy ["f2ppac.fY",200,-50.,50.]
alias:
  centerx: abs(f2ppac.fX) < 10.0;
  centery: abs(f2ppac.fY) < 10.0;
group:
  - name: f2check
    title: f2_check
    contents:
      - name: f2PPAC X vs Y{centerx && centery}
        title: f2ppac X vs Y{centerx && centery}
        x: *f2ppacx
        y: *f2ppacy
        cut: centerx && centery
```

{{< figure src="yaml_multigate.png" width=600 >}}

## TCutG object
We can also use TCutG object to select the event.
As in [new commands](../../../crib_parts/newcommand) page, let's assume we create this TCutG ROOT file by `tcutg` command.
And the ROOT file and TCutG object name is `f2star`.

{{< figure src="tcutg_raw.png" width=600 >}}

If you want to use this object to select event, just add this line is fine, as long as you use [userlogon.C](../../../crib_parts/userconfig).

```yaml { wrap="false" title="hist/f2/f2.yaml" hl_lines="13" }
anchor:
  - &f2ppacx ["f2ppac.fX",200,-50.,50.]
  - &f2ppacy ["f2ppac.fY",200,-50.,50.]
alias:
group:
  - name: f2check
    title: f2_check
    contents:
      - name: f2PPAC X vs Y{f2star}
        title: f2ppac X vs Y{f2star}
        x: *f2ppacx
        y: *f2ppacy
        cut: f2star
```

{{< figure src="tcutg_star.png" width=600 >}}

Of course we can use in "tree->Draw()" because this TCutG objects are automatically loaded.
The following sentence generate the same figure.

```shell { wrap="false" }
artemis [] fcd 0
artemis [] zo
artemis [] tree->Draw("f2ppac.fY:f2ppac.fX>>(200,-50.,50., 200,-50.,50.)","f2star","colz")
```

## TGateStopProcessor

The method used until now was to process just histograms and analyze them for all events in the event loop.
If you know which events you don't want, there are processors that allow you to skip the event loop under certain conditions.
This may speed up the event loop.

For example. when we want to analyze only `beam single` event (it means the events are not coincident with SSD, and let's suppose that condition is given by `single.fID==0`), let's prepare the steering file.

```yaml { wrap="false" title="steering/gate/coin.yaml" hl_lines="11 18" }
Processor:
  - name: proc_gateinit
    type: art::TGateArrayInitializer
    parameter:
      OutputTransparency: 1

  - name: proc_gate
    type: art::TTreeFormulaGateProcessor
    parameter:
      Definitions:
        - "beam_single; single.fID==0"
      OutputTransparency: 1
      Verbose: 1

  - name: beam_single_gate
    type: art::TGateStopProcessor
    parameter:
      GateName: beam_single
      OutputTransparency: 1
      StopIf: 0
      Verbose: 1
```

To use TGateStopProcessor, we need to initialize the "gate" array object, so the first `art::TGateArrayInitializer` is needed.
In the second processor, `art::TTreeFormulaGateProcessor`, we define the gate condition.

Then the `art::TGateStopProcessor` judges the event is skipped or not.
In the case of `StopIf: 0`, artemis ignore the event that the condition become `false`.
In other words, `StopIf: 0` means artemis will analyze the event only when the condition is `true`. 


Then, including this yaml file to the main steering file, you can check only the selected events.

```yaml { wrap="false" title="steering/hoge.yaml" hl_lines="25" }
Anchor:
  - &input ridf/@NAME@@NUM@.ridf
  - &output output/@NAME@/@NUM@/hoge@NAME@@NUM@.root
  - &histout output/@NAME@/@NUM@/hoge@NAME@@NUM@.hist.root

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

# include some other steering files

  - include: gate/coin.yaml

  - name: outputtree
    type: art::TOutputTreeProcessor
    parameter:
      FileName:
        - *output
```


{{% notice style="info" %}}
We didn't check if we can use the TCutG object in this process...
{{% /notice %}}
