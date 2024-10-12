/*ʹ����֪������
 * 1.ʹ��ǰ������޸�����������ص��ļ�·��ֵ
 * 2.��ֻ��һ���򵥵Ĺ���������Demo,����ʵ�ֹ����������Ļ�������,�Դ���һЩ���⣺
 *   ��1������ʱ�����õ�encoded�ַ�����codeTable���������й����л�ȡ�ģ����Ǵ���Ӧ�Ķ������ļ��ж�ȡ��
 *   ��2��д���������ļ�ʱ��������λ������Ӧ�ĺ��������˲�����������ܵ��±���ʱ������������������ʹ���ַ����ͱ�����Ǵӱ��������ļ��ж�ȡ�Ļ���
 *   ��3��ֻ���Թ�Ӣ���ı��ļ��Ĳ��ԣ����������Լ������ı����ܲ�֧��
 * 3.txtFileFunction.h�ļ����Ծ�Ԥ���˱�����Ͷ������ļ��Ķ�д����غ���
 *
 * �����������ޣ����ڴ����д��ڵ����⣬������·Ӣ�۵ĸ���
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
    Timer timer,timerAll;//������ʱ�������ڼ����㷨��ʱ

    //��ȡ�ı��ļ�
    string original = readTxtFile(path);
    cout << "��ȡ�ı��ļ����" << endl;

    cout << endl;
    cout << "--------------------������̿�ʼ--------------------" << endl;
    cout << endl;

    timerAll.start();

    //ͳ���ַ�����Ƶ��
    timer.start();
    unordered_map<char, int> count = countChar(original);
    timer.stop();
    cout << "ͳ���ַ�����Ƶ�����,��ʱ:" << timer.timeCost() << "ms" << endl;
    timer.reset();

    //�����ڵ�����
    timer.start();
    vector<huffmanTreeNode *> nodes = countToNodes(count);
    timer.stop();
    cout << "�����ڵ��������,��ʱ:" << timer.timeCost() << "ms" << endl;
    timer.reset();

    //������������
    timer.start();
    huffmanTreeNode *finallyTree = buildHuffmanTree(nodes);
    timer.stop();
    cout << "���������������,��ʱ:" << timer.timeCost() << "ms" << endl;
    timer.reset();

    //��ȡ�����������
    timer.start();
    unordered_map<char, string> codeTable = getHuffmanCodeTable(finallyTree);
    timer.stop();
    cout << "��ȡ��������������,��ʱ:" << timer.timeCost() << "ms" << endl;
    timer.reset();

    //�ѹ����������д��һ���ļ���
    timer.start();
    writeCodeTable("E:\\GitRepositories\\huffman-code-and-decode-demo\\Code\\CodeTable.txt", codeTable);
    timer.stop();
    cout << "�ѹ����������д��һ���ļ������,��ʱ:" << timer.timeCost() << "ms" << endl;
    timer.reset();

    //���й���������
    timer.start();
    string encoded = encode(original, codeTable);
    timer.stop();
    cout << "���й������������,��ʱ:" << timer.timeCost() << "ms" << endl;
    timer.reset();

    //�ѱ������ļ��Զ�������ʽд���ļ�
    timer.start();
    writeBinaryString("E:\\GitRepositories\\huffman-code-and-decode-demo\\Code\\Encode.bin", encoded);
    timer.stop();
    cout << "�ѱ������ļ��Զ�������ʽд���ļ����,��ʱ:" << timer.timeCost() << "ms" << endl;
    cout << "�������ļ�����" << encoded.size() << "��������λ" << endl;
    timer.reset();

    //�ͷŹ�������
    timer.start();
    clearHuffmanTree(finallyTree);
    timer.stop();
    cout << "�ͷŹ����������,��ʱ:" << timer.timeCost() << "ms" << endl;
    timer.reset();

    cout << endl;
    cout << "--------------------������̽�����������̿�ʼ--------------------" << endl;
    cout << endl;

    //����
    timer.start();
    string decoded = decode(encoded, codeTable);
    timer.stop();
    cout << "�������,��ʱ:" << timer.timeCost() << "ms" << endl;
    timer.reset();

    //�ѽ������ַ���д���ļ�
    timer.start();
    writeTxtFile("E:\\GitRepositories\\huffman-code-and-decode-demo\\Code\\Decode.txt", decoded);
    timer.stop();
    cout << "�ѽ������ַ���д���ļ����,��ʱ:" << timer.timeCost() << "ms" << endl;
    timer.reset();

    cout << endl;
    cout << "--------------------������̽���--------------------" << endl;
    cout << endl;

    timerAll.stop();
    cout << "�������ȫ������ʱ(���������ʾ���ʱ��):" << timerAll.timeCost() << "ms" << endl;
    timerAll.reset();

    return 0;
}