# 安装Vulkan基本环境
## 获取Vulkan调用接口有三种方式：
- 可以动态加载驱动程序的库来提供 Vulkan API 实施，并自己获取它提供的函数指示器。
- 可以使用 Vulkan SDK 并链接至提供的 Vulkan Runtime (Vulkan Loader) 静态库。
- 可以使用 Vulkan SDK，在运行时动态加载 Vulkan Loader 库，并通过它加载函数指示器。

常用的未动态加载Vulkan库。

### 动态load vulkan 运行库步骤：
1. 加载 Vulkan Runtime 库并获取导出函数指示器 

2. Instance表示具体的Vulkan应用。在一个应用程序中可以创建多个实例，这些实例之间相互独立，互不干扰。
3. 创建好Instance，就可以用Instance枚举所有可用的Vulkan GPU设备。
4. 有了GPU设备，就可以获取具体GPU的信息。如果系统中安装了多个GPU设备，就可用GPU信息比较GPU设备之间的兼容性等
5. 找到了合适的GPU后，就可以通过GPU创建设备示例。
notes:
6. 有了设备，就可以创建命令队列。命令队列是与设备绑定的，不能跨设备使用。

7. 队列封装了图形、计算、直接内存访问功能，独立调度、异步等调度操作。


8. Command Buffer

有了设备，就可以创建命令缓冲。命令缓冲是绘制命令的批次集合。

用户可创建任意多的命令缓冲，支持在多线程中创建。

Command占用的内存是通过Command Buffer内存池动态分配，不需要指定内存池的大小。

9. Command
在命令缓冲区中可以创建多个命令。多个命令完成批次即命令缓冲后，可以重复利用。

这里有点像OpenGL里面的NameList。

Command Buffer的操作使用pipeline bARrier区分。barrier可以等待和触发事件。


注：

这里可以看出Command被包装在Command Buffer中，当把Command Buffer提交给Queue中后，Queue中执行的是Command Buffer中的Command。

另外，Command Buffer和Queue的类别需要匹配，否则不能正确执行，但一个Command Buffer并不会跟任何Queue有联系。也就意味着，一个Command Buffer可以被提交给多个Queue，只要他们的类别匹配。

Shaders
使用设备创建Shader。

同样支持多线程。

Pipeline
渲染管线同样需要设备创建。

渲染管线状态包括：Shaders，混合、深度、剔除、模版状态等。

另外Vulkan提供了API保存和加载渲染管线的状态。

Descriptors
Vulkan资源都用descriptor表示, descriptor分成descriptor set，descriptor set从descriptor pool分配。

每个descriptor set都有个layout布局，布局是在pipeline创建的时候确定的。layout在descriptor set 和pipeline之间共享，并且必须匹配。

pipeline可以切换使用相同layout的descriptor set。

多个不同layout的set可以组成链在一个pipeline中使用。

Render Pass
Render Pass表示一帧的某个阶段，包含了绘制过程中的很多信息，包括：

- Layout和framebuffer attachment的类型

-Render Pass在开始和结束的时候该做什么

-Render Pass影响framebuffer的区域-分块渲染和延迟渲染需要的信息


Drawing
Draws位于Render Pass内，在Command Buffer的上下文中执行。支持多种绘制类型：基于索引的和非索引的，直接的和间接的等

多线程支持
同步
使用事件同步任务，可以设置、重置、查询和等待事件。

Command Buffer执行完成后可以触发事件。

任务队列
任务在设备所属的队列中执行，准备好的Command buffer送到队列中执行。

队列保留内存，驱动不负责管理内存，同样由程序管理。

队列可以触发事件，等待信号量。

Presentation
展现就是如何在屏幕上显示图片。

可显示的资源使用与framebuffer绑定的“图片”展现，由与平台相关的模块创建，即所谓的窗口系统接口WSI。

WSI用了列举系统的显示设备和视频模式，全屏，控制显示垂直同步等。

Presenta跟命令缓冲一起进入队列。

资源创建和释放
资源包括CPU资源和GPU资源。

CPU资源通过vkCreate创建，GPU资源由vkAllocMemory创建，由vkBindObjectMemory与CPU对象绑定。

应用程序负责Vulkan对象的析构，需要保证顺序。Vuilkan资源没有引用计数机制，都需要显式释放。

http://blog.csdn.net/zhw_giser/article/details/69567526
http://imgtec.eetrend.com/blog/7483
http://blog.csdn.net/graphics_521/article/details/50855277
宏定义时，不能出现空行


file:///D:/VulkanSDK/1.0.42.2/Documentation/Tutorial/html/04-init_command_buffer.html