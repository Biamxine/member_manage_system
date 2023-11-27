#pragma once
#include<iostream>


using namespace std;

//公司成员类
class Member
{
public:
    int num = 0;            //编号
    string name;            //姓名
    int position;           //职位
    string duty;            //职责

    //输出成员信息
    virtual void printInfo() = 0;


    //输出成员职位
    virtual void getPosition() = 0;
};
