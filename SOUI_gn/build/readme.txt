添加文件列表
1.build\win_toolchain.json  支持不安装vs2013也可以编绎
2.build\common.gni  加入safeseh开关

修改文件列表
1.build\config\BUILD.gn   //预编绎这里改了下，debug模式也改为使用预编了
2.build\vs_toolchain.py  //修改json路径，可以不安装visual studio ide了
3.build\config\win\BUILD.gn  修改默认的mt,md，改为通过指定config来设置
4.build\precompile.h 加了自己的预处理，这不用解释了吧
5.build_overrides\build.gni 定义一些全局参数

chrome代码日期：20161011