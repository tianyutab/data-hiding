#include"readbmp.h"
#include<cstring>
#include<bitset>
//-----------------------------------------------------------------------------------------
//给定一个图像位图数据、宽、高、颜色表指针及每像素所占的位数等信息,将其写到指定文件中
bool saveBmp(char *bmpName, BmpFile &bmpFile)
{
    // char  *qianzhui = "new_";
    // char *name = strcat(qianzhui,bmpFile.getName());
    std::ofstream fp(bmpName,std::ios::binary);

    assure(fp,"文件创建失败！");

   
    //颜色表大小，以字节为单位，灰度图像颜色表为1024字节，彩色图像颜色表大小为0
 
    //以二进制写的方式打开文件
 

    //申请位图文件头结构变量，填写文件头信息
    fp.write(bmpFile.getFileHeader(),14);
    fp.write(bmpFile.getInfoHeader(),40);
    if(bmpFile.getBitCount()==8)
        fp.write(bmpFile.getRgbQuad(),1024);
 
    fp.write(bmpFile.getBmpBuf(),bmpFile.getDataSize());
    

    std::cout<<"文件写入成功！"<<std::endl;
    return 1;
 
}
 

void addInfo(BmpFile& bmpFile)
{
    //隐藏的信息存放在txt中
    std::ifstream inputFile("input.txt",std::ios::binary);
    std::string s;
    std::string dataStr;
    //std::cout<<std::hex<<inputFile<<std::endl;

    while(getline(inputFile,s))
        dataStr = dataStr+'\n'+s;
    std::cout<<"输入信息长度为："<<dataStr.length()<<"字节"<<std::endl;
    // std::cout<<s<<std::endl;
    int length = dataStr.length();
    //一次取一个字节的字符。

//空间有多大
    size_t size = bmpFile.getDataSize();
    int byteSize = size/8;
    if(byteSize>=length)
    {
        std::cout<<"可用空间为"<<byteSize<<"字节"<<std::endl;
    }
    else
    {
        std::cout<<"空间不足！"<<std::endl;
        exit(0);
    }

    if(!bmpFile.getData())
    {
        char *data = bmpFile.getData();
        data = new char[byteSize];
        bmpFile.setData(data);
    }
    strcpy(bmpFile.getData(),dataStr.c_str());
    memset(bmpFile.getData()+length,0,byteSize-length);

    // std::bitset<32> insertInfo('a');
    // std::cout<<insertInfo.to_string()<<std::endl;
    // std::cout<<sizeof insertInfo<<std::endl;
}

void show(BmpFile&bmpFile)
{
    std::fstream outFile("output.txt",std::ios::out);
    outFile.write(bmpFile.getData(),bmpFile.getDataRealSize()+1);
}
//----------------------------------------------------------------------------------------
//以下为像素的读取函数
// void doIt()
// {
 
//     //读入指定BMP文件进内存
 
//     //char readPath[]="nv.BMP";
 
//     //readBmp(readPath);
 
//     //输出图像的信息
 
//     //cout<<"width="<<bmpWidth<<" height="<<bmpHeight<<" biBitCount="<<biBitCount<<endl;
    
//     //循环变量，图像的坐标
 
//     //每行字节数
 
//     int lineByte=(bmpWidth*biBitCount/8+3)/4*4;
 
//     //循环变量，针对彩色图像，遍历每像素的三个分量
 
//     int m=0,n=0,count_xiang_su=0;
 
//     //将图像左下角1/4部分置成黑色
 
// 	fstream outfile("图像像素.txt",ios::in|ios::trunc);
 
//     if(biBitCount==8) //对于灰度图像
// 	{              
// 	//------------------------------------------------------------------------------------
// 	//以下完成图像的分割成8*8小单元，并把像素值存储到指定文本中。由于BMP图像的像素数据是从
// 	//左下角：由左往右，由上往下逐行扫描的
//         int L1=0;
// 		int hang=63;
// 		int lie=0;
// 		//int L2=0;
//         //int fen_ge=8;
// 		for(int fen_ge_hang=0;fen_ge_hang<8;fen_ge_hang++)//64*64矩阵行循环
// 		{ 
// 			for(int fen_ge_lie=0;fen_ge_lie<8;fen_ge_lie++)//64*64列矩阵循环
// 			{ 
// 			//--------------------------------------------
// 				for(L1=hang;L1>hang-8;L1--)//8*8矩阵行
// 				{
// 					for(int L2=lie;L2<lie+8;L2++)//8*8矩阵列
// 					{
// 						m=*(pBmpBuf+L1*lineByte+L2);
// 						outfile<<m<<" ";
// 						count_xiang_su++;
// 						if(count_xiang_su%8==0)//每8*8矩阵读入文本文件
// 						{
// 							outfile<<endl;
// 						}
// 					}
// 				}
// 			//---------------------------------------------
// 				hang=63-fen_ge_hang*8;//64*64矩阵行变换
// 				lie+=8;//64*64矩阵列变换
// 					//该一行（64）由8个8*8矩阵的行组成
// 			}
// 			hang-=8;//64*64矩阵的列变换
// 			lie=0;//64*64juzhen
// 		}
// 	}
 
//     //double xiang_su[2048];
// 	//ofstream outfile("xiang_su_zhi.txt",ios::in|ios::trunc);
// 	if(!outfile)
// 	{
// 		cout<<"open error!"<<endl;
// 		exit(1);
// 	}
//     else if(biBitCount==24)
// 	{//彩色图像
// 		for(int i=0;i<bmpHeight;i++)
// 		{
// 			for(int j=0;j<bmpWidth;j++)
// 			{
// 				for(int k=0;k<3;k++)//每像素RGB三个分量分别置0才变成黑色
// 				{
// 					//*(pBmpBuf+i*lineByte+j*3+k)-=40;
//                     m=*(pBmpBuf+i*lineByte+j*3+k);
// 					outfile<<m<<" ";
// 					count_xiang_su++;
// 					if(count_xiang_su%8==0)
// 					{
// 						outfile<<endl;
// 					}
// 				//n++;
// 				}
// 				n++;
//             }
 
 
//         }
// 		cout<<"总的像素个素为:"<<n<<endl;
// 		cout<<"----------------------------------------------------"<<endl;
// 	}
    
//     //将图像数据存盘
    
//     char writePath[]="nvcpy.BMP";//图片处理后再存储
 
//     saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
 
//     //清除缓冲区，pBmpBuf和pColorTable是全局变量，在文件读入时申请的空间
 
//     delete []pBmpBuf;
 
//     if(biBitCount==8)
//         delete []pColorTable;
// }
 
// void main()
// {
//     doIt();
// }