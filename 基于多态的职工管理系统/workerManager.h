#pragma once
#include <iostream>
#include "worker.h"
using namespace std;
#include <fstream>
#include <string>

const string FILENAME = "empFile.txt";
class WorkerManager {
public:

    WorkerManager();

    ~WorkerManager();

    //展示菜单
    void ShowMeau();

    //退出系统
    void ExitSystem();

    //增加职工
    void addEmp();

    //记录职工人数
    int m_EmpNum;

    //记录职工指针
    Worker** m_EmpArray;

    //保存文件
    void save();

    //判断文件是否为空
    bool m_FileIsempty;

    //统计文件中的人数
    int get_EmpNum();

    //初始化职工
    void init_EMP();

    //显示职工
    void show_EMP();

    //删除职工
    void del_Emp();

    //判断职工是否存在，存在则返回位置
    int isExit(int id);

    //修改职工
    void modify_EMP();

    //查找职工
    void findEMP();

    //排序职工
    void sortEmp();

    //清空数据
    void cleanFile();
};
