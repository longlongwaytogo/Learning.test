
# WebGL加载图片文件


#### 摘要（Abstract) 
		WebGL目前已经被大多数浏览器所支持，但是不同浏览器对图片文件的加载都所以差异。加载文件分为使用web服务器端数据和本地数据两种方式，以下就此问题进行讨论。
#### 关键字(key words)
	WebGL, Image, Texture, CROS(跨域资源共享) crossOrign


## 1. 背景
 学习webGL，写几个简单的小例子没什么问题。但加载纹理图片，确出现了一些严重错误。网上找了好久，总算找到几个靠谱的方法，不敢私藏，在此做一总结。
其中出现的错误有以下几种：
- from origin 'null' has been blocked by CORS policy: Invalid response. Origin 'null' is therefore not allowed access.[添加了 crossorigin=""; 或crossorigin="anonymous" 读取本地文件时所产生错误]
- Uncaught DOMException: Failed to execute 'texImage2D' on 'WebGLRenderingContext': The cross-origin image at[未设置crossorigin属性]

## 2. CROS简介
CORS是一个W3C标准，全称是"跨域资源共享"（Cross-origin resource sharing）。它允许浏览器向跨源(协议 + 域名 + 端口)服务器，发出XMLHttpRequest请求，从而克服了AJAX只能同源使用的限制。

