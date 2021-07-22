# 2021/06/24
# 跨平台开发方案验证


# 1 使用vs2015+qt+gdb 


# 创建


1. 安装qt
1.1 下载qt安装包： qt-opensource-linux-x64-5.12.10.run
1.2 chmod +x qt-opensource-linux-x64-5.12.10.run
1.3 进入root管理员权限，执行 ./qt-opensource-linux-x64-5.12.10.run
1.4 安装 gcc g++ make   
	sudo apt-get  install build-essential
	
1.5 安装mesa驱动 ：sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev
1.6 安装mesa sudo apt-get install mesa-common-dev

1.7 配置环境变量：
	在home目录，执行gedit .bashrc,（或：gedit ~/.bashrc）添加：
	
	export QTDIR=/opt/Qt/Qt5.12.10/5.12.10/gcc_64
	export PATH=$QTDIR/bin:$PATH  
	export MANPATH=$QTDIR/man:$MANPATH  
	export LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH
	
	刷新 bashrc
	用户对 bashrc 所作的任何更改将在您下次启动终端时应用，如果想立即生效可以手动执行如下命令刷新：
	
		source ~/.bashrc

1.8 修改qt chooser

什么是qtchooser
qtchooser其实和jdk版本管理软件一样,是一个qt版本管理软件.用于设置安装多个qt的系统中默认使用的qt版本.我们知道环境变量有一个缺陷:一次只支持一个版本的qt,有的应用可能只兼容低版本qt,这样又要配置环境变量非常麻烦.使用qtchooser方便快速切换qt版本而又不用每次重新配置环境变量

方法1
我们只需要在它的配置目录里将默认配置文件修改即可:

cd /usr/lib/x86_64-linux-gnu/qt-default/qtchooser
sudo nano default.conf


1.9
安装ssh服务
sudo apt-get install openssh-server
启动ssh服务
sudo /etc/init.d/ssh start
设置开机自启动
sudo systemctl enable ssh
关闭ssh开机自动启动命令
sudo systemctl disable ssh
单次开启ssh
sudo systemctl start ssh
单次关闭ssh
sudo systemctl stop ssh
设置好后重启
reboot
————————————————
版权声明：本文为CSDN博主「淦123」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/weixin_40700617/article/details/90780009


1.10 安装gcc
sudo apt-get install gcc
