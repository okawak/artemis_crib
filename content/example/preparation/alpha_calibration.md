---
title: "Alpha calibration"
date: 2023-12-13T14:58:43+09:00
draft: false
author: "Kodai Okawa"
weight: 5
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

This is the CRIB alpha source information.
(unit: MeV)

| ID | alpha-2 | alpha-3 |
|----|----|----|
| | 4.780 | 3.148 |
| | 5.480 | 5.462 |
| | 5.795 | 5.771 |

### calibration files

SSD calibration files need to be set at `prm/ssd/` directory.
The directory structure is like this:

```shell { wrap="false" }
$ tree -L 2 prm/ssd
prm/ssd
├── ch2MeV.dat # test file
├── ch2ns.dat # test file
├── f2ch2MeV.dat
├── f2ch2MeV_raw.dat
├── f2ch2ns.dat
├── tel1
│   ├── ch2MeV_dEX.dat
│   ├── ch2MeV_dEX_raw.dat
│   ├── ch2MeV_dEY.dat
│   ├── ch2MeV_dEY_raw.dat
│   ├── ch2MeV_E.dat
│   ├── ch2MeV_E_raw.dat
│   ├── ch2ns_dEX.dat
│   ├── ch2ns_dEY.dat
│   ├── ch2ns_E.dat
│   └── tel_conf.yaml # telescope configuration, explain later

-- snip --
```

The `prm/ssd/ch2MeV.dat` and `prm/ssd/ch2ns.dat` are used for test, so in the beam time measurement, actually this files are not necessory.
And `prm/ssd/f2*` files are used for F2SSD calibration, and files in `prm/ssd/tel1/` directory are used for SSDs of a telescope.

The `ch2ns.dat` depends on TDC setting, so basically we don't have to care so muc
(Usually the setting (the value) is same with previous experiment.), so we have to prepare the `ch2MeV.dat` files!

{{% notice style="note" %}}
The file name need to be set like this example.
The loaded parameter file name is defined SSD steering file, and we don't want to change the SSD steering files so much, so please use such file names.
{{% /notice %}}
 
The "ch2MeV.dat" file format is like this:

```shell { wrap="false" title="prm/ssd/f2ch2MeV.dat" }
# offset gain
1.7009  0.0173
0.0 1.0 # if there are some SSDs or strip SSD, you can add the line.
```
```math
$$ E~\mathrm{[MeV]} = \mathrm{offset} + \mathrm{gain} \times \mathrm{ch} $$
```

### Usage

We prepared useful macros to calibrate many SSDs.
Please check these for more information.

- [macro/AlphaCalibration.C](https://github.com/okawak/artemis_crib/blob/main/macro/AlphaCalibration.C)
- [macro/run_AlphaCalibraion.C](https://github.com/okawak/artemis_crib/blob/main/macro/run_AlphaCalibration.C)

It is sufficient to use the AlphaCalibration.C, but it is recommended to use the run_AlphaCalibration.C to keep a record of what arguments were used to calibrate.

After you prepared alpha calibration data and steering file (for example `steering/calibration.yaml`) to show raw data, you can use this macro.

```shell { wrap="false" }
$ acd
$ vi macro/run_AlphaCalibration.C
# please set the parameters.
# instraction is written in this file

$ a
artemis [0] add steering/hoge.yaml NAME=hoge NUM=0000
artemis [1] res
artemis [2] .x macro/run_AlphaCalibration.C
```

Then the parameter file that defined at the "run_AlphaCalibration.C" and calibration figures will be created automatically.

These are example of the figures;

- raw fitting figure (figure/calib/tel*/ch2MeV_*/raw/)

{{< figure src="ex_raw.png" width=600 >}}

- calibration line and residual figure (figure/calib/tel*/ch2MeV_*/calibration/)

{{< figure src="ex_cal.png" width=600 >}}

```shell { wrap="false" }
$ a
artemis [0] add steering/hoge.yaml NAME=hoge NUM=0000
artemis [1] res
artemis [2] fcd 0
artemis [3] zo
artemis [4] tree->Draw("...") # draw calibrated data
artemis [5] gStyle->SetOptStat(0)
artemis [6] sa
```

{{< figure src="ex_all_cal.png" width=600 >}}

