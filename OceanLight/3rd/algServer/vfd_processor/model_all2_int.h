/***********************************************************************
* FileName: model.h
* Version:  1.0.0
* Author:  lcy
* Copyright (C) 2016, IMPower Technologies, all rights reserved.
*
* Description: this file contains model data 
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
* 10. LEFT_EYE_IDX: left_eye_index in landmarks (index begin with 0)
*
* 11. NUM_RIGHT_EYE_IDX: number of right_eye_index
*
* 12. RIGHT_EYE_IDX: right_eye_index in landmarks (index begin with 0)
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
**************************************************************************/


#ifndef MODEL_H
#define MODEL_H
#pragma warning(disable: 4305)
#pragma warning(disable: 4838)
#define NUM_LANDMARK 21
#define NUM2 42
#define NUM_LMinv 0.047619
static const float MEAN_SHAPE[NUM2] = { 0.279377,0.316043,0.355046,0.298574,0.43802,0.316303,0.572754,0.31286,0.656616,0.290958,0.734066,0.305586,0.31811,0.382092,0.433394,0.38618,0.584414,0.383274,0.699402,0.374229,0.428428,0.555065,0.511579,0.591719,0.593738,0.552219,0.512913,0.650222,0.513314,0.69314,0.513945,0.745849,0.375294,0.377278,0.642444,0.371653,0.508548,0.538474,0.397162,0.681698,0.629375,0.676284};
#define NUM_PATTERNS 43
static const float DELTAS[NUM_PATTERNS*2] = { 9,0,
0.0356278,0.0617093,-0.0356278,0.0617093,-0.0712558,0,-0.0356278,-0.0617093,0.0356278,-0.0617093,0.046282,0.0267209,0,0.0534418,-0.046282,0.0267209,-0.046282,-0.0267209,0,-6,
0.046282,-0.0267209,0.0385969,0,0.0192985,0.0334258,-0.0192985,0.0334258,-0.0385969,0,-0.0192985,-0.0334258,0.0192985,-0.0334258,0.023141,0.0133605,0,0.0267209,-2,1,
-0.023141,-0.0133605,-0,-0.0267209,0.023141,-0.0133605,0.017814,0,0.00890694,0.0154274,-0.00890694,0.0154274,-0.017814,0,-0.00890694,-0.0154274,0.00890694,-0.0154274,1,0,
0,0.011876,-0.0102849,0.00593803,-0.0102849,-0.00593803,-0,-0.011876,0.0102849,-0.00593803,0.00890694,0,0.00445352,0.00771369,-0.00445352,0.00771369,-0.00890694,0,0,0,
0.00445352,-0.00771369,-0,0};
#define NUM_CASCADE 8
#define NUM_TREE 81
#define NUM_SPLIT_NODE 31
#define NUM_LEAF_NODE 32
#define NUM_LEFT_EYE_IDX 1
static int LEFT_EYE_IDX[NUM_LEFT_EYE_IDX] = {16};
#define NUM_RIGHT_EYE_IDX 1
static int RIGHT_EYE_IDX[NUM_LEFT_EYE_IDX] = {17};

extern const int IDX1[NUM_CASCADE][NUM_TREE][NUM_SPLIT_NODE];
extern const int IDX2[NUM_CASCADE][NUM_TREE][NUM_SPLIT_NODE];
extern const int THRES[NUM_CASCADE][NUM_TREE][NUM_SPLIT_NODE];
extern const float LEAFVAL[NUM_CASCADE][NUM_TREE][NUM_LEAF_NODE][NUM_LANDMARK][2];
#endif

