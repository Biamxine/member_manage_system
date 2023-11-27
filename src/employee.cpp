#include "employee.h"


Employee::Employee(int num, string name, int position)
{
    this->num = num;
    this->name = name;
    this->position = position;
    this->duty = "完成经理交给的任务";
}

//输出成员信息
void Employee::printInfo()
{
    cout << "编号：" << this->num << "              "
         << "姓名：" << this->name << "              "
         << "职位：" << "普通员工" << "              "
         << "职责：" << this->duty << endl;
}

//输出成员职位
void Employee::getPosition()
{
    cout << "成员职位：普通员工" << endl;
}