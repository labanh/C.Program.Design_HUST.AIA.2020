#include"mouse.h"
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "SVGA.h"
//#include "draw.h"
#define  H 16
#define  W 12

int mouse_shape[H][W] =    //鼠标形状二维数组
{
    {1,1,0,0,0,0,0,0,0,0,0,0},
	{1,2,1,0,0,0,0,0,0,0,0,0},
	{1,2,2,1,0,0,0,0,0,0,0,0},
	{1,2,2,2,1,0,0,0,0,0,0,0},
	{1,2,2,2,2,1,0,0,0,0,0,0},
	{1,2,2,2,2,2,1,0,0,0,0,0},
	{1,2,2,2,2,2,2,1,0,0,0,0},
	{1,2,2,2,2,2,2,2,1,0,0,0},
	{1,2,2,2,2,2,2,2,2,1,0,0},
	{1,2,2,2,2,2,2,2,2,2,1,0},
	{1,2,2,2,2,1,1,1,1,1,1,1},
	{1,2,2,2,1,0,0,0,0,0,0,0},
	{1,2,2,1,0,0,0,0,0,0,0,0},	
	{1,2,1,0,0,0,0,0,0,0,0,0},	
	{1,1,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0}
		    			
};

unsigned int mouse_bk[20][20];           //存放被鼠标覆盖的区域
MOUSE mouse={0,0,0};            //定义一个鼠标结构变量
 



/***鼠标初始化***/
void Mouse_Init()
{
	MouseInit();                  //鼠标复位，检测是否安装鼠标
	MouseRange(0,0,1012,752);         //鼠标范围设置
	MouseGet(&mouse);                  //得到鼠标状态
	MouseSpeed(6,4);
	MouseOn(mouse);                 //显示鼠标
}


/***鼠标复位***/
void MouseInit()
{
	union REGS regs;
	regs.x.ax=0;
	int86(0x33,&regs,&regs);
	if(regs.x.ax==0)
	{
		printf("mouse error");
		delay(5000);
		exit(1);
	}
}
/********************************
	功能说明：设置鼠标计数与像素比,值越大鼠标移动速度越慢 
	参数说明：int   vx,	鼠标横向的；int   vy	鼠标纵向的
**
********************************/
void MouseSpeed(int x, int y)
{
	union REGS regs;
	regs.x.ax=0x0f;
	regs.x.cx=x;
    regs.x.dx=y;
	int86(0x33,&regs,&regs);
}
/**********************************************************************
	功能说明：设置鼠标灵敏度；设置鼠标倍速阈值；
	参数说明：x为水平灵敏度，y为竖直灵敏度,v为鼠标即将设定的倍速阈值
	返回值说明：无
*********************************************************************/
void SetMouseSen(int x,int y)
{
	union REGS regs;
    regs.x.ax=0x1a;
	regs.x.bx=x;
	regs.x.cx=y;
   // regs.x.dx=v;
	int86(51,&regs,&regs);
}
/***得到某一点的颜色值***/
unsigned int Getpixel64k(int x, int y)
{
	unsigned int far * const video_buffer = (unsigned int far *)0xa0000000L;
	unsigned char page;                                                  //要切换的页面号
	unsigned long int page_dev;                                           //对应显存地址偏移量                       
	if(x < 0 || x > (SCR_WIDTH - 1) || y < 0 || y > (SCR_HEIGHT - 1))           //判断点是否在屏幕范围内，不在就退出 
	{
		printf("out of range");
	}
	page_dev = ((unsigned long int)y << 10) + x;              //计算显存地址偏移量和对应的页面号，做换页操作
	page = page_dev >> 15;	//32k个点一换页，除以32k的替代算法
	Selectpage(page);
	return video_buffer[page_dev];	 //返回颜色
}

/***鼠标范围设置***/
void MouseRange(int x1, int y1, int x2, int y2)
{
	union REGS mouse;
	/*设置横坐标范围*/
	mouse.x.ax = 7;
	mouse.x.cx = x1;
	mouse.x.dx = x2;
	int86(0x33, &mouse, &mouse);
	/*设置纵坐标范围*/
	mouse.x.ax = 8;
	mouse.x.cx = y1;
	mouse.x.dx = y2;
	int86(0x33, &mouse, &mouse);
}


/***得到鼠标按键状态(不传递鼠标坐标)***/
int MouseBut(MOUSE * mouse)
{ 
	union REGS regs;
	regs.x.ax = 3;
	int86(0x33, &regs, &regs);
	mouse->key = regs.x.bx;
	return mouse->key;     
}


/***得到鼠标位置，按键状态***/
int MouseGet(MOUSE * mouse)
{ 
	union REGS regs;
	regs.x.ax = 3;
	int86(0x33, &regs, &regs);
	mouse->x = regs.x.cx;
	mouse->y = regs.x.dx;
	mouse->key = regs.x.bx;
	return mouse->key;     
}

