#ifndef _IMP_VFD_PARA_H_
#define _IMP_VFD_PARA_H_


#include "imp_algo_type.h"


#include"imp_faceQA.h"


#define IMP_VFD_MAX_FACE_NUMBER 16


/*----------------user parameters -----------------*/
#ifdef __cplusplus
extern "C"
{
#endif


	typedef struct impVFD_FACE_PROP_S
	{
		IMP_RECT_S stPosition;	/* Position of human face */
		IMP_S32 s32Facesize;		/* Face size (in pixels) */
		IMP_U32 u32FaceID;          /*Face ID*/
		IMP_U8 u8Flag;			/* If it would be shown */


		IMP_Align_RES_S alignRes;
		IMP_S16 faceQA_Res;

	}IMP_VFD_FACE_PROP_S;

	typedef struct impVFD_FACE_ROI_S
	{

		IMP_POLYGON_S stPolygon;
		IMP_S32 s32Enable;		/* Switch of ROI */
		IMP_U32 u32Para;		/* Parameter reserved for future use */
	}IMP_VFD_ROI_S;

	typedef struct impVFD_RESULT_S
	{
		IMP_S32 s32Facenumber;	/* Number of face in current processing frame */
		IMP_VFD_FACE_PROP_S stFace[IMP_VFD_MAX_FACE_NUMBER];/* face properties */
		IMP_S32 s32Reserved1;	/* Reserved 1 */
		IMP_S32 s32Reserved2;	/* Reserved 2 */
		IMP_U32 u32Reserved3;	/* Reserved 3 */
		IMP_U32 u32Reserved4;	/* Reserved 4 */

	}IMP_VFD_RESULT_S;

	typedef struct impVFD_PARA_S
	{
		IMP_U32 QAlevel;

		IMP_VFD_ROI_S stROI;	/* 仅支持一个矩形区域*/
		IMP_S32 s32Sizemax;	/* Max size of face */
		IMP_S32 s32Sizemin; /* Min size of face */
		IMP_S32 s32Numax;	/* Max number of face */
		IMP_U32 u32EnableColor; /*color mode of the input image.0:gray image,1: color image */
		IMP_U32 u32Enablerotate;
		IMP_U32 u32RotateLevel;

		IMP_S32 s32Level;	/* Detection balance level, 0 - speed,  5 - accurate */
		IMP_S32 s32TrackLevel;	/* Track balance level, 0 - speed,  5 - accurate */
		IMP_S32 s32Confidence;	/* avoid errorFace, 0 -detec and track,  5 - confirm and track */
		IMP_U32 u32Reserved2;	/* Reserved 2 */
		IMP_U32 u32Reserved3;	/* Reserved 3 */

	}IMP_VFD_PARA_S;

#ifdef __cplusplus
}
#endif

#endif