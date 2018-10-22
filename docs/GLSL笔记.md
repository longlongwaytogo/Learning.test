GLSL  着色语言中的一些知识笔记


### Uniforms（前辍修改）
  - Uniform前辍修饰的变量初始值由外部程序赋值。在program中具有统一访问空间，存储空间有限。在Shader中是只读的，只能由外部主机程序传入值。
  - 它用于存储shader需要的各种数据，如：变换矩阵、光照参数和颜色。基本上，对于Shader是一个常量，但在编译时其值未知，则应当作为一个uniform变量。
 - Uniform变量在Vertex Shader和Fragment Shader之间共享。当使用glUniform***设置了一个uniform变量的值之后，Vertex Shader和Fragment Shader中具有相同的值。
  - Uniform变量被存储在GPU中的“常量存储区”，其空间大小是固定的，可通过API<glGetIntegerv>查询（GL_MAX_VERTEX_UNIFORM_VECTORS 或 GL_MAX_FRAGMENT_UNIFORM_VECTORS ）。

### Attributes（前辍修改） [早期OpenGL版本中使用该字段]
  - Attribute变量是只能在vertex shader中使用的变量。（它不能在fragment shader中声明attribute变量，也不能被fragment shader中使用）
  - Attribute前辍修饰的变量定义的是每个Vertex的属性变量，包括位置，颜色，法线和纹理坐标
  - Attribute 类型的变量在Vertex Shader中是只读的，只能由外部主机程序传入值。
  - Attribute 类型的变量：是为每个被正在画的顶点所指定的数据。在画图前，每个顶点的属性由应用程序输入。
  - 与Uniform变量一样，其存储数量也是有限制的。可用glGetIntegerv（GL_MAX_VERTEX_ATTRIBS）进行查询。GPU至少支持8个属性，所以Vertex Shader源码中不要超过8个attributes。 
  -  在application中，一般用函数glBindAttribLocation（）来绑定每个attribute变量的位置，然后用函数glVertexAttribPointer（）为每个attribute变量赋值。 可以使用glBindAttribLocation进行属性索引绑定。
 
### Varyings [早期OpenGL版本中使用该字段]
   - Varying变量用于存储Vertex Shader的输出和Fragment Shader的输入,它起到数据转递的作用。一般vertex shader修改varying变量的值，然后fragment shader使用该varying变量的值。因此varying变量在vertex和fragment shader二者之间的声明必须是一致的

   - 与Uniform和Attribute一样，其存储数量也是有限制的，可用glGetIntegerv（GL_MAX_VARYING_VECTORS）进行查询。GPU至少支持8个Varying vector，所以Vertex Shader源码中不要超过8个Varying vector。

		 GLint maxVertexAttribs; // n will be >= 8
		 glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
	
### Vertex Attributes  
	 
1、  **常量顶点属性（Constant Vertex Attribute）**

   常量顶点属性对所有顶点都是一样的。因此只需要指定一个值就可以应用于所有顶点。一般很少使用。其设置函数有
 
	void glVertexAttrib1f(GLuint index, GLfloat x);   
	void glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y);  
	void glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z);  
	void glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z,GLfloat w);  
	void glVertexAttrib1fv(GLuint index, const GLfloat *values);  
	void glVertexAttrib2fv(GLuint index, const GLfloat *values);  
	void glVertexAttrib3fv(GLuint index, const GLfloat *values);  
 


2、  **如何装载顶点数据？（Vertex Arrays）**

 Vertex Array（顶点数组）：是一个存储在应用程序空间（Client）中的内存buffer，它存储了每个顶点的属性数据。    

  如何把顶点数据组的数据传递给GPU呢？

        void glVertexAttribPointer(GLuint index,

                                                GLint size,     //每个属性元素个数有效值1-4（x,y,z,w）
                                                GLenum type, //数组中每个元素的数据类型
                                                GLboolean normalized,
                                                GLsizei stride, //如果数据连续存放，则为0或       

                                                                       //size*sizeof(type)
                                                const void *ptr)  //顶点数组指针




reference:  
[https://www.cnblogs.com/sanjin/p/3580331.html]()    
[https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glBindAttribLocation.xml]()  
[https://blog.csdn.net/jeffasd/article/details/78209965]()  
[https://blog.csdn.net/racehorse/article/details/6634830]()  
