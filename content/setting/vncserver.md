---
title: "VNC server"
date: 2023-11-02T17:23:05+09:00
draft: false
author: "Kodai Okawa"
weight: 8
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

When we start the analysis, there are many situations where the analysis server on which artemis is installed is not only operated directly, but also remotely using "ssh".
In such cases, there are various settings that need to be made in order for the figure to be displayed on the local computer, and some of these methods are described in this section.
We recommended to use `VNC server` currently, but note that policies may change in the future.

This is a list of ways to display the figures.
- X11Forwarding
- VNC server
- Save figure and check by using VScode
- Web browser (THttpServer)

## X11Forwarding

This is the simplest method.
Simply transfer the remote X to the local.

```shell { wrap="false" title="your local PC"}
ssh -X analysisPC
```

This "X" option allow the X11Forwarding.

However, the problem with this method is that it takes a long time to process, and it takes longer from the time the command is typed until it is drawn.
It is also not recommended as the process can become slow if a large number of people use it at the same time.

However, it is simpler than other methods and should be used when necessary, e.g. for debugging.


## VNC server
{{% notice style="info" %}}
This is old version of VNC server (TigerVNC). Latest version supports more secure method, so this method may no longer be avaliable in the future...
{{% /notice %}}

## Save figure and check by using VScode

## Web browser (THttpServer)
