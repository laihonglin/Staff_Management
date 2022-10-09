#include "employee.h"

//构造函数
Employee::Employee(int id, string name, int deptID) {
    this->m_ID = id;
    this->m_Name = name;
    this->m_DeptID = deptID;
}

//显示个人信息
void Employee::showInfo() {
    cout << "职工编号：" << this->m_ID;
    cout << "\t职工姓名：" << this->m_Name;
    cout << "\t岗位：" << this->getDepName();
    cout << "\t岗位职责：" << this->getResponsibility() << endl;
}

//获取岗位名称
string Employee::getDepName() {
    return string("员工");
}

//获取岗位职责
string Employee::getResponsibility() {
    return string("完成经理交代的任务");
}
