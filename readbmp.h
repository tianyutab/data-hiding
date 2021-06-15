#ifndef READBMP
#define READBMP
#include<math.h>
#include <iomanip> 
#include <stdlib.h>
#include <windows.h>
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include"require.h"
//using namespace std;
#define DEBUG

class BmpFile
{
private:
    const char *fileName;
    char *pBmpBuf;//读入图像数据的指针
    int bmpWidth;//图像的宽
    int bmpHeight;//图像的高
    int lineByte;
    RGBQUAD *pColorTable;//颜色表指针
    int biBitCount;//图像类型，每像素位数
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHead;
    char *data;
    size_t dataSize;
public:
    BmpFile(const char *);
    const char* getName()const {return fileName;}
    const char* getFileHeader()const {return (char *)&fileHeader;}
    const char* getInfoHeader()const {return (char*)&infoHead;}
    const char* getRgbQuad()const {return (char *)pColorTable;}
    int getBitCount()const {return biBitCount;}
    const char* getBmpBuf()const {return pBmpBuf;}
    int getDataSize()const {return lineByte*bmpHeight;}
    char *getData()const {return data;}
    void setData(char* const newData){data = newData;}
    size_t getDataRealSize()const {return dataSize;}
    void updateData();
    void updateBmpBuf();
    void LoadInfo();
    void getFileInfo();
    void newFile();
    ~BmpFile();

};
#endif //防止多重包含