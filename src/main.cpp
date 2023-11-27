// main.cpp: 定义应用程序的入口点。
//

#include "member_manage_system.h"

using namespace std;

int main() {

    MemberManager mm;
    while (true)
    {
        switch (mm.menu())
        {
        case 0:
            return 0;
        case 1:
            mm.addMember();       //添加成员函数
            break;
        case 2:
            mm.showAllMem();      //显示所有成员函数
            break;
        case 3:
            mm.delMem();          //删除成员函数
            break;
        case 4:
            mm.modMem();          //修改成员函数
            break;
        case 5:
            mm.findMem();         //查找成员函数
            break;
        case 6:
            mm.sortMemArray();    //给成员列表排序
            break;
        case 7:
            mm.delelteAllMem();   //清空数据库函数，删库跑路咯！
            break;
        }

        system("cls");

    }

}
