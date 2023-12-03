#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//Classes
class User;
class Admin;
class SystemHandler;
class Director;
class Teacher;
class Manager;
class Employee;
class Department;
class Complaint;
class DataHandler;

class User //Parent Class for people, follows Interface & Liskov's Principles
{
protected:
    string userName;
    string password;
public:
    User(string userName, string password) {this->userName=userName; this->password=password;}
    virtual void display() {}
    virtual void loginAuthentication(string userName, string password) {}
};

class Admin : public User
{
private:
public:
    Admin(string userName, string password) : User(userName, password) {}
};

class Teacher : public User 
{
private:
    Complaint * complaints;
public:
    Teacher(string userName, string password) : User(userName, password) {}
    
    void FileComplaint()
    {
        int id, status; string desc, deptName;  
    }
};

class Manager : public User 
{
private:
public:
    Manager(string userName, string password) : User(userName, password) {}
};

class Employee : public User
{
private:
public:
    Employee(string userName, string password) : User(userName, password) {}
};


class Complaint {
private:
    int id; 
    string desc;
    int status;
    string TeacherName;
    string deptName; 

public:
    Complaint(const string& description, const string& department, int newStatus, const string& teacher, const string& departmentName)
        : desc(description), status(newStatus), TeacherName(teacher), deptName(departmentName) {}

    string getDesc() const {
        return desc;
    }

    string getDeptName() const {
        return deptName;
    }

    int getStatus() const {
        return status;
    }

    string getTeacherName() const {
        return TeacherName;
    }
};



class Department {
private:
    string deptName;

public:
    void setValue(string deptName) {
        this->deptName = deptName;
    }
    void getValue() const {
        cout << deptName;
    }
};

class DataHandler 
{
protected:
    vector<Department> department;
    vector<Complaint> complaints;

public:
    virtual void loadData() {}

    virtual void storeData() {}

    vector<Department> getDepartments() {
        return department;
    }
    vector<Complaint> getComplaints(){
        return complaints;
    }

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
class ComplaintHandler : public DataHandler {
public:
    void loadData() override {
        ifstream fin;
        fin.open("complaints.txt");
        if (!fin.is_open()) {
            cout << "Error opening complaints.txt" << endl;
            return;
        }

        string line;
        while (getline(fin, line)) {
            string desc, deptName, teacher;
            int status;

            desc = line; // First line is the description
            getline(fin, deptName); // Second line is the department name
            getline(fin, line); // Third line is the status
            status = stoi(line); // Convert status to int
            getline(fin, teacher); // Fourth line is the teacher name

            Complaint complaint(desc, deptName, status, teacher, deptName);
            complaints.push_back(complaint);
        }
        fin.close();
    }

    void storeData() override {
        ofstream fout("complaints.txt");
        if (!fout.is_open()) {
            cout << "Error opening complaints.txt for writing" << endl;
            return;
        }

        for (const auto& complaint : complaints) {
            fout << complaint.getDesc() << "\n"
                 << complaint.getDeptName() << "\n"
                 << complaint.getStatus() << "\n"
                 << complaint.getTeacherName() << "\n";
        }
        fout.close();
    }
};




class TeacherHandler : public DataHandler {
public:
    void loadData() override {
    }
};

class ManagerHandler : public DataHandler {
public:
    void loadData() override {
    }
};


class SystemHandler {
private:
    DataHandler* dataHandler; 

public:
    SystemHandler() : dataHandler(nullptr) {}

    void setDataHandler(DataHandler* handler) {
        dataHandler = handler;
    }

    void accessData() {
        if (dataHandler != nullptr) {
            dataHandler->loadData();
        }
    }

    void displayDepartments() {
    if (dataHandler != nullptr) {
        vector<Department> departments = dataHandler->getDepartments();
        for (const auto& department : departments) {
            department.getValue(); // Display department name
        }
        cout<<endl;
    }
}

void displayComplaints() {
    if (dataHandler != nullptr) {
        vector<Complaint> complaints = dataHandler->getComplaints();
        for (const auto& complaint : complaints) {
            cout << "Description: " << complaint.getDesc() << endl;
            cout << "Department: " << complaint.getDeptName() << endl;
            cout << "Status: " << complaint.getStatus() << endl;
            cout << "Teacher: " << complaint.getTeacherName() << endl;
            cout << "----------------------" << endl;
        }
    }
}

void getComplaintsByDept(string dept)
{
    if (dataHandler != nullptr) {
    vector<Complaint> complaints = dataHandler->getComplaints();
    cout<<"Complaints for "<<dept<<" are: "<<endl;
        for (const auto& complaint : complaints) {
            if(complaint.getDeptName()==dept)
            {
                cout << "Description: " << complaint.getDesc() << endl;
                cout << "Status: " << complaint.getStatus() << endl;
                cout << "Teacher: " << complaint.getTeacherName() << endl;
                cout << "----------------------" << endl;
            }
        }
    }    
}

void getComplaintsByDate()
{

}

};

class Director : public User
{
private:
    SystemHandler * system;
public:
    Director(SystemHandler * systemHandler, string userName, string password) : User(userName, password) {system=systemHandler;}

    void complaintsByName(string name)
    {
        system->getComplaintsByDept(name);
    }
    
};


int main() {
    DepartmentHandler departmentHandler; 
    TeacherHandler teacherHandler; 
    ManagerHandler managerHandler; 
    ComplaintHandler complaintHandler;
    SystemHandler systemHandler;

    systemHandler.setDataHandler(&departmentHandler);
    systemHandler.accessData();
    //systemHandler.displayDepartments();

    systemHandler.setDataHandler(&complaintHandler);
    systemHandler.accessData();
    //systemHandler.displayComplaints();

    //director comes in
    systemHandler.setDataHandler(&complaintHandler);
    Director director(&systemHandler, "hello"  , "world");
    director.complaintsByName("IT");

    // Similar for other handlers...

    return 0;
}

