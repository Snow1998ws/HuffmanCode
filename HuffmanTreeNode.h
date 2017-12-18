#pragma once
class HuffmanTreeNode
{
public:
	int weight;
	int parent, leftchild, rightchild;

	HuffmanTreeNode(int w = 0, int p = 0, int lchild = 0, int rchild = 0)
	{
		weight = w;
		parent = p;
		leftchild = lchild;
		rightchild = rchild;
	}
};
