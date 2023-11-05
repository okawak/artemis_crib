---
title: "Build"
date: 2023-11-02T15:11:33+09:00
draft: false
author: "Kodai Okawa"
weight: 3
tags: ["CRIB"]
---

{{% badge %}}{{< signature >}}{{% /badge %}}

Before starting analysis, you need to build.
The current version of the artemis use "cmake" so the following steps must be taken.

```shell { wrap="false" }
> artlogin (username)
> mkdir build && cd build
> cmake ..
> make -j4
> make install
> acd
```
`acd` is the alias command that is definded after artlogin command. (acd = cd your_work_directory)
Also if you changed some processor, you need to do these process.

Then some important configuration files are automatically created.

```diff { wrap="false" }
 > tree -L 1
 .
+├── artemislogon.C
+├── thisartemis-crib.sh

 -- snip --

 └── run_artemis.cpp
```

Before starting artemis, you need to load the `thisartemis-crib.sh`.
The `artlogin` command is also used to read this script, so run this command again after the build.

```shell { wrap="false" }
> artlogin (usename)
> a
```

Then you can start artemis by using `a` command!
If you want to make sure it works correctly, please look at [Example: preparation/general](https://okawak.github.io/artemis_crib/example/preparation/general/).
