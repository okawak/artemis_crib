---
title: "PPAC calibration"
date: 2023-12-13T14:58:47+09:00
draft: false
author: "Kodai Okawa"
weight: 3
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

CRIB use two kinds of PPAC (Parallel-Plate Avalanche Counter), charge division method or delay-readout method.
The PPAC placed at the F1 focal plane is charge-devision type, and the parameters to be converted to position are fixed and do not need to be calibrated.
Therefore we explain the calibration method for delay-line PPAC (dl-PPAC).

## Principles
Here we briefly describe the principle of converting from the obtained signal to position, but for more details, see here[^1].

[^1]: H. Kumagai et al., Nucl. Inst. and Meth. A **470**, 562 (2001)

We will discuss the x-direction because x and y is exactly same.
First, define the parameters as follows

1. {{< math >}}$k_x${{< /math >}} : convert from signal time difference to position [mm/ns]
2. {{< math >}}$T_{X1},~T_{X2}${{< /math >}} : time at both ends of delay-line, measured at TDC [ns]
3. {{< math >}}$T_{Xin-offset}${{< /math >}} : timing offset come from inside the chamber [ns]
4. {{< math >}}$T_{Xout-offset}${{< /math >}} : timing offset come from outside the chamber [ns] (like from cabling)
5. {{< math >}}$X_{offset}${{< /math >}} : geometry offset [mm]

The artemis codes calculate the X position like this formula (see [TPPACProcessor.cc](https://github.com/artemis-dev/artemis/blob/develop/artemis-share/src/ppac/TPPACProcessor.cc)).

```math
$$ X~\mathrm{[mm]} = k_x\left( \frac{T_{X1} - T_{X2} + T_{Xin-offset} - T_{Xout-offset}}{2} \right) - X_{offset}$$
```
{{% notice style="warning" %}}
Check the sign carefully! We often mistook the direction!!
{{% /notice %}}

## Fixed parameters
The {{< math >}}$T_{X1},~T_{X2}${{< /math >}} are measured value by TDC, and {{< math >}}$k_x${{< /math >}} and {{< math >}}$T_{Xin-offset}${{< /math >}} are specific value to PPAC, so we need to care only {{< math >}}$T_{Xout-offset}${{< /math >}} and {{< math >}}$X_{offset}${{< /math >}}.
{{< math >}}$X_{offset}${{< /math >}} value depends on where we put the PPAC, so what we have to do is determine the line calibration parameter ({{< math >}}$T_{Xout-offset}${{< /math >}}).

The following is a list of dl-PPAC parameters used in CRIB experiment.

| PPAC ID | {{< math >}}$k_x${{< /math >}} [mm/ns] | {{< math >}}$k_y${{< /math >}} [mm/ns] | {{< math >}}$T_{Xin-offset}${{< /math >}}| {{< math >}}$T_{Yin-offset}${{< /math >}} |
|----|----|----|----|----|
| #2 | 1.256 | 1.256 | 0.29 mm | 0.18 mm | 
| #3 | 1.264 | 1.253 | 0.22 mm | 0.30 mm |
| #7 | 1.240 | 1.242 | 0.92 ns | 1.58 ns |
| #8 | 1.241 | 1.233 | 0.17 ns | 0.11 ns |
| #9 | 1.257 | 1.257 | 0.05 mm | 0.04 mm |
| #10| 1.257 | 1.257 | 0.05 mm | 0.04 mm |

{{% notice style="warning" %}}
Different units are used for the offset. However, since the effect of this offset is eventually absorbed to the other offset value, it is no problem to use the values if we calibrate it correctly.
{{% /notice %}}


## Parameter setting

PPAC parameters are defined in the following files

- [prm/ppac/dlppac.yaml](https://github.com/okawak/artemis_crib/blob/main/prm/ppac/dlppac.yaml)

For example, it is like this:
```yaml { wrap="false" title="prm/ppac/dlppac.yaml" }
Type: art::TPPACParameter
Contents:
# #7 PPAC
  f3bppac: # this is the name of PPAC, should be the same name with the one in steering file!
    ns2mm:
    - 1.240
    - 1.242
    delayoffset:
    - 0.92
    - 1.58
    linecalib:
    - 1.31
    - -1.00
    # 0: no exchange, 1: X -> Y, Y -> X
    exchange: 0
    # 0: no reflect, 1: X -> -X
    reflectx: 1 
    geometry:
    - 0.0
    - 0.5
    - 322.0
    TXSumLimit:
    - -800.0
    - 2000.0
    TYSumLimit:
    - -800.0
    - 2000.0
```

- ns2mm

  This is {{< math >}}$k_x${{< /math >}} and {{< math >}}$k_y${{< /math >}} parameters -> input the fixed value

- delayoffset

  This is {{< math >}}$T_{Xin-offset}${{< /math >}} and {{< math >}}$T_{Yin-offset}${{< /math >}} parameters -> input the fixed value

- linecalib

  This is explained next.

- exchange, reflectx

  This parameter should be changed depending on the direction in which the PPAC is placed. The meanings of the parameters are given above as comments.
{{% notice style="note" %}}
  CRIB takes a coordinate system such that when viewed from downstream of the beam, the x-axis is rightward and the y-axis is upward. In other words, it takes a right-handed coordinate system with the beam as the Z-axis. While looking at the actual data, change these parameters so that the coordinate system becomes this coordinate system.
{{% /notice %}}

- geometry

  In the Line calibration, please set this value to (0,0).
  After Line calibration, if we put the PPAC with some geometry offset, we should change this parameters.
  Please be careful that the parameter will add minus this value for X and Y.
  Z offset will be used for [TPPACTrackingProcessor](https://github.com/artemis-dev/artemis/blob/develop/artemis-share/src/ppac/TPPACProcessor.cc).

- TXSumLimit, TYSumLimit

  Used to determine if it is a good event or not. Currently not used.

## Line calibration

Before starting line calibration, please make sure that map file and steering file is correctly set.
Also we need parameter file of prm/ppac/ch2ns.dat to convert TDC channel to ns unit. (already prepared I think) 

{{< mermaid >}}
graph LR;
    A[TDC channel] -->|prm/ppac/ch2ns.dat| B[ns scale]
    B --> |prm/ppac/dlppac.yaml|C{PPAC object}
{{< /mermaid >}}

When you complete the setting except for `linecalib` parameters, let's start calibration!
We prepared two useful macros to calibrate dl-PPAC.

- [macro/run_PPACLineCalibration.C](https://github.com/okawak/artemis_crib/blob/main/macro/run_PPACLineCalibration.C) : Macro to actually execute
- [macro/PPACLineCalibration.C](https://github.com/okawak/artemis_crib/blob/main/macro/PPACLineCalibration.C) : Macro that actually work




