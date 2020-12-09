#pragma once

#include"标头.h"
#include<time.h>
#include<graphics.h>
#include<conio.h>
#include <windows.h>

typedef enum Output {
	BLANK, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, WALL, Flag, Unwatched, Player
}OUTPUT;//枚举输入的几种情况
typedef enum Result {
	Win, Lost, None
}RES;//枚举游戏结果的几种情况
typedef enum Action {
	MOVE, WIPE, FLAG, PAUSE
}ACT;//枚举玩家行动的几种情况
typedef enum ActionInOpen {
	StartTheG, Set, Exit, NONE
};//开始菜单的玩家几种选择
typedef struct ZeroCoord {
	int x;
	int y;
}ZC;//记录地图绘制的零坐标
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
}Land;//每个格子的
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
	int Width;//宽度,x,j;
	int Higth;//高度,y,i;
	int NumOfMine;//雷的数量
	int NumOfFlag;//工具数量
	int Score;
	int NumofStep;
	int Wxs;
	int yxs;
	int LastTime;
	Land** map;//地图模组
	PS PictureStore;
	ZC  ZeroAboutP;//游戏界面之前的像素数
	COORD pla;
}Ginfo;
typedef struct GameNotes {
	int num;//记录这是第几次成功游玩的记录
	int time;//时间
	int numofmine;//记录这次雷的部署数量
}Note;
typedef struct ListNote {
	int NumofNote;
	Note* ListofNote;
}ListNotes;
////////////////////////////////////////////函数设计

void GetTheDataAndBasicSet(Ginfo* info);//基本参数的设置
Land** CreateMapAndInitialize(Ginfo* info);//申请内存创建地图,初始化各个格子的内容
void LayTheMine(Ginfo* info);//布雷:)
void LoadGameImage(Ginfo* info);//加载游戏内容图像
void LoadFaceImage(Ginfo* info);//加载界面的图像
ActionInOpen Open(Ginfo* info);//开始界面的图像
OUTPUT CheckStatus(Land* target);//通过格子里面的属性,确定格子的显示状态
RES CheckMine(Ginfo* info, COORD* pos);//判雷:)
int CountAroundMines(Ginfo* info, COORD pos);//计算这个格子周围的雷数量
RES CheckAround(Ginfo* info, COORD pos);//与判雷结合,然后作为判雷里面延申的功能
void PauseTheGame(Ginfo* info);//帮助界面的代码
int GAMEing(Ginfo* info);//游戏界面的过程
void RefreshMapForInitialize(Ginfo* info);//用于初始化的地图刷新
void updata(Ginfo* info, COORD pos);//通过格子里面的外在显示的变量来在特定位置刷新图像
Land* CordTurnToPos(COORD pos, Ginfo* info);//小工具,将坐标转化为特定格子的地址
Action GetAction(Ginfo* info);//获取键盘内容
COORD* GoThroughEightCORD(COORD pos);//小工具,有规律地获取一个格子周围的8个格子的地址,在checkaround中需要
bool FineToCheck(COORD pos, Ginfo* info);//是否ok去判雷,在checkaround中需要
void Success(Ginfo* info);//成功界面
void Lostsence(Ginfo* info);//失败界面
RES WinChecking(Ginfo* info);//胜负判定:)
void Refreshmap(Ginfo* info);//刷新整个地图
void PutOnFlagRIGHT(Ginfo* info);//无用>^<
void PutOnFlag(Ginfo* info, COORD pos);//在某个位置升旗
COORD MouseClickintopos(Ginfo* info, MOUSEMSG m);//将鼠标点击转化为格子上的具体格子的坐标
void DrawSthAtSp(ZC Zero, IMAGE* target, COORD pos);//在某个位置画上某个图像,在updata中需要重载
void PutOnFlag(Ginfo* info, COORD pos);//升旗:)
RES AutoCheck(Ginfo* info, COORD* cor);//中键事件:)
int CountAroundFLag(Ginfo* info, COORD pos);//计算周围的旗子数量,中键事件中需要重载
ListNotes* Read();//返回一个游戏记录单,里面的数组比需求值多一个
int AddandLoad(int score, ListNote* target, int NumofMine);//写入记录并存档
int SortTheNotes();//排序文件记录
int SetTheGame(Ginfo* info);//设置界面
int Cheat(Ginfo* info);//提示

