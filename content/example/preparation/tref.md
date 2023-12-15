---
title: "Tref for V1190"
date: 2023-12-15T17:39:54+09:00
draft: false
author: "Kodai Okawa"
weight: 2
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

CRIB uses a multi-hit TDC called V1190 to take timing data ([manual](https://drive.google.com/file/d/1YRwkuFTjKFb5OvC1EfxYZtOGGdf-zKkS/view?usp=sharing)).
When a trigger comes into this module, it opens a window with a set time width and records the timing of the data.

However, even if the signal is sent at exactly the same time to the trigger, due to the uncertainty in opening that window, the resulting channel will vary.
Since absolute channel values will vary, but relative channel values for a given (especially trigger) timing will remain the same, it is necessary to subtract all data by some reference channel to achieve good timing resolution.

The signal that serves as the reference for that time is what we call `Tref`!
(Time reference)
Since it is essential that all events contain that data, we put the trigger signal in one of the channels and make it a Tref.

The "tref" settings are made in the following file:

```yaml { wrap="false" title="steering/tref.yaml" }
Processor:
# J1 V1190A
  - name: proc_tref_v1190A_j1
    type: art::TTimeReferenceProcessor
    parameter:
      # [[device] [focus] [detector] [geo] [ch]]
      RefConfig: [12, 2,  7, 0, 15]
      SegConfig: [12, 2,  7, 0]
```

Parameters `RefConfig` and `SegConfig` are set using the same ID as in the [map file](https://okawak.github.io/artemis_crib/setting/map_config/index.html).

The "RefConfig" represents the "Tref" signal and the "SegConfig" represents the V1190 module.
Therefore, the role of the processor is to subtract the "Segconfig" V1190 all timing signal from the "RefConfig" tref signal.

To apply this processor, add the following line to the steering file.
For example,

```yaml { wrap="false" title="steering/chkf3.yaml" hl_lines="22" }
Anchor:
 - &input ridf/@NAME@@NUM@.ridf
 - &output output/chkf3@NAME@@NUM@.root
 - &histout output/chkf3@NAME@@NUM@.hist.root

Processor:
  - name: timer
    type: art::TTimerProcessor

  - name: ridf
    type: art::TRIDFEventStore
    parameter:
      OutputTransparency: 1
      InputFiles:
        - *input

  - name: mapper
    type: art::TMappingProcessor
    parameter:
      OutputTransparency: 1

  - include: tref.yaml
  - include: rf/rf.yaml
  - include: coin/coin.yaml
  - include: ppac/dlppac.yaml
  - include: ssd/f3ssd.yaml

  - name: outputtree
    type: art::TOutputTreeProcessor
    parameter:
      FileName:
        - *output
```

{{% notice style="note" %}}
The tref.yaml should be written before the main processor. In this example, it is written right after TMappingProcessor, and we recommend writing it in this position.
{{% /notice %}}
