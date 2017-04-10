/***********************************************************************
* FileName: imp_align.h
* Author:  lcy
*
* Description: structures and functions for alignment calculations
*
***********************************************************************/

#ifndef IMP_ALIGN_H
#define IMP_ALIGN_H

#include"imp_algo_type.h"
#include"imp_align_tab_5.h"
#include<math.h>

#ifdef __cplusplus
extern "C"
{
#endif


typedef struct imp_align_RES_S
{
	IMP_S16 align_success;
	float shape[NUM2];		
}IMP_Align_RES_S;

/*
***********************************************************************
* Function: ABdot
* Description: matrix multiplication C=A*B
* Parameters:
*		A: [n*m], as input matrix for matrix multiplication
*		B: [m*p], as input matrix for matrix multiplication
*		n: row of A, row of C
*		m: col of A, row of B
*		p: col of B, col of C
*		C: [n*p], a float pointer to an allocated float array, as output
*		   matrix
*
* Example: float A[4] = { 1, 2, 3, 4 };
*          float B[4] = { 2, 3, 4, 5 };
*		   float C[4] = { 0, 0, 0, 0 };
*          ABdot(A,B,2,2,2,C);
*
*          | 1  2 | * | 2  3 |  =  | 10  13 |
*		   | 3  4 |   | 4  5 |     | 22  29 |
*
*		   C={ 10,13,22,29};
*
***********************************************************************
*/
void ABdot(const float* A, const float*B, int n, int m, int p, float* C);


/***********************************************************************
* Function: Btdot
* Description: matrix multiplication Ct=A*Bt
* Input: A [n*m]
*        B [p*m]
*        n: row of A, col of C
*        m: col of A, col of B
*        p: row of B, row of C
* Output: C [p*n]
***********************************************************************/
void Btdot(const float* A, const float*B, int n, int m, int p, float* C);


/***********************************************************************
* Function: AtBdot
* Description: matrix multiplication C=At*B
* Input: A [m*n]
*        B [m*p]
*        n: col of A, row of C
*        m: row of A, row of B
*        p: col of B, col of C
* Output: C [n*p]
***********************************************************************/
void AtBdot(const float* A, const float*B, int n, int m, int p, float* C);


void svd_22(const float*A, float*U, float*Vt, float*S);

/***********************************************************************
* Function: getCOV
* Description: get covariance matrix of 2 shapes
* Input: pred_shape
*        mean_shape
* Output: sigma: variance
			cov: covariance matrix
***********************************************************************/
void getCOV(float* pred_shape,
	const float* mean_shape,
	float* sigma,
	float* cov);


/***********************************************************************
* Function: unnormalizing_shape
* Description: unnormalize shape
* Input: rect_x1,rect_y1,rect_width,rect_height
*        shape_normed: shape normed in [-1,1]*[-1,1]
* Output: shape_unnorm
***********************************************************************/
void unnormalizing_shape(
	float* shape_normed,
	float* shape_unnorm, 
	int rect_x1, int rect_y1, int rect_width, int rect_height
);



/***********************************************************************
* Function: extract_pixel_values
* Description: extract pixel_values from an image
* Input: image
*        shape_normed: face landmarks normed in [-1,1]*[-1,1]
*        tform_inv: inverse of transform matrix
*        deltas: (delta_x,delta_y)
         rect_x1,rect_y1,rect_x2,rect_y2,rect_width,rect_height
* Return: pixel_values
***********************************************************************/

void extract_pixel_values(
	unsigned char* pixel_value,
	IMAGE3_S* image,
	float* shape_normed,
	float* tform_inv,
	const float* deltas, 
	int rect_x1, int rect_y1,
	int rect_x2, int rect_y2,
	int rect_width, int rect_height
);

/***********************************************************************
* Function: find_similarity_tform
* Description: find similarity transform matrix and its inverse matrix
* Input: shape_pred: predicted_shape
*        shape_mean: mean_shape
* Output: tform: transform matrix
*         tform_inv: inverse of transform matrix
***********************************************************************/
void find_similarity_tform(
	float* shape_pred,
	const float* shape_mean,
	float* tform,
	float* tform_inv
);

/***********************************************************************
* Function: which_leaf
* Description: get the leaf_index, given pixel_values of an image
* Input: pixel_values ( of an image)
*        i:  the i_th cascade (index begin with 0)
*        j:  the j_th tree ((index begin with 0)
* Return: leaf_index
***********************************************************************/
int which_leaf(const unsigned char* pixel_values, int i, int j);



/***********************************************************************
* Function: shape_predictor
* Description: get predicted shape of given image
* Parameters:
*	image : IMAGE3_S type pointer refer to a YUV image, as input image
*			for  alignment
*   roi: IMP_RECT_S type, boundingBox of face using Pico_Facedection
*   res: IMP_Align_RES_S type pointer for alignment results
*
***********************************************************************/

IMP_S32 shape_predictor(IMAGE3_S* image, IMP_RECT_S roi, IMP_Align_RES_S* res);

#ifdef __cplusplus
}
#endif

#endif /* IMP_ALIGH_H */

