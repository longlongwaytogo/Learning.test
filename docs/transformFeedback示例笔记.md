Red-book8 Transform Feedback例子理解

transform feedback 是，OpenGL管线中，的，顶点处理阶段结束之后，图元装配和光栅化之前的一个步骤。transform feedback，可以重新捕获即将装配为图元（点、线段、三角形）的顶点，然后将它们的部分或全部属性传递到缓存对象中。

transform feedback主要API

- void glGenTransformFeedbacks(GLsizei n, GLuint* ids)
- void glBindTransformFeedback(GLenum target, GLuint id)
- void glDeleteTransformFeedbacks(GLsizei n, GLuint* ids)
- GLboolean glIsTransformFeedback(GLenum id)

- void glBindBufferBase(GLenum target, GLuint index, GLuint buffer)
- void glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)

- void glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar** varyings, GLenum bufferMode)
- void glBeginTransformFeedback(GLenum primitiveMode)
- void glEndTransformFeedback()
- void glPauseTransformFeedback()
- void glResumeTransformFeedback()

红宝书（OpenGL编程指南8）中，transform feedback示例代码中的一些细节理解：  

- 并没有直接创建feedback对象，而是使用了系统默认的feedback  
- 绘制粒子时，使用两个VBO，一个用于当前绘制的数据，一个用于feedback，捕获更新后的三角形顶点和速度信息，用于下一帧的绘制数据
- 创建tbo，用于保存三角形顶点数据，此处的tbo被同时绑定到两个对象中，1. tbo被绑定到feedback中，用于捕获模型绘制的三角形数据，2. tbo被绑定到纹理对象，用于例子系统中获取三角形数据


