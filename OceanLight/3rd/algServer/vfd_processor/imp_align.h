/***********************************************************************
* FileName: shape_utils.h
* Version:  1.0.0
* Author:  LYU Chunying
* Date:  2016/10/19
* Copyright (C) 2016, IMPower Technologies, all rights reserved.
*
* Description: structures and functions for shape calculations
*
***********************************************************************/

#ifndef IMP_ALIGN_H
#define IMP_ALIGN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "common/imp_algo_type.h"
#include "model_all2_int.h"

#ifdef __cplusplus
extern "C" {
#endif
	/* struct rectangle */
	typedef struct IMP_rect {
		float start_x;
		float start_y;
		float width;
		float height;
	}IMP_rect_xywh;



	// chun
	typedef struct impAlignResult {

		IMP_POINT32F_S points[NUM_LANDMARK];
		IMP_U16 num_points;
		IMP_U32 alignRet;
	}IMP_Align_Res;

	typedef struct impImgQualityResult {
		IMP_S16 faceQA;
	}IMP_FaceQuality_Res;
	// end chun


	//define a callback function pointer
	typedef void(*IMP_VFD_Callback)(IMP_HANDLE hModule, IMAGE3_S *pstImage);
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
	void ABdot(float* A, const float*B, int n, int m, int p, float* C);


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
	void Btdot(float* A, const float*B, int n, int m, int p, float* C);


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
	void AtBdot(float* A, const float*B, int n, int m, int p, float* C);

	void svd_22(float*A, float*U, float*Vt, float*S);

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
	* Input: rect: face detected bounding box
	*        shape_normed: shape normed in [-1,1]*[-1,1]
	* Output: shape_unnorm
	***********************************************************************/
	void unnormalizing_shape(
		IMP_rect_xywh rect,
		float* shape_normed,
		float* shape_unnorm
	);



	/***********************************************************************
	* Function: extract_pixel_values
	* Description: extract pixel_values from an image
	* Input: image
	*        rect: face detected bounding box
	*        shape_normed: face landmarks normed in [-1,1]*[-1,1]
	*        tform_inv: inverse of transform matrix
	*        deltas: (delta_x,delta_y)
	* Return: pixel_values
	***********************************************************************/
void extract_pixel_values(unsigned char* pixel_values,
		IMAGE3_S* image,
		IMP_rect_xywh rect,
		float* shape_normed,
		float* tform_inv,
		const float* deltas, int x2, int y2, int x22, int y22
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
	*   rect: IMP_rect_xywh type, contains detected boundingBox of face
	* Return: predicted_shape: a float pointer to predicted shape, size of
	NUM_LANDMARK
	***********************************************************************/
	void shape_predictor(IMAGE3_S* image, IMP_rect_xywh rect, float* pred);

	IMP_U32 IMP_Alignment(IMAGE3_S* image, IMP_RECT_S roi, IMP_Align_Res* result);





#ifdef __cplusplus
}
#endif

#endif // defined IMP_ALIGN_H
