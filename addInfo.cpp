#include"readbmp.h"
#include<cstring>
#include<bitset>
//-----------------------------------------------------------------------------------------
//����һ��ͼ��λͼ���ݡ����ߡ���ɫ��ָ�뼰ÿ������ռ��λ������Ϣ,����д��ָ���ļ���
bool saveBmp(char *bmpName, BmpFile &bmpFile)
{
    // char  *qianzhui = "new_";
    // char *name = strcat(qianzhui,bmpFile.getName());
    std::ofstream fp(bmpName,std::ios::binary);

    assure(fp,"�ļ�����ʧ�ܣ�");

   
    //��ɫ���С�����ֽ�Ϊ��λ���Ҷ�ͼ����ɫ��Ϊ1024�ֽڣ���ɫͼ����ɫ���СΪ0
 
    //�Զ�����д�ķ�ʽ���ļ�
 

    //����λͼ�ļ�ͷ�ṹ��������д�ļ�ͷ��Ϣ
    fp.write(bmpFile.getFileHeader(),14);
    fp.write(bmpFile.getInfoHeader(),40);
    if(bmpFile.getBitCount()==8)
        fp.write(bmpFile.getRgbQuad(),1024);
 
    fp.write(bmpFile.getBmpBuf(),bmpFile.getDataSize());
    

    std::cout<<"�ļ�д��ɹ���"<<std::endl;
    return 1;
 
}
 

void addInfo(BmpFile& bmpFile)
{
    //���ص���Ϣ�����txt��
    std::ifstream inputFile("input.txt",std::ios::binary);
    std::string s;
    std::string dataStr;
    //std::cout<<std::hex<<inputFile<<std::endl;

    while(getline(inputFile,s))
        dataStr = dataStr+'\n'+s;
    std::cout<<"������Ϣ����Ϊ��"<<dataStr.length()<<"�ֽ�"<<std::endl;
    // std::cout<<s<<std::endl;
    int length = dataStr.length();
    //һ��ȡһ���ֽڵ��ַ���

//�ռ��ж��
    size_t size = bmpFile.getDataSize();
    int byteSize = size/8;
    if(byteSize>=length)
    {
        std::cout<<"���ÿռ�Ϊ"<<byteSize<<"�ֽ�"<<std::endl;
    }
    else
    {
        std::cout<<"�ռ䲻�㣡"<<std::endl;
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
//����Ϊ���صĶ�ȡ����
// void doIt()
// {
 
//     //����ָ��BMP�ļ����ڴ�
 
//     //char readPath[]="nv.BMP";
 
//     //readBmp(readPath);
 
//     //���ͼ�����Ϣ
 
//     //cout<<"width="<<bmpWidth<<" height="<<bmpHeight<<" biBitCount="<<biBitCount<<endl;
    
//     //ѭ��������ͼ�������
 
//     //ÿ���ֽ���
 
//     int lineByte=(bmpWidth*biBitCount/8+3)/4*4;
 
//     //ѭ����������Բ�ɫͼ�񣬱���ÿ���ص���������
 
//     int m=0,n=0,count_xiang_su=0;
 
//     //��ͼ�����½�1/4�����óɺ�ɫ
 
// 	fstream outfile("ͼ������.txt",ios::in|ios::trunc);
 
//     if(biBitCount==8) //���ڻҶ�ͼ��
// 	{              
// 	//------------------------------------------------------------------------------------
// 	//�������ͼ��ķָ��8*8С��Ԫ����������ֵ�洢��ָ���ı��С�����BMPͼ������������Ǵ�
// 	//���½ǣ��������ң�������������ɨ���
//         int L1=0;
// 		int hang=63;
// 		int lie=0;
// 		//int L2=0;
//         //int fen_ge=8;
// 		for(int fen_ge_hang=0;fen_ge_hang<8;fen_ge_hang++)//64*64������ѭ��
// 		{ 
// 			for(int fen_ge_lie=0;fen_ge_lie<8;fen_ge_lie++)//64*64�о���ѭ��
// 			{ 
// 			//--------------------------------------------
// 				for(L1=hang;L1>hang-8;L1--)//8*8������
// 				{
// 					for(int L2=lie;L2<lie+8;L2++)//8*8������
// 					{
// 						m=*(pBmpBuf+L1*lineByte+L2);
// 						outfile<<m<<" ";
// 						count_xiang_su++;
// 						if(count_xiang_su%8==0)//ÿ8*8��������ı��ļ�
// 						{
// 							outfile<<endl;
// 						}
// 					}
// 				}
// 			//---------------------------------------------
// 				hang=63-fen_ge_hang*8;//64*64�����б任
// 				lie+=8;//64*64�����б任
// 					//��һ�У�64����8��8*8����������
// 			}
// 			hang-=8;//64*64������б任
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
// 	{//��ɫͼ��
// 		for(int i=0;i<bmpHeight;i++)
// 		{
// 			for(int j=0;j<bmpWidth;j++)
// 			{
// 				for(int k=0;k<3;k++)//ÿ����RGB���������ֱ���0�ű�ɺ�ɫ
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
// 		cout<<"�ܵ����ظ���Ϊ:"<<n<<endl;
// 		cout<<"----------------------------------------------------"<<endl;
// 	}
    
//     //��ͼ�����ݴ���
    
//     char writePath[]="nvcpy.BMP";//ͼƬ������ٴ洢
 
//     saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
 
//     //�����������pBmpBuf��pColorTable��ȫ�ֱ��������ļ�����ʱ����Ŀռ�
 
//     delete []pBmpBuf;
 
//     if(biBitCount==8)
//         delete []pColorTable;
// }
 
// void main()
// {
//     doIt();
// }