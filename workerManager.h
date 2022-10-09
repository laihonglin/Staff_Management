#pragma once // 防止头文件重复包含

#include <iostream>

using namespace std;

#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream>

#define FILENAME "empFile.txt"

class WorkerManager
{
public:

    // 构造函数
    WorkerManager();

    // 展示菜单
    void Show_Menu();

    // 退出系统
    void ExitSystem();

    //记录文件中的人数个数
    int m_EmpNum;
    //员工数组的指针
    Worker **m_EmpArray;

    //添加职工
    void addEmp();

    //保存文件
    void save() const;

    //标志文件是否为空
    bool m_IsFileEmpty;

    //统计人数
    static int getEmpNum();

    //初始化员工
    void initEmp();

    //显示职工
    void showEmp();

    //删除职工
    void delEmp();

    //按照职工编号判断职工是否存在，若存在返回职工在数组中位置，不存在返回-1
    int isExist(int id);

    //修改职工
    void modEmp();

    //查找职工
    void findEmp();

    //排序职工
    void sortEmp();

    //清空文件
    void clearFile();

    // 析构函数
    ~WorkerManager();
};
