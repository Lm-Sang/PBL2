#ifndef TestQuestionSelection_h
#define TestQuestionSelection_h
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Linklist.h"
using namespace std;

class TestQuestionSelection
{
private:
    string id;
    string testId;
    string chapterId;
    int numberOfQuestions;

public:
    TestQuestionSelection(/* args */);
    ~TestQuestionSelection();
    bool setTestId(string testId);
    bool setChapterId(string chapterId);
    bool setNumberOfQuestions(int numberOfQuestions);
    bool setId(int id);
    bool setId(string id);
    string getTestId();
    string getChapterId();
    int getNumberOfQuestions();
    string getId();
};

class TestQuestionSelectionManager
{
private:
    LinkList<TestQuestionSelection> manager;

public:
    static int count;
    TestQuestionSelectionManager(/* args */);
    ~TestQuestionSelectionManager();
    bool addTestQuestionSelection(string testId, string chapterId, int numberOfQuestions);
    bool deleteTestQuestionSelection(string id);
    bool updateTestQuestionSelection(string id, string testId, string chapterId, int numberOfQuestions);
    TestQuestionSelection getTestQuestionSelectionAt(int index);
    TestQuestionSelection getTestQuestionSelection(string id);
    // TestQuestionSelection *getAllTestQuestionSelection();
    TestQuestionSelection *getTestQuestionSelectionByTestId(string testId, int &count);
    int getCount();
    void saveToFile();
    void loadFromFile();
};

TestQuestionSelection::TestQuestionSelection(/* args */)
{
}
TestQuestionSelection::~TestQuestionSelection()
{
}
bool TestQuestionSelection::setTestId(string testId)
{
    this->testId = testId;
    return true;
}
bool TestQuestionSelection::setChapterId(string chapterId)
{
    if (chapterId.length() == 0)
    {
        return false;
    }
    this->chapterId = chapterId;
    return true;
}
bool TestQuestionSelection::setNumberOfQuestions(int numberOfQuestions)
{
    if (numberOfQuestions < 0)
    {
        return false;
    }
    this->numberOfQuestions = numberOfQuestions;
    return true;
}
bool TestQuestionSelection::setId(int id)
{
    stringstream tmp;
    tmp << "TQS" << setw(3) << setfill('0') << id;
    this->id = tmp.str();
    return true;
}
bool TestQuestionSelection::setId(string id)
{
    this->id = id;
    return true;
}
string TestQuestionSelection::getTestId()
{
    return testId;
}
string TestQuestionSelection::getChapterId()
{
    return chapterId;
}
int TestQuestionSelection::getNumberOfQuestions()
{
    return numberOfQuestions;
}
string TestQuestionSelection::getId()
{
    return id;
}

void TestQuestionSelectionManager::loadFromFile()
{
    ifstream file("TestQuestionSelection.txt");
    if (!file.is_open()) // Kiểm tra nếu file không mở được
    {
        cout << "File not found or could not be opened!" << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty()) // Bỏ qua các dòng trống
            continue;

        stringstream ss(line);
        string id, testId, chapterId, numberOfQuestions;

        if (getline(ss, id, '|') &&
            getline(ss, testId, '|') &&
            getline(ss, chapterId, '|') &&
            getline(ss, numberOfQuestions))
        {
            // Kiểm tra và thêm TestQuestionSelection
            addTestQuestionSelection(testId, chapterId, stoi(numberOfQuestions));
        }
    }
    file.close();
}

void TestQuestionSelectionManager::saveToFile()
{
    ofstream file("TestQuestionSelection.txt");
    if (!file.is_open()) // Kiểm tra file có mở được không
    {
        cout << "Unable to open file for saving." << endl;
        return;
    }

    for (int i = 0; i < count; i++)
    {
        if (manager[i].getId().empty())
            continue;
        file << manager[i].getId() << "|"
             << manager[i].getTestId() << "|"
             << manager[i].getChapterId() << "|"
             << manager[i].getNumberOfQuestions() << endl;
    }
    file.close();
}

int TestQuestionSelectionManager::count = 0;
TestQuestionSelection TestQuestionSelectionManager::getTestQuestionSelectionAt(int index){
    return manager[index];
}
TestQuestionSelectionManager::TestQuestionSelectionManager(/* args */)
{
    loadFromFile();
}
TestQuestionSelectionManager::~TestQuestionSelectionManager()
{
    saveToFile();
}
bool TestQuestionSelectionManager::addTestQuestionSelection(string testId, string chapterId, int numberOfQuestions)
{
    if (count >= 1000)
    {
        return false;
    }
    if (testId.empty() || chapterId.empty() || numberOfQuestions <= 0)
    {
        cout << "Invalid input data. Skipping addition." << endl;
        return false;
    }
    TestQuestionSelection testQuestionSelection;
    testQuestionSelection.setTestId(testId);
    testQuestionSelection.setChapterId(chapterId);
    testQuestionSelection.setNumberOfQuestions(numberOfQuestions);
    testQuestionSelection.setId(count);
    manager.add(testQuestionSelection);
    count++;
    return true;
}
bool TestQuestionSelectionManager::deleteTestQuestionSelection(string id)
{
    for (int i = 0; i < count; i++)
    {
        if (manager[i].getId() == id)
        {
            manager[i].setId("");
            manager[i].setTestId("");
            manager[i].setChapterId("");
            manager[i].setNumberOfQuestions(0);
            saveToFile(); // Lưu lại dữ liệu sau khi xóa
            return true;
        }
    }
    return false;
}

bool TestQuestionSelectionManager::updateTestQuestionSelection(string id, string testId, string chapterId, int numberOfQuestions)
{
    for (int i = 0; i < count; i++)
    {
        if (manager[i].getId() == id)
        {
            manager[i].setTestId(testId);
            manager[i].setChapterId(chapterId);
            manager[i].setNumberOfQuestions(numberOfQuestions);
            saveToFile(); // Lưu lại dữ liệu sau khi cập nhật
            return true;
        }
    }
    return false;
}
TestQuestionSelection TestQuestionSelectionManager::getTestQuestionSelection(string id)
{
    for (int i = 0; i < count; i++)
    {
        if (manager[i].getId() == id)
        {
            return manager[i];
        }
    }
    return TestQuestionSelection();
}
// TestQuestionSelection *TestQuestionSelectionManager::getAllTestQuestionSelection()
// {
//     return manager;
// }
int TestQuestionSelectionManager::getCount()
{
    return count;
}
TestQuestionSelection *TestQuestionSelectionManager::getTestQuestionSelectionByTestId(string testId, int &count)
{
    TestQuestionSelection *result = new TestQuestionSelection[1000];
    count = 0;
    for (int i = 0; i < TestQuestionSelectionManager::count; i++)
    {
        if (manager[i].getTestId() == testId)
        {
            result[count] = manager[i];
            count++;
        }
    }
    return result;
}


#endif