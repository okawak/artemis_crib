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

### TModuleInfo class

In the CRIB processor, there is a processor that inherits from TModuleInfo, [TModuleData](https://github.com/okawak/artemis_crib/blob/main/src-crib/TModuleData.h).
In the constractor of this class use `copy constractor` of TModuleInfo, but the default artemis doesn't implement it.
This class is used when we want to check the raw data.
For the detail, please see [check raw data page](https://okawak.github.io/artemis_crib/example/online_analysis/check_rawdata/index.html).

Therefore, we modified this like this:
```diff { wrap="false" title="artemis/sources/loop/TModuleInfo.cc" lineNos="true" lineNoStart="31" }
  TModuleInfo::TModuleInfo(const TModuleInfo& rhs)
+   : TParameterObject(rhs),
+   fID(rhs.fID),
+   fType(rhs.fType),
+   fHists(nullptr)
  {
+   if (rhs.fHist) {
+     fHists = new TObjArray(*(rhs.fHists));
+   }
+
+   fRanges = rhs.fRanges;
  }
```

<!--
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
-->
