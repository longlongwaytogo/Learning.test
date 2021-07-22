# 2021/06/24
# ubuntu环境配置
1. 安装gnu开发环境：

	sudo apt update
	sudo apt install build-essential
	
	用gcc -v 和g++ -v。来判断gcc和g++的版本是否安装成功。
	
2. 创建root账号：
	sudo passwd root // 首次安装ubuntu需要手动创建root账户
	
3。 Ctrl +h 显示隐藏文件

4. 安装fsearch
FSearch安装
您可以在「终端」中执行如下命令安装 FSearch 搜索工具：

sudo add-apt-repository ppa:christian-boxdoerfer/fsearch-daily
sudo apt update
sudo apt install fsearch-trunk