
## 创建模式

# 1.  单例(Singleton)   [2017/8/31]

**设计模式经典GoF定义的单例模式需要满足以下两个条件：**  

- 保证一个类只创建一个实例。
- 提供对该实例的全局访问点。

## 1.1 定义：

如果系统有类似的实体（有且只有一个，且需要全局访问），那么就可以将其实现为一个单例。实际工作中常见的应用举例

日志类，一个应用往往只对应一个日志实例。
配置类，应用的配置集中管理，并提供全局访问。
管理器，比如windows系统的任务管理器就是一个例子，总是只有一个管理器的实例。
共享资源类，加载资源需要较长时间，使用单例可以避免重复加载资源，并被多个地方共享访问。


	// 延迟初始化(Lazy Singleton)  

		//头文件中
		class Singleton  
		{
		    public:
		        static Singleton& Instance()
		        {
		            if (instance_ == NULL)
		            {
		                instance_ = new Singleton;
		            }
		            return *instance_;
		         }
		    private:
		        Singleton()；
		        ~Singleton()；
		        Singleton(const Singleton&);
		        Singleton& operator=(const Singleton&);
		    private:
		        static Singleton* instance_;
		};
		//实现文件中
		Singleton* Singleton::instance_ = 0;  


实现中构造函数被声明为私有方法，这样从根本上杜绝外部使用构造函数生成新的实例，同时禁用拷贝函数与赋值操作符（声明为私有但是不提供实现）避免通过拷贝函数或赋值操作生成新实例。

提供静态方法Instance()作为实例全局访问点，该方法中先判断有没有现成的实例，如果有直接返回，如果没有则生成新实例并把实例的指针保存到私有的静态属性中。

注意，这里Instance()返回的实例的引用而不是指针，如果返回的是指针可能会有被外部调用者delete掉的隐患，所以这里返回引用会更加保险一些。并且直到Instance()被访问，才会生成实例，这种特性被称为延迟初始化（Lazy initialization），这在一些初始化时消耗较大的情况有很大优势。

Lazy Singleton不是线程安全的，比如现在有线程A和线程B，都通过instance_ == NULL的判断，那么线程A和B都会创建新实例。单例模式保证生成唯一实例的规则被打破了。

Eager Singleton

这种实现在程序开始(静态属性instance初始化)的时就完成了实例的创建。这正好和上述的Lazy Singleton相反。

		//头文件中
		class Singleton  
		{
		    public:
		        static Singleton& Instance()
		        {
		            return instance;
		        }
		    private:
		        Singleton();
		        ~Singleton();
		        Singleton(const Singleton&);
		        Singleton& operator=(const Singleton&);
		    private:
		        static Singleton instance;
		}
		//实现文件中
		Singleton Singleton::instance;  