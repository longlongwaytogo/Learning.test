
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(DesignPattern)


 MACRO (DEF_APP app)
 MESSAGE( "${CMAKE_SOURCE_DIR}/${FILE_DIR}/${app}.cpp")
 add_executable(${app} ${CMAKE_SOURCE_DIR}/${FILE_DIR}/${app}.cpp)
 SET_PROPERTY(TARGET ${app} PROPERTY FOLDER ${FILE_DIR})
 endmacro()
 

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# 创建型模式
SET(FILE_DIR CreationalPattern) 
DEF_APP(Factory)   				# 工厂方法模式  
DEF_APP(AbstractFactory)		# 抽象工厂模式 
DEF_APP(Singleton) 				# 单例模式 
DEF_APP(Builder)				# 建造者模式 
DEF_APP(Prototype)				# 原型模式 


SET(FILE_DIR Structpattern)
DEF_APP(Bridge)    				# 桥接模式
DEF_APP(Adapter)   				# 适配器模式
DEF_APP(Decorator) 				# 装饰模式 
DEF_APP(Composite) 				# 组合模式
DEF_APP(Flyweight) 				# 享元模式
DEF_APP(Facade)    				# 外观模式
DEF_APP(Proxy)	   				# 代理模式

SET(FILE_DIR ActionPattern)
DEF_APP(Template)      			# 模版模式
DEF_APP(Strategy)				# 策略模式
DEF_APP(State)					# 状态模式
DEF_APP(Observe)				# 观察者模式
DEF_APP(Memento)				# 备忘录模式
DEF_APP(Mediator)				# 中介者模式
DEF_APP(Command)				# 命令模式
DEF_APP(Visitor)				# 访问者模式
DEF_APP(ChainofResponsibility)  # 责任链模式
DEF_APP(Iterator)				# 迭代器模式
DEF_APP(Interpreter)			# 解析器模式