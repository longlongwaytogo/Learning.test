package main

import (
	"fmt"
	"io"
	"net"
	"net/http"
	"net/rpc"
)

// 创建一个int类型对象
type Panda int

/**
 * argType是客户端发送过来的内容
 * replyType是服务端返回给客户端的内容
 */
func (this *Panda) GetInfo(argType int, replyType *int) error { //GetInfo首字母大小 因为要被外部访问
	fmt.Println("打印对方发送过来的数据：", argType)
	//执行
	*replyType = argType + 123456
	return nil
}

func pandatext(w http.ResponseWriter, r *http.Request) {
	io.WriteString(w, "hello panda")
}

func main() {
	//客户端页面的请求
	http.HandleFunc("/panda", pandatext)
	//将类实例化为对象
	pd := new(Panda)
	//服务端注册一个对象，该对象就作为一个服务被暴露出去
	rpc.Register(pd)
	//连接到网络
	rpc.HandleHTTP()

	//监听端口
	ln, err := net.Listen("tcp", ":10086")
	if err != nil {
		fmt.Println("network error")
	}
	http.Serve(ln, nil)
}
