#include"TLinkList.h"
#include<iostream>
using namespace std;

int main() {
	TLinkList list;
	int a, b;
	cin >> a;
	while (a != -1) {
		cin >> b;
		list.addOneForTest(a, b);
		list.showLinkData();
		cin >> a;
	}
	return EXIT_SUCCESS;
}