/***设置鼠标显示位置***/
void MouseSet(int x,int y)
{
	union REGS regs;
    regs.x.ax=4;
	regs.x.cx=x;
    regs.x.dx=y;
	int86(0x33,&regs,&regs);      //设置鼠标当前坐标	
	MouseOn(mouse);               //画鼠标	
}

/***判断鼠标是否在指定区域内部***/
int MouseIn(int x1, int y1, int x2, int y2)
{ 
	MOUSE mouse = {0,0,0};                       //very important，设置一个鼠标结构，用来减少对主鼠标结构的调用 
	MouseGet(&mouse);       
	if ((mouse.x >= x1)
		&& (mouse.x <= x2)
		&& (mouse.y >= y1)
		&& (mouse.y <= y2))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/***判断鼠标左键是否在指定区域内按下***/
int MousePress(int x1, int y1, int x2, int y2)
{ 
	MOUSE mouse = {0,0,0};                       
	MouseGet(&mouse);       
	if ((mouse.x >= x1)
		&& (mouse.x <= x2)
		&& (mouse.y >= y1)
		&& (mouse.y <= y2)
		&& ((mouse.key & 1) == 1))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/***鼠标显示***/
void MouseOn(MOUSE mouse)
{
	int i, j;
	for (i = 0; i < H; i++)
	{
		for (j = 0; j < W; j++)
		{
			
			mouse_bk[i][j] = Getpixel64k(j + mouse.x, i + mouse.y);  //存储鼠标覆盖区
			/***画鼠标***/
			if (mouse_shape[i][j] == 1)
				Putpixel64k(mouse.x + j, mouse.y + i, 0);
			else if (mouse_shape[i][j] == 2)
				Putpixel64k(mouse.x + j, mouse.y + i, 0xffff);
		}
	}

}


/***鼠标每次移动重新显示***/
void MouseShow(MOUSE *mouse)
{  
	int i,j;       //循环变量
	int color;     //鼠标某点颜色
	int x,y;
	x=mouse->x;             //鼠标原位置坐标
	y=mouse->y;         
	MouseGet(mouse);    //得到新鼠标状态
	if(mouse->x!=x||mouse->y!=y)         //鼠标移动就重新画鼠标
	{
		for (i = 0; i < H; i++)           	
		{
			for (j = 0; j < W; j++)
			{
				if (mouse_shape[i][j] == 0)
					continue;
				Putpixel64k(x + j, y + i, mouse_bk[i][j]);   //画出原鼠标覆盖区
			}
		}
		MouseOn(*mouse);                            //在新位置显示鼠标
	}
}

/***鼠标隐藏***/
void MouseOff(MOUSE *mouse)
{
	int i,j;
	int x,y;
	x=mouse->x;
	y=mouse->y;
	for (i = 0; i <H; i++)
		for (j = 0; j < W; j++)
		{
			if (mouse_shape[i][j] == 0)
				continue;
			Putpixel64k(x + j, y + i, mouse_bk[i][j]);   //画出原鼠标覆盖区
		}
}

/*初始化鼠标，设置水平垂直方向像素比相等*/
void Curinit(void)
{
	_AX=0;
	geninterrupt(0x33);
	if(_AX==0)
		puts("mouse init fail!");
	_AX=7;
	_CX=10;
	_DX=1000;
	geninterrupt(0x33);
	_AX=8;
	_CX=10;
	_DX=750;
	geninterrupt(0x33);
}

void draw_mouse(int mx,int my)
{
	int i, j;
	for (i = 0; i < H; i++)
	{
		for (j = 0; j < W; j++)
		{
			/***画鼠标***/
			if (mouse_shape[i][j] == 1)
				Putpixel64k(mx + j, my + i, 0);
			else if (mouse_shape[i][j] == 2)
				Putpixel64k(mx + j, my + i, 0xffff);
		}
	}
}

void CurShow(void)
{
	Cursor(500,500,2);
}

void Curhide(void)
{
	Cursor(500,500,1);
}

void Cursor(int x,int y,int flag)
{
	static unsigned int far *tempgraph;
	static int mx,my;
    if(tempgraph==NULL)
	{
		tempgraph=malloc(1000);
	}
	if(1<=x&&x<=1000&&1<=y&&y<=750)
	{
		switch(flag)
		{			
		case 1:	//hidemouse
			Put_image(mx,my,mx+16,my+15,tempgraph);
			//delay(20);
			break;
		case 2:	//showmouse
			do
			{
				_AX=3;
				geninterrupt(0x33);
				mx=_CX;
				my=_DX;
			}
			while(1>=mx||mx>=1000||1>=my||my>=750);
			Get_image(mx,my,mx+16,my+15,tempgraph);
			draw_mouse(mx,my);
			break;
		}
	}
}

void getmouse(int *button,int *x,int *y)
{
	static int mx,my,mbutton;
	_AX=3;
	geninterrupt(0x33);
	mbutton=_BL;
	mx=_CX;
	my=_DX;
	Cursor(mx,my,0);
	if(button!=NULL)
		*button=mbutton;
	if(x!=NULL&&y!=NULL)
	{
		*x=mx;
		*y=my;
	}
}
