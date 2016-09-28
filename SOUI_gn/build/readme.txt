添加文件列表
1.build\win_toolchain.json
2.build\common.gni

修改文件列表


1.build\config\BUILD.gn   //预编绎这里改了下，debug也改为预编了
2.build\vs_toolchain.py  //修改json路径，可以不安装vs编绎
3.build\config\win\BUILD.gn  修改默认的mt,md，改为通过指定config来设置
4.build_overrides\build.gni 定义一些全局参数
5.build\precompile.h 加了自己的预处理，这不用解释了吧

chrome代码日期：20160928