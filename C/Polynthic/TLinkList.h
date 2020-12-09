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
	}NODE;
	//添加节点
	void addNode(NODE target);
	void addNode(int coe, int ind);
	//比较两个节点的值
	int compare(NODE a, NODE b);
	//两个节点相乘
	void nodeMul(NODE a, NODE b,NODE*c);
public:
	NODE* head;//记录头节点的地址
	NODE* tail;//记录最后一个非null的节点
	//构造函数
	TLinkList();
	//浏览链表的内容
	void showLinkData();
	//增加一个节点
	void addOneForTest(int coe, int ind);
	//多项式相加
	void PolyAdd(TLinkList a, TLinkList b);
private:
	//部分函数无法内联
	//节点构造函数
	inline NODE getNode(int coe, int ind) {
		NODE temp;
		temp.pre = nullptr;
		temp.next = nullptr;
		temp.ind = ind;
		temp.coe = coe;
		return temp;
	}
	//节点相乘函数
	inline NODE nudeMul(NODE a, NODE b) {
		int coe = a.coe * b.coe;
		int ind = a.ind + b.ind;
		return getNode(coe, ind);
	}
};

