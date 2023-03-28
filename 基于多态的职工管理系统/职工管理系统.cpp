#include <iostream>
#include "workerManager.h"
using namespace std;



int main() {


    //实例化管理类对象
    WorkerManager wm;

    //调用展示菜单函数


    int choice = 0;

    while (true) {

        wm.ShowMeau();

        cout << "请输入您的选择：" << endl;
        cin >> choice;

        switch (choice) {
        case 0:
            //退出
            wm.ExitSystem();
            break;
        case 1:
            //增加职工信息
            wm.addEmp();
            break;
        case 2:
            //显示职工
            wm.show_EMP();
            break;
        case 3:
            //删除职工
            wm.del_Emp();
            break;
        case 4:
            //修改职工
            wm.modify_EMP();
            break;
        case 5:
            //查找职工
            wm.findEMP();
            break;
        case 6:
            //排序职工
            wm.sortEmp();
            break;
        case 7:
            //清空数据
            wm.cleanFile();
            break;
        default:
            system("cls");//无效数字就清空屏幕
            break;
        }
    }

    return 0;
}