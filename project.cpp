#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class User {
public:
    string userName;
    string password;
    virtual void display() {}
    virtual void loginAuthentication(string userName, string password) {}
};

class Department {
private:
    string deptName;

public:
    void setValue(string deptName) {
        this->deptName = deptName;
    }

    void getValue() {
        cout << deptName;
    }
};

class DataHandler {
protected:
    vector<Department> department;

public:
    virtual void loadData() {
        // Base class loadData() implementation
        // Here you can put a generic behavior for loading data if needed
    }

    vector<Department> getDepartments() {
        return department;
    }

    virtual void storeData() {}
};

class DepartmentHandler : public DataHandler {
public:
    void loadData() override {
        Department tempD;
        string temp;
        ifstream fin;
        fin.open("dept_names.txt");
        while (getline(fin, temp)) {
            if (temp == "-1")
                break;
            tempD.setValue(temp);
            department.push_back(tempD);
        }
    }
};

class SystemHandler {
private:
    vector<Department> department;
    Department D;

public:
    void accessData(DataHandler& dataHandler) {
        dataHandler.loadData(); // Load data using polymorphism
        department = dataHandler.getDepartments();
        if (!department.empty()) {
            D = department.front();
            D.getValue();
        }
    }

    void display() {}
};

int main() {
    DepartmentHandler departmentHandler; // Use DepartmentHandler
    SystemHandler systemHandler;

    systemHandler.accessData(departmentHandler); // Pass DepartmentHandler object
    return 0;
}