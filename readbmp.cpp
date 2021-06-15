#include"readbmp.h"
#include<cassert>
#include<bitset>
using namespace std;
#define DEBUG


 
BmpFile::BmpFile(const char *fileName):fileName(fileName)
{
    data = 0;
    pBmpBuf = 0;
    pColorTable = 0;
}

void BmpFile::LoadInfo()
{
    ifstream fp(fileName,ios::binary);
    assure(fp,"���ļ�ʧ�ܣ�");
    fp.read((char *)&fileHeader,14);

    //fileHeader = {0,0,0,0,0};
    //fp>>fileHeader.bfType>>fileHeader.bfSize>>fileHeader.bfReserved1>>fileHeader.bfReserved2>>fileHeader.bfOffBits;
    //fread(&fileHeader,sizeof(BITMAPFILEHEADER),1,fp);
    //fseek(fp, sizeof(BITMAPFILEHEADER),0);
     
    fp.read((char *)&infoHead,40);
    //fread(&infoHead, sizeof(BITMAPINFOHEADER), 1,fp); //»ñÈ¡Í¼Ïñ¿í¡¢¸ß¡¢Ã¿ÏñËØËùÕ¼Î»ÊýµÈÐÅÏ¢
 
    //bitmapinfoheaderµÄ³¤¶È
    //int bit_map_info_length = infoHead.biSize;
    bmpWidth = infoHead.biWidth;
    bmpHeight = infoHead.biHeight;
    biBitCount = infoHead.biBitCount;
    lineByte=(bmpWidth * biBitCount/8+3)/4*4;

 
//»Ò¶ÈÍ¼Ïñ»¹ÐèÒª´æÏÂµ÷É«°åÐÅÏ¢
    if(biBitCount==8)
	{
 
        //ÉêÇëÑÕÉ«±íËùÐèÒªµÄ¿Õ¼ä£¬¶ÁÑÕÉ«±í½øÄÚ´æ
        cout<<"ͼƬΪ�Ҷ�ͼ��"<<endl;
        pColorTable=new RGBQUAD[256];
 
        //fread(pColorTable,sizeof(RGBQUAD),256,fp);
 
	}
    pBmpBuf=new char[lineByte * bmpHeight];
 
 //ÒÔÒ»¸ö×Ö½ÚÎªµ¥Î»£¬´ælineByte*bmpHeight¸ö×Ö½ÚµÄÐÅÏ¢
    //fread(pBmpBuf,1,lineByte * bmpHeight,fp);
    
    fp.read(pBmpBuf,lineByte * bmpHeight);
 
    
}


void BmpFile::getFileInfo()
{
    //È«²¿headerÐÅÏ¢ËùÕ¼µÄ³¤¶È
    int headerLength = fileHeader.bfOffBits;

        printf("ɫλ:%d,ͼƬ����:%d,ͼƬ�߶�:%d\n",biBitCount,bmpWidth,bmpHeight);
        cout<<"ͼƬ����ռ���ֽ���"<<lineByte*bmpHeight<<endl;
    //exit(0);
    if(headerLength-fileHeader.bfSize==14)
    {
        cout<<"ͼƬΪ���ɫ��"<<endl;
    }
    // int pixelNum = lineByte*bmpHeight;
    // for(int i=0;i<6;i++)
    //     cout<<(int)pBmpBuf[i]<<" ";
    

}

//´ÓÈ«²¿Êý¾ÝÖÐÉú³É×îºóÒ»Î»×é³ÉµÄ×Ö·ûÊý×é
void BmpFile::updateData()
{
    size_t size = getDataSize();
    int byteSize = size/8;
    if(data)
        return;
    data = new char[byteSize];
    memset(data,0,byteSize);
    
    
    for(int i=0;i<byteSize;i++)
    {
        
        bool flags[8] = {0,0,0,0,0,0,0,0};
        data[i] = 0x00;
        for(int j=0;j<8;j++)
        {
            flags[j] = pBmpBuf[i*8+j]&1?true:false;
            
            //0xfeÓë 0x01»ò
            
            data[i] |= flags[j]?0x80:0x00;
            data[i] &= flags[j]?0xff:0x7f;
            data[i] = j<7?data[i]>>1:data[i];
           
        }
        if(data[i]==0x00)
        {
            //i+1¸ö×Ö½Ú£¬i¸ö×Ö·û¡£
            dataSize = i;
            break;
        }
        // bitset<64> bufDataBit(pBmpBuf[i*8,i*8+8]);
        // dataBit.set(0,bufDataBit[7]);
        // dataBit.set(1,bufDataBit[15]);
        // dataBit.set(2,bufDataBit[23]);
        // dataBit.set(3,bufDataBit[31]);
        // dataBit.set(4,bufDataBit[39]);
        // dataBit.set(5,bufDataBit[47]);
        // dataBit.set(6,bufDataBit[55]);
        // dataBit.set(7,bufDataBit[63]);
        // char dataForOneByte = dataBit.to_ulong();
        // strcpy(data+i,&dataForOneByte);
    }
    cout<<"�ɹ���ȡ"<<dataSize<<"�ֽڵ�����!"<<endl;

}

//´ÓÈ«²¿Êý¾ÝÖÐÉú³É×îºóÒ»Î»×é³ÉµÄ×Ö·ûÊý×é
void BmpFile::updateBmpBuf()
{
    size_t size = getDataSize();
    int byteSize = size/8;
    if(!data)
        return;
    //data = new char[byteSize];
    
    //unsigned long long bufData;
    
    unsigned char a;
    
    for(int i=0;i<byteSize;i++)
    {
        bool flag[8]={0,0,0,0,0,0,0,0};
        a= data[i];
        //bufData = pBmpBuf[i*8];
        for(int j=0;j<8;j++)
        {
            
           
            flag[j]=(1&(a>>j)?true:false);
//0xfeÓë 0x01»ò
            pBmpBuf[i*8+j] &= flag[j]?0xff:0xfe;
            pBmpBuf[i*8+j] |= flag[j]?0x01:0x00;
        }
        if(data[i]=='\000')
            break;
        
    }
    cout<<"��������"<<byteSize<<"�ֽڵ����ݣ�"<<endl;

}


BmpFile::~BmpFile()
{
    delete []pBmpBuf;
    if(pColorTable!=0)
        delete []pColorTable;
    if(data)
        delete []data;
}
//-------------------------------------------------------------------------------------------

bool saveBmp(char *bmpName, BmpFile &bmpFile);
void addInfo(BmpFile& bmpFile);
void show(BmpFile&bmpFile);
int main(int argc,char* argv[])
{
    //requireArgs(argc,3);

    BmpFile myFile(argv[1]);
    myFile.LoadInfo();
    myFile.getFileInfo();
    const char* hide = "--hide";
    const char* showLabel = "--show";
    if(!strncmp(argv[2],hide,6))
{
    addInfo(myFile);
    myFile.updateBmpBuf();
    //char name[] = "new_.bmp";
    //strcat(name,argv[1]);
    saveBmp(argv[3],myFile);
}   
else if(!strncmp(argv[2],showLabel,6))
{
    myFile.updateData();
    show(myFile);
}
    return 0;
}
 
