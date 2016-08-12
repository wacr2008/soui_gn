This is an example directory structure that compiles some simple targets using
gcc. It is intended to show how to set up a simple GN build.

Don't miss the ".gn" file in this directory!


1.在此文件中定义好你自己的全局变量build/app.gni
declare_args

2.最好使用sublime text 工具，gn与python很像，是要求强对齐的。
因此你在编辑gn文件时，很容易出现以下的错误。
You got a tab character in here. Tabs are evil. Convert to spaces.

然后你可以通过sublime text来查看，并修正对齐