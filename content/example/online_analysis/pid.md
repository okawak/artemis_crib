---
title: "PID"
date: 2023-12-19T16:45:37+09:00
draft: false
author: "Kodai Okawa"
weight: 2
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}


This is almost the same with [this web application](https://www.cns.s.u-tokyo.ac.jp/crib/cgi-bin/pid/CRIB_PID_calc.html).
This web application uses `enewz` energy loss calculation, but PID using artemis uses `SRIM`.

These are the source code for the PID calculation.

- [TCRIBPIDProcessor.cc](https://github.com/okawak/artemis_crib/blob/main/src-crib/simulation/TCRIBPIDProcessor.cc)
- [TCRIBPIDProcessor.h](https://github.com/okawak/artemis_crib/blob/main/src-crib/simulation/TCRIBPIDProcessor.h)

### Principles

The simple principle of PID (Particle IDentification) is described.

First, the energies of the various beam ions are determined from the value of the magnetic rigidity ({{< math >}}$B\rho${{< /math >}}) of the dipole magnets.
The values are then calculated using relativity.


```math
$$ m_0\gamma\frac{v^2}{\rho} = qevB $$
$$ B\rho = \frac{m_0\gamma\beta c}{qe} $$
$$ \frac{B\rho qe}{c} = m_0\frac{\beta}{\sqrt{1-\beta^2}} $$
```

From this equation, solving for {{< math >}}$\beta^2${{< /math >}},

```math
$$ \beta^2 = \frac{1}{1+\left( \frac{m_0 c}{B\rho qe} \right)^2} $$
$$ \frac{1}{\sqrt{1-\beta^2}} = \sqrt{1+\left( \frac{B\rho qe}{m_0 c} \right)^2} $$
```

Relativistic energy {{< math >}}$E${{< /math >}} is

```math
$$ E = \frac{m_0 c^2}{\sqrt{1-\beta^2}} $$
$$ E^2 = \left(m_0 c^2\right)^2 + \left( B\rho qec \right)^2 $$
```

Therefore, from this equation, {{< math >}}$E${{< /math >}} can be obtained from {{< math >}}$B\rho${{< /math >}} and the kinetic energy can be derived from the following relationship.

```math
$$ E = E_{kin} + m_0 c^2 $$
$$ E_{kin} = m_0 c^2\left( \sqrt{1+\left( \frac{B\rho qec}{m_0 c^2} \right)^2} -1 \right) $$
```

The equation for determining velocity from energy using relativity can also be obtained as follows.
```math
$$ E_{kin} + m_0 c^2 = \frac{m_0 c^2}{\sqrt{1-\left(\frac{v}{c}\right)^2}} $$
$$ v = c\sqrt{1-\left( \frac{1}{\frac{E_{kin}}{m_0 c^2} +1} \right)^2} $$
```

The energy loss of the detector placed on the beamline is then calculated and the PID diagram is obtained by plotting the possible measured values using these relationships.


### Usage

First, please prepare the SRIMlib dataset.
You need all input ion for "mylar" and "Si" target energy loss table.
For the SRIMlib setting, please refer [this page](https://okawak.github.io/artemis_crib/installation/energyloss_calculator/index.html).

Next, you need input ions and beamline parameter files.
The format is like this.

```yaml { wrap="false" title="prm/pid/expname.yaml" }
input_ions:
  - name: 7Li3
    charge: 3
    mass: 7.01435758 # amu
    color: 0 # 0 -> red, 1 -> blue, 2 -> black
  - name: 6He2
    charge: 2
    mass: 6.01778863
    color: 1
  - name: 3H1
    charge: 1
    mass: 3.015500905
    color: 2
  - name: 2H1
    charge: 1
    mass: 2.013553496
    color: 2
  - name: 1H1
    charge: 1
    mass: 1.007276452
    color: 2
  - name: 4He2
    charge: 2
    mass: 4.001506094
    color: 2

# BLD parameters
f1_parameters:
  brho: 1.227 # Tm
  rf_period: 57.0 # ns

f2_parameters:
  PPAC_thickness: 10.0 # um, mylar
  SSD_thickness: 1500.0 # um

f3_parameters:
  a_thickness: 15.0 # um, mylar, PPACa/MWDCa
  b_thickness: 15.0 # um, mylar, PPACb/MWDCb
  distance: 290.5 # mm, between two tracking detectors
  trigger: 0 # PPACa/MWDCa -> 0, PPACb/MWDCb -> 1

# display parameters
f2_display:
  rf_offset: -6.5 # ns
  rf_range: [0.0, 120.0] # ns
  energy_range: [0.0, 100.0] # MeV

f3_display:
  rf_offset: -12.0 # ns
  tof_offset: -2.7 # ns
  rf_range: [0.0, 120.0] # ns
  tof_range: [0.0, 8.0] # ns
```

{{% notice style="info" %}}
You can add the beam ions freely, but you need to prepare SRIM Output table.
{{% /notice %}}


Lastly, let's prepare the steering file.
If you want to do only PID calculation, you can use `chkpid.yaml`.

```yaml { wrap="false" title="steering/chkpid.yaml" }
Processor:
  - name: pid
    type: art::TCRIBPIDProcessor
    parameter:
      FileName: prm/pid/expname.yaml
      Batch: false
      OutputTransparency: 1
```

You can add these sentences for any other steering files.
I think it is useful when you want to overlap the data figure and calculation figure.
If you set `Batch: false`, the canvases for F2 PID and F3 PID will appear automatically.
`Batch: true` is quiet mode.

This is an example of the automatically generated figure.

{{< figure src="auto.png" width=600 >}}

The process for the calculation is performed in init process (I mean not event loop), so when you `add` the steering file, the figure will be created.

```shell { wrap="false" }
> acd
> a
artemis [0] add steering/chkpid.yaml
# process is performed now
# if Batch: false, the two PID figure will appear automatically 

artemis [1] ls

 artemis
>   0 TDirectory pid             pid       

artemis [2] cd 0
artemis [3] ls

 pid
>   0 TMultiGraph                 F2_PID; F2 RF [ns]; F2 SSD [MeV]
    1 TMultiGraph                 F3_PID; F3 RF [ns]; PPACs/MWDCs TOF [ns]
    2 TCanvas F2_canvas       F2_canvas 
    3 TCanvas F3_canvas       F3_canvas 

artemis [4] draw 0
```

{{< figure src="multigraph.png" width=600 >}}

{{% notice style="info" %}}
There are two kinds of object, `TMultiGraph` and `TCanvas`.
The `ht` command cannot draw these object, so I also made `draw` command to be able to draw "TMultiGraph" objects.

HOWEVER, even this "draw" command cannot display the "TCanvas" object yet...
If you save the object using `hstore` command or check from THttpServer, you can check the TCanvas objects.
{{% /notice %}}

This "TMultiGraph" object is useful when you want to overlay th data.
```shell { wrap=false }
artemis [*] ht something # this is gaussian example
artemis [*] dr 0 p same
```

{{< figure src="overlap.png" width=600 >}}

