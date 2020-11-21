/*	FileName: report.h
	Author:   刘子恒 
	Date：    2020/9/7
	function：char judge_password(char mima[]) ;密码格式
			char judge_IDnumber(char id[]); 身份证号格式
			char compare_password(char key1[],char key2[]); 确认密码是否相同
			char right_id(char account[],char id[]);确认身份证号码是否相同
			char judge_same_name(char account[]); 是否注册
			char right_password(char account[],char key[]); 密码正确
			char judge_userfrozen(char account[]); 判断用户是否被冻结 
			char user_freeze(char account[]) ; 冻结账户 
			char user_unfreeze(char account[]);函数功能：将帐户解冻
			char complete_register(char account,char key1,char key2,char id); 完成注册输入
			char complete_login(char account,char key); 完成登录输入
			char complete_admin(char key);完成管理员登录输入
			void wr_user_inf(char account[],char key[],char id[]);将注册信息写入文件
			void wr_user(char account[]);将本次登录的账号写入文件
			char admin_password(char key[]);判断管理员登录时密码是否相符*/
			
/*函数功能：判断密码是否合乎要求
  返回值：0表示长度不合乎要求，1表示合乎要求*/
#ifndef _LGSTATE_H_
#define _LGSTATE_H_

/*函数功能：判断密码是否合乎要求
  返回值：0表示长度不合乎要求，1表示合乎要求*/
char judge_password(char mima[]);

/*函数功能：判断身份证号是否合乎要求
  返回值：0表示长度不合乎要求，1表示内容不合乎要求，2表示合乎要求*/
char judge_IDnumber(char id[]);

 /*函数功能：判断两次输入的密码是否相同
   返回值：0表示不相同，1表示相同*/
char compare_password(char key1[],char key2[]);

/*函数功能：判断注册的账号是否与已有账号重名
  返回值：0表示重名，1表示不重名
  函数功能：判断登录账号是否已经注册
  返回值：0表示已注册，1表示尚未注册*/
char judge_same_name(char account[]);

/*函数功能：判断账号身份证号是否匹配
  返回值：0表示不正确，1表示正确*/  
char right_id(char account[],char id[]);

/*函数功能：判断账号密码是否匹配
  返回值：0表示未被，1表示正确*/
char right_password(char account[],char key[]);

/*函数功能：判断用户是否被冻结 
  返回值：0表示未被冻结，1表示被冻结*/
char judge_userfrozen(char account[]);

/* 函数功能：冻结账户*/
int user_freeze(char account[]);
	
/*函数功能：将帐户解冻*/
char user_unfreeze(char account[]);

/*函数功能：判断是否输入完整 （用于账户注册）
  返回值：1表示全部输入，2表示账号未输入，3表示密码未输入，4表示未确认密码，5表示身份证号未输入*/
char complete_register(char account,char key1,char key2,char id);

/*函数功能：判断是否输入完整 （用于账户登录）
  返回值：1表示全部输入，2表示账号未输入，3表示密码未输入*/
char complete_login(char account,char key);

/*函数功能：判断是否输入完整 （用于管理员登录）
  返回值：1表示全部输入，2表示密码未输入*/
char complete_admin(char key);

/*函数功能：将注册信息写入文件*/
void wr_user_inf(char account[],char key[],char id[]);

/*函数功能：将新密码写入文件*/ 
void user_change_password(char account[],char key[]);

/*函数功能：将本次登录的账号写入文件*/
void wr_user(char account[]);

/*函数功能：将本次登录的账号读出*/
void re_user(char account[]);

/*函数功能：判断管理员登录时密码是否相符
  返回值：0表示不正确，1表示正确*/
char admin_password(char key[]);

/*函数功能：判断id是否存在
  返回值：0表示存在，1表示不存在*/
char judge_same_id(char idnumber[],char account[]);


#endif


