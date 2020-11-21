#ifndef MOUSE_H
#define MOUSE_H

/***鼠标结构***/
typedef struct mouse                                                   
{
	int x;			//光标横坐标
	int y;			//光标纵坐标
	int key;		//按钮的状态，0,1位分别表示左右键，该位为1表示按下，0表示松开
}MOUSE;                  //鼠标结构

extern MOUSE mouse;//声明全局变量，本项目工程共用同一个鼠标结构
//故每个（需要鼠标的）文件都应包含 mouse.h
 
/***鼠标初始化***/
void Mouse_Init(void);
/***鼠标复位***/
void MouseInit(void);
/***鼠标范围***/
void MouseRange(int x1, int y1, int x2, int y2);
/***得到鼠标按键状态(不传递鼠标坐标)***/
int MouseBut(MOUSE * mouse);
/***得到鼠标位置和按键状态***/
int MouseGet(MOUSE *mouse);
//int MouseMove(MOUSE *mouse);
void MouseSpeed(int x, int y);
void SetMouseSen(int x,int y);
/***隐藏鼠标***/
void MouseOff(MOUSE *mouse);
/***重新设置鼠标位置***/
void MouseSet(int x,int y);
//void MouseSet1(int x,int y);
/***64k画鼠标***/
void MouseOn(MOUSE mouse);
/***64k鼠标显示***/
void MouseShow(MOUSE *mouse);
/***256画鼠标***/
//void MouseOn1(MOUSE mouse);
/***256鼠标显示***/
//void MouseShow1(MOUSE *mouse);
/***判断鼠标是否在指定区域内部***/
int MouseIn(int x1, int y1, int x2, int y2);
/***判断鼠标在某一位置的按压状态***/
int MousePress(int x1, int y1, int x2, int y2);
/***得到某一点的颜色值***/
unsigned int Getpixel64k(int x, int y);
/***得到某一点的颜色值***/
//unsigned int Getpixel256(int x, int y);

/***画鼠标***/

void draw_mouse(int mx,int my);

void CurShow(void);

void Cursor(int x,int y,int flag);

void Curinit(void);

void Curhide(void);

void getmouse(int *button,int *x,int *y);





 
#endif
