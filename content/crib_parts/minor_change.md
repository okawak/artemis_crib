---
title: "Minor changes"
date: 2023-11-22T15:05:52+09:00
draft: false
author: "Kodai Okawa"
weight: 100
tags: ["CRIB"]
---

{{% badge %}}{{< signature >}}{{% /badge %}}

### thisartemis.sh.in
Grammar issue I think.
```diff { wrap="false" title="artemis/sources/main/thisartemis.sh.in" }
 export LD_LIBRARY_PATH=$TARTSYS/lib:$LD_LIBRARY_PATH

-if [ "@BUILD_GET@" == "ON" ]; then
+if [[ "@BUILD_GET@" == "ON" ]]; then
     export LD_LIBRARY_PATH=@GET_LIB_DIR@:$LD_LIBRARY_PATH
 fi

-if [ "@MPI_CXX_FOUND@" == "TRUE" ]; then
+if [[ "@MPI_CXX_FOUND@" == "TRUE" ]]; then
     dir=@MPI_CXX_LIBRARIES@
     libdir="$(dirname $dir)"
```

### xval command
Add cross hair.
```diff { wrap="false" title="artemis/sources/commands/TCatCmdXval.cc" lineNos="true" lineNoStart="84" }
 void TCatCmdXval::GetEvent()
 {
+   dynamic_cast<TPad *>(gPad)->DrawCrosshair();
    const int event = gPad->GetEvent();
```

{{< figure src="crosshair.png" width=600 >}}


### pr (projection) command
After the command, the projected histogram will automatically be displayed.

```diff { wrap="false" title="artemis/sources/commands/TCatCmdPr.cc" lineNos="true" lineNoStart="55" }
       if (!obj->InheritsFrom(TH2::Class())) {
          // TArtCore::Info("TCatCmdPr::Run","%s is not 2D histogram",
          //               obj->GetName());
+        Info("Run", "%s is not 2D histogram", obj->GetName());
          continue;
       }
+      Int_t nid = (gDirectory->GetList())->GetEntries();
       Run((TH2*) obj, opt);
+      Info("Run", "id = %d hist is created", nid);
+      TCatHistManager::Instance()->DrawObject(nid);
    }
    return 1;
 }
```

### TCatPadManager
bug???

```diff { wrap="false" title="artemis/sources/core/TCatPadManager.cc" lineNos="true" lineNoStart="232" }
 void TCatPadManager::SetCurrentPadId(Int_t id)
 {
-   if (id < 1 || id > GetNumChild()) return;
+   if (id < 0 || id > GetNumChild()) return; // mod
    fCurrentPadId = id;
 }
```
