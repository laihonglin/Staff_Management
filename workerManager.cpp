#include "workerManager.h"

WorkerManager::WorkerManager()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    //文件不存在情况
    if (!ifs.is_open())
    {
//  cout << "文件不存在！" << endl;       //测试输出
        this->m_EmpNum = 0;             //初始化人数
        this->m_IsFileEmpty = true;     //初始化 文件为空 标签
        this->m_EmpArray = NULL;        //初始化数组
        ifs.close();                    //关闭文件
        return;
    }
    //文件存在，并且没有记录
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
//  cout << "文件为空！" << endl;         //测试输出
        this->m_EmpNum = 0;             //初始化人数
        this->m_IsFileEmpty = true;     //初始化 文件为空 标签
        this->m_EmpArray = NULL;        //初始化数组
        ifs.close();                    //关闭文件
        return;
    }
    //文件存在，且保存职工数据
    int num = this->getEmpNum();
    //  cout << "职工个数为" << num << endl; //测试代码
    this->m_EmpNum = num;              //更新成员属性
    //开辟空间
    this->m_EmpArray = new Worker *[this->m_EmpNum];
    //将文件中的数据储存到数组
    this->initEmp();
}

void WorkerManager::Show_Menu()
{
    cout << "************************" << endl;
    cout << "** 欢迎使用职工管理系统! **" << endl;
    cout << "***** 0.退出管理程序 *****" << endl;
    cout << "***** 1.增加职工信息 *****" << endl;
    cout << "***** 2.显示职工信息 *****" << endl;
    cout << "***** 3.删除离职职工 *****" << endl;
    cout << "***** 4.修改职工信息 *****" << endl;
    cout << "***** 5.查找职工信息 *****" << endl;
    cout << "***** 6.按照编号排序 *****" << endl;
    cout << "***** 7.清空所有文档 *****" << endl;
    cout << "************************" << endl;
    cout << endl;
}

//退出系统
void WorkerManager::ExitSystem()
{
    cout << "欢迎下次使用" << endl;
    exit(0); // 退出程序
}

void WorkerManager::addEmp()
{
    cout << "请输入增加职工数量：" << endl;

    int addNum = 0;
    cin >> addNum;

    if (addNum > 0)
    {
        //计算新空间大小
        int newSize = this->m_EmpNum + addNum;

        //开辟新空间
        Worker **newSpace = new Worker *[newSize];

        //将原来空间下内容存放到新空间下
        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        //输入新数据
        for (int i = 0; i < addNum; ++i)
        {
            int id;
            string name;
            int deptSelect;

            cout << "请输入第" << i + 1 << "个新职工的编号" << endl;
            cin >> id;

            cout << "请输入第" << i + 1 << "个新职工的姓名" << endl;
            cin >> name;

            cout << "请选择该职工岗位（数字）:\n\t1、普通职工\n\t2、经理\n\t3、老板" << endl;
            cin >> deptSelect;

            Worker *worker = NULL;
            switch (deptSelect)
            {
                case 1: //普通员工
                    worker = new Employee(id, name, 1);
                    break;
                case 2: //经理
                    worker = new Employee(id, name, 2);
                    break;
                case 3: //老板
                    worker = new Boss(id, name, 3);
                    break;
                default:
                    break;
            }
            newSpace[this->m_EmpNum + i] = worker;
        }
        //释放原有空间
        delete[] this->m_EmpArray;
        //更改新空间的指向
        this->m_EmpArray = newSpace;
        //更改新的个数
        this->m_EmpNum = newSize;
        //更新职工不为空标志
        this->m_IsFileEmpty = false;
        //提示信息
        cout << "成功添加" << addNum << "名员工！" << endl;
        //保存到文件中
        this->save();
    } else
    {
        cout << "输入有误！" << endl;
    }
    system("read");
    system("clear");
}

void WorkerManager::save() const
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);

    for (int i = 0; i < this->m_EmpNum; ++i)
    {
        ofs << this->m_EmpArray[i]->m_ID << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptID << endl;
    }

    ofs.close();
}

int WorkerManager::getEmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int ID;
    string name;
    int deptID;

    int num = 0;

    while (ifs >> ID && ifs >> name && ifs >> deptID) {
        //记录人数
        num++;
    }
    ifs.close();

    return num;
}

void WorkerManager::initEmp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int ID;
    string name;
    int deptID;

    int index = 0;

    while (ifs >> ID && ifs >> name && ifs >> deptID) {
        Worker *worker = NULL;
        //根据不同的部门ID创建不同的对象
        if (deptID == 0) {
            //普通员工
            worker = new Employee(ID, name, deptID);
        } else if (deptID == 1) {
            //经理
            worker = new Manager(ID, name, deptID);
        } else {
            //老板
            worker = new Boss(ID, name, deptID);
        }
        //存放在数组中
        this->m_EmpArray[index] = worker;
        index++;
    }
    //关闭文件
    ifs.close();
}

void WorkerManager::showEmp()
{
    if (this->m_IsFileEmpty) { cout << "暂时没有员工！" << endl; }
    else{
        for (int i = 0; i < this->m_EmpNum; ++i) {
            //利用多态调用接口
            this->m_EmpArray[i]->showInfo();
        }
    }

    system("read");
    system("clear");
}

int WorkerManager::isExist(int id)
{
    int index = -1;
    for (int i = 0; i < this->m_EmpNum; ++i) {
        if (this->m_EmpArray[i]->m_ID == id) {
            index = i;
            break;
        }
    }
    return index;
}

