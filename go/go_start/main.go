package main

import "fmt"

var x, y int
var ( // 这种因式分解关键字的写法一般用于声明全局变量
	a int
	b bool
)
var c, d int = 1, 2
var e, f = 123, "hello"

//这种不带声明格式的只能在函数体中出现
//g, h := 123, "hello"

//一个可以返回多个值的函数
func numbers() (int, int, string) {
	a, b, c := 1, 2, "str"
	return a, b, c
}

func main() {
	{
		g, h := 123, "hello"
		fmt.Println(x, y, a, b, c, d, e, f, g, h)
	}
	_, numb, strs := numbers() //只获取函数返回值的后两个
	fmt.Println(numb, strs)

	fmt.Println("Hello, World!")
	fmt.Println("Welcome to Go programming.")
	fmt.Println("Hello, World!")
	fmt.Println("菜鸟教程：runoob.com")
	var x int = 10
	var y int = 20
	var sum int = x + y
	fmt.Printf("The sum of %d and %d is %d\n", x, y, sum)
	const Pi float64 = 3.14159265358979323846
	// %d 表示整型数字，%s 表示字符串
	var stockcode = 123
	var enddate = "2020-12-31"
	var url = "Code=%d&endDate=%s"
	var target_url = fmt.Sprintf(url, stockcode, enddate)
	fmt.Println(target_url)

	{
		var a string = "Runoob"
		fmt.Println(a)
	}
	{
		var b, c int = 1, 2
		fmt.Println(b, c)
		var a = "RUNOOB"
		fmt.Println(a)
	}
	{
		// 没有初始化就为零值
		var b int
		fmt.Println(b)

		// bool 零值为 false
		var c bool
		fmt.Println(c)
	}
	{
		var i int
		var f float64
		var b bool
		var s string
		fmt.Printf("%v %v %v %q\n", i, f, b, s)
	}
	{
		var d = true
		fmt.Println(d)
		intVal := 1
		fmt.Printf("intVal is of type %T\n", intVal)
		fmt.Printf("intVal value is %v\n", intVal)
	}
}
