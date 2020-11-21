#include "hz.h"

/*16位点阵汉字输出，x,y表示汉字输出位置，s为汉字串，color表示汉字颜色，
name 为汉字库文件路径，即字体信息*/
void prt_hz16(int x, int y, char *s, unsigned int color, char * name) 
{
	FILE * fp=NULL;
	char buffer[32]={0};                                          //用来读取16汉字的32位字模
	int i=0;
	int j=0;
	unsigned char qh =0;     
    unsigned char wh =0; 	     //汉字区位号
	unsigned long offset=0;     //汉字内码
	unsigned char mask[]={0x80,0x40,0x20,0x10,0x08,0x04,       //用来屏蔽出每一位的信息
						  0x02,0x01};
	if((fp=fopen(name,"rb"))==NULL)
	{
		printf("Can't open hzk16!");
		getch();
		exit(0);
	}
	while(*s)                                         //若汉字串未读完，则继续
    {
		qh=* s-160;                                       //得到汉字内码
        wh=*(s+1) -160;
        offset=(94*(qh-1)+(wh-1))*32L;                     //计算位移量
        fseek(fp,offset, SEEK_SET);                        //汉字库文件中查找内码位置
        fread(buffer, 32, 1, fp);                          //读取相应位置的字模
        for(i=0;i<16;i++)                                  //在指定点输出一个汉字
			{
				for(j=0;j<16;j++)
				{
					if((mask[j%8] & buffer[i*2+j/8])!=0)
					{
						Putpixel64k(x+j,y+i,color);
					}
				}
			}
			x+=16;                                          //横向输出，间距为16
			s+=2;                                           //读取下一个汉字
    }
    fclose(fp);
}


/*(有延迟)24位点阵汉字输出，x,y表示汉字输出位置，s为汉字串，color表示汉字颜色，
name 为汉字库文件路径，即字体信息*/
void prt_hz24(int x, int y,char * s, unsigned int color, char * name)    
{
	FILE * fp=NULL;
	char buffer[72]={0};                                            //用来读取24汉字的72位字模
	int i=0;
	int j=0;
	unsigned char qh=0;
	unsigned char wh=0;
	unsigned long offset=0;
	unsigned char mask[]={0x80,0x40,0x20,0x10,0x08,0x04,       //用来屏蔽出每一位的信息
						  0x02,0x01};
	if((fp=fopen(name,"rb"))==NULL)
	{
		printf("Can't open hzk24!");
        getch();
        exit(0);
    }
    while(*s)
    {
        qh=* s-160;
        wh=*(s+1)-160;
        offset=(94*(qh-1)+(wh-1))*72L;             
        fseek(fp,offset, SEEK_SET);
		fread(buffer, 72, 1, fp);
        for(i=0; i<24; i++)                                 //输出一个汉字
           for(j=0;j<24;j++)
			{
				if((mask[j%8] & buffer[i*3+j/8])!=0)
				{
					Putpixel64k(x+j,y+i,color);
				}					
			}
        s+=2;
        x+=24;                                         //行输出，间距24
		delay(50);                                   //使每个汉字输出过程可见，起到美化效果的作用
    }
    fclose(fp);
}




/*x,y表示汉字输出位置，s为汉字串，color表示汉字颜色，
name 为汉字库文件路径，即字体信息*/
void prt_hz24d(int x, int y,char * s, unsigned int color, char * name)    
{
	FILE * fp=NULL;
	char buffer[72]={0};                                             //用来读取24汉字的72位字模
	int i=0;
	int j=0;
	unsigned char qh=0;
	unsigned char wh=0;
	unsigned long offset=0;
	unsigned char mask[]={0x80,0x40,0x20,0x10,0x08,0x04,       //用来屏蔽出每一位的信息
						  0x02,0x01};
	if((fp=fopen(name,"rb"))==NULL)
	{
		printf("Can't open hzk24d!");
        getch();
        exit(0);
    }
    while(*s)
    {
        qh=* s-160;
        wh=*(s+1)-160;
        offset=(94*(qh-1)+(wh-1))*72L;             
        fseek(fp,offset, SEEK_SET);
		fread(buffer, 72, 1, fp);
        for(i=0; i<24; i++)                                 //输出一个汉字
           for(j=0;j<24;j++)
			{
				if((mask[j%8] & buffer[i*3+j/8])!=0)
				{
					Putpixel64k(x+j,y+i,color);
				}					
			}
           s+=2;
           x+=24;                                         //行输出，间距24
    }
    fclose(fp);
}

