/*
IPD: Indoor Person Detection, 室内人员检测
Author: JW. ZHOU
Date: 2016.7.23
*/
#ifndef _IMP_IPD_API_H_
#define _IMP_IPD_API_H_
#include "common/imp_algo_type.h"
#include "imp_ipd_para.h"

#ifdef __cplusplus
extern "C"
{
#endif
/*
 * Function:    IMP_IPD_Create *
 * Description: Create  IPD algorithm module  *
 * Parameters:  s32Width -- width of processed frame
 *              s32Height -- height of processed frame
 *              hModule -- handle of IPD module *
 * Returns:     creating succeed or not *
 * Remarks:
 */
IMP_EXPORTS IMP_S32 IMP_IPD_Create(IMP_S32 s32Width, IMP_S32 s32Height, IMP_HANDLE* phModule);

/*
 * Function:    IMP_IPD_Release *
 * Description: Release IPD algorithm module  *
 * Parameters:  hModule -- handle of IPD module *
 * Returns:     Error code *
 * Remarks:
 */
IMP_EXPORTS IMP_S32 IMP_IPD_Release(IMP_HANDLE hModule);


/*
 * Function:    IMP_IPD_Process *
 * Description: Process frame with IPD algorithm *
 * Parameters:  hModule -- handle of IPD module
 *              pstImage -- frame to be processed
				pstQCIFImg -- you should keep the image width 176, and the w/h same as pstImage
				pstIPDResult -- result of current processed frame
 * Returns:     Error code *
 * Remarks:
 */
//IMP_EXPORTS IMP_S32 IMP_IPD_Process(IMP_HANDLE hModule, IMAGE3_S *pstImage, IMP_IPD_Result_S *pstIPDResult);
IMP_EXPORTS IMP_S32 IMP_IPD_Process(IMP_HANDLE hModule, IMAGE3_S *pstImage, IMAGE3_S* pstQCIFImg, IMP_IPD_Result_S *pstIPDResult);

/*
 * Function:    IMP_IPD_ConfigParameter *
 * Description: Configure parameters of IPD algorithm *
 * Parameters:  hModule -- handle of IPD module
 *              pstIPDParaSrc -- parameter of the algorithm *
 * Returns:     Error code *
 * Remarks:
 */
IMP_EXPORTS IMP_S32 IMP_IPD_Config(IMP_HANDLE hModule, IMP_IPD_Para_S *pstIPDParaSrc);

#ifdef __cplusplus
}
#endif

#endif /*_IMP_IPD_API_H_*/
