#pragma once
#include"HuffmanTreeNode.h"
#include"String.h"
#include<list>
#include"NodeList.h"
#include<iostream>
using namespace std;
class HuffmanTree
{
public:
	HuffmanTreeNode* nodes;                                //Huffman树结点
	char* leafchars;                                       //叶节点代表的字符
	String *leafcharcodes;                                 //叶节点代表的字符的Huffman编码
	int curpos;
	int num;                                               //叶节点数
	void Select(int cur, int &r1, int &r2);                //选出从1到cur节点中权值最小两个节点


	HuffmanTree() {};
	void CreateHuffmanTree(char ch[], int w[], int n);     //由字符和权值构建Huffman树
	String EnCode(char ch);                                //编码
	NodeList<char> DeCode(String strCode);                 //译码
};


String HuffmanTree::EnCode(char ch)
{
	for (int pos = 0; pos <= num; pos++)
	{
		if (leafchars[pos] == ch)
			return leafcharcodes[pos];
	}
}

NodeList<char> HuffmanTree::DeCode(String strCode)
{
	NodeList<char> charlist;
	for (int i = 1; i <= 2 * num - 1; i++)
		if (nodes[i].parent == 0)
			curpos = i;
	for (int pos = 0; pos < strCode.Length(); pos++)
	{
		if (strCode[pos] == '0')                                     
		{
			//cout << nodes[curpos].leftchild << endl;
			curpos = nodes[curpos].leftchild;                      //当前编码为‘0’访问左节点
		}
		else                                                         
		{
			//cout << nodes[curpos].rightchild << endl;
			curpos = nodes[curpos].rightchild;                     //当前编码为‘1’访问右节点
		}

		if (nodes[curpos].leftchild == 0 && nodes[curpos].rightchild == 0)    //当前为叶节点
		{
			charlist.Insert(charlist.Length() + 1, leafchars[curpos]);       //将译出的字符加入链表
			curpos = 2 * num - 1;
		}
	}
	return charlist;
}

void HuffmanTree::CreateHuffmanTree(char ch[], int w[], int n)
{
	num = n;
	int m = 2 * n - 1;

	nodes = new HuffmanTreeNode[m + 1];
	leafchars = new char[n + 1];
	leafcharcodes = new String[n + 1];

	for (int pos = 1; pos <= n; pos++)
	{
		nodes[pos].weight = w[pos - 1];
		leafchars[pos] = ch[pos - 1];
	}

	for (int pos = n + 1; pos <= m; pos++)
	{
		int r1 = 0, r2 = 0;
		Select(pos - 1, r1, r2);
		nodes[r1].parent = pos;
		nodes[r2].parent = pos;
		nodes[pos].leftchild = r1;
		nodes[pos].rightchild = r2;
		nodes[pos].weight = nodes[r1].weight + nodes[r2].weight;
	}

	for (int pos = 1; pos <= n; pos++)
	{
		char x = '1';
		char y = '0';
		NodeList<char> charcode;
		for (int child = pos, parent = nodes[child].parent; parent != 0;
			child = parent, parent = nodes[child].parent)
		{
			if (nodes[parent].leftchild == child)
			{
				charcode.Insert(1, y);
			}
			else
				charcode.Insert(1,x);
		}
		char p[50];
		int j = 0;
		while (!charcode.Empty())
		{
			p[j] = charcode.GetItemPtr(1)->data;
			j++;
			charcode.Delete(1);
		}
		p[j] = '\0';
		String P(p);
		leafcharcodes[pos] = P;
	}
	curpos = m;
}


void HuffmanTree::Select(int cur, int & r1, int & r2)
{
	nodes[0].weight = 10000;
	for (int i = 1; i <= cur; i++)
	{
		if (nodes[i].weight < nodes[r1].weight && nodes[i].parent == 0)
			r1 = i;
	}
	for (int i = 1; i <= cur; i++)
	{
		if (nodes[i].weight < nodes[r2].weight && i != r1 && nodes[i].parent == 0)
			r2 = i;
	}
}