////////////////////////////////////////函数实现

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
	cleardevice();//清空窗口
	putimage(0, 0, &(info->PictureStore.pause));//放置图像库上对应该界面的图片
	while (1) {
		m = GetMouseMsg();//获取鼠标的信息
		if (m.x > info->Wxs * 0.8 && m.y > info->yxs * 0.8) {
			if (m.uMsg == WM_LBUTTONDOWN) {
				temp = GAMEing(info);//如果点对了,则开始游戏
				if (temp > 0) {//temp记录游戏时长,如果游戏时长非法则不录入
					info->LastTime = temp;
					LN = Read();//将存储在文件的排行榜数据提取出来放在LN中
					AddandLoad(temp, LN, info->NumOfMine);//在其中加入这一次的记录并存入文件
					SortTheNotes();//再次读写并排序,这个是后来加的,有疏忽.原本不必这么麻烦
				}
				return;//结束即返回主界面
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
	if (cur->flag == false) {//判断是否被插旗,插旗的不能被判(防误触)
		cur->watched = true;//更新参数
		if (cur->Mine == true) {
			return Lost;//如果格子上有雷,即失败
		}
		else {
			cur->AroundMine = CountAroundMines(info, *pos);//获取周围雷的数量
			cur->LandOutPut = CheckStatus(cur);//根据其参数更新其的显示
			updata(info, *pos);//更新图像
			if (cur->AroundMine == 0) {
				CheckAround(info, *pos);//如果周围一个雷都没有即蔓延
			}
		}
	}
	return None;//没失败即无事发生
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
		sprintf_s(text, "上次的扫雷用时为%d秒", info->LastTime);
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
		sprintf(text, "小心点,看样子还有%d个地雷呢", left);
	}
	else if (left > info->NumOfMine * 0.3) {
		sprintf(text, "嗯,进展顺利还有%d个雷", left);
	}
	else if (left == 0) {
		sprintf(text, "离成功只剩一步之遥!", left);
	}
	else {
		sprintf(text, "快了,快了,只剩下%d个了", left);
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
	begin = time(NULL);//开始计时
	char test;
	cleardevice();
	putimage(0, 0, &(info->PictureStore.Game));//同上,显示界面
	Refreshmap(info);
	RefreshMapForInitialize(info);//初始化地图
	info->NumofStep = 0;//记录是否是第一次点击,埋雷时需要
	info->NumOfFlag = info->NumOfMine;
	while (1) {//二重循环提升稳定性
		while (1) {
			cur = NULL;
			cor = { -100,-100 };//无效值,用于鼠标点击->坐标,是个保险
			result = None;//结果的初值为None,无事发生
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > info->Wxs - info->ZeroAboutP.x && m.y < info->ZeroAboutP.y) {
					end = -1;
					result = Lost;//这个是中途退出,因为只有result为win&&Lost才可以退出二重循环,所以要改
					break;
				}
				if (m.x < info->ZeroAboutP.x + 30 && m.y < info->ZeroAboutP.y) {
					Cheat(info);//这个是作弊按钮,雕虫小技,不展示源码
					break;
				}
				cor = MouseClickintopos(info, m);
				if (cor.X != -100) {//这个就是为了防止出现无效地址的检测
					cur = CordTurnToPos(cor, info);//将合格坐标转化为地址
				}
				else {
					break;
				}
				if (info->NumofStep == 0) {//这个是判断是不是第一次的
					if (cor.X != -100) {//同上
						info->pla.X = cor.X;//第一次的坐标视为玩家坐标
						info->pla.Y = cor.Y;
						LayTheMine(info);//雷将不会摆在玩家坐标上,即防止玩家第一步踩雷上面
						result = CheckMine(info, &cor);//放完之后对玩家所在位置执行左键
					}
				}
				else {
					if (cur->watched == false && cur != NULL) {
						result = CheckMine(info, &cor);//如果点击位置为位置,即执行win里面的左键事件
					}
					else if (cur != NULL) {
						result = AutoCheck(info, &cor);//为未知,即执行win里面的中键事件
					}
				}
				info->NumofStep++;
			}
			else if (m.uMsg == WM_RBUTTONDOWN) {
				cor = MouseClickintopos(info, m);
				if (cor.X != -100) {
					PutOnFlag(info, cor);//如果右键有效坐标则插旗
					updata(info, cor);//刷新所在位置
				}
			}

			if (result == None) {
				result = WinChecking(info);//如果前面不是失败的话,则进行胜利判定
			}
			if (result == Lost) {//失败则停止计时,进入失败界面
				end = time(NULL);
				Lostsence(info);
				break;
			}
			else if (result == Win) {//成功则停止计时,停止0.25秒让玩家欣赏杰作,进入成功界面
				end = time(NULL);
				Sleep(250);
				Success(info);
				break;
			}
		}
		if (result == Win || result == Lost) {
			break;//只有成功与失败才可以跳出循环,提高稳定性
		}
	}
	if (result == Win) {
		return (end - begin);//只有成功才会存入成绩
	}
	else {
		return 0;//失败没人权
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
		sprintf_s(text, "同志,你还没有开始你的任务,咋就想查看成绩了?");
		outtextxy(x, 10, text);
	}
	else {
		for (i = 0, mc = 0, cur = note->ListofNote; i < note->NumofNote; i++, cur++) {
			if (cur->time < info->LastTime) {
				mc++;
			}
		}
		if (mc == 0) {
			sprintf(text, "同志,你是祖国最优秀的扫雷战士");
			outtextxy(x, 10, text);
		}
		else if (mc < 10) {
			sprintf(text, "同志,你前面还有%d位比你更卖力的,再接再厉嗷", mc);
			outtextxy(x, 10, text);
		}
		else {
			sprintf(text, "同志,你的效率太低了,有%d位同志比你快,你是想背弃大表哥吗?", mc);
			outtextxy(x, 10, text);
		}
	}
	for (i = 0, cur = note->ListofNote; i < note->NumofNote; i++, cur++) {
		sprintf(text, "第%d位同志只花了%d秒就排除了%d颗地雷", cur->num, cur->time, cur->numofmine);
		outtextxy(x, (i + 1) * 30 + y, text);
		if (i == 7) {
			break;//只显示7个数据
		}
	}
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x > info->Wxs * 0.8 && m.y > info->yxs * 0.8) {
				if (info->NumOfMine <= (info->Width * info->Higth) * 0.16) {
					sprintf(text, "祖国很高兴你乐于承担更多任务(%d)", info->NumOfMine);
					outtextxy(info->Wxs * 0.6, info->yxs * 0.7, BLANK);
					outtextxy(info->Wxs * 0.6, info->yxs * 0.7, text);
					info->NumOfMine++;
				}
				else {
					sprintf(text, "你已经够努力了,不需要再加了(%d)", info->NumOfMine);
					outtextxy(info->Wxs * 0.6, info->yxs * 0.7, BLANK);
					outtextxy(info->Wxs * 0.60, info->yxs * 0.7, text);
				}
			}
			else if (m.x<info->Wxs * 0.2 && m.y>info->yxs * 0.7) {
				break;
			}
			else if (m.x < info->Wxs * 0.2 && m.y < info->yxs * 0.3) {
				if (info->Width == 14) {
					sprintf(text, "慈爱的老大哥终将拯救你");
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
					sprintf(text, "为老大哥而战吧!");
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
					sprintf(text, "日常任务?行吧.");
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
					sprintf(text, "好吧,令人失望的懒虫(%d)", info->NumOfMine);
					outtextxy(info->Wxs * 0.6, info->yxs * 0.7, BLANK);
					outtextxy(info->Wxs * 0.7, info->yxs * 0.7, text);
					info->NumOfMine--;
				}
				else {
					sprintf(text, "请求驳回,祖国不养懒虫(%d)", info->NumOfMine);
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
	sprintf(text, "金属探测器扫描中........");
	outtextxy(150, 10, BLANK);
	outtextxy(150, 10, text);
	Sleep(2000);
	sprintf(text, "探测器显示,%d/%d个旗子下有雷", FlagedMine, info->NumOfMine - info->NumOfFlag);
	outtextxy(150, 10, BLANK);
	outtextxy(150, 10, text);
	return 0;
}
