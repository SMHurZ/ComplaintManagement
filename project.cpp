#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

class User //Virtual Class -- Principles followed: Interface & Liskov's
{
    public:
    string userName;
    string password;
    virtual void display(){}
    virtual void loginAuthentication(string userName, string password){}

};

class Department
{
     private:
     string deptName;
     Complaint * complaint;
     Manager * manager;
     Employee * employee;
    
     public:
        
};

class Teacher : public User
{
    private:
    Complaint * complaint;

    public:
};


class Manager : public User
{
    private:
    Department * department;

    public:
    
};

class Employee : public User
{
    public:
        
};

class Director : public User
{
    public:

};

class Administrator : public User
{
    
};

class Complaint
{
    private:
    int complaintID;
    string desc;
    Department * department;
    Teacher * teacher;
    Employee * assignedEmployee;

    public:
    
};


class SystemHandler
{
    private:
       vector<Department> department; 
    public:
    
    void accessData(DataHandler& dataHandler){
    };
    void display(){};
};

class DataHandler 
{
    public:
    void loadData()
    {
        Department * tempD;
        string temp;
        ofstream fout;
        fout.open("dept_names.txt");
        while(fout)
        {
            getline(cin,temp);
            if (temp=="-1")
                break;
            cout<<temp;
        }
    };
    void storeData(){};
};


void main()
{
    DataHandler dataHandler;
    SystemHandler systemHandler;

    dataHandler.loadData();
    systemHandler.accessData(dataHandler);
 
}
