/*******************************************
FileName:dayinfo.h
Author:   刘子恒 
Date：    2020/10/24
Description: 该文件主要用于疫情信息处理 
Others: 无
Function List: 
         wr_day_inf();  	将每日疫情信息写入文件
 		countcases();		计算单个文件中各项总数
 		countallcases();	计算所有文件中各项总数
 		judge_date();		判断输入的日期是否合法
 		judge_cases();		判断输入的疫情信息是否合法
 		countareacases();	读取某区域各项数据
 		wr_area();			将将要通报的文件名写入文件
 		re_area();			将将要通报的文件名读出 
		 wr_database();		将数据写入数据库
 		modify_database();	修改数据库中的数据
 		getoneday();		获取某天在数据库中的位置
********************************************/
#ifndef _DAYINFO_H_
#define _DAYINFO_H_

void wr_day_inf(char area[],char Ye[],char Mo[],char Da[],char In[],char De[],char He[],char User[]);
/*函数功能：将每日疫情信息写入文件*/

void countcases(char *filename,int *suminf,int *sumdea,int *sumheal,int *nowinf);
/*函数功能：计算单个文件中各项总数 */

void countallcases(int filenumbers,int *alsuminf,int *alsumdea,int *alsumheal,int *alnowinf);
/*函数功能：计算所有文件中各项总数 */

int judge_date(char year[],char month[],char day[]);
/*函数功能：判断输入的日期是否合法 */

int judge_cases(char inf[],char dea[],char hea[]);
/*函数功能：判断输入的疫情信息是否合法 */

void countareacases(int areakey,int *suminf,int *sumdea,int *sumheal,int *nowinf);
/*函数功能：读取某区域各项数据*/

void wr_area(int areakey);
/*函数功能：将将要通报的文件名写入文件*/

void re_area(int *areakey);
/*函数功能：将将要通报的文件名读出*/

void wr_database(DAY *a);
/*函数功能：将数据写入数据库*/

void modify_database(SAVEDAY *a,char *area);
/*函数功能：修改数据库中的数据*/

void getoneday(SAVEDAY *a,int areakey,int daykey);
/*函数功能：获取某天在的数据*/

#endif
