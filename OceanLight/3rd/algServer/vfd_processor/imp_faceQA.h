/***********************************************************************
* FileName: imp_faceQA.h
* Author:  lcy
*
* Description: structures and functions for Face Quality Assessment
*
* log: blur, yaw,roll,pitch(up) evaluations
***********************************************************************/

#ifndef IMP_FACEQA_H	
#define IMP_FACEQA_H

#include"imp_align.h"
#include<stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))
#define THRESHOLD(x,mean) ((x>mean)?(1):(0))
#define BLUR_SIZE 30
#define BLUR_2 ((BLUR_SIZE - 2)*(BLUR_SIZE - 2))
#define BLURS_2 (BLUR_SIZE*BLUR_SIZE)

float evaluate_yaw(float* shape);

float evaluate_roll(float* shape);

int evaluate_pitch(float* shape);

float evaluate_blur(IMAGE3_S* image, IMP_RECT_S roi);

float evaluate_illumination(IMAGE3_S* image, IMP_RECT_S roi, float* shape);

/***********************************************************************
* Function: evaluate_faceQA
* Description: face quality assessment 
* Parameters:
*	image : IMAGE3_S type pointer refer to a YUV image, as input image
*   roi: IMP_RECT_S type, boundingBox of face detected by Pico
*   res: IMP_Align_RES_S type pointer for alignment results
*   QAlevel: integer type: 0,1,2,3,4,5
*           0 for close faceQA
*           the higner QAlevel, the higner face quality
* Return: an integer score for faceQA:
*         -1 for no face quality assessment
*         0 for bad quality
*         1 for good quality
*
* Example: 
*        IMAGE3_S* yuvimage=imread(imagename);
*        IMP_RECT_S roi;
*		  roi.s16X1=10; 
*         roi.s16Y1=30;  
*		  roi.s16X2=150;
*         roi.s16Y2=170;  
*        IMP_Align_RES_S res;
*        res.align_success=0;
*        int QA_level=3;
*        int faceQuality= evaluate_faceQA(yuvimage,roi,&res,QA_level);
***********************************************************************/
int evaluate_faceQA(IMAGE3_S* image, IMP_RECT_S roi, IMP_Align_RES_S* res,int QA_level);


#ifdef __cplusplus
}
#endif

#endif /* IMP_FACEQA_H */