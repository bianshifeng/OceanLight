/**
* \defgroup 结构类型定义
* CPC算法配置参数定义
* @author 北京银瀑技术
* @version 0.1
* @data 2009-2015
*/
/*@{*/

/* CPC: Cross-line People Counting, 跨线人流量计数 */

#ifndef _IMP_CPC_PARA_H_
#define _IMP_CPC_PARA_H_

#include "imp_algo_type.h"


#define CPC_MAX_TRAJ_LEN   256        /* 最长跟踪轨迹 */
#define CPC_MAX_TGT_NUM    16         /* 最多的目标数 */

#ifdef __cplusplus
extern "C"
{
#endif

	// 灵敏度设置
	typedef enum impCPC_SENS_E
	{
		IMP_CPC_SENS_HIGH   = 1,          // 检测出来的会多一点， 会有一些误检
		IMP_CPC_SENS_NORMAL = 2,          // 正常检测
		IMP_CPC_SENS_LOW    = 3,          // 检测出来的会少一点 ，但精确一点
	}IMP_CPC_SENSITY_E;


	// CPC输入的参数
	typedef struct impCPC_Para_S
	{
		IMP_CPC_SENSITY_E  enSensity;      // 灵敏度
		IMP_RECT_S         stROIRect;      // ROI具体位置
		LINE_S             stDirection;    // 起始点到结束点的方向为出去的方向;
	}IMP_CPC_Para_S;
	
	// CPC目标类型
	typedef enum impCPC_Type_E
	{
		CPC_BUTT  = -1,
		CPC_ENTER =  0,
		CPC_LEAVE =  1,
	}IMP_CPC_TYPE_E;

	typedef struct impCPC_Tgt_S
	{
		IMP_CPC_TYPE_E enTgtType;  // 跨线目标类型
		IMP_RECT_S     stTgtRect;  // 跨线目标框
	}IMP_CPC_TGT_S;

	// CPC结果输出
	typedef struct impCPC_Result_S
	{
		IMP_U32       u32FrmID;                   // 帧号
		IMP_U32       u32TgtNum;                  // 当前帧跨线目标个数
		IMP_CPC_TGT_S astCPCTgt[CPC_MAX_TGT_NUM]; // 当前跨线目标
		//IMP_U32  u32EnterTgtSum;           // 进来的目标的总数
		//IMP_U32  u32LeaveTgtSum;           // 离开的目标的总数
	} IMP_CPC_Result_S;

#ifdef __cplusplus
}
#endif

#endif /*_IMP_CPC_PARA_H_*/

/*@}*/
