// /**
 // * Created by houbingshuai on 2016/12/3.
 // */
 window.onload = function() {
	// vertex program 
	var vertexShaderSource =
		"void main() { " +
		// set coordinate
		"gl_Position = vec4(0.0, 0.0, 0.0, 1.0); " + 
		// set size 
		"gl_PointSize = 10.0; " + 
		" } ";
	
	// fragment shader 
	var fragmentShaderSource = 
		"void main() { " + 
		// set color
		"gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); " + 
		"} ";
	
	// get canvas
	var canvas = document.getElementById("canvas");
	// get context
	var gl = canvas.getContext('webgl');
	if(!gl) {
		console.log("Failed to get webgl Context!");
		return;
	}
	
	// compile shader 
	var vertexShader = gl.createShader(gl.VERTEX_SHADER);
	gl.shaderSource(vertexShader,vertexShaderSource);
	gl.compileShader(vertexShader);
	
	var fragShader = gl.createShader(gl.FRAGMENT_SHADER);
	gl.shaderSource(fragShader,fragmentShaderSource);
	gl.compileShader(fragShader);
	
	// combine 
	var shaderProgram = gl.createProgram();
	gl.attachShader(shaderProgram,vertexShader);
	gl.attachShader(shaderProgram,fragShader);
	gl.linkProgram(shaderProgram);
	gl.useProgram(shaderProgram);
	
	  //绘制一个点
    gl.drawArrays(gl.POINTS, 0, 1);
	
	

    
 }
