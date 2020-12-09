#pragma once
class TLinkList
{
private:
	typedef struct linkListNode
	{
		int coe;//ϵ��:coeffcient
		int ind;//ָ��:index
		linkListNode* next;//��¼��һ���ڵ�ĵ�ַ
		linkListNode* pre;//ǰһ���ڵ�ĵ�ַ
	}NODE;
	//��ӽڵ�
	void addNode(NODE target);
	void addNode(int coe, int ind);
	//�Ƚ������ڵ��ֵ
	int compare(NODE a, NODE b);
	//�����ڵ����
	void nodeMul(NODE a, NODE b,NODE*c);
public:
	NODE* head;//��¼ͷ�ڵ�ĵ�ַ
	NODE* tail;//��¼���һ����null�Ľڵ�
	//���캯��
	TLinkList();
	//������������
	void showLinkData();
	//����һ���ڵ�
	void addOneForTest(int coe, int ind);
	//����ʽ���
	void PolyAdd(TLinkList a, TLinkList b);
private:
	//���ֺ����޷�����
	//�ڵ㹹�캯��
	inline NODE getNode(int coe, int ind) {
		NODE temp;
		temp.pre = nullptr;
		temp.next = nullptr;
		temp.ind = ind;
		temp.coe = coe;
		return temp;
	}
	//�ڵ���˺���
	inline NODE nudeMul(NODE a, NODE b) {
		int coe = a.coe * b.coe;
		int ind = a.ind + b.ind;
		return getNode(coe, ind);
	}
};

