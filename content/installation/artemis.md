---
title: "artemis"
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

```shell { wrap="false" }
cd hoge
git clone https://github.com/artemis-dev/artemis.git -b develop
cd artemis
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=../install ..
make -j4
make install
source ../install/bin/thisartemis.sh
```

Then, `<CMAKE_INSTALL_PREFIX>/bin/thisartemis.sh` will be created 
and this shell script can configure the environment (ROOT, yaml-cpp, artemis libraries) to use artemis.

Also, I recommend to write `source thisartemis.sh` part in the .bashrc/.zshrc to load this library.

Another option is to use `module` command to manage the environment.
It is also written in [artemis repo](https://github.com/artemis-dev/artemis/blob/develop/README.md).

---

### Note

For the CRIB experiment setting, we modified some parts of artemis source.

Please check the [CRIB configuration](../../crib_parts/).
