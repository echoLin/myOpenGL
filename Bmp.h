#include<fstream>
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef long LONG;

//位图文件头定义
//其中不包含文件类型信息（由于结构体的内存结构决定，如果加了的话将不能正确读取文件信息）
typedef struct tagBITMAPFILEHEADER{
	WORD bfType;//文件类型，必须是0x4424D，即字符“BM”
	DWORD bfSize;//文件大小,包含这14个字节
	WORD bfReserved1;//保留字
	WORD bfReserved2;//保留字
	DWORD bfOffBits;//从文件头到实际位图数据的偏移字节数
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
	DWORD biSize;//信息头大小,40个字节
	LONG biWidth;//图像宽度，以像素为单位
	LONG biHeight;//图像高度,以像素为单位
	WORD biPlanes;//位平面数 必须为1
	WORD biBitCount;//每像素位数（bit ）1（黑白） 4（16色） 8（256色） 24（真彩色图）
	WORD biCompression;//压缩类型 这里为未经压缩的bmp 故为BI_RGB
	DWORD biSizeImage;//压缩图像大小字节数
	LONG biXPelsPerMeter;//水平分辨率
    LONG biYPelsPerMeter;//垂直分辨率
    DWORD biClrUsed;//位图实际用到的色彩数
    DWORD biClrImportant;//本位图中重要的色彩数
}BITMAPINFOHEADER;

typedef struct tagRGBQUAD{
	BYTE rgbBlue;//该颜色的蓝色分量
	BYTE rgbGreen;//该颜色的绿色分量
	BYTE rgbRed;//该颜色的红色分量
	//BYTE rgbReserved;//保留值
}RGBQUAD,Color;//调色板定义

//像素信息
typedef struct tagIMAGEDATA
{
	BYTE red;
	BYTE green;
	BYTE blue;
}IMAGEDATA;



class Bmp{
public:
	unsigned char *pBmpBuf;//读入图像数据的指针
	int bmpWidth;//图像宽
	int bmpHeight;//图像高
	int biBitCount;//图像类型，每像素位数
	Color colorBuffer[480][640];//颜色Buffer
	double zBuffer[480][640];//深度Buffer
	int lineByte;

	Bmp(){
		biBitCount = 8;
		bmpWidth = 640;
		bmpHeight = 480;
		lineByte = (bmpWidth * biBitCount/8+3)/4*4;
	}

void LoadBmp(const char* file){
	BYTE header[54];
	//以二进制方式打开图像文件
	FILE *fp;
	if(!(fp = fopen(file,"rb")))
		return;
	//跳过位图文件头结构BITMAPFILEHEADER
	fseek(fp,sizeof(BITMAPFILEHEADER),0);
	
	//定义位图信息头结构变量，读取位图信息头进没存，存放在变量head中
	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER),1,fp);
	//获取图像宽、高，每像素所占位数等信息
	bmpWidth = head.biWidth;
	bmpHeight = head.biHeight;
	biBitCount = head.biBitCount;
	//定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
	lineByte = (bmpWidth * biBitCount/8+3)/4*4;
	if(biBitCount == 8){
		fread(colorBuffer, sizeof(RGBQUAD),640*480,fp);
	}
	//申请位图数据所需要的空间，读位图数据进入内存
	pBmpBuf = new unsigned char[lineByte * bmpHeight];
	fread(pBmpBuf,1,lineByte * bmpHeight, fp);

	fclose(fp);
	}

void SaveBmp(const char* file){
	BYTE header[54] = {
		  0x42, 0x4d, 0, 0, 0, 0, 0, 0, 0, 0,
		  54, 0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0,
		  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		  0, 0, 0, 0
	 };
	long file_size = (long)bmpWidth *(long)bmpHeight *3 + 54;
	 header[2] = (BYTE)(file_size & 0x000000ff);
	 header[3] = (file_size >> 8) & 0x000000ff;
	 header[4] = (file_size >> 16) & 0x000000ff;
	 header[5] = (file_size >> 24) & 0x000000ff;
	 long wi = bmpWidth;
	 header[18] = wi & 0x000000ff;
	 header[19] = (wi >> 8) & 0x000000ff;
	 header[20] = (wi >> 16) & 0x000000ff;
	 header[21] = (wi >> 24) & 0x000000ff;
	 long he = bmpHeight;
	 header[22] = he & 0x000000ff;
	 header[23] = (he >> 8) & 0x000000ff;
	 header[24] = (he >> 16) & 0x000000ff;
	 header[25] = (he >> 24) & 0x000000ff;

	 FILE *fp;
	 if(!(fp = fopen(file,"wb")))
		 return ;
	 fwrite(header , sizeof(BYTE),54,fp);
	 fwrite(colorBuffer, sizeof(Color), (size_t)(long)bmpWidth*bmpHeight, fp);
	 fclose(fp);
	/*
	//以二进制写的方式打开文件
	 FILE *fp;
	 if(!(fp = fopen(file,"wb")))
		 return ;
	 int colorBufferSize = 0;
	 if(biBitCount == 8)
		 colorBufferSize = 1024;
	 //带存储图像数据每行字节数为4的倍数
	 lineByte = (bmpWidth * biBitCount/8+3)/4*4;
	 //申请位图文件头结构变量，填写文件头信息
	 BITMAPFILEHEADER fileHead;
	 fileHead.bfType = 0x4D42;
	 fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorBufferSize + lineByte*bmpHeight;
	 //写文件头进文件
	 fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1,fp);
	 //申请位图信息头结构变量，填写信息头信息
	 BITMAPINFOHEADER head;
	 head.biBitCount = biBitCount;
	 head.biClrImportant = 0;
	 head.biClrUsed = 0;
	 head.biHeight = bmpHeight;
	 head.biPlanes = 1;
	 head.biSize = 40;
	 head.biSizeImage = lineByte*bmpHeight;
	 head.biWidth = bmpWidth;
	 head.biXPelsPerMeter = 0;
	 head.biYPelsPerMeter = 0;
	 //写位图信息头进文件
	 fwrite(&head, sizeof(BITMAPINFOHEADER),1,fp);
	 //写入colorBuffer
	 fwrite(colorBuffer,sizeof(Color),480*640,fp);
	 fclose(fp);
	 */
}

void setClearColor(Color color){
	for(int i = 0; i<480; i++)
		for(int j = 0; j<640; j++)
			colorBuffer[i][j] = color;
}

void writeColorBuffer(Color c,int x, int y, int z){
	if(x>=0 && x<640 && y>=0 && y<480){
		//if(z>zBuffer[x][y]){
			zBuffer[y][x] = z;
			colorBuffer[y][x] = c;
		//}
	}
}

void setZBuffer(double z){
	for(int i = 0; i<480; i++)
		for(int j = 0; j<640; j++)
			zBuffer[i][j] = z;
}


};
