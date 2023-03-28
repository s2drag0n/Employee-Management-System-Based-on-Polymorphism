#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"


WorkerManager::WorkerManager() {


    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    //文件不存在
    if (!ifs.is_open()) {
        //cout << "文件不存在!" << endl;
        this->m_EmpArray = NULL;
        this->m_EmpNum = 0;
        this->m_FileIsempty = true;
        ifs.close();
        return;
    }

    //文件存在但没有记录
    char ch;
    ifs >> ch;
    if (ifs.eof()) {
        //cout << "文件为空!" << endl;
        this->m_EmpArray = NULL;
        this->m_EmpNum = 0;
        this->m_FileIsempty = true;
        ifs.close();
        return;
    }

    //文件存在且有记录
    int num = this->get_EmpNum();
    //cout << "职工人数为：" << num << endl;
    this->m_EmpNum = num;

    //开辟空间
    this->m_EmpArray = new Worker * [this->m_EmpNum];
    //数据存入堆区
    this->init_EMP();

}

WorkerManager::~WorkerManager() {
    if (this->m_EmpArray != NULL) {
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}

void WorkerManager::ShowMeau() {

    cout << "********************************************************" << endl;
    cout << "********************欢迎使用职工管理系统*****************" << endl;
    cout << "********************0.退出管理系统***********************" << endl;
    cout << "********************1.增加职工信息***********************" << endl;
    cout << "********************2.显示职工信息***********************" << endl;
    cout << "********************3.删除离职职工***********************" << endl;
    cout << "********************4.修改职工信息***********************" << endl;
    cout << "********************5.查找职工信息统*********************" << endl;
    cout << "********************6.按照编号排序***********************" << endl;
    cout << "********************7.清空所有文档***********************" << endl;
    cout << "********************************************************" << endl;
    cout << endl;
}

void WorkerManager::ExitSystem() {
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);    // 退出程序
}

//增加职工
void WorkerManager::addEmp() {
    cout << "请输入添加职工的数量" << endl;

    int addNum = 0;
    cin >> addNum;

    if (addNum > 0) {

        //计算新空间大小
        int newSize = this->m_EmpNum + addNum;

        //开辟新空间
        Worker** newSpace = new Worker * [newSize];

        //将原来的数据拷贝到新空间
        if (this->m_EmpArray != NULL) {
            for (int i = 0; i < this->m_EmpNum; i++) {
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        //添加新数据
        for (int i = 0; i < addNum; i++) {
            int id;
            string name;
            int dSelect;

            cout << "请输入第" << i + 1 << "个" << "新职工的编号" << endl;
            cin >> id;

            cout << "请输入第" << i + 1 << "个" << "新职工的姓名" << endl;
            cin >> name;

            cout << "请选择第" << i + 1 << "个" << "新职工的岗位" << endl;
            cout << "1.普通职工" << endl;
            cout << "2.经理" << endl;
            cout << "3.总裁" << endl;
            cin >> dSelect;

            Worker* worker = NULL;
            switch (dSelect) {
            case 1:
                worker = new Employee(id, name, dSelect);
                break;
            case 2:
                worker = new Manager(id, name, dSelect);
                break;
            case 3:
                worker = new Boss(id, name, dSelect);
                break;
            default:
                break;
            }

            //将创建的职工指针保存到数组
            newSpace[this->m_EmpNum + i] = worker;
        }

        //释放原有空间
        delete[] this->m_EmpArray;

        //更新新空间指向
        this->m_EmpArray = newSpace;

        //更新新的职工人数
        this->m_EmpNum = newSize;

        //数据写入文件
        this->save();

        //提示添加成功
        cout << "成功添加" << addNum << "名新职工" << endl;

        //更新员工不为空
        this->m_FileIsempty = false;


    } else {
        cout << "输入有误" << endl;
    }

    //按任意键 清屏回到上级目录
    system("pause");
    system("cls");
}

void WorkerManager::save() {

    ofstream ofs;
    ofs.open(FILENAME, ios::out);

    for (int i = 0; i < this->m_EmpNum; i++) {
        ofs << this->m_EmpArray[i]->m_ID << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptId << endl;
    }

    ofs.close();
}

int WorkerManager::get_EmpNum() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dId;

    int num = 0;

    while (ifs >> id && ifs >> name && ifs >> dId) {
        num++;
    }

    return num;
}

//初始化员工
void WorkerManager::init_EMP() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dId;

    int index = 0;

    while (ifs >> id && ifs >> name && ifs >> dId) {
        Worker* worker = NULL;
        if (dId == 1) {
            worker = new Employee(id, name, dId);
        } else if (dId == 2) {
            worker = new Manager(id, name, dId);
        } else if (dId == 3) {
            worker = new Boss(id, name, dId);
        }
        this->m_EmpArray[index++] = worker;
    }

    ifs.close();
}

//显示职工
void WorkerManager::show_EMP() {
    if (this->m_FileIsempty) {
        cout << "职工信息文件不存在或者为空" << endl;
    } else {
        for (int i = 0; i < this->m_EmpNum; i++) {
            this->m_EmpArray[i]->showInfo();
        }
    }
    system("pause");
    system("cls");
}

