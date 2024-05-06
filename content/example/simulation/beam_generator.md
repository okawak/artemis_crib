---
title: "Beam Generator"
date: 2023-08-25T18:45:16+09:00
draft: false
author: "Kodai Okawa"
weight: 300
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

Requirements:

- src-crib/simulation/TRandomBeamGenerator
- src-crib/simulation/TTreeBeamGenerator
- src-crib/simulation/TParticleInfo

---

As you know, an "event store" must be used to analyse the event loop.
For example, in the online analysis, we used `TRIDFEventStore`, and in the offline analysis, we can use `TTreeEventStore`.

But when we want to simulate something, there are no data file.
In that case, we can use `TCounterEventStore` or `TRandomNumberEventStore`.

- TCounterEventStore: generate numbers in sequence from 0 to N.
- TRandomNumberEventStore: generate number from 0.0 to 1.0 randomly.

Here I will simply describe a simulation using TCounterEventStore.

{{% notice style="info" %}}
When we use the `TCounterEventStore`, the console will show "no event store" error message.
However, the process will be done without any bugs, so currently okawa recommend to comment out the part to output this message.
{{% /notice %}}

## Random Beam Generator

Here I explain how to use this generator using 26Si14+ beam.
This is the example of steering file.

```yaml { wrap="false" }
Processor:
  - name: timer
    type: art::TTimerProcessor

  - name: count
    type: art::TCounterEventStore
      parameter:
        OutputTransparency: 0
        MaxLoop: 10000 # loop number

  - name: beam_generator
    type: art::TRandomBeamGenerator
      parameter:
        OutputCollection: beam
        OutputTrackCollection: tracking # used for reconstract simulation
        #beam particle information
        MassNum: 26
        AtomicNum: 14
        ChargeNum: 14
        IniEnergy: 55.5 # MeV (after window)
        #beam tracking information
        Xsigma: 1.0 # mm
        Ysigma: 1.0 # mm
        Asigma: 1.0 # deg
        Bsigma: 1.0 # deg
        Esigma: 0.0 # MeV (0 need for solid angle)
```

This produces two branch, "beam" and "tracking".

- beam: contain all information about beam ion
- tracking: used for reconstract simulation (only use paticular purpose)

Actually "tracking" information is contained in "beam" branch.

This is the "beam" branch, TParticleInfo information.

```cpp { wrap="false" }
 art::TParticleInfo

 Data Members
                      int   fMassNumber
                      int   fAtomicNumber
                      int   fCharge
                   double   fCurrentZ              current Z position
                   double   fEnergy                kinetic energy in LAB system
                   TTrack   fTrack                 tracking information in LAB system
           TLorentzVector   fVec                   lorentz vector (px, py, pz, E) of this particle in LAB system
```

`fCurrentZ` is the current Z position and at the beam generation, this value is set as 0.

For example, the beam angle distribution will be like this.

{{< figure src="angle.png" width=300 >}}

## Tree Beam Generator

From the ROOT file, we can generate the beam for using simulation.
For example, from the data, we can know the beam tracking information and it can be used in beam generator.

\<===under development===\>



