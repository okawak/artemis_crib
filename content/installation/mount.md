---
title: "mount setting"
date: 2023-08-14T15:14:29+09:00
draft: false
author: "Kodai Okawa"
tags: ["CRIB"]
weight: 6
---

{{% badge %}}{{< signature >}}{{% /badge %}}

For the convinience, we use one directory to store raw data (ridf files) and make symbolic link to each user work directory.
So first, we need to make raw data directory.

There are three option to do so.

1. use the default SSD/HDD of analysis PC
2. use the external SSD/HDD of analysis PC (need to mount it)
3. use network file system (NFS) and mount it

1 and 2 options are mainly used for offline analysis, while 3 option is used for online analysis.

### 1. use the default SSD/HDD of analysis PC

If you have large size of main storage, the one option is easiest way.
Just like:

```shell { wrap="false" }
cd ~
mkdir data (or where you want to put)
cd data
rsync hoge (cp or scp to put the raw data)
```

The symbolic link process will be done in the next process.

### 2. use the external SSD/HDD of analysis PC (need to mount it)

When your main storage is not so large, you may think to use external storage.
For example, main storage is used for OS installation and external storage is used for experimental data.
(I think this case is for personal analysis using your own PC.)

In that case, you need to do:

1. mount the external storage
2. check and set the file permission to be able to read or write it.

The format and mount process is very depend on the situation, so please check the way in other place.
One important point is that we have output root file when we start to analysis, so it may need to make the directory for outputed root files in the external storage.

### 3. use network file system (NFS) and mount it

For online analysis, the best option is to get the data via a file server, as there is no time to transfer the raw data files each time.

This is example of CRIB system.

{{< mermaid >}}
---
title: Network system of CRIB
---
graph LR;
    A(MPV E7) --> D{<strong>DAQ main PC</strong><br></br>file server}
    B(MPV1 J1) --> D
    C(MPV2 J1) --> D
    D --> E[Analysis PC]
{{< /mermaid >}}

If you mount some storage, please not the mount point because we need the information of mount point when we configure the [new experiment environment](../../setting/new_experiment).
