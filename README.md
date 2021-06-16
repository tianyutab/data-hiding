### 在bmp格式的图片中实现数据隐藏

实现原理是，bmp图片表示的颜色范围较广，以真彩色为例，用3个字节表示一个像素，一共可以表示256 * 256 * 256种颜色。但是人眼能识别的颜色有限，因此可以在不影响肉眼识别的基础上，每个像素拿出末尾的3bit用来存放数据。数据隐藏在图片中，并且不改变图片的大小。

#### 使用说明
包含2个头文件，2个源文件，使用g++进行编译。
有两条命令：
- readbmp.exe 23.bmp --hide 000.bmp
//第一个为编译成功之后的执行文件，作为命令名称，第二个参数是想要隐藏数据的图像名（暂时只支持bmp格式）第三个参数"--hide",第四个参数是隐藏好之后生成的新的图像。
//提前在本目录下建一个input.txt文件，存放要隐藏的数据

- readbmp.exe 000.bmp --show
//第一个参数为执行文件，第二个参数为隐藏了数据的图片
此命令会生成一个output.txt文件，执行结束后隐藏信息会写入。

#### 注意
- 使用g++ 编译
- 如果执行时弹出缺少dll文件，需要把g++的路径设置为环境变量。
