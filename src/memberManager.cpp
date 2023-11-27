#include "memberManager.h"

MemberManager::MemberManager()
{
    ifstream ifs;
    ifs.open(DBNAME, ios::in);

    //数据库文件不存在
    if (!ifs.is_open())
    {
        cout << "数据库文件不存在！" << endl << endl;
        this->memNum = 0;
        this->memArray = NULL;
        this->dbIsEmpty = true;
        ifs.close();
        return;
    }

    //文件存在，但是为空
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        cout << "数据库文件为空！" << endl << endl;
        this->memNum = 0;
        this->memArray = NULL;
        this->dbIsEmpty = true;
        ifs.close();
        return;
    }

    ifs.close();  //关掉上面的输入数据流

    //数据库文件存在且有数据
    this->dbIsEmpty = false;
    this->memNum = this->getDBMemNum();
    cout << "成员数量为" << this->memNum << endl;
    //将数据库文件中的数据读到成员列表中
    this->memArray = new Member * [this->memNum];
    this->memArrayInit();
    
}

MemberManager::~MemberManager()
{
    if (!this->memArray)
    {
        //释放所有成员内存
        for (int i = 0; i < this->memNum; i++)
        {
            if (this->memArray[i] != nullptr)
            {
                delete this->memArray[i];
            }
        }
        delete[] memArray;
        memArray = nullptr;
    }
}


//根据数据库文件初始化成员列表
void MemberManager::memArrayInit()
{
    ifstream ifs;
    ifs.open(DBNAME, ios::in);

    int num = 0;
    string name;
    int position = 0;

    int index = 0;
    while (ifs >> num && ifs >> name && ifs >> position)
    {
        Member* newMem = NULL;
        switch (position)
        {
        case 1:
            newMem = new Employee(num, name, position);
            break;
        case 2:
            newMem = new Manager(num, name, position);
            break;
        case 3:
            newMem = new Boss(num, name, position);
            break;
        }

        this->memArray[index++] = newMem;
    }

    ifs.close();
}



//由于cin输入int类型失败的话会出bug，所以写个函数判断是否有误，有误进行处理并要求重新输入
void MemberManager::cinInt(string about, int& intNum, string range = "[\\s\\S]+")
{
    while (true)
    {
        cout << about << endl;
        cin >> intNum;

        if (cin.fail() || !regex_match(to_string(intNum), regex(range)))
        {
            cin.clear();
            cin.ignore(1024, '\n');

            cout << "输入有误！请重新输入！" << endl << endl;
            system("pause");
            continue;
        }
        else
        {
            return;
        }
    }
}


//添加成员列表数据到数据库文件
void MemberManager::saveToDB()
{
    ofstream ofs;
    ofs.open(DBNAME, ios::out);

    for (int i = 0; i < this->memNum; i++)
    {
        ofs << this->memArray[i]->num << "\t"
            << this->memArray[i]->name << "\t"
            << this->memArray[i]->position << endl;
    }
    ofs.close();
}

//统计数据库文件中的成员数量函数
int MemberManager::getDBMemNum()
{

    int dbMemNum = 0;

    ifstream ifs;
    ifs.open(DBNAME, ios::in);

    int num = 0;
    int position = 0;
    string name;
    while (ifs >> num && ifs >> name && ifs >> position)
    {
        dbMemNum++;
    }
    ifs.close();

    return dbMemNum;
}

//判断成员是否存在，若存在则返回该成员在成员列表中的索引值
int MemberManager::memIsExist(int id)
{
    //成员列表无人
    if (this->memNum == 0)
    {
        return -1;
    }

    //逐个对比，返回编号满足的成员的索引值
    for (int i = 0; i < this->memNum; i++)
    {
        if (this->memArray[i]->num == id)
        {
            return i;
        }
    }
    return -1;
}
int MemberManager::memIsExist(int id, Member** tempMemArray, int tempMemNum)
{
    //传进来的成员列表无人
    if (tempMemNum == 0)
    {
        return -1;
    }

    //逐个对比，返回编号满足的成员的索引值
    for (int i = 0; i < tempMemNum; i++)
    {
        if (tempMemArray[i]->num == id)
        {
            return i;
        }
    }
    return -1;
}

