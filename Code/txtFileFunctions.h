/**
 *  与文本文件操作相关的函数
 */
#pragma once

#include <fstream>
#include <unordered_map>
#include <string>
#include <bitset>

using namespace std;

//把一个文本文件的内容读到一个字符串中
string readTxtFile(string path) {
    ifstream fin(path);
    string s;
    char ch;
    while (fin.get(ch)) {
        s.push_back(ch);
    }
    return s;
}

//将一个字符串写入一个文本文件
void writeTxtFile(string path, string s) {
    ofstream fout(path);
    fout << s;
}

//将一个只包含'0'和'1'的字符串以二进制位的形式写进一个文件中
void writeBinaryString(string path, const string &binaryStr) {
    // 打开文件以二进制模式写入
    ofstream outFile(path, ios::binary);
    if (!outFile) {
        cout << "Failed to open the file" << path << endl;
        return;
    }

    // 每 8 位转换为一个字节并写入文件
    for (size_t i = 0; i < binaryStr.size(); i += 8) {
        string byteStr = binaryStr.substr(i, 8); // 获取 8 位
        // 如果不足 8 位，可以用 '0' 填充
        while (byteStr.size() < 8) {
            byteStr += '0'; // 右侧填充 0
        }
        bitset<8> bits(byteStr); // 将字符串转换为位集
        char byte = static_cast<char>(bits.to_ulong()); // 转换为字节
        outFile.write(&byte, sizeof(byte)); // 写入字节
    }

    outFile.close(); // 关闭文件
}

//从一个二进制文件中读取一个只包含'0'和'1'的字符串
string readBinFile(const string &filename) {
    ifstream inFile(filename, ios::binary); // 以二进制模式打开文件
    if (!inFile) {
        cout << "无法打开文件: " << filename << endl;
        return "";
    }

    string binaryStr;
    char byte; // 用于存储每个字节
    while (inFile.get(byte)) { // 逐字节读取文件
        // 将字节转换为8位的二进制字符串
        bitset<8> bits(static_cast<unsigned char>(byte)); // 将字符转换为无符号字符
        binaryStr += bits.to_string(); // 将二进制字符串拼接到结果中
    }

    inFile.close(); // 关闭文件
    return binaryStr;
}


//把哈夫曼编码表写进一个文本文件中
void writeCodeTable(string path, unordered_map<char, string> codeTable) {
    ofstream fout(path);
    for (auto &p: codeTable) {
        fout << p.first << " " << p.second << endl;
    }
}

//从一个文本文件中读取哈夫曼编码表
unordered_map<char, string> readCodeTable(string path) {
    ifstream fin(path);
    unordered_map<char, string> codeTable;
    char ch;
    string code;
    while (fin >> ch >> code) {
        codeTable[ch] = code;
    }
    return codeTable;
}