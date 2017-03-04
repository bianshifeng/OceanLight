#ifndef  __IMP_FRAME_STRUCT_H__
#define  __IMP_FRAME_STRUCT_H__

typedef	enum {
	FREE_FRAME,			//未分配的
	USED_FRAME,			//正在使用的
	ALLOCATED_FRAME,	//分配好内存的
	DISPLAYED_FRAME,	//将要显示的
}IMP_FRAME_STATUS;

typedef enum {
    IMG_FORMAT_RGB = 1,
    IMG_FORMAT_YUV420P = 2,
}IMG_DATA_FORMAT;

typedef struct IMP_PicOutFrame {
	int 	nWidth;
	int 	nHeight;
    IMG_DATA_FORMAT nImgFormat;
    unsigned char* 	pu8D1;
    unsigned char*	pu8D2;
    unsigned char*	pu8D3;
	char* 	pResult;
    int     nUseFlag;
    int     nResFlag;
	int		nFrameNo;
    qint64 nFrameTime;
}IMP_PicOutFrame;

#endif
