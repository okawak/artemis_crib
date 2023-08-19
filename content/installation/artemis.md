---
title: "Artemis"
date: 2023-08-14T14:28:33+09:00
draft: false
author: "Kodai Okawa"
weight: 4
---

{{% badge style="warning" %}}Not recommended{{% /badge %}}

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
```

Then, `<CMAKE_INSTALL_PREFIX>/bin/thisartemis.sh` will be created 
and this shell script can configure the environment (ROOT, yaml-cpp, artemis libraries) to use artemis.

(It means you don't have to write like `export PATH=${yaml-cpp path}:$PATH` or `source thisroot.sh` in .zshrc or .bashrc.)

Another option is to use `module` command to manage the environment.
It is also written in [artemis repo](https://github.com/artemis-dev/artemis/blob/develop/README.md).

---

**The following methods are not recommended!!**

For Ubuntu case, somehow it seems that there are some linking problem.

To avoid it, if I changed like below, the artemis will work well...

- [Mod] artemis/sources/main/CMakeLists.txt

```diff
- add_executable(artemis main.cc TArtRint.cc)
+ add_executable(artemis main.cc dummy.cc TArtRint.cc)
```

- [Add] artemis/sources/main/dummy.cc

```cpp
#include <TModuleDecoderV1190.h>
#include <TParameterLoader.h>
#include <TTreeProjection.h>
#include <TRDFEventStore.h>
#include <TRIDFEventStore.h>

// any class seems okay
void dummy()
{
  art::TModuleDecoderV1190 *dummy_decoder = new art::TModuleDecoderV1190();
  art::TParameterLoader *dummy_param = new art::TParameterLoader();
  art::TTreeProjection *dummy_hist = new art::TTreeProjection();
  art::TRDFEventStore *dummy_rdf = new art::TRDFEventStore();
  art::TRIDFEventStore *dummy_ridf = new art::TRIDFEventStore();
}
```

Libraries that are not directly involved in the artemis executable do not seem to be linked, 
despite using target_link_library(hoge) in CMakeLists.txt.
