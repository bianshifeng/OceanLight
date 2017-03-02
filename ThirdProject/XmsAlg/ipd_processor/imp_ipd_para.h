/************************************************************************/
/* @File:      imp_ipd_para.h, IPD: Indoor Person Detection
   @Descrip:   Detect Indoor Person, no need detect other object,
        this file will define some user configuration parameter and
	    define algorithm results
   @Right:    All rights reserved by Beijing IMPower Technologies Co. Ltd.   
   @Version:  IPDv3
   @Date:     2016/7/23
*/
/************************************************************************/
#ifndef _IMP_IPD_PARA_H_
#define _IMP_IPD_PARA_H_

#include "imp_algo_type.h"

#define TEST_IPD_ADV_PARA  0         /* Test Advanced Parameter */

#if TEST_IPD_ADV_PARA
#include "imp_ipd_adv_para.h"
#endif

#define MAX_WAR_NUM    16             /* Max warning num */

#ifdef __cplusplus
extern "C"
{
#endif
	
	// Sensitivity
	typedef enum impIPD_SENS_E
	{
		IMP_IPD_SENS_HIGH   = 1,           /* if use this, will detect more, maybe more mistake */
		IMP_IPD_SENS_NORMAL = 2,           /* default sens, */ 
		IMP_IPD_SENS_LOW    = 3,           /* if use this, detect result will be accurate more, but detect less */
	}IMP_IPD_SENSITY_E;


	// Input Para
	typedef struct impIPD_Para_S
	{
		IMP_IPD_SENSITY_E   enSensity;     /* Sensitivity */
		IMP_U32             u32Flag;       /* Reserved para */
#if TEST_IPD_ADV_PARA
		IMP_S32             s32Valid;      /* Advanced Para use or not */
		IMP_IPD_Adv_Para_S  stIPDAdvPara;  /* Advanced Parameter */
#endif
	}IMP_IPD_Para_S;
	
	// Target Item
	typedef struct impIPDTgtItem_S
	{
		IMP_S32             s32TgtID;      /* Target ID */
		IMP_RECT_S          stTgtRct;      /* Target Rect */
	}IMP_IPD_Tgt_Item_S;

	// Algorithm Results
	typedef struct impIPD_Result_S
	{
		IMP_S32             s32TgtNum;           /* Target Num */
		IMP_IPD_Tgt_Item_S  astTgtSet[MAX_WAR_NUM]; /* Target Set */ 
	} IMP_IPD_Result_S;
#ifdef __cplusplus
}
#endif

#endif /*_IMP_IPD_PARA_H_*/
