//boss.cpp
#include "boss.h"

//构造函数
Boss::Boss(int id, string name, int deptID) {
    this->m_ID = id;
    this->m_Name = name;
    this->m_DeptID = deptID;
}

//显示个人信息
void Boss::showInfo() {
    cout << "职工编号：" << this->m_ID;
    cout << "\t职工姓名：" << this->m_Name;
    cout << "\t岗位：" << this->getDepName();
    cout << "\t岗位职责：" << this->getResponsibility() << endl;
}

//获取岗位名称
string Boss::getDepName() {
    return string("老板");
}

//获取岗位职责
string Boss::getResponsibility() {
    return string("管理公司所有事物");
}
