---
title: "Online-mode analysis"
date: 2023-12-12T13:13:43+09:00
draft: false
author: "Kodai Okawa"
weight: 2
tags: ["CRIB"]
---

{{% badge %}}{{< signature >}}{{% /badge %}}

We often use “nssta” (non-save mode start) analysis in the beam tuning. 
It is not necessary to take data, but we need to check the beam condition by using artemis.
In this case, `TRIDFEventStore` can be used as online mode.

By default, if we don't add an input file name and set the SHMID (Shared Memory ID), artemis will use online mode.
However, it is necessary to use different types of steering files, one for use in online-mode and the other for use from a file, which can be complicated...

Therefore, the same steering file was changed to automatically go online mode when the ridf file was not present.

```shell { wrap="false" }
# from ridf files
artemis [0] add steering/hoge.yaml NAME=hoge NUM=0000
```

```shell { wrap="false" }
# online-mode
artemis [0] add steering/hoge.yaml # no argument
```

To achieve this, the original file was changed as follows.
```diff { wrap="false" lineNos="true" lineNoStart="129" title="artemis/sources/loop/ridf/TRIDFEventStore.cc" }
    for (Int_t i=0; i!=n;i++) {
       printf("file = %s\n",fFileName[i].Data());
+      if(!gSystem->FindFile(".", fFileName[i])) {
+         Info("Init", "No input file -> Online mode");
+         fIsOnline = kTRUE;
+      }
    }
```



#### steering file
We always use SHMID=0, so it works simply by adding the following sentence.

```yaml { wrap="false" hl_lines="7" }
   - name: ridf
     type: art::TRIDFEventStore
     parameter:
       OutputTransparency: 1
       InputFiles:
         - *input
       SHMID: 0
```
