+++
archetype = "chapter"
title = "Q&A"
weight = 5
+++

### Cannot be analysed in online mode...

When you start the event loop in online mode and artemis gets stuck, `babian` may not have been activated.
There is a shellscript to run the "babian" in cribana PC.

```shell { wrap="false" }
~/bin/run_babian
ps aux | grep babi # check if the "babian" process is working or not
```

---

### "chkridf" command shows "Rev", "Dev", "FP", "Det" and "Mod" ID, but they are different from map file configuration...?

chkridf command shows like this:
```shell { wrap="false" }
chkridf hoge.ridf
```
```plain { wrap="false" hl_lines="8" }
-- snip --

:
Segment Header / blkn=1
hd1 = 0x2100004c
ly=2, cid=4, size=76, efn=120
Segment ID = 12600853 (0x00c04615)
Rev 0 / Dev 12 / FP  1 / Det 6 / Mod 21
2000 0200 4072 0000 406c 0010 405f 0001
4068 0011 406a 0002 4053 0012 4058 0003
4058 0013 4051 0004 4066 0014 404d 0005
4047 0015 4045 0006 4056 0016 405a 0007
404b 0017 4050 0008 406c 0018 404b 0009
4069 0019 4059 000a 4051 001a 404e 000b
405f 001b 4064 000c 4052 001c 4033 000d
4055 001d 4064 000e 4067 001e 4043 000f
4052 001f 1dd2 0401 1dd2 0601

-- snip --
```


---
