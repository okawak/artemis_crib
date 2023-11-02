---
title: "new_user"
date: 2023-11-02T14:42:56+09:00
draft: false
author: "Kodai Okawa"
weight: 2
tags: ["CRIB"]
---

{{% badge %}}{{< signature >}}{{% /badge %}}

After `artnew` command, you can see new directory of config files.

```diff { wrap="false" }
 > tree -a art_analysis
 art_analysis
 ├── .conf
 │   ├── artlogin.sh
+│   └── test.sh
 ├── bin
 │   ├── art_check
 │   ├── art_setting
 │   └── artnew
+└── test
```

This is experiment name "test" example.
In order to load this script `test.sh`, please modify "EXP_NAME" environment valiable in .zshrc.

```shell { title=".bashrc/.zshrc" wrap="false" }
export EXP_NAME="test" # your experiment
```

And load the config file.

```shell { wrap="false" }
> source ~/.zshrc
```

Then you can make your own work directory by using `artlogin` command!

### Let's start "artlogin" command!

For example, let's make default user (user name is the same with experiment name)!

```shell { wrap="false" }
> artlogin
```

If you want to make your own directory, the following will work.

```shell { wrap="false" }
> artlogin yourname
```

1. Check if you really want to make your work directory

```txt { wrap="false" }
artlogin: user 'test' not found.
create new user? (y/n): y
Cloning into '/Users/okawa/art_analysis/test/test'...
done.
```

2. Git setting

```txt { wrap="false" }
artlogin: making local git config
Input fullname: KodaiOkawa
Is it Okay? (y/n): y
Input email address: okawa@cns.s.u-tokyo.ac.jp
Is it Okay? (y/n): y
```

3. Symbolic link setting. If there are no problem, the current directory move to your artemis work directory

```shell { wrap="false" }
> pwd
/home/crib/art_analysis/test/test
> ls -l
```

If your synbolic link seems okay, the setting is all!

---

If `artnew` setting have problem, the error message will appear.
Typical examples are as follows.

```txt { wrap="false" }
mkdir: /data: Read-only file system
```

This is a case of the directory permissions not being set correctly.
Use the `chmod` command or similar to set them correctly and try again.




