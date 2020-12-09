#include"fct.h"

int main() {
	Ginfo infomation;
	Ginfo* info;
	Land* cur;

	info = &infomation;
	GetTheDataAndBasicSet(info);
	info->map = CreateMapAndInitialize(info);
	initgraph(info->Wxs, info->yxs);
	while (1) {
		switch (Open(info)) {
		case StartTheG:
			PauseTheGame(info);
			break;
		case Set:
			SetTheGame(info);
			break;
		case Exit:
			exit(148);
		default:
			break;
		}
	}
	closegraph();
	return 0;
}