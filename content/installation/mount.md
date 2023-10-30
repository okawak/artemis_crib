---
title: "Mount setting"
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

```shell
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

As this figure, we use file server in the DAQ main PC.

##### 3.1 server setting

The OS of the DAQ PC is CentOS7, but I think it can be applied for current OS. (like `yum` -> `dnf`)
First, please install required package.

```shell
sudo yum install -y rpcbind nfs-utils
```

Then prepare the raw data file directory for sharing.

```shell
mkdir /data (any location) 
```

And setting file for nfs is `/etc/exports`, and here is the example.

```
/data 192.168.1.5
/data 192.168.2.0/24(rw)
```

The first one means the host of 192.168.1.5 can access the shared directory "/data".
In the default setting, users cannot write to this directory.

The host of the second line means the range that can access.
If we add `rw` option, users can write to this directory.
For the other options, please check [the official site](https://access.redhat.com/documentation/ja-jp/red_hat_enterprise_linux/7/html/storage_administration_guide/nfs-serverconfig).

Finally, the following command is used to reflect the settings.

```shell
firewall-cmd --permanent --zone=public --add-service=nfs
firewall-cmd --reload
systemctl start rpcbind
systemctl enable rpcbind
systemctl start nfs
systemctl enable nfs
```

If you do not have a firewall set up, you do not need the relevant commands.

##### 3.2 client setting

The package is also needed for client PC.

```shell
sudo yum install -y nfs-utils
```

Prepare the mounted directory and mount it.

```shell
mkdir /mnt/data
sudo mount -t nfs host_IP_address:/data /mnt/data
df -h
```
If you see the mounted configuration, your nfs configuration is complete.

To reflect the mount settings when the system is rebooted, add a setting to `/etc/fstab`.

```diff { title="/etc/fstab" }
+ host_IP_address:/data   /mnt/data   nfs   defaults   0 0
```

```shell
sudo mount -a
```






