
#include "boss.h"



Boss::Boss(int num, string name, int position)
{
    this->num = num;
    this->name = name;
    this->position = position;
    this->duty = "管理公司所有事务";
}

//输出成员信息
void Boss::printInfo()
{
    cout << "编号：" << this->num << "              "
         << "姓名：" << this->name << "              "
        << "职位：" << "老板" << "              "
         << "职责：" << this->duty << endl;
}

//输出成员职位
void Boss::getPosition()
{
    cout << "成员职位：老板" << endl;
}