gn for soui &amp; gn demo,vs2013 and yasm 

特性
1.vs2013,vs2015 测试OK
2.支持yasm，并且支持调用系统的yasm
3.支持gtest单元测试
4.支持7z打包资源，支持加密压缩文件目录树
5.支持protobuf类自动生成


需要vs2013和vs2015的编绎相关工具的,请从我的网盘中直接下载
https://pan.baidu.com/s/1dFF7kf3
里面有两个vs2013_files.zip和vs2015_files.zip,解压到C盘即可(如果想放到其它盘需要修改build\win_toolchain.json相关配置).
目前默认是使用vs2015编绎.如需要使用vs2013编绎,请修改build目录下面相关的文件,比如vs_toolchain.py



目录说明
  gndemo
  包含完整的gn测试样例。
  soui_gn
  包含soui的gn脚本。
  考虑到google已开始在用gn替换gyp，此项目也将完全不再使用gyp。
  win_toolchain
  提取vs2013,vs2015的文件用来在未安装vs的机器上编绎

如何编绎？
　a.不依赖于系统安装的vs2013?
   goto win_toolchain dir, run python package_from_installed.py 2013
   unzip  **.zip to c:\\vs2013_files
   再自行安装wdk，然后将wdk的安装文件拷到c:\\vs2013_files\\wdk　目录里面，比如将C:\Program Files (x86)\Windows Kits\10下面的所有文件拷到c:\\vs2013_files\\wdk
  b.想使用系统安装的vs2013进行编绎?
   直接将SOUI_gn/env.bat中 Set DEPOT_TOOLS_WIN_TOOLCHAIN=1 改为 Set DEPOT_TOOLS_WIN_TOOLCHAIN=0
