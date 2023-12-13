---
title: "Basic"
date: 2023-12-13T14:58:34+09:00
draft: false
author: "Kodai Okawa"
weight: 1
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

I would now like to introduce the actual analysis using the CRIB analysis server.
There are two ways to enter the analysis server, directly or remotely via ssh.
If you come to CRIB and operate the server directly, I think it is quicker to analyse using the server 
while asking the CRIB members directly as I think they are nearby.


### 1. SSH configuration

To enter the CRIB server, you need to enter the CNS network.
To do this, you need to create an account on the CNS login server.
Please contact Okawa (okawa@cns.s.u-tokyo.ac.jp) or the person responsible for CRIB [(see here)](https://www.cns.s.u-tokyo.ac.jp/crib/crib-new/home-en/index.html) and tell us that you want a login server account.

The CNS login server uses public key cryptography, so you need to send a shared key when you apply.
This section describes how to create the key, especially on MacOS.

```shell { wrap="false" }
cd # move to /Users/yourname/ (home directory)
mkdir .ssh # if there is no .ssh directory
cd .ssh
ssh-keygen
```

You will be asked a number of interactive questions after this command, all of which are fine by default (Enter).
Then you will see the pair of public-key and private-key.

```shell { wrap="false" }
ls 
id_rsa  id_rsa.pub
```

`id_rsa` is the private-key, and `id_rsa.pub` is the public-key.
The private key is important for security reasons and should be kept on your own computer.
Then, please send this public-key to the CNS member.
in MacOS, `open .` command will open a finder for that directory, so it is easy to attach it to an email from here.
In the email,

- your fullname (affiliation)
- username
- attached public-key

are needed.


Next, let's set up multi-stage ssh.
As the login server is just a jump server, it is useful to be able to ssh to the CRIB analysis server at once!
So create the following config file. The file placed in this directory is automatically read when you ssh.

```shell { wrap="false" }
cd ~/.ssh
vi config
```
```aconf { wrap="false" title="~/.ssh/config" hl_lines="2 3 13" lineNos="true" }
Host login
    HostName CNS_loginserver_hostname
    User username
    IdentityFile ~/.ssh/id_rsa
    ForWardX11Timeout 24h
    ControlPersist 30m
    ForwardAgent yes
    ControlMaster auto
    ControlPath ~/.ssh/mux-%r@%h:%p

# any name is okay
Host cribana
    HostName analysisPC_hostname
    User crib
    IdentityFile ~/.ssh/id_rsa
    ProxyCommand ssh login nc %h %p
    ForwardAgent yes
    ControlMaster auto
    ControlPath ~/.ssh/mux-%r@%h:%p
    ControlPersist 30m
```

You will be informed of the second and third lines above that we highlighted, so please change this parts.
And ask the IP address of the CRIB analysis PC to the CRIB member, and change the 13 line. 

Then you can enter the CRIB analysis PC just by
```shell { wrap="false" }
ssh cribana
```

CRIB member will tell you the passward!

For the VNC server (local forwarding), please see [this section](https://okawak.github.io/artemis_crib/setting/vncserver/index.html).



### 2. your artemis configuration
When you enter the CRIB computer, please check this is `zsh` shell.
```shell { wrap="false" }
> echo $SHELL
/usr/local/bin/zsh
```

{{% notice style="info" %}}
Currently, zsh installed locally is used. It is planned to update the OS in the future, after which it will differ from this path in the future.
{{% /notice %}}

If it is not `zsh` (like bash), please command
```shell
> zsh
```

Then you can start to configure by
```shell { wrap="false" }
> artlogin yourname
# input your information...

> mkdir build
> cd build
> cmake ..
> make -j4
> make install
> acd
```

For the detail, please check [here](https://okawak.github.io/artemis_crib/setting/new_user/index.html).

### 3. basic usage

- start artemis

```shell { wrap="false" }
> acd # move to your artemis work directory
> a # start artemis!

> a macro/macro.C # run macro script
```

- important command in the artemis console
```shell { wrap="false" }
# read steering file
artemis [*] add steering/hoge.yaml NAME=hoge NUM=0000

# start event loop
artemis [*] res
artemis [*] start # defined in CRIB artemis

# stop event loop
artemis [*] sus
artemis [*] stop # defined in CRIB artemis

# help
artemis [*] help

# quit from artemis
artemis [*] .q
```

- commands for checking histograms
```shell { wrap="false" }
# check and move the directory
artemis [*] ls
artemis [*] cd 0 # cd ID

# move to home directory in artemis
artemis [*] cd # cd .. will work?

# draw the histograms
artemis [*] ht 0 colz # ht ID option
artemis [*] hn colz # draw the next histogram object
artemis [*] hb colz # draw the previous histogram object

# divide the canvas
artemis [*] zone 2 2 # 2 x 2 canvas

# save and print the canvas
artemis [*] sa
artemis [*] pri
```

- analize using TTree
```shell { wrap="false" }
# check the files
artemis [*] fls

# move to the created ROOT file
artemis [*] fcd 0 # fcd fileID

# check the all branches
artemis [*] br

# check the data members or methods
artemis [*] br branchname # ex. artemis [1] br ppaca

# the name of TTree object is "tree" (actually TArtTree object)
artemis [*] tree->Draw("ppaca.fY:ppaca.fX>>ppaca(100,-20.,20., 100,-20.,20.)","","colz")
```


See [here](https://okawak.github.io/artemis_crib/setting/artemis_commands/index.html) for an example using random numbers.
