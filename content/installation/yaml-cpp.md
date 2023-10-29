---
title: "Yaml-cpp"
date: 2023-08-14T13:57:35+09:00
draft: false
author: "Kodai Okawa"
weight: 4
---

{{% badge %}}{{< signature >}}{{% /badge %}}

Current version of the artemis use yaml-cpp-0.7.
If your package system (like `apt` or `dnf`) cannot install version 0.7, please install from the source.

See also [Github repo](https://github.com/jbeder/yaml-cpp) and [README of the artemis](https://github.com/artemis-dev/artemis/blob/develop/README.md)
Please install it as a shared object like below commands.

```shell
cd path/to/the/directory/you/want/to/install/yaml-cpp
git clone https://github.com/jbeder/yaml-cpp.git
cd yaml-cpp
mkdir build && cd build
cmake -DYAML_BUILD_SHARED_LIBS=ON -DBUILD_TESTING=OFF ..
make
sudo make install
```

Default install path is `/usr/local/lib` or `/usr/local/lib64`.
If you do not want to pollute the general environment, specify `CMAKE_INSTALL_PREFIX` and set **PATH** environment variable.

```shell
cmake -DCMAKE_INSTALL_PREFIX=/foo/bar -DYAML_BUILD_SHARED_LIBS=ON -DBUILD_TESTING=OFF ..
```
