# gl_NormalMatrix理解：

  法线矩阵：G
  模型视图矩阵：M 
   则：		
		G: = M逆矩阵的转置矩阵
		
	若： M是正交矩阵，M的逆矩阵= M的转置矩阵
	所以，当没有Scale变换时，（只存在Rotate、Transform变换）
	ModelView = G 
		
		http://www.songho.ca/opengl/gl_normaltransform.html
		https://www.cnblogs.com/hefee/p/3817397.html
		
	OSG中计算 gl_NormalMatrix:
	
	if (_normalMatrixUniform.valid())
    {
        Matrix mv(*_modelView);
        mv.setTrans(0.0, 0.0, 0.0); // 法线与平移无关，可以去掉

        Matrix matrix;
        matrix.invert(mv); // 求逆矩阵
		// 进行转置变换
        Matrix3 normalMatrix(matrix(0,0), matrix(1,0), matrix(2,0),
                             matrix(0,1), matrix(1,1), matrix(2,1),
                             matrix(0,2), matrix(1,2), matrix(2,2));

        _normalMatrixUniform->set(normalMatrix);
    }