/*使用须知！！！
 * 1.使用前请务必修改主函数中相关的文件路径值
 * 2.这只是一个简单的哈夫曼编码Demo,可以实现哈夫曼编解码的基本功能,仍存在一些问题：
 *   （1）解码时，所用的encoded字符串和codeTable都是在运行过程中获取的，不是从相应的二进制文件中读取的
 *   （2）写进二进制文件时，最后不足八位的在相应的函数中做了补零操作，可能导致编码时程序崩溃（如果解码所使用字符串和编码表是从编码所得文件中读取的话）
 *   （3）只测试过英文文本文件的测试，对于中文以及其他文本可能不支持
 * 3.txtFileFunction.h文件中以经预留了编码表和二进制文件的读写的相关函数
 *
 * 本人能力有限，关于代码中存在的问题，期望各路英雄的斧正
 * */

#include <iostream>
#include <string>
#include <vector>
#include "huffmanCode.h"
#include "txtFileFunctions.h"
#include "Timer.h"

using namespace std;

int main() {
    string path = "E:\\GitRepositories\\huffman-code-and-decode-demo\\Code\\test.txt";
    Timer timer,timerAll;//声明计时器，用于计量算法用时

    //读取文本文件
    string original = readTxtFile(path);
    cout << "读取文本文件完成" << endl;

    cout << endl;
    cout << "--------------------编码过程开始--------------------" << endl;
    cout << endl;

    timerAll.start();

    //统计字符出现频率
    timer.start();
    unordered_map<char, int> count = countChar(original);
    timer.stop();
    cout << "统计字符出现频率完成,用时:" << timer.timeCost() << "ms" << endl;
    timer.reset();

    //构建节点数组
    timer.start();
    vector<huffmanTreeNode *> nodes = countToNodes(count);
    timer.stop();
    cout << "构建节点数组完成,用时:" << timer.timeCost() << "ms" << endl;
    timer.reset();

    //构建哈夫曼树
    timer.start();
    huffmanTreeNode *finallyTree = buildHuffmanTree(nodes);
    timer.stop();
    cout << "构建哈夫曼树完成,用时:" << timer.timeCost() << "ms" << endl;
    timer.reset();

    //获取哈夫曼编码表
    timer.start();
    unordered_map<char, string> codeTable = getHuffmanCodeTable(finallyTree);
    timer.stop();
    cout << "获取哈夫曼编码表完成,用时:" << timer.timeCost() << "ms" << endl;
    timer.reset();

    //把哈夫曼编码表写在一个文件中
    timer.start();
    writeCodeTable("E:\\GitRepositories\\huffman-code-and-decode-demo\\Code\\CodeTable.txt", codeTable);
    timer.stop();
    cout << "把哈夫曼编码表写在一个文件中完成,用时:" << timer.timeCost() << "ms" << endl;
    timer.reset();

    //进行哈夫曼编码
    timer.start();
    string encoded = encode(original, codeTable);
    timer.stop();
    cout << "进行哈夫曼编码完成,用时:" << timer.timeCost() << "ms" << endl;
    timer.reset();

    //把编码后的文件以二进制形式写进文件
    timer.start();
    writeBinaryString("E:\\GitRepositories\\huffman-code-and-decode-demo\\Code\\Encode.bin", encoded);
    timer.stop();
    cout << "把编码后的文件以二进制形式写进文件完成,用时:" << timer.timeCost() << "ms" << endl;
    cout << "编码后的文件包含" << encoded.size() << "个二进制位" << endl;
    timer.reset();

    //释放哈夫曼树
    timer.start();
    clearHuffmanTree(finallyTree);
    timer.stop();
    cout << "释放哈夫曼树完成,用时:" << timer.timeCost() << "ms" << endl;
    timer.reset();

    cout << endl;
    cout << "--------------------编码过程结束，解码过程开始--------------------" << endl;
    cout << endl;

    //解码
    timer.start();
    string decoded = decode(encoded, codeTable);
    timer.stop();
    cout << "解码完成,用时:" << timer.timeCost() << "ms" << endl;
    timer.reset();

    //把解码后的字符串写入文件
    timer.start();
    writeTxtFile("E:\\GitRepositories\\huffman-code-and-decode-demo\\Code\\Decode.txt", decoded);
    timer.stop();
    cout << "把解码后的字符串写入文件完成,用时:" << timer.timeCost() << "ms" << endl;
    timer.reset();

    cout << endl;
    cout << "--------------------解码过程结束--------------------" << endl;
    cout << endl;

    timerAll.stop();
    cout << "编码解码全过程用时(包含输出提示语句时间):" << timerAll.timeCost() << "ms" << endl;
    timerAll.reset();

    return 0;
}