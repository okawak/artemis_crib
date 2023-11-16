---
title: "Analysis environment"
date: 2023-11-16T16:36:56+09:00
draft: false
author: "Kodai Okawa"
weight: 1
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

CRIB shares the analysis environment of all experiments under one user account (username crib).
Therefore, when you want to check data from an old experiment or when several people are analysing the data, you need to log in to the same user account.

Of course, the analysis environment varies according to the experiment (and even different environments for different users within the same experiment!) and these have to be managed well.
The ".bashrc/.zshrc" and "artlogin (artlogin2)" commands set them up.
Currently we are using "zsh (.zshrc)".

#### Experimental environment

```shell { wrap="false" title=".bashrc/.zshrc" }
export EXP_NAME="current" # your experiment
export EXP_NAME_OLD="previous" # old experiment
```

The `EXP_NAME` is current experiment and you can enter the environment by using `artlogin` command.
At the same time, the `EXP_NAME_OLD` is the old experiment and you can use `artlogin2` command.

In the current version, we support two experimental environment and if you want to check other experimental data, please change `EXP_NAME_OLD`.

{{% notice style="warning" %}}
When you modify ".bashrc/.zshrc", all people's settings will change.
Therefore please do not change `EXP_NAME` as much as possible, because we want to set this environment variable as the active experiment.
If you change this, please report it so that CRIB members are aware of it.
{{% /notice %}}

{{% notice style="info" %}}
Commands may be created in the future to enter the environment of all experiments flexibly, not just two. (like artoldlogin {expname} {username}?)
{{% /notice %}}

Then you can enter the different analysis environment like this:

```shell { wrap="false" }
> artlogin (username)
> artlogin2 (username)
```

#### User environment

CRIB uses a default user as well as individual analysis environments.
The username of the default user is the same with experiment name.

If you set the name of the experiment to "si26a" (`EXP_NAME`), then the username "si26a" will be the default user.
The user's environment can be entered with the "artlogin" command with no arguments.

```shell { wrap="false" }
> artlogin
> pwd
/home/crib/art_analysis/si26a/si26a
```

If you want to test something by changing files, or if you want to use your own VNC server, you can enter that environment by specifying its name as an argument.

```shell { wrap="false" }
> artlogin okawa # if this is the first time to command, you will see setup comments.
> pwd
/home/crib/art_analysis/si26a/okawa
```

{{% notice style="warning" %}}
When using the default user, try to avoid using a VNC server (do not create .vncdisplay files).
The main reason for creating a default user is to analyse locally (for shifters) in the online analysis, and using a VNC server makes it impossible to view the figures locally.
{{% /notice %}}


#### Directory structure

The directory structure comprising artemis is as follows.
(The location of artemis itself is omitted).

```shell { wrap="false" }
> tree -L 2 ~/art_analysis
/home/crib/art_analysis
├── current # accessed by "artlogin"
│   ├── current # default user
│   └── okawa # individual user
├── previous # accessed by "artlogin2"
│   ├── previous
│   └── okawa
├── old1
│   ├── old1
│   └── okawa
└── old2

# -- snip --
```
