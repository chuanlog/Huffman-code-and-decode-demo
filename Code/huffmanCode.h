/*
 * 哈夫曼编码的函数
 */
#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include "huffmanTreeNode.h"

//比较两颗哈夫曼树
class compare {
public:
    bool operator()(huffmanTreeNode *a, huffmanTreeNode *b) {
        return a->weight > b->weight;
    }
};

//合并两颗哈夫曼树，返回新的哈夫曼树节点
huffmanTreeNode *merge(huffmanTreeNode *a, huffmanTreeNode *b) {
    huffmanTreeNode *newNode = new huffmanTreeNode('\0', a->weight + b->weight);
    newNode->left = a;
    newNode->right = b;
    return newNode;
}

//构建哈夫曼树并返回根节点
huffmanTreeNode *buildHuffmanTree(std::vector<huffmanTreeNode *> &nodes) {
    std::priority_queue<huffmanTreeNode *, std::vector<huffmanTreeNode *>, compare> q;
    for (auto node: nodes) {
        q.push(node);
    }
    while (q.size() > 1) {
        huffmanTreeNode *a = q.top();
        q.pop();
        huffmanTreeNode *b = q.top();
        q.pop();
        huffmanTreeNode *newNode = merge(a, b);
        q.push(newNode);
    }
    return q.top();
}

//构建哈夫曼编码表的帮助函数
void getHuffmanCodeTableHelper(huffmanTreeNode *root, std::unordered_map<char, std::string> &table, std::string code) {
    if (root == nullptr) return;
    if (root->left == nullptr && root->right == nullptr) {
        table[root->ch] = code;
        return;
    }
    getHuffmanCodeTableHelper(root->left, table, code + "0");
    getHuffmanCodeTableHelper(root->right, table, code + "1");
}

//获取哈夫曼编码表
std::unordered_map<char, std::string> getHuffmanCodeTable(huffmanTreeNode *root) {
    std::unordered_map<char, std::string> table;
    getHuffmanCodeTableHelper(root, table, "");
    return table;
}

//返回哈夫曼编码结果
string encode(string s, unordered_map<char, string> codeTable) {
    string res;
    for (auto ch: s) {
        res += codeTable[ch];
    }
    return res;
}

//清空哈夫曼树
void clearHuffmanTree(huffmanTreeNode *root) {
    if (root == nullptr)return;
    clearHuffmanTree(root->left);
    clearHuffmanTree(root->right);
    delete root;
}

//统计一个字符串中不同字符的出现次数
unordered_map<char, int> countChar(string s) {
    unordered_map<char, int> count;
    for (auto ch: s) {
        count[ch]++;
    }
    return count;
}

//把统计结果转化为初始的哈夫曼节点
vector<huffmanTreeNode*> countToNodes(unordered_map<char, int> count) {
    vector<huffmanTreeNode*> nodes;
    for (auto item: count) {
        nodes.push_back(new huffmanTreeNode(item.first, item.second));
    }
    return nodes;
}

//解码函数
string decode(const string encoded,const unordered_map<char, string>&codeTable) {
    string decoded; // 用于存储解码后的字符串
    string currentCode; // 用于存储当前的编码

    // 反转编码表，便于查找
    unordered_map<string, char> reversedCodeTable;
    for (const auto &entry : codeTable) {
        reversedCodeTable[entry.second] = entry.first; // 将编码作为键，字符作为值
    }

    // 遍历编码字符串
    for (char bit : encoded) {
        currentCode += bit; // 将当前位添加到 currentCode
        if (reversedCodeTable.find(currentCode) != reversedCodeTable.end()) {
            // 如果找到了对应的字符，添加到 decoded 中
            decoded += reversedCodeTable[currentCode];
            currentCode.clear(); // 清空 currentCode 准备下一个字符
        }
    }

    return decoded; // 返回解码后的字符串
}