//主界面菜单
int MemberManager::menu()
{
    int choice = 0;
    while (true)
    {
        cout << "欢迎使用职工管理系统！" << endl
             << "0、退出管理程序" << endl
             << "1、增加职工信息" << endl
             << "2、显示职工信息" << endl
             << "3、删除离职职工" << endl
             << "4、修改职工信息" << endl
             << "5、查找职工信息" << endl
             << "6、按照编号排序" << endl
             << "7、清空所有记录" << endl << endl;

        //检测输入的是否是0-7的数字，如果不是提示错误并重新要求输入
        this->cinInt("请输入您的选择：", choice, "[01234567]");
        return choice;
    }
}

//添加成员
void MemberManager::addMember()
{
    int newMemNum = 0;

    //输入添加成员数量并判断输入是否有误
    this->cinInt("请输入需要添加成员的数量：", newMemNum);
    if (newMemNum == 0)
    {
        return;
    }

    //创建新的成员列表
    Member **newMemArray = new Member * [this->memNum + newMemNum];

    //把旧的列表成员添加到新的列表
    if (this->memNum)
    {
        for (int i = 0; i < this->memNum; i++)
        {
            newMemArray[i] = this->memArray[i];
        }
    }

    //添加新成员
    int choice = 0;
    int iMem = 0;
    while (iMem < newMemNum)
    {
        cout << endl << endl;
        cout << "请选择第" << iMem + 1 << "位成员职位：" << endl
            << "1、老板" << endl
            << "2、经理" << endl
            << "3、普通员工" << endl << endl;

        //判断输入是不是数字且在1-3之间
        this->cinInt( "请输入数字选择：", choice, "[123]" );

        //新建一个成员
        int num;                               //新成员编号
        string name;                           //新成员姓名

        //判断输入的成员编号是否已存在，若存在则报错
        while (true)
        {
            this->cinInt("请输入该成员编号：", num);
            if (this->memIsExist(num, newMemArray, this->memNum + iMem) == -1)
            {
                break;
            }
            else
            {
                cout << "输入的成员编号已被其他人使用！！！" << endl;
                cout << "请重新输入……" << endl << endl;
                system("pause");
            }
        }

        cout << "请输入该成员姓名：" << endl;
        cin >> name;

        Member* newMem = NULL;
        switch (choice)
        {
        case 1:
            newMem = new Boss(num, name, 3);
            break;
        case 2:
            newMem = new Manager(num, name, 2);
            break;
        case 3:
            newMem = new Employee(num, name, 1);
            break;
        }

        //把新成员添加到新成员列表
        newMemArray[this->memNum + iMem] = newMem;
        iMem++;
    }

    //释放旧成员列表内存
    delete[] this->memArray;

    //更新成员数量和成员列表
    this->memNum += newMemNum;
    this->memArray = newMemArray;

    //把数据存到数据库文件
    this->dbIsEmpty = false;
    this->saveToDB();

    cout << endl;
    cout << "成功添加" << newMemNum << "名新成员！-^v^-UU-^v^-" << endl;
    cout << "按任意键返回目录" << endl;
    system("pause");
}


//显示所有成员
void MemberManager::showAllMem()
{
    if (this->dbIsEmpty)
    {
        cout << "文件不存在或记录为空！" << endl;
        system("pause");
        return;
    }

    cout << endl << endl;
    cout << "所有成员信息如下：" << endl;
    for (int i = 0; i < this->memNum; i++)
    {
        this->memArray[i]->printInfo();
    }

    system("pause");
}

