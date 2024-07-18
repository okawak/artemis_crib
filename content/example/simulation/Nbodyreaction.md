---
title: "Nbody Reaction"
date: 2023-08-25T18:46:12+09:00
draft: false
author: "Kodai Okawa"
weight: 301
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

make a reaction considering phase space.

- steering file example

```yaml { wrap="false" }
  - name: reaction_proc
    type: art::TNBodyReactionProcessor
    parameter:
      InputCollection: *beam_name
      OutputCollection: products # size is DecayParticleNum
      OutputReactionCollection: reaction
      # beam information (for initialize TSrim)
      BeamNucleus: [*beam_Z, *beam_A] # (Z, A)
      BeamEnergy: *beam_E
      # target information
      TargetIsGas: true # false-> solid, true-> gas target
      TargetName: he # from TSrim energy loss
      TargetMassNum: 4 # hit ion
      TargetAtomicNum: 2 # hit ion
      TargetThickness: 1000 # mm (for gas target, allow up to this value)
      TargetPressure: 250 # Torr (used for gas target)
      # reaction particles information
      DecayParticleNum: 2
      ReactionMassNum: [29, 1] # will be [id=0, id=1]
      ReactionAtomicNum: [15, 1]
      ExciteLevel: [0.0, 0.0] # MeV
      # cross section file, if not, it use constant cross section for energy
      # require: "energy cross-section" format, deliminator should be a space ' '
      CrossSectionPath: path/to/cs/file
      CrossSectionType: 0 # 0-> LAB, kinematics is different, 1-> LAB, kinematics is same, 2-> CM

```

**NOTE**

- using TSrim library, so need to set `TargetName` that registered this library
- if cross section file is not found, it use constant dsigma/dE
- cross section file format should be

```text
# comment
# energy cross_section
0.0 0.0
0.1 1.0 # comment

# 0.2, 2.0 camma is not allowed...
```

- output `products` is size two array, like products[0] -> id=0 particle
- output `reaction` contain reaction information, like Ecm, Thetacm

```shell { wrap="false" }
artemis [] classinfo art::TReactionInfo

 art::TReactionInfo

 Data Members

                   double   fEnergy                / Ecm of the reaction
                   double   fTheta                 / Thetacm of the reaction
                   double   fX                     / reaction position at LAB system, x
                   double   fY                     / reaction position at LAB system, y
                   double   fZ                     / reaction position at LAB system, z
                   double   fExEnergy              / excited energy of residual nucleus
                ESortType   kID                                        
                ESortType   kTiming                                    
               ESortOrder   kASC                                       
               ESortOrder   kDESC   
```
