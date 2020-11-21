/**********************************************
该文件主要用于信息输入 
Function list :    show_gb  画光标 
                   Getinfo  信息输入 
                   Getcode  密码输入 
***********************************************/
#include"GETS.h"
#include"common.h"

/***画光标函数***/
void show_gb(int x,int y)
{
	Line1(x,y,x,y+16,0);
}

/***信息输入时所做的相同操作***/
void Getinfo(int x1,int y1,char *name,int num)
{
	char showtemp[2]= {0,0};
	int key;    			//按键值
	int i=0,k,temp;
	int border=x1+4;	    //border表示显示图片的左边界
		x1=x1+4;
	y1=y1+5;
	for(i=strlen(name)-1;i>=0;i--)
	{
		*showtemp=name[i];
		prt_asc16_ch(x1+i*8,y1-2,showtemp[0],0);
	}
	i=strlen(name);
	while(bioskey(1))					//清空输入缓冲区
	{
		bioskey(0);
	}
	border+=8*i;
	while(1)     													//当按下回车键时表示输入完毕（回车键值为13）
    {
	    show_gb(border,y1);//光标闪烁 
		if(bioskey(1)==0||!MouseGet(&mouse))			//延时函数，使光标闪烁，在点击鼠标或有输入时退出
		{
			for(k=0;k<100;k++)				//延时的同时检测鼠标键盘
			{
				delay(2);
				if(bioskey(1)||MouseGet(&mouse))
				{
					break;
				}
			}
		}
		if(bioskey(1))
		{
			temp=bioskey(0)&0x00ff;
			if(temp!='\r'&&temp!='\n')	//检测输入不为回车键，则继续，否则输入结束
			{
				if(('0'<=temp&&temp<='9'||('a'<=temp&&temp<='z')||temp=='_')&&i<num)	//检测为数字或字母或下划线，则记录
				{
					Bar1(border,y1,border+8, y1+16, 0xffff);
					name[i]=temp;				//字符送入给定字符串			
					*showtemp=temp;
					prt_asc16(border,y1-2,showtemp,0); //显示新的字符串达到画面与实际输入的同步
					i++;
					name[i]='\0';		//标记字符串结尾
					border+=8;
					show_gb(border,y1);
				}
				else if('A'<=temp&&temp<='Z'&&i<num)	//由于文件名不区分大小写，而后面的文件部分要用用户名做文件名 
				{							//故在注册时就不区分大小写了 
					Bar1(border,y1,border+8, y1+16, 0xffff);
					temp+=32;
					name[i]=temp;				//字符送入给定字符串			
					*showtemp=temp;       //显示新的字符串达到画面与实际输入的同步
					prt_asc16(border,y1-2,showtemp,0);
					i++;
					name[i]='\0';		//标记字符串结尾
					border+=8;
					show_gb(border,y1);
				}
				else if(temp=='\b'&&i>0)			//检测是否为退格键，是则消除前一个字符
				{
					border-=8;
					Bar1(border,y1,border+8, y1+16, 0xffff);
					i--;
					name[i]='\0';
					Bar1(border,y1,border+8, y1+16, 0xffff);
					show_gb(border,y1);
				}
			}
			else
			{
				break;
			}
		}
		if(!MouseIn(378,296,724,322)&&MouseGet(&mouse))		//如果鼠标点击输入框外的部分，退出
		{
			break;
		}
		Bar1(border,y1,border+8, y1+16, 0xffff);
		if(bioskey(1)==0||!MouseGet(&mouse))			//延时函数，使光标闪烁，在点击鼠标或有输入时退出
		{
			for(k=0;k<100;k++)				//延时的同时检测鼠标键盘
			{
				delay(2);
				if(bioskey(1)||MouseGet(&mouse))
				{
					break;
				}
			}
		}
	}
	Bar1(border,y1,border+8, y1+16, 0xffff);
}




