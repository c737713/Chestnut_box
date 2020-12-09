#pragma once
class TLinkList
{
private:
	typedef struct linkListNode
	{
		int coe;//系数:coeffcient
		int ind;//指数:index
		linkListNode* next;//记录下一个节点的地址
		linkListNode* pre;//前一个节点的地址
	}node;
	//添加节点
	void addNode(node target);
	void addNode(int coe, int ind);
	//比较两个节点的值
	int compare(node a, node b);
public:
	node* head;//记录头节点的地址
	node* tail;//记录最后一个非null的节点
	//构造函数
	TLinkList();
	//浏览链表的内容
	void showLinkData();
	//增加一个节点
	void addOneForTest(int coe, int ind);
	//节点相加
};

