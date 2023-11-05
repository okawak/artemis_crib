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
In particular, a library called [SRIMlib](https://github.com/okawak/SRIMlib) has been developed by Okawa and some processors need to load this library.


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
