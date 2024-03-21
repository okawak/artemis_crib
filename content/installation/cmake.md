---
title: "cmake"
date: 2023-10-29T16:03:04+09:00
draft: false
author: "Kodai Okawa"
weight: 2
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

Generally, `sudo dnf install cmake`, `sudo apt install cmake` or `brew install cmake` support latest version of the cmake, but for some older machine like CentOS7, it is too old to install ROOT.

The latest ROOT require CMake 3.16 or higher, and if your system doesn't support this version, you need to install manually.

You can get more information from [here](https://github.com/Kitware/Cmake).


```shell { wrap="false" }
cd hoge
git clone https://github.com/Kitware/Cmake.git
cd Cmake
./bootstrap
make -j8
sudo make install
```

If you want to set the version, you can change the branch (tag).
The default branch is `master`.
