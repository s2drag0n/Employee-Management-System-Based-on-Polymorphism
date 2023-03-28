#pragma once
#include <iostream>
#include <string>
using namespace std;

//职工抽象类
class Worker {
public:

    //编号
    int m_ID;

    //姓名
    string m_Name;

    //部门编号
    int m_DeptId;

    //获取岗位名称
    virtual string getDeptName() = 0;

    //显示个人信息
    virtual void showInfo() = 0;
};