void prt_asc16( int x,int y,char * s,unsigned int color)		//输出一串英文函数
{

	FILE *  fp=NULL;
	int i=0;
	int j=0;
	unsigned long offset=0;
	char buffer[16]={0};
	if ((fp=fopen("hzk\\ASC16","rb"))==NULL)
	{
                  printf("asc16 wrong!");		
                     exit(1);
	}
	while(*s)
        { 
	offset=*s * 16L;                         	//计算位移量
	fseek(fp,offset,0);
	fread(buffer,16,1,fp);                        	//读出字模信息
	
	for(i=0;i<16;i++)
	{
		for(j=0;j<8;j++)
		{
			if((buffer[i]>>(7-j))&0x1)    	//为1的位显示
			{
				Putpixel64k(x+j,y+i,color);
			}
		}
	}
    s++;
    x+=10;
   }
	fclose(fp);
}

void prt_asc16_ch( int x,int y,char s,unsigned int color)		//输出一个英文函数
{

	FILE *  fp=NULL;
	int i=0;
	int j=0;
	unsigned long offset=0;
	char buffer[16]={0};
	unsigned char mask[]={0x80,0x40,0x20,0x10,0x08,0x04,       //用来屏蔽出每一位的信息
						  0x02,0x01};
	if ((fp=fopen("hzk\\ASC16","rb"))==NULL)
	{
                  printf("asc16 wrong!");
				  getch();		
                     exit(1);
	}
	offset=s * 16L;                         	//计算位移量
	fseek(fp,offset,0);
	fread(buffer,16,1,fp);                        	//读出字模信息	
	for(i=0;i<16;i++)
	{
		for(j=0;j<8;j++)
		{
			if((mask[j] & buffer[i])!=0)    	
			{
				Putpixel64k(x+j,y+i,color);
			}
		}
	}
	fclose(fp);
}

void Read_Asc16(char key,unsigned char *buffer)
{
    unsigned long offset=0;
	FILE*fp=NULL;
	if ((fp=fopen("hzk\\ASC16","rb"))==NULL)
	{
                  printf("asc16 wrong!");
				  getch();		
                     exit(1);
	}
	offset=key* 16L;                         	//计算位移量
	fseek(fp,offset,0);
	fread(buffer,16,1,fp);                    //读出字模信息	
	fclose(fp);
}

void Put_Asc16(int x,int y,char key,unsigned int color)
{
    int i=0;
	int j=0;
    unsigned char buffer[16];
	unsigned char mask[]={0x80,0x40,0x20,0x10,0x08,0x04,       //用来屏蔽出每一位的信息
						  0x02,0x01};
    Read_Asc16(key,buffer);
    for(i=0;i<16;i++)
        for(j=0;j<8;j++)
            if((mask[j] & buffer[i])!=0)
                Putpixel64k(x+i,y+j,color);
}

/*显示放大后的英文字符*/
void Put_Asc16_Size(int x,int y,int xsize,int ysize,char key,unsigned int color)
{
	int i=0;
	int j=0;
	int m=0;
	int n=0;
	unsigned char buffer[16]={0};
	unsigned char mask[]={0x80,0x40,0x20,0x10,0x08,0x04,       //用来屏蔽出每一位的信息
						  0x02,0x01};
	Read_Asc16(key,buffer);
	for(i=0;i<16;i++)
		for(j=0;j<8;j++)
	        for(m=1;m<=ysize;m++)
				for(n=1;n<=xsize;n++)
					if((mask[j] & buffer[i])!=0)
				        Putpixel64k(x+j*xsize+n,y+m+i*ysize,color);
}

/*显示放大后的英文和数字字符串*/
void put_asc16_size(int x,int y,int xsize,int ysize,char *s,unsigned int color )
{
    int i=0;
    for(i=0;s[i]!=0;i++)
    {
		Put_Asc16_Size(x+i*xsize*8,y,xsize,ysize,s[i],color);
    }
}

/*x,y表示汉字输出位置，xsize,ysize为放大倍数，s为汉字串，color表示汉字颜色，name 为汉字库文件路径，即字体信息*/
void prt_hz16_size(int x, int y, int xsize,int ysize,char *s, unsigned int color, char * name)  
{
	FILE * fp;
	char buffer[32];                                          //用来读取16汉字的32位字模
	int i=0;
	int j=0;
	int m=0;
	int n=0;
	unsigned char qh=0;          	//用来计算汉字位号和区号
	unsigned char wh=0;    
	unsigned long offset=0;                                     //记录位移量
	unsigned char mask[]={0x80,0x40,0x20,0x10,0x08,0x04,       //用来屏蔽出每一位的信息
						  0x02,0x01};
	if((fp=fopen(name,"rb"))==NULL)
	{
		printf("Can't open hzk16!");
		getch();
		exit(0);
	}
	while(*s!=0)                                         //若汉字串未读完，则继续
    {
		qh=* s-160;                                       //计算区号和位号
        wh=*(s+1) -160;
        offset=(94L*(qh-1)+(wh-1))*32;                     //计算汉字的地址码
        fseek(fp,offset, 0);                        //汉字库文件中查找内码位置
        fread(buffer, 32, 1, fp);                          //读取相应位置的字模
        for(i=0;i<16;i++)                                  //在指定点输出一个汉字
		{
			for(j=0;j<16;j++)
			{
				if((mask[j%8] & buffer[i*2+j/8])!=0)
				{
					for(m=0;m<xsize;m++)
					{
						for(n=0;n<ysize;n++)
					    {
							Putpixel64k(x+j*xsize+m,y+i*ysize+n,color);
        				}
					}
				}
			}
		}
	    x+=16*xsize;                                          //横向输出，间距为16*xsize
		s+=2;                                           //读取下一个汉字
    }
    fclose(fp);
}

