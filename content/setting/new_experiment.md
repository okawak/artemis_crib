---
title: "New experiment"
date: 2023-11-02T13:58:35+09:00
draft: false
author: "Kodai Okawa"
weight: 1
tags: ["CRIB"]
---

{{% badge %}}{{< signature >}}{{% /badge %}}

If you installed with "curl" command explained previous chapter, you should have `artnew` command.
This command will make new experiment directory interactively.

Before using this command, please check and make the **directory structure**!

- rawdata directory (like /mnt/data or /data? Create it to suit your situation.)
- output rootfile directory (like /data/art_output?)
- git repository
  - local repository: suit for online analysis
  - remote repository: suit for offline analysis


---

### Let's start "artnew" command!
The word after ":" is your input.

```shell { wrap="false" }
> artnew
```

1. Input the experiment name

```txt { wrap="false" }
create new artemis work directory? (y/n): y
Input experimental name: test
Is it OK? (y/n): y
Input value: test
```

2. Check the base directory (default value is fine!)
**If there are no input, the default value will be used**.

```txt { wrap="false" }
artnew: If no input is provided, the default value is used.
Input repository path or URL (default: https://github.com/okawak/artemis_crib.git):
Is it OK? (y/n): y
Input value: https://github.com/okawak/artemis_crib.git
```

3. Input the rawdata directory

```txt { wrap="false" }
Input rawdata directory path (default: /data/test/ridf):
Is it OK? (y/n): y
Input value: /data/test/ridf
```

4. Input the output directory

```txt { wrap="false" }
Input output data directory path (default: /data/test/user):
Is it OK? (y/n): y
Input value: /data/test/user
```

5. Input the git setting (PLEASE MAKE your own repository. Local repository will be fine)

```txt { wrap="false" }
Based on the repository, do you make your own repository? (y/n): y
is it local repository (y/n): y
artnew: making LOCAL repository of test
Input the local repository path (default: $HOME/repos/exp):
Is it OK? (y/n): y
Input value: /home/crib/repos/exp

-- snip --

art_analysis setting for test is finished!
```

The initial setting is completed!!

