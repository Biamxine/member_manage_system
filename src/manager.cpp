#include "manager.h"




Manager::Manager(int num, string name, int position)
{
    this->num = num;
    this->name = name;
    this->position = position;
    this->duty = "完成老板交给的任务，并下发任务给普通员工";
}

//输出成员信息
void Manager::printInfo()
{
    cout << "编号：" << this->num << "              "
         << "姓名：" << this->name << "              "
         << "职位：" << "经理" << "              "
         << "职责：" << this->duty << endl;
}

//输出成员职位
void Manager::getPosition()
{
    cout << "成员职位：经理" << endl;
}