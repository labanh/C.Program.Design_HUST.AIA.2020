#include "common.h"
#include "lgstate.h"
/*	FileName: report.c
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
char judge_password(char mima[])
{
    int i;
    int flag = 1;
    for (i = 0; i < 6; i++)
    {
        if (mima[i] == '\0') //若密码长度小于6，则长度错误
        {
            flag = 0;
            break;
        }
    }
    return flag;
}

/*函数功能：判断身份证号是否合乎要求
  返回值：0表示长度不合乎要求，1表示内容不合乎要求，2表示合乎要求*/
char judge_IDnumber(char id[])
{
    int i;
    int flag = 2;
    for (i = 0; i < 19; i++)
    {
        if (id[i] == '\0') //若提前结束，则长度错误
        {
            break;
        }
        if ((i < 17) && (id[i] < '0' || id[i] > '9')) //若在除最后一位之外出现非数字字符，则内容错误
        {
            flag = 1;
            break;
        }
        if ((i == 17) && (id[i] != 'x' && id[i] != 'X') && (id[i] < '0' || id[i] > '9')) //若在最后一位出现不是x或X的非数字字符，则内容错误
        {
            flag = 1;
            break;
        }
    }
    if (i < 18 && flag != 1)
    {
        flag = 0;
    }
    return flag;
}

/*函数功能：判断两次输入的密码是否相同
   返回值：0表示不相同，1表示相同*/
