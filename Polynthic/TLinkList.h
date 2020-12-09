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
	}node;
	//��ӽڵ�
	void addNode(node target);
	void addNode(int coe, int ind);
	//�Ƚ������ڵ��ֵ
	int compare(node a, node b);
public:
	node* head;//��¼ͷ�ڵ�ĵ�ַ
	node* tail;//��¼���һ����null�Ľڵ�
	//���캯��
	TLinkList();
	//������������
	void showLinkData();
	//����һ���ڵ�
	void addOneForTest(int coe, int ind);
	//�ڵ����
};