//删除成员函数
void MemberManager::delMem()
{
    //判断成员列表是否为空
    if (this->dbIsEmpty)
    {
        cout << "成员列表为空！" << endl;
        system("pause");
        return;
    }

    int delMem = -1;
    this->cinInt("请输入你想删除的成员的编号：", delMem);

    int delIndex = this->memIsExist(delMem);
    if (delIndex == -1)
    {
        cout << "成员不存在！" << endl;
        cout << "按任意键返回菜单界面" << endl;
        system("pause");
        return;
    }

    //指针前移，从逻辑上删除成员
    for (int i = delIndex; i < this->memNum - 1; i++)
    {
        this->memArray[i] = this->memArray[i + 1];
    }
    
    
    if (!(--this->memNum))
    {
        this->dbIsEmpty = true;
    }
    this->saveToDB();

    cout << "删除成功！" << endl;
    cout << "点击任意键返回菜单界面……" << endl;
    system("pause");
}

//修改成员函数
void MemberManager::modMem()
{
    //判断成员列表是否为空
    if (this->dbIsEmpty)
    {
        cout << "文件不存在或成员列表为空！" << endl;
        system("pause");
        return;
    }

    //要求输入被修改的成员编号
    int modMemNum = -1;
    this->cinInt("请输入你想修改的成员的编号：", modMemNum);
    int modIndex = this->memIsExist(modMemNum);
    if (modIndex == -1)
    {
        cout << "查无此人！" << endl;
        system("pause");
        return;
    }

    //修改成员
    int modNum = 0;
    string modName;
    int modPosition = 0;
    
    this->cinInt("请输入修改后的成员编号：", modNum);
    cout << "请输入修改后的成员姓名：" << endl;
    cin >> modName;
    cout << "请选择修改后的成员职位：" << endl
         << "1、老板" << endl
         << "2、经理" << endl
         << "3、普通员工" << endl << endl;
    this->cinInt("请输入数字选择：", modPosition, "[123]");

    Member* modMem = NULL;
    switch (modPosition)
    {
    case 1:
        modMem = new Boss(modNum, modName, 3);
        break;
    case 2:
        modMem = new Manager(modNum, modName, 2);
        break;
    case 3:
        modMem = new Employee(modNum, modName, 1);
        break;
    }

    //释放掉被修改的成员内存，并将指向它的指针指向被修改后的成员内存
    delete this->memArray[modIndex];
    this->memArray[modIndex] = modMem;

    //保存到数据库文件
    this->saveToDB();

    cout << "修改成员成功！" << endl;
    cout << "按任意键返回菜单界面……" << endl;
    system("pause");


}




//查找成员函数
void MemberManager::findMem()
{
    if (this->dbIsEmpty)
    {
        cout << "文件不存在或成员列表为空！" << endl;
        cout << "按任意键返回菜单界面……" << endl;
        system("pause");
    }

    cout << "你可以选择按照编号查找成员或者按照姓名查找成员：" << endl
         << "1、按照编号" << endl
         << "2、按照姓名" << endl << endl;

    int findType = 0;
    this->cinInt("请选择：", findType, "[12]");

    //按照编号查找
    if (findType == 1)
    {
        int findMemNum = -1;
        this->cinInt("请输入查找的成员编号：", findMemNum);

        //查找成员索引
        int findMemIndex = this->memIsExist(findMemNum);
        cout << "查找结果如下：" << endl << endl;
        if (findMemIndex == -1)
        {
            cout << "成员不存在！" << endl;
            cout << endl << "按任意键返回菜单界面……" << endl;
            system("pause");
        }
        else
        {
            this->memArray[findMemIndex]->printInfo();
            cout << endl << "按任意键返回菜单界面……" << endl;
            system("pause");
        }
    }
    else  //按照姓名查找
    {
        string findMemName;
        cout << "请输入查找的成员姓名：" << endl;
        cin >> findMemName;

        cout << "查找结果如下：" << endl << endl;
        //遍历一遍成员列表，符合结果的打印输出
        int rightResult = 0;
        for (int i = 0; i < this->memNum; i++)
        {
            if (this->memArray[i]->name == findMemName)
            {
                this->memArray[i]->printInfo();
                rightResult++;
            }
        }
        if (rightResult == 0)
        {
            cout << "成员不存在！" << endl;
        }
        cout << endl << "按任意键返回菜单界面……" << endl;
        system("pause");
    }
}

