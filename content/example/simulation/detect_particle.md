---
title: "Detect particles"
date: 2023-08-25T18:46:55+09:00
draft: false
author: "Kodai Okawa"
weight: 304
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

Using the defined reactions (TNBodyReactionProcessor) and geometry (TUserGeoInitialiser) so far,
it is possible to determine whether the particles enter the detector after the reaction and to simulate the parameters obtained.

```yaml { wrap="false" }
  - name: detector_proc
    type: art::TDetectParticleProcessor
    parameter:
      InputCollection: products
      InputTrackCollection: track
      OutputCollection: detects
      # target information (use if gas target)
      TargetIsGas: *target_is_gas # true -> gas target
      TargetName: *target_name
      TargetPressure: *target_pressure # Torr (used for gas target)
      EnergyResolution: [0.0] # x 100 = %, det id = 0, 1, ..
```

- `products` is an array object of produced ions [id=0 ion, id=1 ion...]
- `detects` is an array object of detected ions [id=0 ion, id=1 ion...]

## Example of the output

We will show an example of a simulation performed for a **gas target case**, and resolution = 0.0.

First, this is a figure of the detected position of light particle.
We defined five telescopes in this example, and we can clearly see the position of the detectors.
If we focus on heavy particle, we cannot see the position distribution because all ions are stopped in the gas target.

{{< figure src="reac_pos.png" width=400 >}}

As an example, we will show you figures of a telescope with the largest angle.
Here is dE-E plots.

{{< figure src="dee.png" width=400 >}}

The relationship between energy and timing is like this.

{{< figure src="et.png" width=400 >}}

Also, here is the angular distribution of the LAB system.

{{< figure src="angle.png" width=400 >}}

## Summary

The processor created by [okawak](https://github.com/okawak) allows simple simulations to be performed without creating new sources,
if the following conditions are met.

- use latest version of artemis_crib
- properly install and link [TSrim](https://www.cns.s.u-tokyo.ac.jp/gitlab/hayakawa/tsrim) library
- the target is registered the TSrim library
- relatively low energy (some parts use classical kinematics)
- the shape of the detectors is square (may update?)

There are only two files that need to be prepared for the simulation.

- `prm/geo/hoge.yaml` -> define detector configuration (example [prm/geo/si26a.yaml](https://github.com/okawak/artemis_crib/blob/main/prm/geo/si26a.yaml))
  - It is useful to make symbolic link to `current`
- `steering/huga.yaml` -> define simulation parameters (example [steering/simNBodyReaction.yaml](https://github.com/okawak/artemis_crib/blob/main/steering/simNBodyReaction.yaml))
