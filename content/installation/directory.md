---
title: "Directory"
date: 2023-08-14T15:14:29+09:00
draft: false
author: "Kodai Okawa"
weight: 5
---

{{% badge %}}{{< signature >}}{{% /badge %}}

For the convinience, we use one directory to store raw data (ridf files) and make symbolic link to each user work directory.
So first, we need to make raw data directory.

There are three option to do so.

1. put the files in the same storage
2. put the files in the external storage
3. use network file system (NFS) and mount it (like xfs)

If you have large size of main storage, the one option is easiest way.
Just like:

```shell
cd ~
mkdir data (or where you want to put)
cd data
rsync hoge (cp or scp to put the raw data)
```

The symbolic link process will be done in the next process.

---

When your main storage is not so large, you may think to use external storage.
For example, main storage is used for OS installation and external storage is used for experimental data.
(I think this case is for personal analysis using your own PC.)

In that case, you need to do:

1. mount the external storage
2. check and set the file permission to be able to read or write it.

The format and mount process is very depend on the situation, so please check the way in other place.
One important point is that we have output root file when we start to analysis, so it may need to make the directory for outputed root files in the external storage.

---

When you have file server, we can use network file system (NFS).
This is CRIB online analysis case, so let me explain it in detail.

{{< mermaid >}}
---
title: Network system of CRIB
---
graph LR;
    A(MPV E7) --> D{<strong>DAQ main PC</strong><p></p>file server}
    B(MPV1 J1) --> D
    C(MPV2 J1) --> D
    D --> E[Analysis PC]
{{< /mermaid >}}

As this figure, we use file server in the DAQ main PC.

#### server setting

Actually now the PC is CentOS7, but for future setting, I will note the setting for newer OS.
First, please install required package.

```shell
sudo dnf install -y rpcbind nfs-utils
```

Then prepare the directory for share.
Any name and place is okay.

```shell
mkdir /share or /data 
```

And setting file for nfs is `/etc/exports`, and here is the example.

```
/share/exp1 192.168.0.5/10(rw,no_root_squash,async)
mkdir /share or /data 
```


#### cliant setting
