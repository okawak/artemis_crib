---
title: "Artemis"
date: 2023-08-14T14:28:33+09:00
draft: false
author: "Kodai Okawa"
tags: ["CRIB"]
weight: 5
---

{{% badge %}}{{< signature >}}{{% /badge %}}

From the current situation, CRIB experiment doesn't use GET system, 
so we describe how to install it without linking it to GET decoder.

Also, it can link to `openMPI`, but the below commands assume not using openMPI.
See [artemis repo](https://github.com/artemis-dev/artemis/blob/develop/README.md) for more information.

```shell
cd hoge
git clone https://github.com/artemis-dev/artemis.git -b develop
cd artemis
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=../install ..
make -j8
make install
source ../install/bin/thisartemis.sh
```

Then, `<CMAKE_INSTALL_PREFIX>/bin/thisartemis.sh` will be created 
and this shell script can configure the environment (ROOT, yaml-cpp, artemis libraries) to use artemis.

(It means you don't have to write like `export PATH=${yaml-cpp path}:$PATH` or `source thisroot.sh` in .zshrc or .bashrc.)

Another option is to use `module` command to manage the environment.
It is also written in [artemis repo](https://github.com/artemis-dev/artemis/blob/develop/README.md).

---
{{% notice style="note" %}}
This is 2023/10/29 current information 
{{% /notice %}}

Okawa think there is a grammatical error in the **sources/main/thisartemis.sh.in**, so I changed like:


```diff
-if [ "@BUILD_GET@" == "ON" ]; then
+if [[ "@BUILD_GET@" == "ON" ]]; then
     export LD_LIBRARY_PATH=@GET_LIB_DIR@:$LD_LIBRARY_PATH
 fi

-if [ "@MPI_CXX_FOUND@" == "TRUE" ]; then
+if [[ "@MPI_CXX_FOUND@" == "TRUE" ]]; then
     dir=@MPI_CXX_LIBRARIES@
     libdir="$(dirname $dir)"
```
