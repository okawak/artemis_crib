---
title: "Requirements"
date: 2023-08-14T13:36:14+09:00
author: "Kodai Okawa"
draft: false
weight: 1
---

{{% badge %}}{{< signature >}}{{% /badge %}}

The following machines have been tested for operation.

### CRIB's analysis machine

- Ubuntu 22.04.4 LTS
- gcc 11.4.0
- cmake 3.22.1
- ROOT 6.30/04
- yaml-cpp 0.7
- artemis commit ID a976bb9
- [new] TSrim python-develop branch

### Example of installation of required dependencies

- for Ubuntu

```shell { wrap="false" }
sudo apt-get install binutils cmake dpkg-dev g++ gcc \
libssl-dev git libx11-dev \
libxext-dev libxft-dev libxpm-dev python3 libtbb-dev \
libvdt-dev libgif-dev \
gfortran libpcre3-dev \
libglu1-mesa-dev libglew-dev libftgl-dev \
libfftw3-dev libcfitsio-dev libgraphviz-dev \
libavahi-compat-libdnssd-dev libldap2-dev \
python3-dev python3-numpy libxml2-dev libkrb5-dev \
libgsl-dev qtwebengine5-dev nlohmann-json3-dev libmysqlclient-dev \
libyaml-cpp-dev
```

---

NOTE:

- From 2023/10, Ubuntu system is also avaliable. ([issue48](https://github.com/artemis-dev/artemis/pull/48))
- We have confirmed that it works on RedHat-based Linux (Alma linux, Rocky linux etc.).
