#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "CurrentUser.h"
#include "Linklist.h"
using namespace std;

class student
{
private:
    string id;
    string name;
    string username;
    string password;

public:
    student(string id = "", string name = "", string username = "", string password = "");
    ~student();

    string getId() const;
    string getUsername() const;
    string getPassword() const;
    string getName() const;
    bool setName(string name);
    bool setPassword(string password);
    void setId(int id);
    void formattedId(int id);
};

class studentManager
{
private:
    static int idCounter;

    bool isValidName(const string &name) const;
    bool isUsernameUnique(const string &username) const;
    bool isValidPassword(const string &password) const;
    LinkList <student> studentList;
    void saveToFile() const;

public:
    studentManager();
    ~studentManager();
    student getstudentAt(int index);
    int getListSize();
    bool registerStudent(const string &name, const string &username, const string &password);
    bool login(const string &username, const string &password, CurrentUser &user);
    bool update(const string id, const string &newPassword, const string &newName);
    void loadFromFile();
};

int studentManager::idCounter = 0;

student::student(string id, string name, string username, string password)
    : id(id), name(name), username(username), password(password) {}

student::~student() {}

string student::getId() const { return id; }
string student::getUsername() const { return username; }
string student::getPassword() const { return password; }
string student::getName() const { return name; }
void student::setId(int id) { formattedId(id); }
void student::formattedId(int id)
{
    stringstream tmp;
    tmp << "STD" << setw(3) << setfill('0') << id;
    this->id = tmp.str();
}
bool student::setName(string name)
{
    this->name = name;
    return true;
}

bool student::setPassword(string password)
{
    this->password = password;
    return true;
}



student studentManager::getstudentAt(int index){
    return studentList[index];
}

studentManager::~studentManager(){
    
}
int studentManager::getListSize(){
    return studentList.getSize();
}
studentManager::studentManager()
{
    loadFromFile();
}
bool studentManager::isUsernameUnique(const string &username) const
{
    for (int i = 0; i < idCounter; i++)
    {
        if (studentList[i].getUsername() == username)
        {
            return false;
        }
    }
    return true;
}

bool studentManager::isValidPassword(const string &password) const
{
    return password.length() > 6;
}

bool studentManager::isValidName(const string &name) const
{
    for (char c : name)
    {
        if (!isalpha(c) && c != ' ')
        {
            return false;
        }
    }
    if (name.length() < 3)
    {
        return false;
    }
    return true;
}

bool studentManager::registerStudent(const string &name, const string &username, const string &password)
{
    if (idCounter >= 100)
    {
        return false;
    }

    if (!isValidName(name) || !isUsernameUnique(username) || !isValidPassword(password))
    {
        return false;
    }
    stringstream tmp;
    tmp << "STD" << setw(3) << setfill('0') << idCounter;
    string id = tmp.str();
    student newstudent(id, name, username, password);
    studentList.add(newstudent);
    idCounter++;

    saveToFile();
    return true;
}

bool studentManager::login(const string &username, const string &password, CurrentUser &user)
{
    for (int i = 0; i < idCounter; i++)
    {
        if (studentList[i].getUsername() == username && studentList[i].getPassword() == password)
        {
            user = CurrentUser(studentList[i].getId(), studentList[i].getUsername(), studentList[i].getPassword(), studentList[i].getName(), "Student");
            return true;
        }
    }
    return false;
}

void studentManager::saveToFile() const
{
    ofstream outFile("student.txt");
    if (!outFile.is_open())
    {
        return;
    }

    for (int i = 0; i < idCounter; i++)
    {
        outFile << studentList[i].getId() << ","
                << studentList[i].getName() << ","
                << studentList[i].getUsername() << ","
                << studentList[i].getPassword() << endl;
    }

    outFile.close();
}

void studentManager::loadFromFile()
{
    ifstream inFile("student.txt");
    if (!inFile.is_open())
    {
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string id, name, username, password;
        getline (ss, id, ',');
        getline(ss, name, ',');
        getline(ss, username, ',');
        getline(ss, password);

        student newstudent(id, name, username, password);
        studentList.add(newstudent);
        idCounter++;
    }

    inFile.close();
}

bool studentManager::update(const string id, const string &newPassword, const string &newName)
{
    for (int i = 0; i < studentList.getSize(); i++)
        if (studentList[i].getId() == id )
        {
            studentList[i].setName(newName);
            studentList[i].setPassword(newPassword);
            return true;
        }   
    return false;
}

#endif // STUDENT_H