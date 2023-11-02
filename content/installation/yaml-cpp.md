---
title: "yaml-cpp"
date: 2023-08-14T13:57:35+09:00
draft: false
author: "Kodai Okawa"
weight: 4
---

{{% badge %}}{{< signature >}}{{% /badge %}}

{{% notice style="info" %}}
The yaml-cpp can be installed by some package manager like `apt` or `dnf`, but I'm not sure it will work or not in the installation of the artemis.
{{% /notice %}}

Current version of the artemis use yaml-cpp-0.7 or higher.
In order to use this library, please install from the repository.

See also [Github repo](https://github.com/jbeder/yaml-cpp) and [README of the artemis](https://github.com/artemis-dev/artemis/blob/develop/README.md)
Please install it as a shared object like below commands.

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
