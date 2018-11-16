// demo.js 

var canvas;
var gl;
var texture;
var uFrame;
window.onload = init;

function CheckError(msg) {
    var error = gl.getError();
    if(error != 0)
    {
        var errMsg = "OpenGL error: " + error.toString(16);
        if(msg) { errMsg = msg + "\n" + errMsg;}
        alert(msg);
    }
}

function configureTexture(image) {
   // debugeger;
    texture = gl.createTexture();
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, texture);
    gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, image);
    //gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, 240, 100, 0, gl.RGB, gl.UNSIGNED_BYTE, image);
    gl.generateMipmap(gl.TEXTURE_2D);
   // gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER,gl.NEAREST_MIPMAP_LINEAR);
    gl.texParameteri( gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
    gl.texParameteri( gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
}

function init() {
    canvas = document.getElementById("gl-canvas");
    gl = WebGLUtils.setupWebGL(canvas);
    if(!gl) { alert("WebGL isn't available");}
    gl.viewport(0,0,canvas.clientWidth, canvas.height);
    gl.clearColor(1.0, 0.0, 0.0, 1.0);

    // read shader and init property arrays
    var program = InitShaders(gl, "vertex-shader", "fragment-shader");
    gl.useProgram(program);

    var vertices = {};
    vertices.data = new Float32Array(
        [ -0.5, -0.5,
           0.5, -0.5,
           0.5,  0.5,
          -0.5,  0.5 
        ]);

    vertices.bufferId = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vertices.bufferId);
    gl.bufferData(gl.ARRAY_BUFFER, vertices.data,gl.STATIC_DRAW);
    var vPos = gl.getAttribLocation(program,"vPos");
    gl.vertexAttribPointer(vPos,2,gl.FLOAT,false,0,0);
    gl.enableVertexAttribArray(vPos);

    var texCoords = {};
    texCoords.data = new Float32Array(
        [
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,
            0.0, 1.0
        ]);

        texCoords.bufferId = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, texCoords.bufferId);
        gl.bufferData(gl.ARRAY_BUFFER, texCoords.data,gl.STATIC_DRAW);
        var vTexCoord = gl.getAttribLocation(program, "vTexCoord");
        gl.vertexAttribPointer(vTexCoord, 2, gl.FLOAT,false,0,0);
        gl.enableVertexAttribArray(vTexCoord);

        // init text 
        var image = new Image();
        image.onload = function() {
            configureTexture(image);
            render();
        }
        image.crossOrigin="";
       //image.crossOrigin = "anonymous";
       //image.src = "I:\\co\\Learning.test.git\\GFX\\webgl\\webGL\\deom2\\tiles.jpg";
       //image.src="tiles.jpg";
       image.src="https://raw.githubusercontent.com/longlongwaytogo/Learning.test/master/GFX/webgl/webGL/deom2/ypos.jpg";
       //image.src="https://www.khronos.org/assets/uploads/ceimg/made/assets/uploads/apis/WebGL_100px_June16_180_75.png"
       // image.src="https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1542279463670&di=471eaa742343829cfa4dd53b818202d3&imgtype=0&src=http%3A%2F%2Fpic.qiantucdn.com%2F58pic%2F16%2F91%2F94%2F87Z58PIC3zb_1024.jpg";
       
       gl.activeTexture(gl.TEXTURE0);
       var uTexture = gl.getUniformLocation(program, "uTexture");
       gl.uniform1i(uTexture,0);
       uFrame = gl.getUniformLocation(program, "uFrame");
}

var frameNumber = 0;

function render() {
    gl.uniform1f(uFrame,frameNumber++);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    window.requestAnimationFrame(render, canvas);
}