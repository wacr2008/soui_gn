添加文件列表
1.build/win_toolchain.json  支持不安装vs2013也可以编绎
2.build_overrides/common.gni  加入safeseh开关,use_system_yasm开关

修改文件列表
1.build/config/pch.gni   //预编绎这里改了下，非!is_official_build模式下编绎也改为使用预编了
2.build/vs_toolchain.py  //修改json路径，可以不安装visual studio ide了
3.build/config/win/BUILD.gn debug默认关了INCREMENTAL 加入enable_safeseh开关，默认是关了它的，修改默认的mt,md，改为通过指定config来设置,区分2013，2013不使用什么fastfail之类的编绎优化，警告太多烦
4.build/precompile.h 加了自己的预处理，这不用解释了吧
5.build_overrides/build.gni 定义一些全局参数
6.build/config/compiler/BUILD.gn加入vs版本号检查，vs2013就不要用utf8了  cflags += [ "/utf-8" ]
7.third_party/yasm_assemble.gni加入use_system_yasm开关，可以使用系统的yasm,不用每次都编一把。
 
基于chromium代码日期：20170104
