/******************************************************
* FileName: imp_align_tab.h
* Author:  lcy
*
* Description: this file contains alignment model data 
*
*
* Data list:
* 1. NUM_LANDMARK: number of landmarks (face key points)
*
* 2. MEAN_SHAPE£º mean-shape (x1,y1,x2,y2,...)
*    float MEAN_SHAPE[NUM_LANDMARK*2]
*
* 3. NUM_PATTERNS: number of patterns 
*
* 4. DELTAS: list of (delta_x, delta_y)
*    float DELTAS[NUM_PATTERNS*2]
* 5. NUM_CASCADE: number of cascades
*
* 6. NUM_TREE:  number of trees
*
* 7. NUM_SPLIT_NODE: number of split nodes
*
* 8. NUM_LEAF_NODE: number of leaf nodes
*
* 9. NUM_LEFT_EYE_IDX: number of left_eye_index
*
* 10. LEFT_EYE_IDX: left_eye_index in landmarks 
*    (index begin with 0)
*
* 11. NUM_RIGHT_EYE_IDX: number of right_eye_index
*
* 12. RIGHT_EYE_IDX: right_eye_index in landmarks 
*     (index begin with 0)
*
* 13. IDX1: index 1 for split-node, 
*     IDX1[NUM_CASCADE][NUM_TREE][NUM_SPLIT_NODE]
*
* 12. IDX2: index 2 for split-node
*     IDX2[NUM_CASCADE][NUM_TREE][NUM_SPLIT_NODE]
*
* 13. THRES: threshold for split-node
*     THRES[NUM_CASCADE][NUM_TREE][NUM_SPLIT_NODE]
*
* 14. LEAFVAL: leaf values (delta-shape)
*     LEAFVAL[NUM_CASCADE][NUM_TREE][NUM_LEAF_NODE][NUM_LANDMARK][2] 
*
********************************************************************/

#ifndef IMP_ALIGN_TAB_H
#define IMP_ALIGN_TAB_H
#pragma warning (disable:4305)
#pragma warning (disable:4838)


#ifdef __cplusplus
extern "C"
{
#endif
#define NUM_LANDMARK 5
#define NUM2 10
#define NUM_LMinv 0.2
#define EYE1_X 0
#define EYE1_Y 1
#define EYE2_X 2
#define EYE2_Y 3
#define NOSE_X 4
#define NOSE_Y 5
#define MOUTH1_X 6
#define MOUTH1_Y 7
#define MOUTH2_X 8
#define MOUTH2_Y 9
static const float MEAN_SHAPE[NUM_LANDMARK*2] = {
     0.332538038,0.337732464,
    0.689238012,0.32978186,
    0.512147665,0.548582971,
    0.363080859,0.737215638,
    0.671671331,0.729896009};
#define NUM_PATTERNS 43
static const float DELTAS[NUM_PATTERNS*2] = { 
    0.09514366835,0,
    0.0475717634,0.08239676058,
    -0.0475717634,0.08239676058,
    -0.09514366835,0,
    -0.0475717634,-0.08239676058,
    0.0475717634,-0.08239676058,
    0.06179763749,0.0356788598,
    0,0.0713577196,
    -0.06179763749,0.0356788598,
    -0.06179763749,-0.0356788598,
    -0,-0.0713577196,
    0.06179763749,-0.0356788598,
    0.05153611302,0,
    0.02576812916,0.04463154078,
    -0.02576812916,0.04463154078,
    -0.05153611302,0,
    -0.02576812916,-0.04463154078,
    0.02576812916,-0.04463154078,
    0.03089874983,0.0178394299,
    0,0.0356788598,
    -0.03089874983,0.0178394299,
    -0.03089874983,-0.0178394299,
    -0,-0.0356788598,
    0.03089874983,-0.0178394299,
    0.02378595434,0,
    0.01189290546,0.02059926093,
    -0.01189290546,0.02059926093,
    -0.02378595434,0,
    -0.01189290546,-0.02059926093,
    0.01189290546,-0.02059926093,
    0.01373279281,0.007928699255,
    0,0.01585725509,
    -0.01373279281,0.007928699255,
    -0.01373279281,-0.007928699255,
    -0,-0.01585725509,
    0.01373279281,-0.007928699255,
    0.01189290546,0,
    0.005946523976,0.01029963046,
    -0.005946523976,0.01029963046,
    -0.01189290546,0,
    -0.005946523976,-0.01029963046,
    0.005946523976,-0.01029963046,
    -0,0};
#define NUM_CASCADE 9
#define NUM_TREE 90
#define NUM_SPLIT_NODE 31
#define NUM_LEAF_NODE 32
#define NUM_LEFT_EYE_IDX 1
static int LEFT_EYE_IDX[NUM_LEFT_EYE_IDX] = {0};
#define NUM_RIGHT_EYE_IDX 1
static int RIGHT_EYE_IDX[NUM_LEFT_EYE_IDX] = {1};

extern const int IDX1[NUM_CASCADE][NUM_TREE][NUM_SPLIT_NODE]; 
extern const int IDX2[NUM_CASCADE][NUM_TREE][NUM_SPLIT_NODE];
extern const int THRES[NUM_CASCADE][NUM_TREE][NUM_SPLIT_NODE] ;
extern const float LEAFVAL[NUM_CASCADE][NUM_TREE][NUM_LEAF_NODE][NUM_LANDMARK][2];


#ifdef __cplusplus
}
#endif

#endif  /*IMP_ALIGN_TAB_H*/

