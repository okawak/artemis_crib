---
title: "ROOT"
date: 2023-08-14T12:27:52+09:00
author: "Kodai Okawa"
draft: false
weight: 3
---

{{% badge %}}{{< signature >}}{{% /badge %}}

Artemis uses [ROOT library](https://root.cern/).
For detailded information, please refer [Installing ROOT](https://root.cern/install/)

This is one example to install the ROOT from the source.

```shell { wrap="false" }
# You may update your local copy by issuing a `git pull` command from within `root_src/`.
cd install_dir
git clone https://github.com/root-project/root.git root_src
# check out the tag to specify the ROOT version
cd root_src
git checkout -b v6-30-04 refs/tags/v6-30-04
cd ..

mkdir root_build root_install && cd root_build
cmake -DCMAKE_INSTALL_PREFIX=../root_install -Dmathmore=ON ../root_src # && check cmake configuration output for warnings or errors
make -j4
make install
source ../root_install/bin/thisroot.sh # or thisroot.{fish,csh}
```

If there are any problems at the compile, additional packages may need to be installed.
See also [dependencies](https://root.cern/install/dependencies/).

I recommend to write `source thisroot.sh` part in the .bashrc/.zshrc to load this library.
