#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/** 度*/
#define DEGREE 3
/** 孩子指针数量 */
#define POINT_NUM (DEGREE<<1)
/** 节点记录数量 */
#define RECORD_NUM (POINT_NUM - 1)
/** 数据的类型 */
#define record_type int32_t

typedef struct btree_node
{
    /** 指向孩子的指针 */
    btree_node* child[POINT_NUM];
    /** 指向父亲的指针 */
    btree_node* parent;
    /** 节点记录的数据 */
    record_type record[RECORD_NUM];
    /** 是否为叶子节点 */
    int16_t is_leaf;
} btree_node;

/** 创建一个空的节点*/
btree_node* create_new_node();

/** 插入数据 */
void insert_data(record_type val);

#endif
