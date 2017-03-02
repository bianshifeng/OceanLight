#ifndef _IMP_IPD_ADV_PARA_H_
#define _IMP_IPD_ADV_PARA_H_
#include "imp_algo_type.h"

typedef struct impIPD_Adv_Para_S
{
	IMP_S32   s32ScanStep;              // 扫描步长2,3,4; 扫描步长为3是步长为2耗时的一半
	IMP_S32   s32StartScale;            // 开始的尺度; 如果设为2, 则检测到的最小人头大小为 pow(fScaleChange, 2) * 24
	IMP_S32   s32ScaleNum;		        // 尺度个数; 可设0~10
	IMP_S32   s32UsedClsN;		        // 用哪个分类器 -1代表全部, 0~3, 设置单独用哪一个 
	IMP_FLOAT fScaleChange;             // 尺度间的变化比例 // 尺度间的变化比例1~1.5

	IMP_S32   s32Reserved;              // 保留参数
}IMP_IPD_Adv_Para_S;





#endif // end of file
