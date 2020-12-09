#include"TLinkList.h"
#include<iostream>
using namespace std;


TLinkList::TLinkList() {
	this->head = new NODE;
	this->head->coe = -100;
	this->head->ind = -86;
	this->head->pre = nullptr;
	this->tail = head;
	this->head->next = nullptr;
}

int TLinkList::compare(NODE a, NODE b) {
	if (a.ind > b.ind) {
		return 1;
	}
	else if (a.ind == b.ind) {
		return 0;
	}
	else {
		return -1;
	}
}

void TLinkList::addNode(NODE target) {
	NODE* cur;//�Ƚ������ڵ��ֵ
	if (target.coe == 0) {//���ϵ��Ϊ0
		return;
	}
	//Ѱ�ҵ�Ŀ���Ǵ�����ڵ�λ�õ�ǰһ��
	for (cur = head; cur->next != nullptr && compare(target, *(cur->next)) > 0; cur = cur->next);
	if (cur == tail) {//���û�з���Ҫ��Ľڵ�λ��
		NODE* temp = new NODE;
		*temp = getNode(target.coe, target.ind);
		temp->pre = tail;
		tail->next = temp;
		tail = temp;
	}
	else if (cur->next->ind == target.ind) {
		NODE* tempTarget = cur->next;
		tempTarget->coe += target.coe;
		if (tempTarget->coe == 0) {//��ɺ�Ľڵ����Ϊ0�����ɾ������
			printf("ϵ��Ϊ0,ɾ��\n");
			tempTarget->pre->next = tempTarget->next;
			if (tempTarget->next != nullptr) {
				tempTarget->next->pre = tempTarget->pre;
			}
			delete(tempTarget);
		}
	}
	else if (target.ind > cur->ind) {//����ҵ�Ŀ��λ��,�Ҹô���δ����
		NODE* tempNode = new NODE;
		*tempNode = getNode(target.coe, target.ind);
		tempNode->pre = cur;
		tempNode->next = cur->next;
		cur->next = tempNode;
		tempNode->next->pre = tempNode;
	}
	else {
		cout << "ERROR" << endl;
	}
}

void TLinkList::addNode(int coe, int ind) {
	NODE temp=getNode(coe,ind);
	addNode(temp);
}

void TLinkList::showLinkData() {
	NODE* cur = nullptr;
	if (head->next == nullptr) {
		cout << "\aΪ��" << endl;
	}
	for (cur = head->next; cur != nullptr; cur = cur->next) {
		if (cur != head->next) {
			cout << " + ";
		}
		cout << cur->coe << "X^" << cur->ind;
	}
	cout << endl;
}

void TLinkList::addOneForTest(int coe, int ind) {
	addNode(coe, ind);
}

void TLinkList::PolyAdd(TLinkList a, TLinkList b) {
	TLinkList* result = new TLinkList;
	NODE* cur;
	for (cur = a.head->next; cur != nullptr; cur = cur->next) {
		result->addNode(*cur);
	}
	for (cur = b.head->next; cur != nullptr; cur = cur->next) {
		result->addNode(*cur);
	}
	this->head = result->head;
	this->tail = result->tail;
}