//给成员列表排序
void MemberManager::sortMemArray()
{
    if (this->dbIsEmpty)
    {
        cout << "文件不存在或成员列表为空！" << endl;
        cout << "按任意键返回菜单界面……" << endl;
        system("pause");
    }

    cout << "你可以选择编号是按照从小到大排序还是从大到小排序：" << endl
        << "1、从小到大" << endl
        << "2、从大到小" << endl << endl;

    int sortType = 0;
    this->cinInt("请输入选择：", sortType);
    
    //从小到大排序
    //选择排序算法
    if (sortType == 1)
    {
        int minMemNumIndex = -1;
        for (int i = 0; i < this->memNum; i++)
        {
            minMemNumIndex = i;
            for (int y = i + 1; y < this->memNum; y++)
            {
                if (this->memArray[y]->num < this->memArray[minMemNumIndex]->num)
                {
                    minMemNumIndex = y;
                }
            }
            if (i != minMemNumIndex)
            {
                Member* temp = this->memArray[i];
                this->memArray[i] = this->memArray[minMemNumIndex];
                this->memArray[minMemNumIndex] = temp;
            }
        }
    }

    //从大到小排序
    if (sortType == 2)
    {
        int maxMemNumIndex = -1;
        for (int i = 0; i < this->memNum; i++)
        {
            maxMemNumIndex = i;
            for (int y = i + 1; y < this->memNum; y++)
            {
                if (this->memArray[y]->num > this->memArray[maxMemNumIndex]->num)
                {
                    maxMemNumIndex = y;
                }
            }
            if (i != maxMemNumIndex)
            {
                Member* temp = this->memArray[i];
                this->memArray[i] = this->memArray[maxMemNumIndex];
                this->memArray[maxMemNumIndex] = temp;
            }
        }
    }

    //保存修改到数据库文件
    this->saveToDB();
    cout << "排序成功！";
    this->showAllMem();
}


//清空数据库函数，删库跑路咯！
void MemberManager::delelteAllMem()
{
    if (this->dbIsEmpty)
    {
        cout << "文件不存在或成员列表为空！" << endl;
        cout << "按任意键返回菜单界面……" << endl;
        system("pause");
    }

    
    int repeatConfirm = 0;
    cout << "您真的想要清空数据库吗？" << endl
        << "1、真的" << endl
        << "2、不想" << endl << endl;
    this->cinInt("请做出您的选择：", repeatConfirm);

    //如果不想清空就退出函数
    if (repeatConfirm != 1)
    {
        cout << endl << "好吧，你做出了正确的选择。" << endl;
        system("pause");
        return;
    }

    cout << "您真的真的想要清空数据库吗？" << endl
        << "1、真的真的" << endl
        << "2、不想" << endl << endl;
    this->cinInt("请做出您的选择：", repeatConfirm);

    //如果不想清空就退出函数
    if (repeatConfirm != 1)
    {
        cout << endl << "好吧，你做出了正确的选择。" << endl;
        system("pause");
        return;
    }

    //先清空数据库文件
    ofstream ofs;
    ofs.open(DBNAME, ios::trunc);
    ofs.close();

    //释放所有成员内存
    for (int i = 0; i < this->memNum; i++)
    {
        if (this->memArray[i] != nullptr)
        {
            delete this->memArray[i];
        }
    }
    delete[] memArray;
    memArray = nullptr;

    this->memNum = 0;
    this->dbIsEmpty = true;

    cout << "成功清空数据库！！！！！！！！！！" << endl;
    cout << "按任意键返回菜单界面……" << endl;
    system("pause");

}

