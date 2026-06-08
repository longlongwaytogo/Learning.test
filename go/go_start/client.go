package main

import (
	"fmt"
	"net/rpc"
)

func main() {
	//建立网络连接
	cli, err := rpc.DialHTTP("tcp", "127.0.0.1:10086")
	if err != nil {
		fmt.Println("network failed")
	}

	var pd int
	//客户端调用服务端GetInfo方法，并传递参数
	err = cli.Call("Panda.GetInfo", 10086, &pd)
	if err != nil {
		fmt.Println("call() failed")
	}
	fmt.Println("服务端输出的值：", pd)

}
