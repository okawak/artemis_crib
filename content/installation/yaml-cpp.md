---
title: "yaml-cpp"
date: 2023-08-14T13:57:35+09:00
draft: false
author: "Kodai Okawa"
weight: 4
---

{{% badge %}}{{< signature >}}{{% /badge %}}

Current version of the artemis use yaml-cpp-0.7 or higher.
The `sudo dnf install yaml-cpp-devel` or `sudo apt install libyaml-cpp-dev` will work.

If you want to install from the source, please check [Github repo](https://github.com/jbeder/yaml-cpp) and [README of the artemis](https://github.com/artemis-dev/artemis/blob/develop/README.md)

```shell { wrap="false" }
cd hoge
git clone https://github.com/jbeder/yaml-cpp.git
cd yaml-cpp
mkdir build && cd build
cmake -DYAML_BUILD_SHARED_LIBS=ON -DBUILD_TESTING=OFF ..
make
sudo make install
```

Default install path is `/usr/local/lib` or `/usr/local/lib64`.
If you do not want to pollute the general environment, specify `CMAKE_INSTALL_PREFIX` and set **PATH** environment variable.

```shell { wrap="false" }
cmake -DCMAKE_INSTALL_PREFIX=/foo/bar -DYAML_BUILD_SHARED_LIBS=ON -DBUILD_TESTING=OFF ..
```
