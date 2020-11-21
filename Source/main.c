/***********************

程序主函数
 
**********************/
#include "common.h"
#include "main.h"
void main(void)
{

    int page = 12; //页面切换变量

    SetSVGA64k();
    Mouse_Init();

    while (1)
    {
        switch (page)
        {
        case 0: //欢迎页面
            page = welcome();
            break;
        case 1: //登录页面
            page = login_user();
            break;

        case 2: //管理员登录页面
            page = login_admin();
            break;
        case 3: //注册页面
            page = register_user();
            break;

        case 4: //忘记密码页面
            page = refound_user();
            break;

        case 5: //可视化界面
            page = visual_page();
            break;

        case 6: //通报界面
            page = report();
            break;

        case 7: //数据查询界面
            page = inquiry();
            break;

        case 8: //管理员界面
            page = admin_menu();
            break;

        case 9: //冻结用户界面
            page = aduser();
            break;

        case 10: //数据审核页面
            page = admin_review();
            break;

        case 11: //数据修改页面
            page = admin_modify();
            break;

        case 12: //数据展示页面（柱状图）
            page = showinfo_main();
            break;

        case -1:         //退出程序
            CloseSVGA(); //关闭图形界面
            exit(0);
        }
    }
}
