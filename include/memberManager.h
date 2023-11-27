#pragma once
#include <iostream>
#include<fstream>
#include<regex>
#include<string>

#include "boss.h"
#include "employee.h"
#include "manager.h"

using namespace std;

#define DBNAME "memberDB.txt"

class MemberManager
{
protected:
    int memNum;              //成员数量
    Member **memArray;       //成员列表
    bool dbIsEmpty;          //数据库文件状态

public:
    MemberManager();

    ~MemberManager();

    //根据数据库文件初始化成员列表
    void memArrayInit();

    //由于cin输入int类型失败的话会出bug，所以写个函数判断是否有误，有误进行处理并要求重新输入
    void cinInt(string about, int& intNum, string range );

    //添加成员列表数据到数据库文件
    void saveToDB();

    //统计数据库文件中的成员数量函数
    int getDBMemNum();

    //判断成员是否存在，若存在则返回该成员在成员列表中的索引值
    int memIsExist(int id);
    int memIsExist(int id, Member** tempMemArray, int tempMemNum);

    int menu();          //主菜单界面
    void addMember();    //添加成员函数
    void showAllMem();   //显示所有成员函数
    void delMem();       //删除成员函数
    void modMem();       //修改成员函数
    void findMem();      //查找成员函数
    void sortMemArray(); //给成员列表排序
    void delelteAllMem();//清空数据库函数，删库跑路咯！

};