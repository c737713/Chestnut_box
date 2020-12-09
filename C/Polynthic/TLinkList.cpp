#include"TLinkList.h"
#include<iostream>
using namespace std;

TLinkList::TLinkList() {
	this->head = new node;
	this->head->coe = -100;
	this->head->ind = -86;
	this->head->pre = nullptr;
	this->tail = head;
	this->head->next = nullptr;
}

int TLinkList::compare(node a, node b) {
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

void TLinkList::addNode(node target) {
	node* cur;//�Ƚ������ڵ��ֵ
	if (target.coe == 0) {//���ϵ��Ϊ0
		return;
	}
	//Ѱ�ҵ�Ŀ���Ǵ�����ڵ�λ�õ�ǰһ��
	for (cur = head; cur->next != nullptr && compare(target, *(cur->next)) > 0; cur = cur->next);
	if (cur == tail) {//���û�з���Ҫ��Ľڵ�λ��
		node* temp = new node;
		temp->coe = target.coe;
		temp->ind = target.ind;
		temp->pre = tail;
		temp->next = nullptr;
		tail->next = temp;
		tail = temp;
	}
	else if (cur->next->ind == target.ind) {
		node* tempTarget = cur->next;
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
		node* tempNode = new node;
		tempNode->coe = target.coe;
		tempNode->ind = target.ind;
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
	node temp;
	temp.coe = coe;
	temp.ind = ind;
	addNode(temp);
}

void TLinkList::showLinkData() {
	node* cur = nullptr;
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
	node* cur;
	for (cur = a.head->next; cur != nullptr; cur = cur->next) {
		result->addNode(*cur);
	}
	for (cur = b.head->next; cur != nullptr; cur = cur->next) {
		result->addNode(*cur);
	}
	this->head = result->head;
	this->tail = result->tail;
}
