#pragma once

#include"��ͷ.h"
#include<time.h>
#include<graphics.h>
#include<conio.h>
#include <windows.h>

typedef enum Output {
	BLANK, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, WALL, Flag, Unwatched, Player
}OUTPUT;//ö������ļ������
typedef enum Result {
	Win, Lost, None
}RES;//ö����Ϸ����ļ������
typedef enum Action {
	MOVE, WIPE, FLAG, PAUSE
}ACT;//ö������ж��ļ������
typedef enum ActionInOpen {
	StartTheG, Set, Exit, NONE
};//��ʼ�˵�����Ҽ���ѡ��
typedef struct ZeroCoord {
	int x;
	int y;
}ZC;//��¼��ͼ���Ƶ�������
typedef struct Land {
	OUTPUT LandOutPut;
	bool Mine;
	bool Boundary;
	bool watched;
	bool flag;
	bool pla;
	int AroundMine;
	int size;
	COORD coordinate;
}Land;//ÿ�����ӵ�
typedef struct PictureStore {
	IMAGE p0;
	IMAGE p1;
	IMAGE p2;
	IMAGE p3;
	IMAGE p4;
	IMAGE p5;
	IMAGE p6;
	IMAGE p7;
	IMAGE p8;
	IMAGE uwd;
	IMAGE wal;
	IMAGE flag;
	IMAGE start;
	IMAGE success;
	IMAGE lost;
	IMAGE pause;
	IMAGE set;
	IMAGE Game;
}PS;
typedef struct Gameinformation {
	int Width;//���,x,j;
	int Higth;//�߶�,y,i;
	int NumOfMine;//�׵�����
	int NumOfFlag;//��������
	int Score;
	int NumofStep;
	int Wxs;
	int yxs;
	int LastTime;
	Land** map;//��ͼģ��
	PS PictureStore;
	ZC  ZeroAboutP;//��Ϸ����֮ǰ��������
	COORD pla;
}Ginfo;
typedef struct GameNotes {
	int num;//��¼���ǵڼ��γɹ�����ļ�¼
	int time;//ʱ��
	int numofmine;//��¼����׵Ĳ�������
}Note;
typedef struct ListNote {
	int NumofNote;
	Note* ListofNote;
}ListNotes;
////////////////////////////////////////////�������

void GetTheDataAndBasicSet(Ginfo* info);//��������������
Land** CreateMapAndInitialize(Ginfo* info);//�����ڴ洴����ͼ,��ʼ���������ӵ�����
void LayTheMine(Ginfo* info);//����:)
void LoadGameImage(Ginfo* info);//������Ϸ����ͼ��
void LoadFaceImage(Ginfo* info);//���ؽ����ͼ��
ActionInOpen Open(Ginfo* info);//��ʼ�����ͼ��
OUTPUT CheckStatus(Land* target);//ͨ���������������,ȷ�����ӵ���ʾ״̬
RES CheckMine(Ginfo* info, COORD* pos);//����:)
int CountAroundMines(Ginfo* info, COORD pos);//�������������Χ��������
RES CheckAround(Ginfo* info, COORD pos);//�����׽��,Ȼ����Ϊ������������Ĺ���
void PauseTheGame(Ginfo* info);//��������Ĵ���
int GAMEing(Ginfo* info);//��Ϸ����Ĺ���
void RefreshMapForInitialize(Ginfo* info);//���ڳ�ʼ���ĵ�ͼˢ��
void updata(Ginfo* info, COORD pos);//ͨ�����������������ʾ�ı��������ض�λ��ˢ��ͼ��
Land* CordTurnToPos(COORD pos, Ginfo* info);//С����,������ת��Ϊ�ض����ӵĵ�ַ
Action GetAction(Ginfo* info);//��ȡ��������
COORD* GoThroughEightCORD(COORD pos);//С����,�й��ɵػ�ȡһ��������Χ��8�����ӵĵ�ַ,��checkaround����Ҫ
bool FineToCheck(COORD pos, Ginfo* info);//�Ƿ�okȥ����,��checkaround����Ҫ
void Success(Ginfo* info);//�ɹ�����
void Lostsence(Ginfo* info);//ʧ�ܽ���
RES WinChecking(Ginfo* info);//ʤ���ж�:)
void Refreshmap(Ginfo* info);//ˢ��������ͼ
void PutOnFlagRIGHT(Ginfo* info);//����>^<
void PutOnFlag(Ginfo* info, COORD pos);//��ĳ��λ������
COORD MouseClickintopos(Ginfo* info, MOUSEMSG m);//�������ת��Ϊ�����ϵľ�����ӵ�����
void DrawSthAtSp(ZC Zero, IMAGE* target, COORD pos);//��ĳ��λ�û���ĳ��ͼ��,��updata����Ҫ����
void PutOnFlag(Ginfo* info, COORD pos);//����:)
RES AutoCheck(Ginfo* info, COORD* cor);//�м��¼�:)
int CountAroundFLag(Ginfo* info, COORD pos);//������Χ����������,�м��¼�����Ҫ����
ListNotes* Read();//����һ����Ϸ��¼��,��������������ֵ��һ��
int AddandLoad(int score, ListNote* target, int NumofMine);//д���¼���浵
int SortTheNotes();//�����ļ���¼
int SetTheGame(Ginfo* info);//���ý���
int Cheat(Ginfo* info);//��ʾ

