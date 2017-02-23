/*
CPC: Cross-line People Counting, 跨线人流量计数
Author: JW. ZHOU
Date: 2015.9.23
*/
#ifndef _IMP_CPC_API_H_
#define _IMP_CPC_API_H_
#include "imp_algo_type.h"
#include "imp_cpc_para.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * Function:    IMP_CPC_Create *
 * Description: Create  CPC algorithm module  *
 * Parameters:  s32Width -- width of processed frame
 *              s32Height -- height of processed frame
 *              hModule -- handle of CPC module *
 * Returns:     creating succeed or not *
 * Remarks:
 */
IMP_EXPORTS IMP_S32 IMP_CPC_Create(IMP_S32 s32Width, IMP_S32 s32Height, IMP_HANDLE* phModule);

/*
 * Function:    IMP_CPC_Release *
 * Description: Release CPC algorithm module  *
 * Parameters:  hModule -- handle of CPC module *
 * Returns:     Error code *
 * Remarks:
 */
IMP_EXPORTS IMP_S32 IMP_CPC_Release(IMP_HANDLE hModule);


/*
 * Function:    IMP_CPC_Process *
 * Description: Process frame with CPC algorithm *
 * Parameters:  hModule -- handle of CPC module
 *              pstImage -- frame to be processed
				pstCPCResult -- result of current processed frame
 * Returns:     Error code *
 * Remarks:
 */
IMP_EXPORTS IMP_S32 IMP_CPC_Process(IMP_HANDLE hModule, IMAGE3_S *pstImage, IMP_CPC_Result_S *pstCPCResult);

/*
 * Function:    IMP_CPC_ConfigParameter *
 * Description: Configure parameters of CPC algorithm *
 * Parameters:  hModule -- handle of CPC module
 *              pstCPCParaSrc -- parameter of the algorithm *
 * Returns:     Error code *
 * Remarks:
 */
IMP_EXPORTS IMP_S32 IMP_CPC_Config(IMP_HANDLE hModule, IMP_CPC_Para_S *pstCPCPara);


#ifdef __cplusplus
}
#endif

#endif /*_IMP_CPC_API_H_*/