void WorkerManager::delEmp()
{
    if (this->m_IsFileEmpty) { cout << "暂时没有员工！" << endl; }
    else {
        //按照职工编号删除
        cout << "请输入想要删除职工的编号：";
        int id = 0;
        cin >> id;

        int index = this->isExist(id);

        if (index != -1) {   //说明职工存在，并且要删除掉index位置上的职工
            //数据前移
            for (int i = index; i < this->m_EmpNum; i++) {
                this->m_EmpArray[i] = this->m_EmpArray[i + 1];
            }
            //更新数组中记录的人员个数
            this->m_EmpNum--;
            //更新同步到文件中
            this->save();

            cout << "职工id " << id << " 删除成功！" << endl;
        } else { cout << "删除失败，未找到该员工！" << endl; }
    }

    system("read");
    system("clear");
}

void WorkerManager::modEmp()
{
    if (this->m_IsFileEmpty) { cout << "暂时没有员工！" << endl; }
    else {
        cout << "请输入想要修改的职工编号：";
        int id;
        cin >> id;

        int ret = this->isExist(id);
        if (ret != -1) {
            //查找到职工的编号
            delete this->m_EmpArray[ret];

            int newID = 0;
            string newName;
            int newDeptSelect = 0;

            cout << "查找到职工编号为 " << id << " 的员工，请输入新的职工编号：";
            cin >> newID;

            cout << "请输入姓名：";
            cin >> newName;

            cout << "请选择该职工岗位（数字）:\n\t1、普通职工\n\t2、经理\n\t3、老板" << endl;
            cin >> newDeptSelect;

            Worker *worker = NULL;
            switch (newDeptSelect) {
                case 1: //普通员工
                    worker = new Employee(newID, newName, 1);
                    break;
                case 2: //经理
                    worker = new Employee(newID, newName, 2);
                    break;
                case 3: //老板
                    worker = new Boss(newID, newName, 3);
                    break;
                default:
                    break;
            }

            //更改数据到数组中
            this->m_EmpArray[ret] = worker;

            cout << "新员工 " << this->m_EmpArray[ret]->m_Name << " 修改成功！" << endl;

            //保存到文件中
            this->save();
        } else { cout << "删除失败，未找到该员工！" << endl; }
    }
    system("read");
    system("clear");
}

void WorkerManager::findEmp()
{
    if (this->m_IsFileEmpty) { cout << "暂时没有员工！" << endl; }
    else {
        cout << "请输入查找的方式：\n"
             << "1. 按职工编号查找\n"
             << "2. 站姓名查找" << endl;

        int select;
        cin >> select;

        if (select == 1) {          //按职工编号查找
            int id;
            cout << "请输入想要查找的职工编号：" << endl;
            cin >> id;

            int ret = this->isExist(id);
            if (ret != -1) {
                system("clear");
                cout << "该职工信息如下：" << endl;
                this->m_EmpArray[ret]->showInfo();
            } else { cout << "查无此人！没有编号为 " << id << " 的员工！" << endl; }
        } else if (select == 2) {   //按照姓名查找
            string name;
            cout << "请输入想要查找的姓名：";
            cin >> name;

            bool isFound = false;      //找到的标志
            for (int i = 0; i < m_EmpNum; i++) {
                if (this->m_EmpArray[i]->m_Name == name) {
                    if (!isFound) {
                        isFound = true;
                        system("clear");
                    }
                    this->m_EmpArray[i]->showInfo();
                }
            }
            if (!isFound) {
                cout << "职工 " << name << " 查无此人！" << endl;
            }
        } else { cout << "输入选项有误！" << endl; }
    }
    system("read");
    system("clear");
}

void WorkerManager::sortEmp()
{
    if (this->m_IsFileEmpty) {
        cout << "暂时没有员工！" << endl;
        system("read");
        system("clear");
    } else {
        cout << "请选择排序方式：\n"
             << "1. 按照职工编号进行升序\n"
             << "2. 按照职工编号进行降序" << endl;

        int select = 0;
        cin >> select;

        for (int i = 0; i < m_EmpNum; i++) {
            int minOrMaxIndex = i;
            for (int j = i + 1; j < m_EmpNum; j++) {
                if (select == 1) {          //升序
                    if (this->m_EmpArray[minOrMaxIndex]->m_ID > this->m_EmpArray[j]->m_ID) { minOrMaxIndex = j; }
                } else if (select == 2) {   //降序
                    if (this->m_EmpArray[minOrMaxIndex]->m_ID < this->m_EmpArray[j]->m_ID) { minOrMaxIndex = j; }
                }
            }
            if (i != minOrMaxIndex) {
                Worker *temp = this->m_EmpArray[i];
                this->m_EmpArray[i] = this->m_EmpArray[minOrMaxIndex];
                this->m_EmpArray[minOrMaxIndex] = temp;
            }
        }
        this->save();
        cout << "排序成功！新的结果为：" << endl;
        this->showEmp();
    }
}

void WorkerManager::clearFile()
{
    cout << "是否确认清空？确认操作后所有数据将会丢失！\n"
         << "1. 确认\n"
         << "2. 取消" << endl;

    short selection = 0;
    cin >> selection;

    if (selection == 1) {
        //打开模式：ios::trunc   如果存在，删除文件并重新创建
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();

        //维护指针
        if (this->m_EmpArray != NULL) {
            for (int i = 0; i < this->m_EmpNum; ++i) {
                if (this->m_EmpArray[i] != NULL) { delete this->m_EmpArray[i]; }
            }
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_EmpNum = 0;
            this->m_IsFileEmpty = true;
        }
        cout << "职工数据清除成功！" << endl;
        system("read");
    }
    system("clear");
}

WorkerManager::~WorkerManager()
{
    if (this->m_EmpArray != NULL)
    {
        delete[]this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}