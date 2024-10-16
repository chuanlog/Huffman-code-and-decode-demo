# Huffman code and decode demo

#### 介绍
本仓库用c++语言实现了一个Huffman code and decode 的演示程序

####使用须知
使用须知！！！
 1.使用前请务必修改主函数中相关的文件路径值
 2.这只是一个简单的哈夫曼编码Demo,可以实现哈夫曼编解码的基本功能,仍存在一些问题：
    （1）解码时，所用的encoded字符串和codeTable都是在运行过程中获取的，不是从相应的二进制文件中读取的
    （2）写进二进制文件时，最后不足八位的在相应的函数中做了补零操作，可能导致编码时程序崩溃（如果解码所使用字符串和编码表是从编码所得文件中读取的话）
    （3）只测试过英文文本文件的测试，对于中文以及其他文本可能不支持
 3.txtFileFunction.h文件中以经预留了编码表和二进制文件的读写的相关函数

 本人能力有限，关于代码中存在的问题，期望各路英雄的斧正。