//删除职工
void WorkerManager::del_Emp() {
    if (this->m_FileIsempty) {
        cout << "文件不存在或者记录为空" << endl;
    } else {
        //按照职工编号删除
        cout << "请输入想要删除的职工编号" << endl;
        int id = 0;
        cin >> id;

        int index = this->isExit(id);

        if (index != -1) {
            for (int i = index; i < this->m_EmpNum - 1; i++) {
                this->m_EmpArray[i] = this->m_EmpArray[i + 1];
            }
            this->m_EmpNum--;
            this->save();
        } else {
            cout << "删除失败，未找到该职工" << endl;
        }
    }

    //按任意键 清屏
    system("pause");
    system("cls");
}

//判断职工是否存在
int WorkerManager::isExit(int id) {
    int index = -1;
    for (int i = 0; i < this->m_EmpNum; i++) {
        if (this->m_EmpArray[i]->m_ID == id) {
            //找到职工
            index = i;
            break;
        }
    }
    return index;
}

//修改职工
void WorkerManager::modify_EMP() {
    if (this->m_FileIsempty) {
        cout << "文件不存在或记录为空" << endl;
    } else {
        cout << "请输入修改职工的编号：" << endl;
        int id;
        cin >> id;

        int ret = this->isExit(id);
        if (ret != -1) {
            delete this->m_EmpArray[ret];

            int newId = 0;
            string newName = "";
            int dSelect = 0;
            cout << "查到：" << id << "号职工，请输入新职工号：" << endl;
            cin >> newId;
            cout << "请输入新姓名：" << endl;
            cin >> newName;
            cout << "请输入岗位：" << endl;
            cout << "1.普通职工：" << endl;
            cout << "2.经理：" << endl;
            cout << "3.总裁：" << endl;
            cin >> dSelect;

            Worker* worker = NULL;
            switch (dSelect) {
            case 1:
                worker = new Employee(newId, newName, dSelect);
                break;
            case 2:
                worker = new Manager(newId, newName, dSelect);
                break;
            case 3:
                worker = new Boss(newId, newName, dSelect);
                break;
            default:
                break;
            }

            this->m_EmpArray[ret] = worker;

            if (this->m_EmpArray[ret] != NULL) {
            cout << "修改成功！" << this->m_EmpArray[ret]->m_DeptId << endl;
            }

            this->save();
        } else {

        }

    }

    system("pause");
    system("cls");
}

//查找职工
void WorkerManager::findEMP() {
    if (this->m_FileIsempty) {
        cout << "文件不存在或记录为空" << endl;
    } else {
        cout << "请输入查找的方式" << endl;
        cout << "1.按职工编号" << endl;
        cout << "2.按姓名" << endl;
        int select = 0;
        cin >> select;

        if (select == 1) {
            int id;
            cout << "请输入查找的职工编号" << endl;
            cin >> id;

            int ret = this->isExit(id);
            if (ret != -1) {
                cout << "查找成功！该职工的信息如下：" << endl;
                if (this->m_EmpArray[ret] != NULL) {
                    this->m_EmpArray[ret]->showInfo();
                } else {
                    cout << "查找失败，查无此人" << endl;
                }
            }
        } else if (select == 2) {
            string name;
            cout << "请输入查找的职工姓名" << endl;
            cin >> name;
            bool flag = false;
            for (int i = 0; i < this->m_EmpNum; i++) {
                if (this->m_EmpArray[i]->m_Name == name) {
                    flag = true;
                    cout << "查找成功！职工编号为" << this->m_EmpArray[i]->m_ID << "的信如下：" << endl;
                    this->m_EmpArray[i]->showInfo();
                }
            }
            if (flag == false) {
                cout << "查找失败，查无此人" << endl;
            }
        } else {
            cout << "输入信息有误" << endl;

        }
    }
    system("pause");
    system("cls");

}

//排序职工
void WorkerManager::sortEmp() {
    if (this->m_FileIsempty) {
        cout << "文件不存在或记录为空" << endl;
    } else {
        cout << "请选择排序方式：" << endl;
        cout << "1.按职工号升序" << endl;
        cout << "2.按职工号降序" << endl;

        int select = 0;
        cin >> select;

        for (int i = 0; i < this->m_EmpNum; i++) {
            int minOrMax = i;
            for (int j = i + 1; j < this->m_EmpNum; j++) {
                if (select == 1) {
                    if (m_EmpArray[minOrMax]->m_ID > m_EmpArray[j]->m_ID) {
                        minOrMax = j;
                    }
                } else if (select == 2) {
                    if (m_EmpArray[minOrMax]->m_ID < m_EmpArray[j]->m_ID) {
                        minOrMax = j;
                    }
                } else {
                    cout << "输入有误" << endl;
                }
                if (i != minOrMax) {
                    Worker* worker = m_EmpArray[i];
                    m_EmpArray[i] = m_EmpArray[minOrMax];
                    m_EmpArray[minOrMax] = worker;
                }
            }
        }
        save();
    }
    system("pause");
    system("cls");
}

//清空数据
void WorkerManager::cleanFile() {
    cout << "确认清空？" << endl;
    cout << "1.确认" << endl;
    cout << "2.取消" << endl;

    int select = 0;
    cin >> select;

    if (select == 1) {
        ofstream ofs(FILENAME, ios::trunc);//trunc表示删除文件并重新创建
        ofs.close();

        if (this->m_EmpArray != NULL) {
            for (int i = 0; i < this->m_EmpNum; i++) {
                if (this->m_EmpArray[i] != NULL) {
                    delete this->m_EmpArray[i];
                    m_EmpArray[i] = NULL;
                }
            }
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_EmpNum = 0;
            this->m_FileIsempty = true;
        }
        cout << "清空成功" << endl;
    }
    system("pause");
    system("cls");
}