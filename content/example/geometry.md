---
title: "Geometry"
date: 2023-08-25T16:34:00+09:00
draft: false
author: "Kodai Okawa"
weight: 302
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

In this page, I will explain how to determine the detecter geometry configration.

---

Firstly, let's prepare the parameter file like this:

```yaml { title = "prm/geo/example.yaml"}
material:
  - name: Vaccum # id=0
    atomic_mass: 0.0
    atomic_num: 0.0
    density: 0.0 # g/cm3

  - name: Si # id=1
    atomic_mass: 28.084
    atomic_num: 14.0
    density: 2.321

# Note: beam axis -> z, upper direction -> y
conposition:
  detector:
    - name: tel1
      strip: [16, 16]
      center_rotation: [0., 0., 322.0] # mm
      offset: [0., 0., 0.]
      distance: 244.0 
      angle: -4.0 # deg
      thickness: [0.02, 0.301, 1.494, 1.486]
      material: [Si]

    - name: tel2
      strip: [16, 16]
      center_rotation: [0., 0., 322.0]
      offset: [0., 0., 0.]
      distance: 154.5
      angle: 27.0
      thickness: [0.02, 0.300, 1.494, 1.485]
      material: [Si]

volume:
  top: # detector world
    name: TOP
    type: box # now only box is available
    material: 0 
    size: [400.0, 200.0, 1288.0] # mm

  detector:
    - name: tel1
      type: box
      material: 1 
      size: [50.0, 50.0, 1.0] # mm

    - name: tel2
      type: box
      material: 1 
      size: [50.0, 50.0, 1.0] # mm
```

There are many components to explain!
The `material` node is used to define ``TGeoMaterial`` and ``TGeoMedium`` classes.
(But they are not directly used.)
From **name** to **density** node are used to make a instance of this object.
This values are not used in the current processors.

The next `conposition` node define the detector configuration!
General telescopes of the CRIB experiment consist of **DSSSD** and **SSD** (single-pad),
and the node below defines the SSD of the telescope.

- name: Name of the telescope. For example tel1, tel2, and so on.
- strip: X x Y strip number. It is defined as an array like [16, 32], this means X:16 strips and Y:32 strips
- thickness: Thickness of the each layer. If there are two layer, the size of the array become two. You can add to any size. The unit is **mm**.
- material: material of the each layer. The string is used in `SRIMlib` calculation. This node is defined as a array for each layer, but if it is one, the same material is applied. For example, in example.yaml, [Si] means [Si, Si, Si, Si]. (You need to prepare SRIMlib setting beforehand!)


Let's move on to the geometry part!
The node is `center_rotation`, `offset`, `distance` and `angle`.
Please look at this figure.

{{< figure src="../geo_example.png" >}}

Please not that the center_rotation and offset are defined in (x, y, z) coordinate (-> [x, y, z]), but distance and angle is scalar value.
The unit of length is `mm`, angle is `deg`.


{{% notice style="info" %}}
The sign of the angle is defined as positive at this figure.
And generally, we set z=0 at target position. (For the gas target, we set 0 at window position.)
{{% /notice %}}


The last part is `volume` node!
In this parts, the shape of the detector will be defined by using ``TGeoVolume`` class.
The TGeoVolume needs **name**, **type**, **material** and **size**.
For the type, I only prepared "box". (It means the code use only vol->MakeBox method.)

The first `top` node must be set because it defined "detector world".
Generally, the material is okay to set vaccum.
And the material is defined in the `material` node, and the id (the order) can be used.
So the format is like `material: 0`.
And the size is generally set to the size of the scattering chamber, but for the safety, it is okay to set larger number.
Also the unit is `mm` and format is (x, y, z).

Next, at the `volume/detector` node, we can define the detector size.
Please NOTE that the name should be the same with `conposition/detector/name` node.

---

Then, let's check if the parameter file can be correctly used!
Please prepare the steering file.

```yaml { title = "steering/geo_example.yaml"}
Anchor:

Processor:
- name: detector_initialize
  type: art::TUserGeoInitializer
  parameter:
    Name: prm_detector
    FileName: prm/geo/example.yaml
    OutputTransparency: 1
```

This steering file doesn't use event loop.
Just we want to check the parameter file works well or not.

Then let's see in the artemis!
```shell
acd
a

-- snip --

artemis [0] add steering/geo_example.yaml

-- snip --

artemis [1] ls

 artemis
>   0 TGeoVolume TOP             Top volume

artemis [2]
```

The detector geometry object is successfully generated!
In order to check the object, please use [draw](https://github.com/okawak/artemis_crib/blob/main/src-crib/commands/TCmdDraw.cc) command for example.
(It is defined only in CRIB artemis, to draw not only histogram object. This is under development.)

```shell
artemis [2] draw 0
```

{{< figure src="../geo_canvas.png" >}}

The red box is the TOP, and the black boxes are detectors.
If the detector is placed where you expect it to be, the parameters have been successfully set!

In the event loop process, if you want to use the detector geometry information, you can use `prm_detector` in the steering files.
I will explain the next session!




