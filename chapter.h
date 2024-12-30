#ifndef CHAPTER_H
#define CHAPTER_H

#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "CurrentUser.h"
#include "Linklist.h" // Thêm tệp header cho LinkedList

using namespace std;

// Lớp Chapter
class Chapter
{
private:
    string id;
    string name;
    string subjectId;
    string userId;

public:
    Chapter(const string &id, const string &name, const string &userId, const string &subjectId);
    Chapter();
    ~Chapter();
    void formattedId(int id);
    const string &getId() const;
    const string &getName() const;
    const string &getSubjectId() const;
    const string &getUserId() const;
    void setName(const string &newName);
    string setId(int id);
    bool setId(const string &id);
};

// Lớp ChapterManager
class ChapterManager
{
private:
    LinkList<Chapter> chapters; // Sử dụng danh sách liên kết thay vì mảng tĩnh
    static int chapterCount;
    void loadFromFile();
    void saveToFile() const;

public:
    ChapterManager();
    ~ChapterManager();
    int getChapterCount() const;
    bool addChapter(const string &name, const string &subjectId, CurrentUser user);
    const LinkList<Chapter> &getAllChapters() const; // Trả về tham chiếu tới LinkedList
    Chapter getChapterAt(int index) const;
    LinkList<Chapter> getChapterSubject(const string &SubjectId);
    bool updateChapter(const string &id, const string &newName);
    bool deleteChapter(const string &id);
    string getChapterIdByName(const string &name);
};


Chapter::Chapter(const string &id, const string &name, const string &userId, const string &subjectId) 
                : id(id), name(name), userId(userId), subjectId(subjectId) {}


Chapter::Chapter() {}

const string &Chapter::getId() const {
    return id;
}

const string &Chapter::getSubjectId() const{
    return subjectId;
}

const string &Chapter::getName() const {
    return name;
}

const string &Chapter::getUserId() const {
    return userId;
}

void Chapter::setName(const string &newName) {
    name = newName;
}

string Chapter::setId(int id) {
    stringstream tmp;
    tmp << "CHA" << setw(3) << setfill('0') << id;
    return tmp.str();
}

void Chapter::formattedId(int id) {
    stringstream tmp;
    tmp << "CHA" << setw(3) << setfill('0') << id;
    this->id = tmp.str();
}

bool Chapter::setId(const string &id) {
    if (id.length() != 6) {
        return false;
    }
    if (id.substr(0, 3) != "CHA") {
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

Chapter::~Chapter() {}

// ----------------- ChapterManager Implementation -----------------

int ChapterManager::chapterCount = 0;

ChapterManager::ChapterManager() {
    loadFromFile();
}

ChapterManager::~ChapterManager() {
    saveToFile();
}

Chapter ChapterManager::getChapterAt(int index) const {
    return chapters[index];
}

void ChapterManager::loadFromFile() {
    ifstream inputFile("chapter.txt");
    if (!inputFile) {
        return;
    }
    string name;
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string id, name, userId, subjectId;
        getline(ss, id, '|');
        getline(ss, userId, '|');
        getline(ss, subjectId, '|');
        getline(ss, name);
        Chapter tmp = Chapter(id, name, userId, subjectId);
        chapters.add(tmp); // Thêm vào danh sách liên kết
        chapterCount++;
    }
}

void ChapterManager::saveToFile() const {
    ofstream outFile("chapter.txt");
    if (!outFile.is_open()) {
        return;
    }
    for (int i = 0; i < chapters.getSize(); ++i) {
        outFile << chapters[i].getId() << "|" << chapters[i].getUserId() << "|" << chapters[i].getSubjectId() << "|" << chapters[i].getName() << endl;
    }
    outFile.close();
}

bool ChapterManager::addChapter(const string &name, const string &subjectId, CurrentUser user) {
    if (name.empty() || name.length() < 3) {
        return false;
    }
    for (int i = 0; i < chapters.getSize(); ++i) {
        if (chapters[i].getName() == name) {
            return false;
        }
    }
    stringstream tmp;
    tmp << "CHA" << setw(3) << setfill('0') << chapterCount;    
    string id = tmp.str();
    Chapter newChapter(id, name, user.getId(), subjectId);
    chapters.add(newChapter); // Thêm chương mới vào danh sách
    chapterCount++;
    saveToFile();
    return true;
}

const LinkList<Chapter> &ChapterManager::getAllChapters() const {
    return chapters;
}


// Chapter *ChapterManager::getChapterById(const int id) {
//     for (int i = 0; i < chapters.getSize(); ++i) {
//         Chapter chapter = chapters[i]; // Lấy tham chiếu tới phần tử
//         if (stoi(chapter.getId().substr(3)) == id) { // Lấy ID từ "CHA###"
//             return &chapter;
//         }
//     }
//     return nullptr;
// }

// LinkList<Chapter> ChapterManager::getChapterSubject(const string &SubjectId){
//     LinkList<Chapter> chapterList;
//     for (int i = 0; i < chapters.getSize(); ++i) {
//         if (chapters[i].getSubjectId() == SubjectId) {
//             Chapter newChapter(chapters[i].getId(), chapters[i].getName(), chapters[i].getSubjectId());
//             chapterList.add(newChapter);
//         }
//     }
//     return chapterList;
// }

bool ChapterManager::updateChapter(const string &id, const string &newName) {
    for (int i = 0; i < chapters.getSize(); ++i) {
        Chapter chapter = chapters[i];
        if (chapter.getId() == id) {
            chapter.setName(newName);
            chapters.update(i, chapter); // Cập nhật dữ liệu
            saveToFile();
            return true;
        }
    }
    return false;
}

bool ChapterManager::deleteChapter(const string &id) {
    for (int i = 0; i < chapters.getSize(); ++i) {
        if (chapters[i].getId() == id) {
            chapters.remove(i); // Xóa phần tử tại vị trí i
            chapterCount--;
            saveToFile();
            return true;
        }
    }
    return false;
}

int ChapterManager::getChapterCount() const {
    return chapterCount;
}

string ChapterManager::getChapterIdByName(const string &name) {
    for (int i = 0; i < chapters.getSize(); ++i) {
        if (chapters[i].getName() == name) {
            return chapters[i].getId();
        }
    }
    return "";
}


#endif // CHAPTER_H
