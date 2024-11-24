#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include "Linklist.h" // Sử dụng danh sách liên kết

using namespace std;

// Lớp Subject
class Subject {
private:
    string id;    // Mã định danh môn học
    string name;  // Tên môn học
    string userId;

public:
    Subject(const string &id, const string &userId, const string &name = ""); // Constructor
    Subject();                               // Constructor mặc định
    ~Subject();                              // Destructor

    const string &getId() const;  // Lấy mã định danh
    const string &getName() const; // Lấy tên môn học
    const string &getUserId() const;

    void setId(int id);                 // Đặt mã định danh từ số
    bool setId(const string &id);       // Đặt mã định danh từ chuỗi
    void setName(const string &name);   // Đặt tên môn học

    void formattedId(int id);           // Định dạng mã định danh
};

// Lớp SubjectManager
class SubjectManager {
private:
    LinkList<Subject> subjects; // Danh sách liên kết chứa các môn học
    static int subjectCount;    // Đếm số môn học hiện tại
    void loadFromFile();        // Đọc dữ liệu từ tệp
    void saveToFile() const;    // Ghi dữ liệu ra tệp

public:
    SubjectManager();  // Constructor
    ~SubjectManager(); // Destructor

    int getSubjectCount() const;                // Lấy số lượng môn học
    bool addSubject(const string &name, CurrentUser user);        // Thêm môn học mới
    const LinkList<Subject> &getAllSubjects() const; // Trả về danh sách môn học
    Subject getSubjectAt(int index);      // Lấy môn học theo ID
    bool updateSubject(const string &id, const string &newName); // Cập nhật tên
    bool deleteSubject(const string &id);       // Xóa môn học
    string getSubjectIdByName(const string &name); // Lấy ID theo tên
};

Subject::Subject(const string &id, const string &userId, const string &name) :  id(id), userId(userId), name(name) {
} 

Subject::Subject() {}

Subject::~Subject() {}

const string &Subject::getId() const {
    return id;
}

const string &Subject::getName() const {
    return name;
}

const string &Subject::getUserId() const {
    return userId;
}

void Subject::setName(const string &newName) {
    name = newName;
}

void Subject::setId(int id) {
    formattedId(id);
}

bool Subject::setId(const string &id) {
    if (id.length() != 6 || id.substr(0, 3) != "SUB") {
        return false;
    }
    for (int i = 3; i < 6; ++i) {
        if (!isdigit(id[i])) {
            return false;
        }
    }
    this->id = id;
    return true;
}

void Subject::formattedId(int id) {
    stringstream tmp;
    tmp << "SUB" << setw(3) << setfill('0') << id;
    this->id = tmp.str();
}

// ----------------- SubjectManager Implementation -----------------

int SubjectManager::subjectCount = 0;

int SubjectManager::getSubjectCount() const {
    return subjectCount;
} 

SubjectManager::SubjectManager() {
    loadFromFile();
}

SubjectManager::~SubjectManager() {
    saveToFile();
}

void SubjectManager::loadFromFile() {
    ifstream inputFile("subject.txt");
    if (!inputFile) {
        return;
    }
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string id, name, userId;
        getline(ss, id, '|');
        getline(ss, userId, '|');
        getline(ss, name);
        Subject tmp(id, userId, name);
        subjects.add(tmp);
        subjectCount++;
    }
}

void SubjectManager::saveToFile() const {
    ofstream outputFile("subjects.txt");
    if (!outputFile) {
        return;
    }
    for (int i = 0; i < subjects.getSize(); ++i) {
        outputFile << subjects[i].getId() << "|" << subjects[i].getUserId() << "|" << subjects[i].getName() << endl;
    }
}

bool SubjectManager::addSubject(const string &name, CurrentUser user) {
    if (name.empty() || name.length() < 3) {
        return false;
    }
    for (int i = 0; i < subjects.getSize(); ++i) {
        if (subjects.get(i).getName() == name) {
            return false;
        }
    }

    stringstream tmp;
    tmp << "SUB" << setw(3) << setfill('0') << subjectCount;
    string id = tmp.str();
    Subject newSubject(id, user.getId(), name);
    subjects.add(newSubject);
    subjectCount++;
    saveToFile();
    return true;
}

const LinkList<Subject> &SubjectManager::getAllSubjects() const {
    return subjects;
}

Subject SubjectManager::getSubjectAt(int index) {
    return subjects[index];
}

bool SubjectManager::updateSubject(const string &id, const string &newName) {
    for (int i = 0; i < subjects.getSize(); ++i) {
        Subject subject = subjects.get(i);
        if (subject.getId() == id) {
            subject.setName(newName);
            subjects.update(i, subject);
            saveToFile();
            return true;
        }
    }
    return false;
}

bool SubjectManager::deleteSubject(const string &id) {
    for (int i = 0; i < subjects.getSize(); ++i) {
        if (subjects.get(i).getId() == id) {
            subjects.remove(i);
            subjectCount--;
            saveToFile();
            return true;
        }
    }
    return false;
}

string SubjectManager::getSubjectIdByName(const string &name) {
    for (int i = 0; i < subjects.getSize(); ++i) {
        if (subjects.get(i).getName() == name) {
            return subjects.get(i).getId();
        }
    }
    return "";
}

#endif // SUBJECT_H