char compare_password(char key1[], char key2[])
{
    int i;
    int flag = 0;
    for (i = 0; i < 13; i++)
    {
        if (key1[i] != key2[i])
        {
            flag = 0;
            break;
        }
        if (key1[i] == '\0')
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

/*函数功能：判断注册的账号是否与已有账号重名
  返回值：0表示重名，1表示不重名
  函数功能：判断登录账号是否已经注册
  返回值：0表示已注册，1表示尚未注册*/
char judge_same_name(char account[])
{
    FILE *fp;
    USER *u = NULL;
    int i, j;
    int flag = 1;
    int length;
    if ((fp = fopen("UserInfo.dat", "rb+")) == NULL)
    {
        printf("\nUserInfo.dat error file");
        delay(3000);
        exit(1); //打开失败，退出程序
    }
    fseek(fp, 0, SEEK_END);
    length = ftell(fp) / sizeof(USER);
    for (i = 0; i < length; i++)
    {
        if ((u = (USER *)malloc(sizeof(USER))) == NULL)
        {
            printf("memory error JudgeSameName");
            delay(3000);
            exit(1); //分配空间不足，退出程序
        }
        fseek(fp, i * sizeof(USER), SEEK_SET);
        fread(u, sizeof(USER), 1, fp);
        for (j = 0; j < 13; j++)
        {
            if (u->UserName[j] != account[j])
            {
                break;
            }
            if (account[j] == '\0')
            {
                j = 13;
                break;
            }
        }
        if (j == 13)
        {
            flag = 0;
            break;
        }
        free(u);
        u = NULL;
    }
    if (u != NULL)
    {
        free(u);
        u = NULL;
    }
    //setbkcolor(RED);
    if (fclose(fp) != 0) //关闭文件
    {
        printf("\nError in closing file UserInfo.");
        delay(3000);
        exit(1);
    }
    return flag;
}

/*函数功能：判断账号密码是否匹配
  返回值：0表示不正确，1表示正确*/
char right_password(char account[], char key[])
{
    FILE *fp;
    USER *u = NULL;
    int i, j, k = 0;
    int flag = 0;
    int length;
    if ((fp = fopen("UserInfo.dat", "rb+")) == NULL)
    {
        printf("\nUserInfo.dat error file");
        delay(3000);
        exit(1); //打开失败，退出程序
    }
    fseek(fp, 0, SEEK_END);
    length = ftell(fp) / sizeof(USER);
    for (i = 0; i < length; i++)
    {
        if ((u = (USER *)malloc(sizeof(USER))) == NULL)
        {
            printf("memory error RightPassword");
            delay(3000);
            exit(1); //分配空间不足，退出程序
        }
        fseek(fp, i * sizeof(USER), SEEK_SET);
        fread(u, sizeof(USER), 1, fp);
        for (j = 0; j < 13; j++)
        {
            if (u->UserName[j] != account[j])
            {
                break;
            }
            if (account[j] == '\0')
            {
                k = 1; //存在此账户
                break;
            }
        }
        if (k == 1)
        {
            for (j = 0; j < 13; j++)
            {
                if (u->password[j] != key[j])
                {
                    flag = 0;
                    break;
                }
                if (key[j] == '\0')
                {
                    flag = 1;
                    break;
                }
            }
            break;
        }
        free(u);
        u = NULL;
    }
    if (u != NULL)
    {
        free(u);
    }

    if (fclose(fp) != 0) //关闭文件
    {
        printf("\nError in closing file UserInfo.");
        delay(3000);
        exit(1);
    }
    return flag;
}

/*函数功能：判断用户是否被冻结 
  返回值：1表示冻结，0表示未冻结*/
char judge_userfrozen(char account[])
{
    FILE *fp;
    USER *u = NULL;
    int i, j, k = 0;
    char flag = 0;
    int length;
    if ((fp = fopen("UserInfo.dat", "rb+")) == NULL)
    {
        printf("\nUserInfo.dat error file");
        delay(3000);
        exit(1); //打开失败，退出程序
    }
    fseek(fp, 0, SEEK_END);
    length = ftell(fp) / sizeof(USER);
    for (i = 0; i < length; i++)
    {
        if ((u = (USER *)malloc(sizeof(USER))) == NULL)
        {
            printf("memory error RightPassword");
            delay(3000);
            exit(1); //分配空间不足，退出程序
        }
        fseek(fp, i * sizeof(USER), SEEK_SET);
        fread(u, sizeof(USER), 1, fp);
        for (j = 0; j < 13; j++)
        {
            if (u->UserName[j] != account[j])
            {
                break;
            }
            if (account[j] == '\0')
            {
                k = 1; //存在此账户
                break;
            }
        }
        if (k == 1)
        {
            if (u->UserState == '1')
            {
                flag = 0;
            }
            else
            {
                flag = 1;
            }
            break;
        }
        free(u);
        u = NULL;
    }
    if (u != NULL)
    {
        free(u);
    }

    if (fclose(fp) != 0) //关闭文件
    {
        printf("\nError in closing file UserInfo.");
        delay(3000);
        exit(1);
    }
    return flag;
}

/*函数功能：将帐户冻结
返回值：0帐户已被冻结 1：帐户冻结成功 2：帐户不存在*/
int user_freeze(char account[])
{
    FILE *fp;
    USER *u = NULL;
    int i, j, k = 0;
    int length;
    int flag;
    if ((fp = fopen("UserInfo.dat", "rb+")) == NULL)
    {
        printf("\nUserInfo.dat error file");
        delay(3000);
        exit(1); //打开失败，退出程序
    }
    fseek(fp, 0, SEEK_END);
    length = ftell(fp) / sizeof(USER);
    for (i = 0; i < length; i++)
    {
        k = 0;
        if ((u = (USER *)malloc(sizeof(USER))) == NULL)
        {
            printf("memory error RightPassword");
            delay(3000);
            exit(1); //分配空间不足，退出程序
        }
        fseek(fp, i * sizeof(USER), SEEK_SET);
        fread(u, sizeof(USER), 1, fp);
        for (j = 0; j < 12; j++)
        {
            if (u->UserName[j] != account[j])
            {
                break;
            }
            if (account[j] == '\0')
            {
                k = 1; //存在此账户
                break;
            }
        }
        if (k == 1)
        {
            if (u->UserState == '2')
            {
                flag = 0;
            }
            if (u->UserState == '1')
            {
                flag = 1;
                u->UserState = '2';
            }
        }
        else if (flag != 0 && flag != 1)
        {
            flag = 2;
        }
        fseek(fp, i * sizeof(USER), SEEK_SET);
        fwrite(u, sizeof(USER), 1, fp);
        free(u);
        u = NULL;
    }
    if (u != NULL)
    {
        free(u);
    }
    if (fclose(fp) != 0) //关闭文件
    {
        printf("\nError in closing file UserInfo.");
        delay(3000);
        exit(1);
    }
    return flag;
}

/*函数功能：将帐户解冻
返回值：0帐户已被解冻 1：帐户解冻成功 2：帐户不存在*/
char user_unfreeze(char account[])
{
    FILE *fp;
    USER *u = NULL;
    int i, j, k = 0;
    int length;
    char flag;
    if ((fp = fopen("UserInfo.dat", "rb+")) == NULL)
    {
        printf("\nUserInfo.dat error file");
        delay(3000);
        exit(1); //打开失败，退出程序
    }
    fseek(fp, 0, SEEK_END);
    length = ftell(fp) / sizeof(USER);
    for (i = 0; i < length; i++)
    {
        k = 0;
        if ((u = (USER *)malloc(sizeof(USER))) == NULL)
        {
            printf("memory error RightPassword");
            delay(3000);
            exit(1); //分配空间不足，退出程序
        }
        fseek(fp, i * sizeof(USER), SEEK_SET);
        fread(u, sizeof(USER), 1, fp);
        for (j = 0; j < 12; j++)
        {
            if (u->UserName[j] != account[j])
            {
                break;
            }
            if (account[j] == '\0')
            {
                k = 1; //存在此账户
                break;
            }
        }
        if (k == 1)
        {
            if (u->UserState == '1')
            {
                flag = 0;
            }
            if (u->UserState == '2')
            {
                flag = 1;
                u->UserState = '1';
            }
        }
        else if (flag != 0 && flag != 1)
        {
            flag = 2;
        }
        fseek(fp, i * sizeof(USER), SEEK_SET);
        fwrite(u, sizeof(USER), 1, fp);
        free(u);
        u = NULL;
    }
    if (u != NULL)
    {
        free(u);
    }
    if (fclose(fp) != 0) //关闭文件
    {
        printf("\nError in closing file UserInfo.");
        delay(3000);
        exit(1);
    }
    return flag;
}

/*函数功能：判断账号身份证号是否匹配
  返回值：0表示不正确，1表示正确*/
char right_id(char account[], char id[])
{
    FILE *fp;
    USER *u = NULL;
    int i, j, k = 0;
    int flag = 0;
    int length;
    if ((fp = fopen("UserInfo.dat", "rb+")) == NULL)
    {
        printf("\nUserInfo.dat error file");
        delay(3000);
        exit(1); //打开失败，退出程序
    }
    fseek(fp, 0, SEEK_END);
    length = ftell(fp) / sizeof(USER);
    for (i = 0; i < length; i++)
    {

        if ((u = (USER *)malloc(sizeof(USER))) == NULL)
        {
            printf("memory error RightPassword");
            delay(3000);
            exit(1); //分配空间不足，退出程序
        }
        fseek(fp, i * sizeof(USER), SEEK_SET);
        fread(u, sizeof(USER), 1, fp);
        k = 0;
        for (j = 0; j < 13; j++)
        {
            if (u->UserName[j] != account[j])
            {
                break;
            }
            if (account[j] == '\0')
            {
                k = 1; //存在此账户
                break;
            }
        }
        if (k == 1)
        {
            for (j = 0; j < 19; j++)
            {
                if (u->IDnumber[j] != id[j])
                {
                    flag = 0;
                    break;
                }
                if (id[j] == '\0')
                {
                    flag = 1;
                    break;
                }
            }
            break;
        }
        free(u);
        u = NULL;
    }
    if (u != NULL)
    {
        free(u);
    }
    fclose(fp);
    return flag;
}

/*函数功能：判断是否输入完整 （用于账户注册）
  返回值：1表示全部输入，2表示账号未输入，3表示密码未输入，4表示未确认密码，5表示身份证号未输入*/
char complete_register(char account, char key1, char key2, char id)
{
    if (account == '\0')
    {
        return 2;
    }
    if (key1 == '\0')
    {
        return 3;
    }
    if (key2 == '\0')
    {
        return 4;
    }
    if (id == '\0')
    {
        return 5;
    }
    return 1;
}

/*函数功能：判断是否输入完整 （用于账户登录）
  返回值：1表示全部输入，2表示账号未输入，3表示密码未输入*/
char complete_login(char account, char key)
{
    if (account == '\0')
    {
        return 2;
    }
    if (key == '\0')
    {
        return 3;
    }
    return 1;
}

/*函数功能：判断是否输入完整 （用于管理员登录）
  返回值：1表示全部输入，2表示密码未输入*/
char complete_admin(char key)
{
    if (key == '\0')
    {
        return 2;
    }
    return 1;
}

/*函数功能：将注册信息写入文件*/
void wr_user_inf(char account[], char key[], char id[])
{
    FILE *fp;
    USER *u;
    int i;
    if ((fp = fopen("UserInfo.dat", "rb+")) == NULL)
    {
        printf("\nUserInfo.dat error file");
        delay(3000);
        exit(1); //打开失败，退出程序
    }
    if ((u = (USER *)malloc(sizeof(USER))) == NULL)
    {
        printf("memory error WrUserInf");
        delay(3000);
        exit(1); //分配空间不足，退出程序
    }
    for (i = 0; i < 13; i++)
    {
        u->UserName[i] = account[i];
    }
    for (i = 0; i < 13; i++)
    {
        u->password[i] = key[i];
    }
    for (i = 0; i < 19; i++)
    {
        u->IDnumber[i] = id[i];
    }
    //	for(i=0;i<4;i++)
    //	{
    //		u->reportnum[i]='0';
    //	}
    //	u->reportnum[4]='\0';
    u->UserState = '1';
    u->n[0] = '\r';
    u->n[1] = '\n';
    fseek(fp, 0, SEEK_END);
    fwrite(u, sizeof(USER), 1, fp);
    free(u);
    if (fclose(fp) != 0) //关闭文件
    {
        printf("\nError in closing file UserInfo.");
        delay(3000);
        exit(1);
    }
}

/*函数功能：将新密码写入文件*/
void user_change_password(char account[], char key[])
{
    FILE *fp;
    USER *u = NULL;
    int i, j, k = 0;
    int length;
    int mimalength;
    if ((fp = fopen("UserInfo.dat", "rb+")) == NULL)
    {
        printf("\nUserInfo.dat error file");
        delay(3000);
        exit(1); //打开失败，退出程序
    }
    fseek(fp, 0, SEEK_END);
    length = ftell(fp) / sizeof(USER);
    for (i = 0; i < length; i++)
    {
        k = 0;
        if ((u = (USER *)malloc(sizeof(USER))) == NULL)
        {
            printf("memory error RightPassword");
            delay(3000);
            exit(1); //分配空间不足，退出程序
        }
        fseek(fp, i * sizeof(USER), SEEK_SET);
        fread(u, sizeof(USER), 1, fp);
        for (j = 0; j < 12; j++)
        {
            if (u->UserName[j] != account[j])
            {
                break;
            }
            if (account[j] == '\0')
            {
                k = 1; //存在此账户
                break;
            }
        }
        if (k == 1)
        {
            for (j = 0; j < 13; j++)
            {
                if (key[j] == '\0')
                {
                    mimalength = j + 1;
                    break;
                }
            }
            for (j = 0; j < mimalength; j++)
            {
                u->password[j] = key[j];
            }
            for (j = mimalength; j < 13; j++)
            {
                u->password[j] = '\0';
            }
        }
        fseek(fp, i * sizeof(USER), SEEK_SET);
        fwrite(u, sizeof(USER), 1, fp);
        free(u);
        u = NULL;
    }
    if (u != NULL)
    {
        free(u);
    }
    if (fclose(fp) != 0) //关闭文件
    {
        printf("\nError in closing file UserInfo.");
        delay(3000);
        exit(1);
    }
}

/*函数功能：将本次登录的账号写入文件*/
void wr_user(char account[])
{
    FILE *fp;
    if ((fp = fopen("usernow.dat", "rb+")) == NULL)
    {
        printf("usernow.dat file error\n");
        delay(3000);
        exit(1);
    }
    fseek(fp, 0, SEEK_SET);
    fwrite(account, sizeof(char), 13, fp);
    if (fclose(fp) != 0) //关闭文件
    {
        printf("\nError in closing file usernow.");
        delay(3000);
        exit(1);
    }
}

/*函数功能：将本次登录的账号读出*/
void re_user(char account[])
{
    FILE *fp;
    if ((fp = fopen("usernow.dat", "rb+")) == NULL)
    {
        printf("usernow.dat file error\n");
        delay(3000);
        exit(1);
    }
    fseek(fp, 0, SEEK_SET);
    fread(account, sizeof(char), 13, fp);
    if (fclose(fp) != 0) //关闭文件
    {
        printf("\nError in closing file usernow.");
        delay(3000);
        exit(1);
    }
}

/*函数功能：判断管理员登录时密码是否相符
  返回值：0表示不正确，1表示正确*/
char admin_password(char key[])
{
    char adpassword[5 + 1] = "admin";
    int i;
    int flag = 1;
    for (i = 0; i < 5; i++)
    {
        if (key[i] != adpassword[i])
        {
            flag = 0;
            break;
        }
    }
    if (key[5] != '\0')
    {
        flag = 0;
    }
    return flag;
}

/*函数功能：判断id是否存在
  返回值：0表示存在，1表示不存在*/
char judge_same_id(char idnumber[], char account[])
{
    FILE *fp;
    USER *u = NULL;
    int i, j;
    int flag = 1;
    int length;
    if ((fp = fopen("UserInfo.dat", "rb+")) == NULL)
    {
        printf("\nUserInfo.dat error file");
        delay(3000);
        exit(1); //打开失败，退出程序
    }
    fseek(fp, 0, SEEK_END);
    length = ftell(fp) / sizeof(USER);
    for (i = 0; i < length; i++)
    {
        if ((u = (USER *)malloc(sizeof(USER))) == NULL)
        {
            printf("memory error JudgeSameName");
            delay(3000);
            exit(1); //分配空间不足，退出程序
        }
        fseek(fp, i * sizeof(USER), SEEK_SET);
        fread(u, sizeof(USER), 1, fp);
        for (j = 0; j < 19; j++)
        {
            if (u->IDnumber[j] != idnumber[j])
            {
                break;
            }
            if (idnumber[j] == '\0')
            {
                j = 19;
                break;
            }
        }
        if (j == 19)
        {
            flag = 0;
            strcpy(account, u->UserName);
            break;
        }
        free(u);
        u = NULL;
    }
    if (u != NULL)
    {
        free(u);
        u = NULL;
    }
    if (fclose(fp) != 0) //关闭文件
    {
        printf("\nError in closing file UserInfo.");
        delay(3000);
        exit(1);
    }
    return flag;
}
