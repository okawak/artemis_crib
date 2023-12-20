---
title: "Git"
date: 2023-12-13T15:02:26+09:00
draft: false
author: "Kodai Okawa"
weight: 9
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

Analysis files for each experiment are managed using `git`. 
This is so that they can be quickly restored if they are all lost for some reason.

`Git` is a bit complicated and you can commit freely if you are knowledgeable, but if you are unfamiliar with it, you don't have to worry too much.
The main use is that if someone creates a useful file, it will be reflected for each user as well.

Here is a brief description of how to use it.

## Directory structure

In the CRIB analysis PC, we used local repository.
The files related the repository is stored here.

```shell { wrap="false" }
> cd ~
> tree -L 1 repos/exp
repos/exp
├── he6p2024.git
├── he6p.git
└── o14a.git

# 2023/12/18 current status
```

{{% notice style="warning" %}}
Note that if you delete the files in this directory, you will lose all backups.
{{% /notice %}}


## basic commands

I will describe the most commonly used commands and how to resolve conflicts.
