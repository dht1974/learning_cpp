建议安装opensuse tumbleweed、arch 等滚动更新版本的linux，保持系统最新

没有最新编译环境的话，可以通过网站编译：https://wandbox.org/

1. prebuild_std_lib.sh 将std库进行预编译，编译结果放入gcm.cache，加快编译速度
   g++12目前对module还未完全支持，标准库还没有进行module化

2. cpp11，部分从c++11引入的新功能，现在用g++12进行编译，使用std预编译库，可以加快编译 

3. make: [Makefile:6: prebuild] Error 1 (已忽略）
   编译过程中，这个错误忽略掉就可以，是建立gcm.cache软链接时重复建立
