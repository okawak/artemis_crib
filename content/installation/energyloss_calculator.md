---
title: "energyloss calculator"
date: 2023-08-14T15:14:00+09:00
draft: false
author: "Kodai Okawa"
tags: ["CRIB"]
weight: 7
---

{{% badge %}}{{< signature >}}{{% /badge %}}

Some CRIB-specific files use energy loss libraries.

{{% notice style="warning" %}}
Until 2023 we used [SRIMlib](https://github.com/okawak/SRIMlib) library developed by Okawa,
but we plan to replace new library [TSrim](https://www.cns.s.u-tokyo.ac.jp/gitlab/hayakawa/tsrim)
because Okawa will not maintain this library in the future.

We are still developping the code, so not stable version yet.
{{% /notice %}}

---

#### SRIMlib installation

```shell { wrap="false" }
git clone https://github.com/okawak/SRIMlib.git
cd SRIMlib
mkdir build
cd build
cmake ..
make
make install
```

Before using this library, you need to make database file (just .root file)

```shell { wrap="false" }
cd ..
source thisSRIMlib.sh
update
```

If you want to make energy loss figures, "f" option will work.

```shell { wrap="false" }
update -f
```

Also, I recommend to write `source thisSRIMlib.sh` part in the .bashrc/.zshrc to load this library.
