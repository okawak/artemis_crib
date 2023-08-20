# Github Pages
this manual is going to be made by using [HUGO](https://gohugo.io/) and [relearn theme](https://github.com/McShelby/hugo-theme-relearn).

# How to post new contents
**After checking your local environment**, please push your commits.

```shell
git clone --recursive https://github.com/okawak/artemis_crib.git -b pages-build
cd artemis_crib
hugo new chapter/hoge.md
vim content/chapter/hoge.md
hugo serve

git add content/chapter/hoge.md
git commit -m "commit message"
git push
```