/***密码输入时所做的相同操作***/
void Getcode(int x1,int y1,char *code,int num)
{
	char showtemp[2]= {0,0};
	int key;    			//按键值
	int i=0,k,temp;
	int border=x1+4;	    //border表示显示图片的左边界
		x1=x1+4;
	y1=y1+5;
	for(i=strlen(code)-1;i>=0;i--)
	{
		*showtemp=code[i];
		prt_asc16_ch(x1+i*8,y1-2,'*',0);
	}
	i=strlen(code);
	while(bioskey(1))					//清空输入缓冲区
	{
		bioskey(0);
	}
	border+=8*i;
	while(1)     													//当按下回车键时表示输入完毕（回车键值为13）
   {
	   show_gb(border,y1);
		if(bioskey(1)==0||!MouseGet(&mouse))			//延时函数，使光标闪烁，在点击鼠标或有输入时退出
		{
			for(k=0;k<100;k++)				//延时的同时检测鼠标键盘
			{
				delay(2);
				if(bioskey(1)||MouseGet(&mouse))
				{
					break;
				}
			}
		}
		if(bioskey(1))
		{
			temp=bioskey(0)&0x00ff;
			if(temp!='\r'&&temp!='\n')	//检测输入不为回车键，则继续，否则输入结束
			{
				//if('0'<=temp&&temp<='9'||'a'<=temp&&temp<='z'||'A'<=temp&&temp<='Z')	//检测为数字或字母，则记录
				if(('0'<=temp&&temp<='9'||'a'<=temp&&temp<='z'||temp=='_')&&i<num)	//检测为数字或字母或下划线，则记录
				{
					Bar1(border,y1,border+8, y1+16, 0xffff);
					code[i]=temp;				//字符送入给定字符串			
					*showtemp=temp;
					prt_asc16(border,y1-2,showtemp,0); //显示新的字符串达到画面与实际输入的同步
					delay(150);
					Bar1(border,y1,border+8, y1+16, 0xffff);
					prt_asc16(border,y1-2,"_",0);
					delay(50);
					Bar1(border,y1,border+8, y1+16, 0xffff);
					prt_asc16(border,y1-2,"*",0);
					i++;
					code[i]=0;		//标记字符串结尾
					border+=8;
					show_gb(border,y1);
				}
				else if('A'<=temp&&temp<='Z'&&i<num)	//由于文件名不区分大小写，而后面的文件部分要用用户名做文件名 
				{							//故在注册时就不区分大小写了 
					Bar1(border,y1,border+8, y1+16, 0xffff);
					temp+=32;
					code[i]=temp;				//字符送入给定字符串			
					*showtemp=temp;       //显示新的字符串达到画面与实际输入的同步
					prt_asc16(border,y1-2,showtemp,0);
					delay(300);
					Bar1(border,y1,border+8, y1+16, 0xffff);
					prt_asc16(border,y1-2,"_",0);
					delay(100);
					Bar1(border,y1,border+8, y1+16, 0xffff);
					prt_asc16(border,y1-2,"*",0);
					i++;
					code[i]=0;		//标记字符串结尾
					border+=8;
					show_gb(border,y1);
				}
				else if(temp=='\b'&&i>0)			//检测是否为退格键，是则消除前一个字符
				{
					border-=8;
					Bar1(border,y1,border+8, y1+16, 0xffff);
					i--;
					code[i]=0;
					Bar1(border,y1,border+8, y1+16, 0xffff);
					show_gb(border,y1);
				}
			}
			else
			{
				break;
			}
		}
		if(!MouseIn(378,296,724,322)&&MouseGet(&mouse))		//如果鼠标点击输入框外的部分，退出
		{
			break;
		}
		Bar1(border,y1,border+8, y1+16, 0xffff);
		if(bioskey(1)==0||!MouseGet(&mouse))			//延时函数，使光标闪烁，在点击鼠标或有输入时退出
		{
			for(k=0;k<100;k++)				//延时的同时检测鼠标键盘
			{
				delay(2);
				if(bioskey(1)||MouseGet(&mouse))
				{
					break;
				}
			}
		}
	}
	Bar1(border,y1,border+8, y1+16, 0xffff);
}


