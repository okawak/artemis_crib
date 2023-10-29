---
title: "Root"
date: 2023-08-14T12:27:52+09:00
author: "Kodai Okawa"
draft: false
weight: 3
---

{{% badge %}}{{< signature >}}{{% /badge %}}

Artemis uses [ROOT library](https://root.cern/).

We confirmed that version 6.28 of the ROOT will work well, but if the ROOT updates, we are not sure that the ARTEMIS will work well, 
so we recommend to build from the sources.

For detailded information, please refer [Installing ROOT](https://root.cern/install/)
Recommendations are described below.

```shell
# The latest stable branch gets updated automatically on each release.
# You may update your local copy by issuing a `git pull` command from within `root_src/`.
cd hoge # where you want to install ROOT
git clone --branch latest-stable --depth=1 https://github.com/root-project/root.git root_src
mkdir root_build root_install && cd root_build
cmake -DCMAKE_INSTALL_PREFIX=../root_install ../root_src # && check cmake configuration output for warnings or errors
cmake --build . -- install -j4 # if you have 4 cores available for compilation
source ../root_install/bin/thisroot.sh # or thisroot.{fish,csh}
```

If there are any problems at the compile, additional packages may need to be installed.
See also [dependencies](https://root.cern/install/dependencies/).

{{% notice style="info" %}}
If errors related to xrootd, TBB and clad occur, the cmake options `-Dxrootd=OFF`, `-Dimt=OFF` and `-Dclad=OFF` may work respectively.
{{% /notice %}}

`source thisroot.sh` part will be written in thisartemis.sh (this is created after artemis installation),
but before installing artemis, you need to type this once.

after completing the installation of the artemis, you don't have to execute this command for each time.
