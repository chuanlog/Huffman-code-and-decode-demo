/*
 * 哈夫曼树的节点结构体
 */
#pragma once
#include <iostream>

using namespace std;

struct huffmanTreeNode {
    char ch;//字符，没有字符时为空
    int weight;//权重
    huffmanTreeNode *left;//左子树
    huffmanTreeNode *right;//右子树
    huffmanTreeNode(char ch,int weight) : ch(ch),weight(weight),left(nullptr),right(nullptr){}
    huffmanTreeNode() : ch('\0'),weight(0),left(nullptr),right(nullptr){}
};