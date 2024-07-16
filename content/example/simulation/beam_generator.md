---
title: "Beam Generator"
date: 2023-08-25T18:45:16+09:00
draft: false
author: "Kodai Okawa"
weight: 300
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

It is very useful to use Monte Carlo (MC) simulation to obtain various calculated values.
From this section, we will show the simple example how to perform MC simulation using artemis.

First, we will set the generator of the beam that will bombard on the target.
We have two kinds of generator:

- Random parameter beam (using Random number)
- Get beam parameter from ROOT file

After you get beam information from a measurement, second option might be useful.

## Random Beam Generator

This is an example of a steering file.

```yaml { wrap="false" }
Processor:
  - name: random_eventstore
    type: art::TRandomNumberEventStore
    parameter:
      OutputTransparency: 1
      MaxLoop: *loopnum

  - name: beam_generator
    type: art::TRandomBeamGenerator
    parameter:
      OutputCollection: *beam_name
      OutputTrackCollection: *track_name
      #beam particle information
      MassNum: *beam_A
      AtomicNum: *beam_Z
      ChargeNum: *beam_Z
      IniEnergy: *beam_E
      #beam tracking information
      Xsigma: 1.0 # mm
      Ysigma: 1.0 # mm
      Asigma: 1.0 # deg
      Bsigma: 1.0 # deg
      Esigma: *beam_Esigma
```

This produces two branch, "beam" and "track".

- beam: contain all information about beam ion
- track: used for reconstract simulation

Actually "track" information is contained in "beam" branch.

Here is the detail of the type of "beam".

```cpp { wrap="false" }
artemis [] classinfo art::TParticleInfo

 art::TParticleInfo

 Data Members

                      int   fMassNumber                                
                      int   fAtomicNumber                              
                      int   fCharge                                    
                   double   fEnergy                kinetic energy in LAB system
                   double   fCurrentZ              current Z position  
                   double   fTime                  Duration time (ns)  
                   TTrack   fTrack                 tracking information in LAB system
           TLorentzVector   fVec                   lorentz vector (px, py, pz, E) of this particle
                   double   fTheta_cm              theta angle (deg) in CM system
                   double   fPhi_cm                phi angle (deg) in CM system

-- snip --
```

`fCurrentZ` is the current Z position and at the beam generation, this value will be set as 0 after this processor.

For example, the beam angle distribution will be like this.

{{< figure src="angle.png" width=400 >}}

## Tree Beam Generator

The tracking information obtained from the experiment can also be used to generate the beam.
In the current version, the position and angle of the beam are read from a ROOT file and the energy is given randomly.

This is an example of a steering file.

```yaml { wrap="false" }
Processor:

  - name: periodic_tree
    type: art::TTreePeriodicEventStore
    parameter:
      OutputTransparency: 1
      FileName: *input
      TreeName: tree
      MaxEventNum: *loopnum

  - name: proc_copy_processor
    type: art::TBranchCopyProcessor
    parameter:
      InputCollection: f3ppac # need to inherit from TTrack
      OutputCollection: *track_name

  - name: beam_generator
    type: art::TTreeBeamGenerator
    parameter:
      InputCollection: *track_name
      OutputCollection: *beam_name
      # beam particle information
      MassNum: *beam_A
      AtomicNum: *beam_Z
      ChargeNum: *beam_Z
      IniEnergy: *beam_E
      Esigma: *beam_Esigma
```

It reads an object named "f3ppac", which inherits from TTrack, from a TTree named "tree" in a file named "*input",
and creates an object of the same type as before named `TParticleInfo`.
