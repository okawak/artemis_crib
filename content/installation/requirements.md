---
title: "Requirements"
date: 2023-08-14T13:36:14+09:00
author: "Kodai Okawa"
draft: false
weight: 1
---

{{% badge %}}{{< signature >}}{{% /badge %}}

The following machines have been tested for operation.

### CRIB's analysis machine

- Ubuntu 22.04.4 LTS
- gcc 11.4.0
- cmake 3.22.1
- ROOT 6.30/04
- yaml-cpp 0.7

---

NOTE:
- From 2023/10, Ubuntu system is also avaliable. ([issue48](https://github.com/artemis-dev/artemis/pull/48))
- Installation seems to be difficult on `macOS` (because of `clang` not `gcc`) in the current version.
- We have confirmed that it works on RedHat-based Linux (Alma linux).