////////////////////////////////////////����ʵ��

Land** CreateMapAndInitialize(Ginfo* info) {
	Land** head, * cur;
	int width = info->Width + 2;
	int higth = info->Higth + 2;
	//CreateMap
	head = (Land**)malloc(sizeof(Land*) * higth);
	for (int i = 0; i < higth; i++) {
		head[i] = (Land*)malloc(sizeof(Land) * width);
	}
	for (int i = 0; i < higth; i++) {
		for (int j = 0; j < width; j++) {
			cur = *(head + i) + j;
			if (i == 0 || i == higth - 1) {
				cur->Boundary = TRUE;
			}
			else if (j == 0 || j == width - 1) {
				cur->Boundary = TRUE;
			}
			else {
				cur->Boundary = FALSE;
			}
			cur->Mine = FALSE;
			cur->LandOutPut = BLANK;
			cur->watched = true;
			cur->AroundMine = 0;
			cur->flag = FALSE;
			cur->coordinate.X = j;
			cur->coordinate.Y = i;
		}
	}
	return head;
}
void GetTheDataAndBasicSet(Ginfo* info) {
	FILE* fp;
	info->Width = 14;
	info->Higth = 8;
	info->NumOfMine = (info->Higth * info->Width) * 0.08;
	if (info->Width > 10 && info->Higth > 10) {
		info->Wxs = info->Width * 30 + 100;
		info->yxs = info->Higth * 30 + 100;
	}
	else {
		info->Wxs = 640;
		info->yxs = 400;
	}
	LoadGameImage(info);
	LoadFaceImage(info);
	//info->NumOfMine = 4;
	info->NumOfFlag = info->NumOfMine;
	info->Score = 0;
	info->NumofStep = 0;
	info->ZeroAboutP.x = 100;
	info->ZeroAboutP.y = 120;
	info->LastTime = -1;
	fp = fopen("score.txt", "r");
	if (fp == NULL) {
		fp = fopen("score.txt", "a+");
		fprintf(fp, "%d", 0);
	}
	fclose(fp);
	return;
}
void PauseTheGame(Ginfo* info) {
	MOUSEMSG m;
	ListNote* LN = NULL;
	int temp = 0;
	cleardevice();//��մ���
	putimage(0, 0, &(info->PictureStore.pause));//����ͼ����϶�Ӧ�ý����ͼƬ
	while (1) {
		m = GetMouseMsg();//��ȡ������Ϣ
		if (m.x > info->Wxs * 0.8 && m.y > info->yxs * 0.8) {
			if (m.uMsg == WM_LBUTTONDOWN) {
				temp = GAMEing(info);//��������,��ʼ��Ϸ
				if (temp > 0) {//temp��¼��Ϸʱ��,�����Ϸʱ���Ƿ���¼��
					info->LastTime = temp;
					LN = Read();//���洢���ļ������а�������ȡ��������LN��
					AddandLoad(temp, LN, info->NumOfMine);//�����м�����һ�εļ�¼�������ļ�
					SortTheNotes();//�ٴζ�д������,����Ǻ����ӵ�,�����.ԭ��������ô�鷳
				}
				return;//����������������
			}
		}
	}
}
COORD MouseClickintopos(Ginfo* info, MOUSEMSG m) {
	short x;
	short y;
	COORD cur;
	cur = { -100,-100 };
	x = (m.x - info->ZeroAboutP.x) / 30 + 1;
	y = (m.y - info->ZeroAboutP.y) / 30 + 1;
	if (x < 1 || x >= info->Width + 1 || y < 1 || y >= info->Higth + 1) {
		return cur;
	}
	cur = { x,y };
	return cur;
}
Land* CordTurnToPos(COORD pos, Ginfo* info) {
	int x = 0, y = 0;
	Land* cur;
	x = pos.X;
	y = pos.Y;
	cur = *(info->map + y) + x;
	return cur;
}
bool OKtoLaytheMine(COORD pos, Ginfo* info) {
	Land* cur;
	cur = CordTurnToPos(pos, info);
	if (cur->Boundary == true || cur->Mine == true) {
		return false;
	}
	else if (pos.X == info->pla.X && pos.Y == info->pla.Y) {
		return false;
	}
	else if (CountAroundMines(info, pos) == 8) {
		return false;
	}
	return true;
}
void LayTheMine(Ginfo* info) {
	srand((unsigned)time(NULL));
	int x, y;
	COORD por;
	Land* cur;
	for (int i = 0; i < info->NumOfMine; i++) {
		while (1) {
			x = rand() % info->Width;
			y = rand() % info->Higth;
			por = { (short)x,(short)y };
			cur = CordTurnToPos(por, info);
			if (OKtoLaytheMine(por, info) == true) {
				cur->Mine = TRUE;
				break;
			}
		}
	}
}
void LoadGameImage(Ginfo* info) {
	PS* Pstore;
	Pstore = &(info->PictureStore);
	loadimage(&(Pstore->p0), "P\\0.jpg", 30, 30);
	loadimage(&(Pstore->p1), "P\\1.jpg", 30, 30);
	loadimage(&(Pstore->p2), "P\\2.jpg", 30, 30);
	loadimage(&(Pstore->p3), "P\\3.jpg", 30, 30);
	loadimage(&(Pstore->p4), "P\\4.jpg", 30, 30);
	loadimage(&(Pstore->p5), "P\\5.jpg", 30, 30);
	loadimage(&(Pstore->p6), "P\\6.jpg", 30, 30);
	loadimage(&(Pstore->p7), "P\\7.jpg", 30, 30);
	loadimage(&(Pstore->p8), "P\\8.jpg", 30, 30);
	loadimage(&(Pstore->flag), "P\\flag.jpg", 30, 30);
	loadimage(&(Pstore->uwd), "P\\uwd.jpg", 30, 30);
	//loadimage(&(Pstore->wal), "P\\wall1.jpg", 30, 30);
	return;
}
void LoadFaceImage(Ginfo* info) {
	PS* Pstore;
	int x, y;
	x = info->Wxs;
	y = info->yxs;
	Pstore = &(info->PictureStore);
	loadimage(&(Pstore->Game), "P\\game.jpg", x, y);
	loadimage(&(Pstore->lost), "P\\lost.jpg", x, y);
	loadimage(&(Pstore->pause), "P\\pause.jpg", x, y);
	loadimage(&(Pstore->set), "P\\set.jpg", x, y);
	loadimage(&(Pstore->start), "P\\start.jpg", x, y);
	loadimage(&(Pstore->success), "P\\success.jpg", x, y);
	return;
}
void DrawSthAtSp(ZC Zero, IMAGE* target, COORD pos) {
	int x, y;
	x = Zero.x;
	y = Zero.y;
	x += (pos.X - 1) * 30;
	y += (pos.Y - 1) * 30;
	putimage(x, y, target);
	return;
}
OUTPUT CheckStatus(Land* target) {
	Land* cur;
	cur = target;
	if (cur->Boundary == true) {
		return WALL;
	}
	else if (cur->flag == true && cur->watched == false) {
		return Flag;
	}
	else if (cur->watched == false) {
		return Unwatched;
	}
	else {
		switch (cur->AroundMine) {
		case 0:
			return BLANK;
		case 1:
			return ONE;
		case 2:
			return TWO;
		case 3:
			return THREE;
		case 4:
			return FOUR;
		case 5:
			return FIVE;
		case 6:
			return SIX;
		case 7:
			return SEVEN;
		case 8:
			return EIGHT;
		}
	}
	return WALL;
}
RES CheckMine(Ginfo* info, COORD* pos) {
	Land* cur;
	cur = *(info->map + pos->Y) + pos->X;
	if (cur->flag == false) {//�ж��Ƿ񱻲���,����Ĳ��ܱ���(����)
		cur->watched = true;//���²���
		if (cur->Mine == true) {
			return Lost;//�������������,��ʧ��
		}
		else {
			cur->AroundMine = CountAroundMines(info, *pos);//��ȡ��Χ�׵�����
			cur->LandOutPut = CheckStatus(cur);//������������������ʾ
			updata(info, *pos);//����ͼ��
			if (cur->AroundMine == 0) {
				CheckAround(info, *pos);//�����Χһ���׶�û�м�����
			}
		}
	}
	return None;//ûʧ�ܼ����·���
}
void updata(Ginfo* info, COORD pos) {
	IMAGE* target = NULL;
	Land* cur = NULL;
	cur = *(info->map + pos.Y) + pos.X;
	cur->LandOutPut = CheckStatus(cur);
	switch (cur->LandOutPut) {
	case BLANK:
		target = &(info->PictureStore.p0);
		break;
	case ONE:
		target = &(info->PictureStore.p1);
		break;
	case TWO:
		target = &(info->PictureStore.p2);
		break;
	case THREE:
		target = &(info->PictureStore.p3);
		break;
	case FOUR:
		target = &(info->PictureStore.p4);
		break;
	case FIVE:
		target = &(info->PictureStore.p5);
		break;
	case SIX:
		target = &(info->PictureStore.p6);
		break;
	case SEVEN:
		target = &(info->PictureStore.p7);
		break;
	case EIGHT:
		target = &(info->PictureStore.p8);
		break;
	case WALL:
		target = &(info->PictureStore.wal);
		break;
	case Unwatched:
		target = &(info->PictureStore.uwd);
		break;
	case Flag:
		target = &(info->PictureStore.flag);
		break;
	}
	DrawSthAtSp(info->ZeroAboutP, target, pos);
	return;
}
ActionInOpen Open(Ginfo* info) {
	MOUSEMSG m;
	char text[100];
	cleardevice();
	putimage(0, 0, &(info->PictureStore.start));
	if (info->LastTime > 0) {
		sprintf_s(text, "�ϴε�ɨ����ʱΪ%d��", info->LastTime);
		outtextxy(0.3 * info->Wxs, 0.01 * info->yxs, text);
	}
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x <= info->Wxs * 0.2) {
				if (m.y >= info->yxs * 0.8) {
					return StartTheG;
				}
				else {
					break;
				}
			}
			else if (m.x >= info->Wxs * 0.8) {
				if (m.y <= info->yxs * 0.2) {
					return Exit;
				}
				else if (m.y >= info->yxs * 0.8) {
					return Set;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
	}
	return NONE;
}
int CountAroundMines(Ginfo* info, COORD pos) {
	int x, y, count = 0;
	COORD* cur = NULL, * target;
	Land* landcur = NULL;
	target = GoThroughEightCORD(pos);
	cur = target;
	for (int i = 0; i < 8; i++, cur++) {
		x = cur->X;
		y = cur->Y;
		landcur = *(info->map + y) + x;
		if (landcur->Mine == TRUE) {
			count++;
		}
	}
	free(target);
	return count;
}
int CountAroundFLag(Ginfo* info, COORD pos) {
	int x, y, count = 0;
	COORD* cur = NULL, * target;
	Land* landcur = NULL;
	target = GoThroughEightCORD(pos);
	cur = target;
	for (int i = 0; i < 8; i++, cur++) {
		x = cur->X;
		y = cur->Y;
		landcur = *(info->map + y) + x;
		if (landcur->flag == TRUE) {
			count++;
		}
	}
	free(target);
	return count;
}
RES CheckAround(Ginfo* info, COORD pos) {
	COORD* cur, * target;
	Land* landcur;
	RES result;
	result = None;
	target = GoThroughEightCORD(pos);
	cur = target;
	for (int i = 0; i < 8; i++, cur++) {
		if (FineToCheck(*cur, info) == true) {
			landcur = *(info->map + cur->Y) + cur->X;
			if (landcur->watched == false && landcur->flag == false) {
				if (CheckMine(info, cur) == Lost) {
					free(target);
					return Lost;
				}
			}
		}
	}
	free(target);
	return None;
}
void RefreshMapForInitialize(Ginfo* info) {
	COORD curcoord;
	int i, j;
	for (i = 0; i < info->Higth + 2; i++) {
		for (j = 0; j < info->Width + 2; j++) {
			curcoord = { (short)j,(short)i };
			updata(info, curcoord);
		}
	}
	return;
}
bool FineToCheck(COORD pos, Ginfo* info) {
	int x, y;
	Land* cur;
	x = pos.X;
	y = pos.Y;
	cur = *(info->map + y) + x;
	if (cur->Boundary == TRUE) {
		return FALSE;
	}
	else if (cur->watched == TRUE) {
		return FALSE;
	}
	return TRUE;
}
void Success(Ginfo* info) {
	MOUSEMSG m;
	cleardevice();
	putimage(0, 0, &(info->PictureStore.success));
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			return;
		}
	}
}
void Lostsence(Ginfo* info) {
	MOUSEMSG m;
	cleardevice();
	putimage(0, 0, &(info->PictureStore.lost));
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			return;
		}
	}
}
void Refreshmap(Ginfo* info) {
	int i, j;
	Land* cur;
	COORD pos;
	for (i = 0; i < info->Higth + 2; i++) {
		for (j = 0; j < info->Width + 2; j++) {
			pos = { (short)j,(short)i };
			cur = *(info->map + i) + j;
			cur->Mine = false;
			cur->watched = false;
			cur->flag = false;
			cur->LandOutPut = BLANK;
			cur->AroundMine = 0;
		}
	}
	return;
}
RES WinChecking(Ginfo* info) {
	int unwatched = 0;
	int FlagedMine = 0;
	int check = 0;
	int i, j;
	char text[100];
	Land* cur;
	for (i = 0; i < info->Higth; i++) {
		for (j = 0; j < info->Width; j++) {
			cur = *(info->map + i + 1) + j + 1;
			if (cur->watched == false && cur->Boundary == false) {
				unwatched++;
			}
			if (cur->Mine == true && cur->flag == true) {
				FlagedMine++;
			}
		}
	}
	check = info->NumOfMine - FlagedMine;
	if (unwatched <= check || check <= 0) {
		//return Win;
	}
	if (unwatched == info->NumOfMine) {
		return Win;
	}
	return None;
}
COORD* GoThroughEightCORD(COORD pos) {
	SHORT x, y;
	COORD* cur;
	COORD* target;
	x = pos.X;
	y = pos.Y;
	target = (COORD*)malloc(sizeof(COORD) * 8);
	cur = target;
	*cur++ = { x - 1,y - 1 };
	*cur++ = { x - 1,y };
	*cur++ = { x - 1,y + 1 };
	*cur++ = { x,y - 1 };
	*cur++ = { x,y + 1 };
	*cur++ = { x + 1,y - 1 };
	*cur++ = { x + 1,y };
	*cur = { x + 1,y + 1 };
	return target;
}
void ProgressReporting(Ginfo* info) {
	char text[100], BLANK[100];
	int left = 0;
	strcpy(BLANK, "                                                           ");
	left = info->NumOfMine - (info->NumOfMine - info->NumOfFlag);
	if (left > info->NumOfMine * 0.5) {
		sprintf(text, "С�ĵ�,�����ӻ���%d��������", left);
	}
	else if (left > info->NumOfMine * 0.3) {
		sprintf(text, "��,��չ˳������%d����", left);
	}
	else if (left == 0) {
		sprintf(text, "��ɹ�ֻʣһ��֮ң!", left);
	}
	else {
		sprintf(text, "����,����,ֻʣ��%d����", left);
	}
	outtextxy(150, 10, BLANK);
	outtextxy(150, 10, text);
	return;
}
void PutOnFlag(Ginfo* info, COORD pos) {
	Land* cur;
	int x, y;
	x = pos.X;
	y = pos.Y;
	cur = *(info->map + y) + x;
	if (cur->Boundary == TRUE) {
		return;
	}
	else if (cur->watched == TRUE) {
		return;
	}
	else if (cur->flag == TRUE) {
		cur->flag = FALSE;
		info->NumOfFlag++;
		return;
	}
	else if (info->NumOfFlag > 0) {
		cur->flag = TRUE;
		info->NumOfFlag--;
		ProgressReporting(info);
		return;
	}
	else {
		return;
	}
}
RES AutoCheck(Ginfo* info, COORD* cor) {
	int NumofAroundFlag = 0;
	Land* cur;
	cur = CordTurnToPos(*cor, info);
	NumofAroundFlag = CountAroundFLag(info, *cor);
	if (cur->AroundMine <= NumofAroundFlag) {
		if (CheckAround(info, *cor) == Lost) {
			return Lost;
		}
	}
	return None;
}
int GAMEing(Ginfo* info) {
	Land* cur = NULL;
	RES result;
	COORD cor;
	MOUSEMSG m;
	int begin = 0, end = 0;
	begin = time(NULL);//��ʼ��ʱ
	char test;
	cleardevice();
	putimage(0, 0, &(info->PictureStore.Game));//ͬ��,��ʾ����
	Refreshmap(info);
	RefreshMapForInitialize(info);//��ʼ����ͼ
	info->NumofStep = 0;//��¼�Ƿ��ǵ�һ�ε��,����ʱ��Ҫ
	info->NumOfFlag = info->NumOfMine;
	while (1) {//����ѭ�������ȶ���
		while (1) {
			cur = NULL;
			cor = { -100,-100 };//��Чֵ,���������->����,�Ǹ�����
			result = None;//����ĳ�ֵΪNone,���·���
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > info->Wxs - info->ZeroAboutP.x && m.y < info->ZeroAboutP.y) {
					end = -1;
					result = Lost;//�������;�˳�,��Ϊֻ��resultΪwin&&Lost�ſ����˳�����ѭ��,����Ҫ��
					break;
				}
				if (m.x < info->ZeroAboutP.x + 30 && m.y < info->ZeroAboutP.y) {
					Cheat(info);//��������װ�ť,���С��,��չʾԴ��
					break;
				}
				cor = MouseClickintopos(info, m);
				if (cor.X != -100) {//�������Ϊ�˷�ֹ������Ч��ַ�ļ��
					cur = CordTurnToPos(cor, info);//���ϸ�����ת��Ϊ��ַ
				}
				else {
					break;
				}
				if (info->NumofStep == 0) {//������ж��ǲ��ǵ�һ�ε�
					if (cor.X != -100) {//ͬ��
						info->pla.X = cor.X;//��һ�ε�������Ϊ�������
						info->pla.Y = cor.Y;
						LayTheMine(info);//�׽�����������������,����ֹ��ҵ�һ����������
						result = CheckMine(info, &cor);//����֮����������λ��ִ�����
					}
				}
				else {
					if (cur->watched == false && cur != NULL) {
						result = CheckMine(info, &cor);//������λ��Ϊλ��,��ִ��win���������¼�
					}
					else if (cur != NULL) {
						result = AutoCheck(info, &cor);//Ϊδ֪,��ִ��win������м��¼�
					}
				}
				info->NumofStep++;
			}
			else if (m.uMsg == WM_RBUTTONDOWN) {
				cor = MouseClickintopos(info, m);
				if (cor.X != -100) {
					PutOnFlag(info, cor);//����Ҽ���Ч���������
					updata(info, cor);//ˢ������λ��
				}
			}

			if (result == None) {
				result = WinChecking(info);//���ǰ�治��ʧ�ܵĻ�,�����ʤ���ж�
			}
			if (result == Lost) {//ʧ����ֹͣ��ʱ,����ʧ�ܽ���
				end = time(NULL);
				Lostsence(info);
				break;
			}
			else if (result == Win) {//�ɹ���ֹͣ��ʱ,ֹͣ0.25����������ͽ���,����ɹ�����
				end = time(NULL);
				Sleep(250);
				Success(info);
				break;
			}
		}
		if (result == Win || result == Lost) {
			break;//ֻ�гɹ���ʧ�ܲſ�������ѭ��,����ȶ���
		}
	}
	if (result == Win) {
		return (end - begin);//ֻ�гɹ��Ż����ɼ�
	}
	else {
		return 0;//ʧ��û��Ȩ
	}
}
ListNotes* Read() {
	FILE* fp;
	Note* ListNote, * cur;
	ListNotes* LN;
	int CountofNotes = 0;
	LN = (ListNotes*)malloc(sizeof(ListNotes));
	fp = fopen("score.txt", "r");
	if (fp == NULL) {
		fp = fopen("score.txt", "a+");
		LN->NumofNote = 0;
	}
	else {
		fscanf(fp, "%d", &(LN->NumofNote));
		if (LN->NumofNote > 1000 || LN->NumofNote < -1000) {
			LN->NumofNote = 0;
		}
	}
	CountofNotes = LN->NumofNote;
	ListNote = (Note*)malloc(sizeof(Note) * (CountofNotes + 1));
	LN->ListofNote = ListNote;
	cur = ListNote;
	for (int i = 0; i < CountofNotes; i++) {
		fscanf(fp, "%d", &(cur->num));
		fscanf(fp, "%d", &(cur->time));
		fscanf(fp, "%d", &(cur->numofmine));
		cur++;
	}
	fclose(fp);
	return LN;
}
int AddandLoad(int score, ListNote* target, int NumofMine) {
	int i;
	Note* cur;
	FILE* fp;
	//add
	cur = target->ListofNote;
	for (i = 0; i < target->NumofNote; i++) {
		cur++;
	}
	target->NumofNote++;
	cur->num = target->NumofNote;
	cur->time = score;
	cur->numofmine = NumofMine;
	//load
	fp = fopen("score.txt", "w");
	if (fp == NULL) {
		exit(148);
	}
	cur = target->ListofNote;
	fprintf(fp, "%d\n", target->NumofNote);
	for (int i = 0; i < target->NumofNote; i++) {
		if (cur->num<1000 && cur->num>-1) {
			fprintf(fp, "%d %d %d\n", cur->num, cur->time, cur->numofmine);
		}
		cur++;
	}
	fclose(fp);
	return 0;
}
int SortTheNotes() {
	FILE* fp;
	ListNotes* LN, LIST;
	Note* cur, temp;
	float score1, score2;
	int min, i, j;
	LN = &LIST;
	fp = fopen("score.txt", "r");
	fscanf(fp, "%d", &(LN->NumofNote));
	if (LN->NumofNote > 1000 || LN->NumofNote < -1000) {
		LN->NumofNote = 0;
	}
	LN->ListofNote = (Note*)malloc(sizeof(Note) * (LN->NumofNote + 1));
	cur = LN->ListofNote;
	for (int i = 0; i < LN->NumofNote; i++) {
		fscanf(fp, "%d", &(cur->num));
		fscanf(fp, "%d", &(cur->time));
		fscanf(fp, "%d", &(cur->numofmine));
		cur++;
	}
	fclose(fp);
	Note* List;
	List = LN->ListofNote;
	for (i = 0; i < LN->NumofNote; i++) {
		min = i;
		for (j = i; j < LN->NumofNote; j++) {
			score1 = (float)(List + j)->time / (float)(List + j)->numofmine;
			score2 = (float)(List + min)->time / (float)(List + min)->numofmine;
			if (score1 < score2) {
				min = j;
			}
		}
		if (min != i) {
			temp.time = (List + i)->time;
			(List + i)->time = (List + min)->time;
			(List + min)->time = temp.time;

			temp.num = (List + i)->num;
			(List + i)->num = (List + min)->num;
			(List + min)->num = temp.num;

			temp.numofmine = (List + i)->numofmine;
			(List + i)->numofmine = (List + min)->numofmine;
			(List + min)->numofmine = temp.numofmine;
		}
	}
	fp = fopen("score.txt", "w");
	if (fp == NULL) {
		exit(148);
	}
	cur = LN->ListofNote;
	fprintf(fp, "%d\n", LN->NumofNote);
	for (int i = 0; i < LN->NumofNote; i++) {
		if (cur->num<1000 && cur->num>-1) {
			fprintf(fp, "%d %d %d\n", cur->num, cur->time, cur->numofmine);
		}
		cur++;
	}

	fclose(fp);
	return 0;
}
int SetTheGame(Ginfo* info) {
	MOUSEMSG m;
	ListNote* note;
	int i, j, mc;
	Note* cur;
	int x = 150;
	int y = 20;
	char text[70], BLANK[1000];
	cleardevice();
	putimage(0, 0, &(info->PictureStore.set));
	SortTheNotes();
	note = Read();
	strcpy(BLANK, "                                                                                                            ");
	if (info->LastTime <= 0) {
		sprintf_s(text, "ͬ־,�㻹û�п�ʼ�������,զ����鿴�ɼ���?");
		outtextxy(x, 10, text);
	}
	else {
		for (i = 0, mc = 0, cur = note->ListofNote; i < note->NumofNote; i++, cur++) {
			if (cur->time < info->LastTime) {
				mc++;
			}
		}
		if (mc == 0) {
			sprintf(text, "ͬ־,��������������ɨ��սʿ");
			outtextxy(x, 10, text);
		}
		else if (mc < 10) {
			sprintf(text, "ͬ־,��ǰ�滹��%dλ�����������,�ٽ������", mc);
			outtextxy(x, 10, text);
		}
		else {
			sprintf(text, "ͬ־,���Ч��̫����,��%dλͬ־�����,�����뱳��������?", mc);
			outtextxy(x, 10, text);
		}
	}
	for (i = 0, cur = note->ListofNote; i < note->NumofNote; i++, cur++) {
		sprintf(text, "��%dλͬ־ֻ����%d����ų���%d�ŵ���", cur->num, cur->time, cur->numofmine);
		outtextxy(x, (i + 1) * 30 + y, text);
		if (i == 7) {
			break;//ֻ��ʾ7������
		}
	}
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x > info->Wxs * 0.8 && m.y > info->yxs * 0.8) {
				if (info->NumOfMine <= (info->Width * info->Higth) * 0.16) {
					sprintf(text, "����ܸ��������ڳе���������(%d)", info->NumOfMine);
					outtextxy(info->Wxs * 0.6, info->yxs * 0.7, BLANK);
					outtextxy(info->Wxs * 0.6, info->yxs * 0.7, text);
					info->NumOfMine++;
				}
				else {
					sprintf(text, "���Ѿ���Ŭ����,����Ҫ�ټ���(%d)", info->NumOfMine);
					outtextxy(info->Wxs * 0.6, info->yxs * 0.7, BLANK);
					outtextxy(info->Wxs * 0.60, info->yxs * 0.7, text);
				}
			}
			else if (m.x<info->Wxs * 0.2 && m.y>info->yxs * 0.7) {
				break;
			}
			else if (m.x < info->Wxs * 0.2 && m.y < info->yxs * 0.3) {
				if (info->Width == 14) {
					sprintf(text, "�Ȱ����ϴ���ս�������");
					info->Width = 8;
					info->Higth = 7;
					info->Score = 0;
					info->NumofStep = 0;
					info->ZeroAboutP.x = 150;
					info->ZeroAboutP.y = 120;
					outtextxy(info->Wxs * 0.6, info->yxs * 0.7, BLANK);
					outtextxy(info->Wxs * 0.7, info->yxs * 0.7, text);
					info->map = CreateMapAndInitialize(info);
				}
				else if (info->Width == 8) {
					sprintf(text, "Ϊ�ϴ���ս��!");
					info->Width = 17;
					info->Higth = 9;
					info->NumOfFlag = info->NumOfMine;
					info->Score = 0;
					info->NumofStep = 0;
					info->ZeroAboutP.x = 70;
					info->ZeroAboutP.y = 110;
					outtextxy(info->Wxs * 0.6, info->yxs * 0.7, BLANK);
					outtextxy(info->Wxs * 0.8, info->yxs * 0.7, text);
					info->map = CreateMapAndInitialize(info);
				}
				else {
					sprintf(text, "�ճ�����?�а�.");
					info->Width = 14;
					info->Higth = 8;
					info->NumOfFlag = info->NumOfMine;
					info->Score = 0;
					info->NumofStep = 0;
					info->ZeroAboutP.x = 100;
					info->ZeroAboutP.y = 120;
					outtextxy(info->Wxs * 0.6, info->yxs * 0.7, BLANK);
					outtextxy(info->Wxs * 0.8, info->yxs * 0.7, text);
					info->map = CreateMapAndInitialize(info);
				}
				info->NumOfMine = (info->Higth * info->Width) * 0.08;
			}
		}
		else if (m.uMsg == WM_RBUTTONDOWN) {
			if ((m.x > info->Wxs * 0.8 && m.y > info->yxs * 0.8)) {
				if (info->NumOfMine >= (info->Width * info->Higth) * 0.03) {
					sprintf(text, "�ð�,����ʧ��������(%d)", info->NumOfMine);
					outtextxy(info->Wxs * 0.6, info->yxs * 0.7, BLANK);
					outtextxy(info->Wxs * 0.7, info->yxs * 0.7, text);
					info->NumOfMine--;
				}
				else {
					sprintf(text, "���󲵻�,�����������(%d)", info->NumOfMine);
					outtextxy(info->Wxs * 0.6, info->yxs * 0.7, BLANK);
					outtextxy(info->Wxs * 0.7, info->yxs * 0.7, text);
				}
			}
		}
	}
	return 0;
}
int Cheat(Ginfo* info) {
	int FlagedMine = 0;
	char text[100], BLANK[100];
	int i, j;
	Land* cur;
	strcpy(BLANK, "                                                           ");
	for (i = 0; i < info->Higth; i++) {
		for (j = 0; j < info->Width; j++) {
			cur = *(info->map + i + 1) + j + 1;
			if (cur->Mine == true && cur->flag == true) {
				FlagedMine++;
			}
		}
	}
	sprintf(text, "����̽����ɨ����........");
	outtextxy(150, 10, BLANK);
	outtextxy(150, 10, text);
	Sleep(2000);
	sprintf(text, "̽������ʾ,%d/%d������������", FlagedMine, info->NumOfMine - info->NumOfFlag);
	outtextxy(150, 10, BLANK);
	outtextxy(150, 10, text);
	return 0;
}
