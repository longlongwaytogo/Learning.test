1. qt 调试输出窗口乱码解决：

如果再勾选了“Force UTF-8 MSVC compiler output”， ，去掉此勾选
https://blog.csdn.net/fxfeixue/article/details/108790539


cmake 创建qt工程
https://blog.csdn.net/qq_40181592/article/details/101623231

[Build C++ Applications in a Linux Docker Container with Visual Studio](https://devblogs.microsoft.com/cppblog/build-c-applications-in-a-linux-docker-container-with-visual-studio/)


cmake 远程调试linux 需要输入一下命令：
echo 0| sudo tee /proc/sys/kernel/yama/ptrace_scope
参考：https://github.com/Microsoft/MIEngine/wiki/Troubleshoot-attaching-to-processes-using-GDB

安装和设置 Linux 工作负载
https://docs.microsoft.com/zh-cn/cpp/linux/download-install-and-setup-the-linux-development-workload?view=msvc-160&viewFallbackFrom=vs-2019#linux-setup-ubuntu-on-wsl

linux 打包：
https://blog.csdn.net/zyhse/article/details/106381937