主要是修改支持使用系统自带的protobu,不要每次都编一把protobuf,这样好烦。。。
更重要的是公司用的还是清朝的2.3版本。懒得去为2.3的代码再写一份gn了。直接这样使用吧

1.修改proto_library.gni，官方原版改名为proto_library_bak.gni
2.添加binaries目录，就是将你自己使用的版本扔进去
