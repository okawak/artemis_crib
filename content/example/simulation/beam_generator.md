---
title: "Beam_generator"
date: 2023-08-25T18:45:16+09:00
draft: false
author: "Kodai Okawa"
weight: 300
tags: []
---

{{% badge %}}{{< signature >}}{{% /badge %}}

The previous sections have described how to loop events from a `ridf` file or `root` file, but now I will describe how to generate events to use as a simulation.

Requirements:

- src-crib/simulation/TRandomBeamGenerator
- src-crib/simulation/TTreeBeamGenerator
- src-crib/simulation/TParticleInfo

---

As you know, an "event store" must be used to analyse the event loop.
For example, in the online analysis, we used `TRIDFEventStore`, and in the offline analysis, we used `TTreeEventStore`.

But when we want to simulate something, there are no data file.
In that case, we can use `TCounterEventStore` or `TRandomNumberEventStore`.

- TCounterEventStore: generate numbers in sequence from 0 to N.
- TRandomNumberEventStore: generate number from 0.0 to 1.0 randomly.

Here I will simply describe a simulation using TCounterEventStore.

{{% notice style="info" %}}
As I explained in `CRIB_parts` before, in the current artemis version, the TCounterEventStore does not seem to be recognised as EventStore.
So if we use this EventStore, "no event store" comments will output.
I don't think it makes problem, so it is okay comment out the part of TLoop.cc that prints "no event store".
(Possibly a problem with your environment).
{{% /notice %}}
