#ifndef _DATA_H_
#define _DATA_H_

typedef struct UseInfo
{
	char UserName[12+1];//用户名
	char password[12+1];//密码
	char IDnumber[18+1];//身份证号
	char UserState;  //用户是否被冻结  0：未被冻结，1：被冻结 
	char n[2];//存储'\n\r' 使得数据存储时换行 

}USER;

typedef struct DayInfo//用于储存用户通报数据，等待管理员审核 
{	
	char area[5+1];//通报区域 
	char year[4+1];//年 
	char month[2+1];//月 
	char day[2+1];//日 
	char infestor[6];//该日新增感染 
	char death[6];//该日新增死亡 
	char heal[6];//该日治愈 
	char username[13];//上报者 
	char infostate;//数据状态 0 为未审核，1为审核通过，2为审核不通过 
	char n[2];//存储'\n\r' 使得数据存储时换行 
}DAY;

typedef struct Save_Dayinfo//储存信息 
{
	char year[4+1];//年 
	char month[2+1];//月 
	char day[2+1];//日 
	char infestor[6];//该日新增感染 
	char death[6];//该日新增死亡 
	char heal[6];//该日治愈 
	char allinf[7];//到该日为止 总感染数 
	char alldea[7];//到该日为止 总治愈数 
	char allhea[7];//到该日为止 总死亡数 
	char n[2];//存储'\n\r' 使得数据存储时换行 
}SAVEDAY; 

typedef struct Chartinfo//储存信息 
{
	int infestor;//该日新增感染 
	int death;//该日新增死亡 
	int heal;//该日治愈 
	int allinf;//到该日为止 总感染数 
	int alldea;//到该日为止 总治愈数 
	int allhea;//到该日为止 总死亡数 

}CHARTDATA; 


#endif


