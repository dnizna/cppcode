#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "btree.h"

btree_node* create_new_node()
{
    btree_node* node = (btree_node*)malloc(sizeof(btree_node));
    for(int i = 0; i < RECORD_NUM; ++i)
    {
        node->record[i] = -1;
    }
    node->is_leaf = 1;
}

/** 返回当前记录的有效个数*/
uint32_t record_size(btree_node* node)
{
    uint32_t cnt = 0, i = 0;
    for(; i < RECORD_NUM; ++i)
    {
        if(node->record[i] != -1)
            cnt++;
    }
    return cnt;
}

/** 返回可插入记录的下标*/
int32_t max_record_index(btree_node* node)
{
    int i = 0;
    for(; i < RECORD_NUM; ++i)
    {
        if(node->record[i] == -1 )
            break;
    }
    return i - 1; 
}

/** 右移*/
void  shift_right(btree_node* node, int start, int offset)
{
    int max_index = max_record_index(node) + offset;
    if(max_index >= RECORD_NUM)
    {
        fprintf(stderr, "数组超过最大范围!");
        return;
    }
    for(int i = max_index, pos = start + offset; i >= pos; --i)
    {
        node->record[i] = node->record[i - offset];
        node->record[i - offset] = -1;
    }
    for(int i = max_index + 1, pos = start + offset; i >= pos; --i)
    {
        node->child[i] = node->child[i - offset];
        node->child[i - offset] = NULL;
    }
}

/** 左移*/ 
void shift_left(btree_node* node, int start, int offset)
{
    int max_index = max_record_index(node) + offset;
    if(max_index >= RECORD_NUM)
    {
        fprintf(stderr, "数组超过最大范围!");
        return;
    }
    for(int i = max_index, pos = start + offset; i >= pos; --i)
    {
        node->record[i - offset] = node->record[i];
        node->record[i] = -1;
    }
    for(int i = max_index + 1, pos = start + offset; i >= pos; --i)
    {
        node->child[i - offset] = node->child[i];
        node->child[i] = NULL;
    }
}

btree_node* splic_node(btree_node* node, record_type val)
{
}

void insert_data(btree_node* node, record_type val)
{
    if(node == NULL)
        return;
    if(record_size(node) == RECORD_NUM)
    {
        node = splic_node(node, val);
        return;
    }
    int i = 0;
    for(; i < RECORD_NUM; ++i)
    {
        if(node->record[i] == -1 || node->record[i] > val)
            break;
    }
    if(!node->is_leaf)
    {
        insert_data(node->child[i], val);
        return;
    }

}