CORS需要浏览器和服务器同时支持。它的通信过程，都是浏览器自动完成，不需要用户参与。对于开发者来说，CORS通信与同源的AJAX通信没有差别，代码完全一样。浏览器一旦发现AJAX请求跨源，就会自动添加一些附加的头信息，有时还会多出一次附加的请求，但用户不会有感觉。
因此，实现CORS通信的关键是服务器。只要服务器实现了CORS接口，就可以跨源通信。
[来源:](https://www.cnblogs.com/cityspace/p/6858969.html)

####  举例来说CROS：
	跨域是指从一个域名的网页去请求另一个域名的资源。比如从www.baidu.com 页面去请求 www.google.com 的资源。跨域的严格一点的定义是：只要 协议，域名，端口有任何一个的不同，就被当作是跨域. 

或者，如：
	我们写博客时，经常会链接github库中的图片资源，博客所处的网站和github 属于两个不同的源,当使用浏览器代开这个博客页面时，服务器，需要先从博客主站点下载资源，同时，从github中获取图片资源，这个就是跨域操作了。

### 2.1 为什么浏览器要限制跨域
原因就是安全问题：如果一个网页可以随意地访问另外一个网站的资源，那么就有可能在客户完全不知情的情况下出现安全问题。比如下面的操作就有安全问题：

用户访问www.mybank.com ，登陆并进行网银操作，这时cookie啥的都生成并存放在浏览器
用户突然想起件事，并迷迷糊糊地访问了一个邪恶的网站 www.xiee.com
这时该网站就可以在它的页面中，拿到银行的cookie，比如用户名，登陆token等，然后发起对www.mybank.com 的操作。
如果这时浏览器不予限制，并且银行也没有做响应的安全处理的话，那么用户的信息有可能就这么泄露了。

### 2.2 为什么要跨域

然有安全问题，那为什么又要跨域呢？ 有时公司内部有多个不同的子域，比如一个是location.company.com ,而应用是放在app.company.com , 这时想从 app.company.com去访问 location.company.com 的资源就属于跨域。  

当然，上面说的博客中引用github中的图片，这个本来不存在安全问题，也是这么公开访问的。

## 3. WebGL 加载图片
  
  好了，言归正传，回到WebGL这里。WebGL加载图片主要分两种，一种为web服务器方式访问(http协议),一种为加载本地图片，但不同浏览器支持不同。以下使用`firefox：59.0.2`， `chrome：59.0.3071.115`，进行测试。



#### 3.1 加载本地图片


1 、**firefox**
 对于火狐浏览器：加载本地图片，需要做如下设置：

		（1）Firefox的用户请在浏览器的地址栏输入“about:config”，回车
		（2）在过滤器（filter）中搜索“security.fileuri.strict_origin_policy”
		（3）将security.fileuri.strict_origin_policy设置为false
		（4）关闭目前开启的所有Firefox窗口，然后重新启动Firefox

2 、 **chrome**
 网上说以下方法可行，但我的版本没有效果，但也把方法贴出来：

		Windows 下：
		设置Chrome的快捷方式属性，在“目标”后面加上 --allow-file-access-from-files，注意前面有个空格，重新打开Chrome即可。
		Mac：
		只能通过终端打开浏览器：打开终端，输入下面命令：open -a "Google Chrome" --args --disable-web-security然后就可以屏蔽安全访问了[ --args：此参数可有可无]
3、 如果没有读取本地文件权限，并且没有设置crossOrigin属性，则会出现以下错误：
		
	Uncaught DOMException: Failed to execute 'texImage2D' on 'WebGLRenderingContext': The cross-origin image at
否则：
 		
	from origin 'null' has been blocked by CORS policy: Invalid response. Origin 'null'

### 3.2 加载网络文件


1、 firefox: 无论是否有crossOrigin，均可访问（之前已经设置了读取本地文件）
2、chrome: 不添加crossOrign，访问其他网站图片失败，添加crossOrign，访问正确


### 3.3 自己搭建服务器
若没有合适的网络资源测试，可以自己在本地搭建web服务，网上有很多工具可以搭建web服务，其中有以下方法：

**首先你要安装nodejs+ http-server**

		// 安装
		
		npm install http-server -g
		
		// 用法
		
		http-server [path] [options]

## 4、其他加载本地图片
当然，由于是本地图片，所以是否支持跨域没有尝试，目前决定可以正确加载本地图片
在国外一个网站博客中，他给出的Water例子中，使用到<image>标签加载图片，然后再从image标签中解析图片数据，这个也不失为一种变通方案。
这个是他的网站：[http://madebyevan.com/]()
Water例子中用到的框架是他的项目[https://github.com/evanw/lightgl.js]()
以下是部分代码： 
	
	// ### GL.Texture.fromImage(image[, options])
	//
	// Return a new image created from `image`, an `<img>` tag.
	Texture.fromImage = function(image, options) {
	  options = options || {};
	  var texture = new Texture(image.width, image.height, options);
	  try {
	    gl.texImage2D(gl.TEXTURE_2D, 0, texture.format, texture.format, texture.type, image);
	  } catch (e) {
	    if (location.protocol == 'file:') {
	      throw new Error('image not loaded for security reasons (serve this page over "http://" instead)');
	    } else {
	      throw new Error('image not loaded for security reasons (image must originate from the same ' +
	        'domain as this page or use Cross-Origin Resource Sharing)');
	    }
	  }
	  if (options.minFilter && options.minFilter != gl.NEAREST && options.minFilter != gl.LINEAR) {
	    gl.generateMipmap(gl.TEXTURE_2D);
	  }
	  return texture;
	};


## 5、 引用网站
1. [跨域请求](https://www.cnblogs.com/happyflyingpig/p/8118818.html)
2. [cors-permission/WebGL - Cross Origin Images ](https://webglfundamentals.org/webgl/lessons/webgl-cors-permission.html)
3. [一行命令搭建简易静态文件http服务器](https://wdd.js.org/one-command-create-static-file-server.html)
4. [mozilla官网关于CORS使用--Using CORS to load WebGL textures from cross-domain images](https://hacks.mozilla.org/2011/11/using-cors-to-load-webgl-textures-from-cross-domain-images/)
5. [weglFundamental关于--Cross Origin Images](https://webglfundamentals.org/webgl/lessons/webgl-cors-permission.html)
6. [CORS_settings_attributes](https://developer.mozilla.org/en-US/docs/Web/HTML/CORS_settings_attributes)



 