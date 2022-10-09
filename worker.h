#pragma once

#include <iostream>
#include <string>

using namespace std;

//职工抽象基类
class Worker {
public:
    //显示个人信息
    virtual void showInfo() = 0;

    //获取岗位名称
    virtual string getDepName() = 0;

    //岗位职责
    virtual string getResponsibility() = 0;

    //纯虚析构
    virtual ~Worker() = 0;

    int m_ID;       //职工编号
    string m_Name;  //职工姓名
    int m_DeptID;   //职工所在部门名称编号
};

