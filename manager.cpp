#include "manager.h"

//构造函数
Manager::Manager(int id, string name, int deptID) {
    this->m_ID = id;
    this->m_Name = name;
    this->m_DeptID = deptID;
}

//显示个人信息
void Manager::showInfo() {
    cout << "职工编号：" << this->m_ID;
    cout << "\t职工姓名：" << this->m_Name;
    cout << "\t岗位：" << this->getDepName();
    cout << "\t岗位职责：" << this->getResponsibility() << endl;
}

//获取岗位名称
string Manager::getDepName() {
    return string("经理");
}

//获取岗位职责
string Manager::getResponsibility() {
    return string("完成老板交代的任务，并给普通员工下发任务");
}
