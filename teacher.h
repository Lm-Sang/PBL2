#ifndef TEACHER_H
#define TEACHER_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "CurrentUser.h"
#include "Linklist.h"
using namespace std;

class teacher
{
private:
    string id;
    string name;
    string username;
    string password;

public:
    teacher(string id = "", string name = "", string username = "", string password = "");
    ~teacher();

    string getId() const;
    string getUsername() const;
    string getPassword() const;
    string getName() const;
    bool setName(string name);
    bool setPassword(string password);
    void setId(int id);
    void formattedId(int id);
};

class teacherManager
{
private:
    bool isValidName(const string &name) const;
    bool isUsernameUnique(const string &username) const;
    bool isValidPassword(const string &password) const;
    LinkList<teacher> teacherList;

public:
    static int idCounter;
    teacherManager();
    ~teacherManager();
    teacher getTeacherAt(int index);
    int getListSize();
    bool registerTeacher(const string &name, const string &username, const string &password);
    bool login(const string &username, const string &password, CurrentUser &user);
    bool update(const string id, const string newPassword, const string newName);
    void saveToFile() const;
    void loadFromFile();
};

int teacherManager::idCounter = 0;

teacher::teacher(string id, string name, string username, string password)
    : id(id), name(name), username(username), password(password) {}

teacher::~teacher() {}

string teacher::getId() const { return id; }
string teacher::getUsername() const { return username; }
string teacher::getPassword() const { return password; }
string teacher::getName() const { return name; }
void teacher::setId(int id) { formattedId(id); }

void teacher::formattedId(int id)
{
    stringstream tmp;
    tmp << "TEA" << setw(3) << setfill('0') << id;
    this->id = tmp.str();
}
bool teacher::setName(string name)
{
    this->name = name;
    return true;
}

bool teacher::setPassword(string password)
{
    this->password = password;
    return true;
}

teacherManager::~teacherManager()
{
}

teacher teacherManager::getTeacherAt(int index)
{
    return teacherList[index];
}
int teacherManager::getListSize()
{
    return teacherList.getSize();
}
teacherManager::teacherManager()
{
    loadFromFile();
}
bool teacherManager::isUsernameUnique(const string &username) const
{
    for (int i = 0; i < idCounter; i++)
    {
        if (teacherList[i].getUsername() == username)
        {
            return false;
        }
    }
    return true;
}

bool teacherManager::isValidPassword(const string &password) const
{
    return password.length() > 6;
}

bool teacherManager::isValidName(const string &name) const
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

bool teacherManager::registerTeacher(const string &name, const string &username, const string &password)
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
    tmp << "TEA" << setw(3) << setfill('0') << idCounter;
    string id = tmp.str();
    teacher newTeacher(id, name, username, password);
    teacherList.add(newTeacher);
    idCounter++;

    saveToFile();
    return true;
}

bool teacherManager::login(const string &username, const string &password, CurrentUser &user)
{
    for (int i = 0; i < idCounter; i++)
    {
        if (teacherList[i].getUsername() == username && teacherList[i].getPassword() == password)
        {
            user = CurrentUser(teacherList[i].getId(), teacherList[i].getUsername(), teacherList[i].getPassword(), teacherList[i].getName(), "Teacher");
            return true;
        }
    }
    return false;
}

void teacherManager::saveToFile() const
{
    try
    {
        ofstream outFile("teacher.txt");

        if (!outFile.is_open())
        {
            cout << "Error opening file for writing!" << endl;
            return; // Dừng lại nếu tệp không mở được
        }


        for (int i = 0; i < idCounter; i++)
        {
            outFile << teacherList[i].getId() << ","
                    << teacherList[i].getName() << ","
                    << teacherList[i].getUsername() << ","
                    << teacherList[i].getPassword() << endl;
        }


        outFile.close();
        if (outFile.fail()) // Kiểm tra lỗi sau khi đóng tệp
        {
            cout << "Error closing the file!" << endl;
        }
    }
    catch (exception e)
    {
        cout << e.what() << endl;
    }
}

void teacherManager::loadFromFile()
{
    ifstream inFile("teacher.txt");
    if (!inFile.is_open())
    {
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string id, name, username, password;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, username, ',');
        getline(ss, password);

        teacher newTeacher(id, name, username, password);
        teacherList.add(newTeacher);
        idCounter++;
    }

    inFile.close();
}

bool teacherManager::update(const string id, const string newPassword, const string newName)
{
    for (int i = 0; i < teacherList.getSize(); i++)
    {
        if (teacherList[i].getId() == id)
        {
            teacherList[i].setName(newName);
            teacherList[i].setPassword(newPassword);
            saveToFile();
            return true;
        }
    }
    return false;
}

#endif // TEACHER_H