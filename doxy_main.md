# Home

This is a detailed instruction about source code for developers.
For installation and usage, please go to [this page](../..) created by Hugo.

## Doxygen LISENSE

This pages are created by [doxygen](https://www.doxygen.nl/) and [Doxygen Awesome theme](https://jothepro.github.io/doxygen-awesome-css/).

Copyright © 1997-2009 by Dimitri van Heesch.

Permission to use, copy, modify, and distribute this software and its documentation under the terms of the GNU General Public License is hereby granted. No representations are made about the suitability of this software for any purpose. It is provided "as is" without express or implied warranty. See the GNU General Public License for more details.

Documents produced by doxygen are derivative works derived from the input used in their production; they are not affected by this license.

## 豆知識

日本語ですみません。ライブラリを整備している中で、気になったことをメモしておきます。
時間がある時に英語で整備し直すかもしれません。

### 1. //!の意味

プロセッサなどを作成していると、

```cpp
TClonesArray **fInData; //!
```

のようなコードに出くわすことがあるが、この最後の"//!"についてはよくわかっていなかった。
このおまじないのようなものを消すとエラーが出てくるし、調べてもDoxygenのコメント形式だというような情報しか得られずよくわからないままだった。

最近ChatGPTに聞いてみると、初めて知ったことだが、ROOTのCINTやClingインタープリタででポインタのポインタをI/Oシステムで使うことが難しく、
正しく解析できないというエラーで、//!をつけるとこのI/O処理から除外するように伝えることができるらしい。

難しくて完全には理解できていないが、ポインタのポインタをROOTで扱うのは難しいから、//!をつけるとROOTの範疇から外すという意味合いになるということなのかな???
ROOTの作法ではなく、純粋なC++な知識だけが必要なものがいいなあと感じたり。。。

### 2. ClassDefについて

ClassをDictionaryに登録するときに、ClassDefを使うが、クラスメソッドをoverrideするときにClassDefを使うと長い警告文が出てくる。

調べてみると、ClassDefにも種類があるようで、オーバーライドを使用する時には、ClassDefOverrideというものが定義されているらしい。
[情報](https://root-forum.cern.ch/t/classdef-variants/44736)の通り全てを列挙してみると、

- ClassDef: Regular
- ClassDefOverride: Use this one if your class definition use the c++ `override` keyword for virtual functions (If you use the regular ClassDef, the compiler might warn that the function declared in the ClassDef are missing the override keyword).
- ClassDefNV: Use if you class does not (and shoud not) have a virtual function table (i.e. no virtual function in the class and any of its base classes

ROOTには認識されるが、Dictionaryに登録しない場合は、

- ClassDefInline
- ClassDefInlineOverride
- ClassDefInlineNV

という書き方もできるらしいが、一応まだexperimentalらしい。

通常は、ClassDefかClassDefOverrideだけ使えば良さそうな感じかな?

### Processorの仮想関数について

TProcessorを継承して新しいプロセッサを作成するときに、オーバーライドすることができる汎用的に使えそうな(自分が使っている)クラスメソッドの一覧のメモ。

```cpp
   // InitProcメソッドで呼ばれる
   virtual void Init (TEventCollection *) {;}

   // user defined member functions to process data
   virtual void BeginOfRun() {;}
   virtual void EndOfRun() {;}
   virtual void PreProcess() {;}
   virtual void Process() {;}
   virtual void PostProcess() {;}
   virtual void PreLoop() {;}
   virtual void PostLoop() {;}
   virtual void Terminate() {;}
```

使うときは、virtual修飾子はつけなくてもよく(つけても良い)、overrideキーワードをつけておくとオーバーライドした関数であることがわかって良いかも。
この時は、ClassDefOverrideを使う。
どのタイミングでこの関数が呼ばれるかという違いがあるが、InitとProcessさえあれば行いたい処理は十分可能だと思う。

関数が呼ばれるタイミングは以下の通り。

- <add> -> Init
- -> <res> -> BeginOfRun -> PreLoop -> (PreProcess -> Process -> PostProcess) -> (PreProcess -> Process -> PostProcess) -> ...
- -> PostProcess -> PostLoop -> EndOfRun
- -> <.q> -> Terminate

途中でsusを挟んだ場合は、

- PostProcess) -> <sus> -> PostLoop -> <res> -> PreLoop -> (PreProcess -> Process -> PreProcess) -> ...

といったような順番で呼ばれる。
