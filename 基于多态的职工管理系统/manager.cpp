#include "manager.h"

Manager::Manager(int id, string name, int dId) {
    this->m_ID = id;
    this->m_Name = name;
    this->m_DeptId = dId;
}

//获取岗位名称
string Manager::getDeptName() {
    return string("经理");
}

//显示个人信息
void Manager::showInfo() {
    cout << "职工编号:" << this->m_ID
        << "\t职工姓名：" << this->m_Name
        << "\t岗位姓名：" << this->getDeptName()
        << "\t岗位职责：完成老板给的任务，并将任务分发给员工" << endl;
}