/*输出既有16*16汉字又有16*16asc字符的字符串函数，x,y表示汉字输出位置，xsize,ysize为放大倍数，s为混合字符串，
color表示字符颜色，name 为汉字库文件路径，即字体信息*/
void prt_hz16_asc16_size(int x, int y, int xsize,int ysize,char *s, unsigned int color, char * name)
{
	FILE * fp1=NULL;
	FILE * fp2=NULL;
	char buffer1[16]={0};                                          //用来读取16ascll字符的16位字模
	char buffer2[32]={0};                                          //用来读取16汉字的32位字模
	int i=0;
	int j=0;
	int m=0;
	int n=0;                                                             //循环变量
	unsigned char qh=0;
    unsigned char wh=0;                                    //用来计算汉字区位号
	unsigned long offset=0;                               //记录位移量
	unsigned char mask[]={0x80,0x40,0x20,0x10,0x08,0x04,       //用来屏蔽出字模每一位的信息
						  0x02,0x01};
	if ((fp1=fopen("hzk\\ASC16","rb"))==NULL)
	{
        CloseSVGA();
		printf("asc16 wrong!");		
        getch();            
		exit(1);
	}
	if((fp2=fopen(name,"rb"))==NULL)
	{
		CloseSVGA();
		printf("Can't open hzk16!");
		getch();
		exit(0);
	}
 
	while(*s!=0)                                         //若混合字符串未读完，则继续
    {
        if((*s&0x80)==0)                               //若该字符字节最高位为0，表明该字节ASCII码，输出字符
		{
			offset=*s * 16L;                         	//计算位移量
	        fseek(fp1,offset,0);
	        fread(buffer1,16,1,fp1);                //读出字模信息
		    for(i=0;i<16;i++)                         //在指定点输出一个放大后的字符
			{
				for(j=0;j<8;j++)
				{
					if(mask[j]&buffer1[i])
					{
						for(m=0;m<xsize;m++)
						{
							for(n=0;n<ysize;n++)
						    {
	                            Putpixel64k(x+j*xsize+m,y+2*ysize+i*ysize+n,color); //y+2*ysize是为了平衡汉字与英文字符的高度
							}
						}
					}
				}
			}
			x+=8*xsize;           //横向输出，间距为8*xsize
			s++;		                //读取下一个字符
		}		
		else if((*s&0x80)!=0)                                     //若该字符字节最高位为1，表明该字节为汉字内码一部分，输出汉字  
		{
			qh=* s-160;                                       //计算区号和位号
    	    wh=*(s+1) -160;
     	    offset=(94L*(qh-1)+(wh-1))*32;  //计算汉字的地址码
   	   	    fseek(fp2,offset, 0);                        //汉字库文件中查找内码位置
  	        fread(buffer2, 32, 1, fp2);                  //读取相应位置的字模
  	        for(i=0;i<16;i++)                               //在指定点输出一个放大后的汉字
			{
				for(j=0;j<16;j++)
				{
					if((mask[j%8] & buffer2[i*2+j/8])!=0)
					{
						for(m=0;m<xsize;m++)
						{
							for(n=0;n<ysize;n++)
						    {
								Putpixel64k(x+j*xsize+m,y+i*ysize+n,color);
							}
						}
					}					
				}
			}
			x+=16*xsize;              //横向输出，间距为16*xsize
			s+=2;   			             //读取下一个字符
        }
	}
    fclose(fp1);
	fclose(fp2);
}	

