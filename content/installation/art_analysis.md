---
title: "art_analysis"
date: 2023-08-14T15:14:43+09:00
draft: false
author: "Kodai Okawa"
tags: ["CRIB", "unsettled"]
weight: 8
---

{{% badge %}}{{< signature >}}{{% /badge %}}

With this command, all initial settings of "art_analysis" are made.

```shell { wrap="false" }
curl --proto '=https' --tlsv1.2 -sSf https://okawak.github.io/artemis_crib/bin/init.sh | sh
```

After that, please add the following lines to the .bashrc/.zshrc.

```shell { title=".bashrc/.zshrc" wrap="false" }
# this is option
source ${HOME}/Cern/root/root_install/bin/thisroot.sh &> /dev/null
source ${HOME}/repos/artemis/install/bin/thisartemis.sh &> /dev/null
source ${HOME}/repos/SRIMlib/thisSRIMlib.sh &> /dev/null

# need from this line!
export EXP_NAME="expname" # your experiment
export EXP_NAME_OLD="expname" # this is option
export PATH="${HOME}/art_analysis/bin:${PATH}"
source ${HOME}/art_analysis/bin/art_setting -q
```

The setting is all!

Then, the following commands (shellscript) will be downloaded.

---

### artlogin.sh

This is loaded when you command `artlogin`. This command is described in the next chapter.

### artnew

With this command, new artemis environment will be created interactively.

### art_setting

This is like a library. The shellscript function `artlogin`, `a` etc. are written.

### art_check

Checking these shellscript is updatable or not.

