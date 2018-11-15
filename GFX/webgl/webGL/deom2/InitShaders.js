// InitShaders.js

function InitShaders( gl, vertexShaderId, fragmentShaderId)
{
    var vertShader;
    var fragShader;

    var vertElem = document.getElementById(vertexShaderId);
    if(!vertElem) {
        alert("Unable to load vertex shader"  + vertexShderId);
        return -1;
    }
    else {
        vertShader = gl.createShader(gl.VERTEX_SHADER);
        gl.shaderSource(vertShader, vertElem.text);
        gl.compileShader(vertShader);
        if(!gl.getShaderParameter(vertShader,gl.COMPILE_STATUS)) {
            var ms = "Vertex shader failed to compile." + "The error log is:"
            + "<pre>" + gl.getShaderInfoLog(vertShader) + "</pre>";
            alert(msg);
            return -1;
        }
    }

    var fragElem = document.getElementById(fragmentShaderId);
    if(!fragElem) { 
        alert("Unable to load vertex shader " + fragmentShaderId);
        return -1;
    }
    else {
        fragShader = gl.createShader(gl.FRAGMENT_SHADER);
        gl.shaderSource(fragShader,fragElem.text);
        gl.compileShader(fragShader);

        if(!gl.getShaderParameter(fragShader,gl.COMPILE_STATUS)) {
            var msg = "Fragment shader failed to compile. " + "The error log is:" 
            + "<pre>" + gl.getShaderInfoLog(fragShader) + "</pre>";
            
            alert(msg);
            return -1;
        }
    }
    
    var program = gl.createProgram();
    gl.attachShader(program, vertShader);
    gl.attachShader(program, fragShader);
    gl.linkProgram(program);

    if(!gl.getProgramParameter(program, gl.LINK_STATUS)) {
        var msg = "Shader program failed to link. " 
        + "The error log is:" 
        + "<pre>" + gl.getProgramInfoLog(program) + "</pre>";
        
        alert(msg);
        return -1;
    }
    return program;
}