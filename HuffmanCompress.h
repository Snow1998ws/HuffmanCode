#pragma once
#include"HuffmanTree.h"
#include<fstream>
#include<iostream>
#include<stdio.h>
using namespace std;
//字符缓存器
struct BufferType
{
	char ch;                                     //字符
	int bits;                                    //实际比特数
};


class HuffmanCompress
{
protected:
	HuffmanTree* pHuffmanTree;
	FILE* infp;                                 //输入文件
	FILE* outfp;                                //输出文件
	BufferType buf;                             //字符缓存


	void Write(int bit);                        //向目标文件中写入一个比特
	void WriteToOutfp();                        //强行将字符缓存写入目标文件


public:
	HuffmanCompress() {};                       //无参数的构造函数
	void Compress();                            //压缩算法
	void DeCompress();                          //解压缩算法
};



//向目标文件中写入一个比特
void HuffmanCompress::Write(int bit)
{
	buf.bits++;                                    //缓存比特数自增1
	buf.ch = (buf.ch << 1) | bit;                  //将bit加入到缓存字符中
	if (buf.bits == 8)
	{       //缓存区已满，写入目标文件
		fputc(buf.ch, outfp);                      //写入目标文件
		buf.bits = 0;                              //初始化bits
		buf.ch = 0;                                //初始化ch
	}
}

//强行将字符缓存写入目标文件
void HuffmanCompress::WriteToOutfp()
{
	int len = buf.bits;                            //缓存实际比特数
	if (len > 0)                                    
	{     //缓存非空，将缓存的比特个数增加到8，自动写入目标文件
		for (int i = 0; i < 8 - len; i++)
			Write(0);
	}
}

void HuffmanCompress::Compress()
{
	char infName[256], outfName[256];                        //输入输出文件名
	cout << "请输入源文件名: ";
	cin >> infName;
	if ((infp = fopen(infName, "rb")) == NULL)
	{
		cout << "打开源文件失败!!" << endl;
		return;
	}
	fgetc(infp);
	cout << "请输入目标文件: ";
	cin >> outfName;
	if ((outfp = fopen(outfName, "wb")) == NULL)
	{
		cout << "打开目标文件失败!!" << endl;
		return;
	}

	const int n = 256;
	char ch[n];
	int w[n];
	int i, size = 0;
	char cha;

	for (i = 0; i < n; i++)
	{         //初始化ch[],w[]          
		ch[i] = (char)i;
		w[i] = 0;
	}

	rewind(infp);                               //使源文件指针指向文件开始处
	cha = fgetc(infp);                          //取出源文件第一个字符
	while (!feof(infp))
	{
		w[(char)cha]++;                         //字符cha出现频度自增1
		size++;                                 //文件大小自增1
		cha = fgetc(infp);                      //取出文件下一字符
	}
	if (pHuffmanTree != NULL)
		delete[] pHuffmanTree;                 //释放空间
	pHuffmanTree = new HuffmanTree();          
	pHuffmanTree->CreateHuffmanTree(ch, w, n);  //创建哈夫曼树
	rewind(outfp);
	fwrite(&size, sizeof(int), 1, outfp);       //向目标文件写入源文件大小
	for (i = 0; i < n; i++)
	{            //向目标文件写入字符出现频度
		fwrite(&w[i], sizeof(int), 1, outfp);
	}
	buf.bits = 0;      
	buf.ch = 0;
	rewind(infp);
	cha = fgetc(infp);
	while (!feof(infp))
	{           //对源文件字符进行编码，并将编码写入目标文件
		String strTmp = pHuffmanTree->EnCode(cha);         //字符编码
		for (i = 0; i < strTmp.Length(); i++)
		{         //向目标文件写入编码
			if (strTmp[i] == '0')              //写入0
				Write(0);                      //写入1
			else
				Write(1);
		}
		cha = fgetc(infp);
	}
	WriteToOutfp();                           //强行写入目标文件

	fclose(infp);
	fclose(outfp);
}

void HuffmanCompress::DeCompress()
{
	char infName[256], outfName[256];
	cout << "请输入压缩文件名: ";
	cin >> infName;
	if ((infp = fopen(infName, "rb")) == NULL)
	{
		cout << "打开源文件失败!!" << endl;
		return;
	}
	cout << "请输入目标文件名: ";
	cin >> outfName;
	if ((outfp = fopen(outfName, "wb")) == NULL)
	{
		cout << "打开目标文件失败!!" << endl;
		return;
	}
	const int n = 256;
	char ch[n];
	int w[n];
	int i, size;
	char cha;
	rewind(infp);
	fread(&size, sizeof(int), 1, infp);                     //取出目标文件的大小
	for (i = 0; i < n; i++)
	{
		ch[i] = (char)i;
		fread(&w[i], sizeof(int), 1, infp);                 //取出目标文件字符频度
	}
	if (pHuffmanTree != NULL)
		delete[] pHuffmanTree;
	pHuffmanTree = new HuffmanTree();
	pHuffmanTree->CreateHuffmanTree(ch, w, n);              //创建Huffman树
	int len = 0;
	char p[100000];
	int k = 0;
	cha = fgetc(infp);
	while (!feof(infp))
	{
		for(int i = 7; i >= 0; i--)
		{             //将1byte数据转换成二进制串
			if ((cha >> i) & 1)
				p[k] = '1';                          
			else
				p[k] = '0';
			k++;
		}
		cha = fgetc(infp);
	}
	p[k] = '\0';
	String temp(p);
	NodeList<char> strTemp = pHuffmanTree->DeCode(temp);
	while(true)
	{
		len++;
		fputc(strTemp.GetItemPtr(1)->data, outfp);
		strTemp.Delete(1);
		if (len == size) break;
	}
	fclose(infp);
	fclose(outfp);
}
