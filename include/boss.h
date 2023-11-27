#pragma once

#include <iostream>
#include "member.h"

using namespace std;

//老板类:public 公司成员类
class Boss : public Member
{
public:
    Boss(int num, string name, int position);

    //输出成员信息
    virtual void printInfo();

    //输出成员职位
    virtual void getPosition();

};