/*输出既有24*24汉字又有32*32 asc字符的字符串函数，x,y表示汉字输出位置，s为混合字符串，
color表示字符颜色，name 为汉字库文件路径，即字体信息*/
void prt_hz24_asc32(int x, int y,char *s, unsigned int color, char * name)
{
	FILE * fp1=NULL;
	FILE * fp2=NULL;
	char buffer1[16]={0};                                          //用来读取12ascll字符的12位字模
	char buffer2[72]={0};                                          //用来读取24汉字的72位字模
	int i=0;
	int j=0;
	int m=0;
	int n=0;                                                             //循环变量
	unsigned char qh=0;
    unsigned char wh=0;                                    //用来计算汉字区位号
	unsigned long offset=0;                               //记录位移量
	unsigned char mask[]={0x80,0x40,0x20,0x10,0x08,0x04,       //用来屏蔽出字模每一位的信息
						  0x02,0x01};
	if ((fp1=fopen("hzk\\ASC16","rb"))==NULL)
	{
        CloseSVGA();
		printf("asc16 wrong!");		
        getch();            
		exit(1);
	}
	if((fp2=fopen(name,"rb"))==NULL)
	{
		CloseSVGA();
		printf("Can't open hzk24!");
		getch();
		exit(0);
	}
	while(*s!=0)                                         //若混合字符串未读完，则继续
    {
        if((*s&0x80)==0)                               //若该字符字节最高位为0，表明该字节ASCII码，输出字符
		{
			offset=*s * 16L;                         	//计算位移量
	        fseek(fp1,offset,0);
	        fread(buffer1,16,1,fp1);                //读出字模信息
		    for(i=0;i<16;i++)                              //在指定点输出一个32*32字符
			{
				for(j=0;j<8;j++)
				{
					if(mask[j]&buffer1[i])
					{
						for(m=0;m<2;m++)
						{
							for(n=0;n<2;n++)
						    {
	                            Putpixel64k(x+j*2+m,y-2+i*2+n,color); //y-2是为了平衡汉字与英文字符的高度
							}
						}
					}
				}
			}
			x+=8*2;           //横向输出，间距为16
			s++;		                //读取下一个字符
		}		
		else if((*s&0x80)!=0)                                     //若该字符字节最高位为1，表明该字节为汉字内码一部分，输出汉字  
		{
			qh=* s-160;                                       //计算区号和位号
    	    wh=*(s+1) -160;
     	    offset=(94L*(qh-1)+(wh-1))*72;  //计算汉字的地址码
   	   	    fseek(fp2,offset, 0);                        //汉字库文件中查找内码位置
  	        fread(buffer2, 72, 1, fp2);                  //读取相应位置的字模
  	        for(i=0;i<24;i++)                               //在指定点输出一个放大后的汉字
			{
				for(j=0;j<24;j++)
				{
					if((mask[j%8] & buffer2[i*3+j/8])!=0)
					{
						Putpixel64k(x+j,y+i,color);
					}					
				}
			}
			x+=24;              //横向输出，间距为24
			s+=2;   			             //读取下一个字符
        }
	}
    fclose(fp1);
	fclose(fp2);
}	
	
/*画整数倍12*24人民币符号￥函数*/
void RMB(int x,int y,int xsize,int ysize,unsigned color)
{
	int i=0;
	int j=0;
	int m=0;
	int n=0;  //循环变量
	int RMB[24][12]={
	    {0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,0,0,0,1,1,1,1},
		{0,1,1,0,0,0,0,0,0,1,1,0},
		{0,1,1,0,0,0,0,0,0,1,0,0},
		{0,0,1,1,0,0,0,0,1,1,0,0},
		{0,0,0,1,0,0,0,0,1,0,0,0},
	    {0,0,0,1,1,0,0,1,1,0,0,0},
		{0,0,0,0,1,1,1,1,0,0,0,0},
		{0,0,0,0,0,1,1,0,0,0,0,0},
	    {1,1,1,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,1,1,0,0,0,0,0},
		{0,0,0,0,0,1,1,0,0,0,0,0},
		{0,0,0,0,0,1,1,0,0,0,0,0},
		{0,0,0,0,0,1,1,0,0,0,0,0},
		{0,0,0,0,0,1,1,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,1,1,0,0,0,0,0},
		{0,0,0,0,0,1,1,0,0,0,0,0},
		{0,0,0,0,0,1,1,0,0,0,0,0},
		{0,0,0,0,0,1,1,0,0,0,0,0},
		{0,0,0,0,0,1,1,0,0,0,0,0},
	    {0,0,0,1,1,1,1,1,1,0,0,0}}; //储存人民币图标的数组
		
	for(i=0;i<24;i++)
	{
		for(j=0;j<12;j++)
		{
			if(RMB[i][j]!=0)
			    for(m=0;m<xsize;m++)
			    {
				    for(n=0;n<ysize;n++)
				    {
					    Putpixel64k(x+j*xsize+m,y+i*ysize+n,color);
				    }
			    } 
		}
	}
}



