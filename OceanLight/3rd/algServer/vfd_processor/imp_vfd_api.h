/* File:	imp_vfd_api.h
*
* Version: 6.5
*
* Author: IMPower Algorithm Team
*
* Description:	Fundamental type definitions for IMPower algorithms
*
* Copyright (C) 2009-2016, IMPower Technologies, all rights reserved.
*
* date: 20170112 
*/

#ifndef _IMP_VFD_API_H_
#define _IMP_VFD_API_H_
#include<stdlib.h>
#include "imp_vfd_para.h"

#ifdef __cplusplus
extern "C"
{
#endif

	/*----------------user API -----------------*/

	IMP_HANDLE IMP_VFD_Create(IMP_S32 s32Width, IMP_S32 s32Height);

	IMP_U32 IMP_VFD_Config(IMP_HANDLE hModule, IMP_VFD_PARA_S *pstVFDParaSrc);

	IMP_U32 IMP_VFD_Process(IMP_HANDLE hModule, IMAGE3_S *pstImage);

	IMP_U32 IMP_VFD_Release(IMP_HANDLE* pHandle);

	IMP_U32 IMP_VFD_GetResult(IMP_HANDLE hModule, IMP_VFD_RESULT_S *pstVFDResult);

#ifdef __cplusplus
}
#endif

#endif /* _IMP_VFD_API_H_ */