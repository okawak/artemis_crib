---
title: "User config"
date: 2023-12-12T13:43:31+09:00
draft: false
author: "Kodai Okawa"
weight: 3
tags: ["CRIB"]
---

{{% badge %}}{{< signature >}}{{% /badge %}}

{{% notice style="warning" %}}
still under consideration in this part!
{{% /notice %}}

CRIB often wants to customise artemis because it originally used ANAPAW and wants to perform analysis like ANAPAW.
However, we do not want to make too many changes to the source code of artemis itself, and we want to make it work in the user-defined part. (it means in the **artemis work directory**)

In particular, it is often the case that we want to create a new artemis command, but writing the command source on the work directory and registering it in `artemislogon.C` did not work somehow...

Also, artemislogon.C is automatically generated (from .artemislogon.C.in) by the cmake functionality, and even if this itself is changed, it will revert when cmake is redone.


Therefore, a file called `userlogon.C` was prepared, which only took out the user-defined part from artemislogon.C.
The following files have been modified to read this.

```diff { wrap="false" title="artemis/sources/main/TArtRint.cc" lineNos="true" lineNoStart="14" }
 #include <TInterpreter.h>
+#include <TSystem.h>
 #include "TLoopManager.h"
```

```diff { wrap="false" title="artemis/sources/main/TArtRint.cc" lineNos="true" lineNoStart="44" }
    TRint::ProcessLine(".x artemislogon.C");
+   FileStat_t info;
+   if (gSystem->GetPathInfo("userlogon.C", info)==0) {
+      TRint::ProcessLine(".x userlogon.C");
+   }
```

If there is a `userlogon.C` file in the work directory, it is loaded, otherwise artemis can be used as usual.


### userlogon.C

This file can be used freely!
What we wanted to do most is to register user-defined commands, which can be done as follows.

```cpp { wrap="false" title="userlogon.C" }
{
   // User commands register
   // cf definition: TCatCmdFactory *cf = TCatCmdFactory::Instance();
   cf->Register(TCatCmdLoopStart::Instance());
   cf->Register(TCatCmdLoopStop::Instance());
   cf->Register(new art::TCmdXfitg);
   cf->Register(new art::TCmdXstatus);
   cf->Register(new art::TCmdXYblow);
   cf->Register(new art::TCmdXblow);
   cf->Register(TCatCmdTCutG::Instance());
   cf->Register(new art::TCmdErase);
   cf->Register(new art::TCmdDraw);

   // TTree merge setting
   TTree::SetMaxTreeSize( 1000000000000LL ); // 1TB
}
```
(For some reason, an error occurred when writing in artemislogon.C.)
You can also customise it in other ways to make it easier for you. For example, when creating a TTree, a setting to increase the file size limit is also included by default.
