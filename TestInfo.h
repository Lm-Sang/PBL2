#ifndef TEST_H
#define TEST_H
#include "Linklist.h"
#include <string>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
using namespace std;

class Test
{
private:

    static int currentId;
    string id;
    string teacherId;
    string title;
    int totalQuestion;
    string password;
    int duration;
    string startsAt;
    string endsAt;

public:
    enum Status { INCOMING, ONGOING, COMPLETED };   
    Status status;
    Test();

    Test(string teacherId, string title, int totalQuestion, string password,
         int duration, string startsAt, string endsAt, Status status = INCOMING);
    ~Test();

    string getId() const;
    string getTeacherId() const;
    string getTitle() const;
    int getTotalQuestion() const;
    string getPassword() const;
    int getDuration() const;
    string getStartsAt() const;
    string getEndsAt() const;
    Status getStatus() const;

    void setId(int id);
    void setTeacherId(string teacherId);
    void setTitle(string title);
    void setTotalQuestion(int totalQuestion);
    void setPassword(string password);
    void setDuration(int duration);
    void setStartsAt(string startsAt);
    void setEndsAt(string endsAt);
    void setStatus(Status status);
    void updateStatus();
};

class TestManager
{
private:
    LinkList<Test> TestList;
    int testCount = 0;

    bool validateTeacherId(const string &teacherId) const;
    bool validatePassword(const string &password) const;
    bool validateDuration(const int &duration) const;
    bool validateTitle(const string &title) const;
    bool validateTotalQuestion(const int& totalQuestion) const;
    bool validateStartsAt(const string &startsAt) const;
    bool validateEndsAt(const string &endsAt) const;

public:
    TestManager();
    void saveToFile() const;
    void loadFromFile();
    int getTestCount() const;

    Test getTestAt(int index);
    Test *getTestById(const string testId);
    LinkList <Test> getTestByTeacherId(const string &teacherId, int &count);
    bool deleteTestById(const string testId);
    bool checkPassword(const Test &test, const string &pass) const;
    bool createTest(const string &teacherId, const string &title, const int &totalQuestion, const string &password,
                    const int &duration, const string &startsAt, const string &endsAt);
    bool updateTest(const string &testId, const string &teacherId, const string &title, const int &totalQuestion,
                    const string &password, const int &duration, const string &startsAt, const string &endsAt);

    int countIncomingTest(string id);
    int countRunningTest(string id);
    int countCompletedTest(string id);
};

// Constructor
Test::Test()
    : id(""), teacherId(""), title(""), totalQuestion(0), password(""),
    duration(10), startsAt(""), endsAt(""), status(INCOMING)
{
}

Test::Test(string teacherId, string title, int totalQuestion, string password,
           int duration, string startsAt, string endsAt, Status status)
    : teacherId(teacherId), title(title), totalQuestion(totalQuestion), password(password),
    duration(duration), startsAt(startsAt), endsAt(endsAt), status(status)
{
    stringstream ss;
    ss << "TID" << setw(3) << setfill('0') << currentId++;
    id = ss.str();
}

// Cac ham GET
Test::~Test() {}
string Test::getId() const { return id; }
string Test::getTeacherId() const { return teacherId; }
string Test::getTitle() const { return title; }
int Test::getTotalQuestion() const { return totalQuestion; }
string Test::getPassword() const { return password; }
int Test::getDuration() const { return duration; }
string Test::getStartsAt() const { return startsAt; }
string Test::getEndsAt() const { return endsAt; }
Test::Status Test::getStatus() const { return status; }

// Cac ham SET
void Test::setId(int id) {     
    stringstream tmp;
    tmp << "TID" << setw(3) << setfill('0') << id;
    this->id = tmp.str(); 
}
void Test::setTeacherId(string teacherId) { this->teacherId = teacherId; }
void Test::setTitle(string title) { this->title = title; }
void Test::setTotalQuestion(int totalQuestion) { this->totalQuestion = totalQuestion; }
void Test::setPassword(string password) { this->password = password; }
void Test::setDuration(int duration) { this->duration = duration; }
void Test::setStartsAt(string startsAt) { this->startsAt = startsAt; }
void Test::setEndsAt(string endsAt) { this->endsAt = endsAt; }
void Test::setStatus(Status newStatus) { this->status = newStatus; }

int Test::currentId = 1;

TestManager::TestManager()
{
    loadFromFile();
}

// HAM LUU VAO TEP
void TestManager::saveToFile() const
{
    ofstream outFile("TestInfo.txt");
    if (!outFile.is_open())
    {
        return;
    }

    for (int i = 0; i < testCount; i++)
    {
        outFile << TestList[i].getId() << ","
                << TestList[i].getTeacherId() << ","
                << TestList[i].getTitle() << ","
                << TestList[i].getTotalQuestion() << ","
                << TestList[i].getPassword() << ","
                << TestList[i].getDuration() << ","
                << TestList[i].getStartsAt() << ","
                << TestList[i].getEndsAt() << ","
                << TestList[i].getStatus() << "\n";
    }
    outFile.close();
}

// HAM DOC TEP
void TestManager::loadFromFile()
{
    ifstream inFile("TestInfo.txt"); 
    if (!inFile.is_open())
    {
        return;
    }
    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string  teacherId, title, totalQuestionStr, password, durationStr, startsAt, endsAt;

        if (!getline(ss, teacherId, ',') ||
            !getline(ss, title, ',') ||
            !getline(ss, totalQuestionStr, ',') ||
            !getline(ss, password, ',') ||
            !getline(ss, durationStr, ',') ||
            !getline(ss, startsAt, ',') ||
            !getline(ss, endsAt, ','))
        {
            continue;
        }

        int duration = stoi(durationStr);
        int totalQuestion = stoi(totalQuestionStr);

        Test Test(teacherId, title, totalQuestion, password, duration, startsAt, endsAt);
        TestList.add(Test);
        TestList[testCount].setId(testCount);
        TestList[testCount].updateStatus();
        testCount++;
    }
    inFile.close();
}


// KTRA MAT KHAU
bool TestManager::validatePassword(const string &password) const
{
    if (password.length() <= 5)
        return false;
    for (char c : password)
    {
        if (!isalnum(c))
            return false;
    }
    return true;
}

// KTRA TEACHERID
bool TestManager::validateTeacherId(const string &teacherId) const
{
    if (teacherId.length() != 6) {
        return false;
    }
    if (teacherId.substr(0, 3) != "TEA") {
        return false;
    }
    for (int i = 3; i < 6; ++i) {
        if (!isdigit(teacherId[i])) {
            return false;
        }
    }
    return true;
}

// KTRA THOI GIAN LAM BAI
bool TestManager::validateDuration(const int &duration) const
{
    return duration >= 10;
}

// KTRA TIEU DE BAI THI
bool TestManager::validateTitle(const string &title) const
{
    if (title.empty())
    {
        return false;
    }
    for (char c : title)
    {
        if (!isalnum(c) && c != ' ')
        {
            return false;
        }
    }
    return true;
}

//KTRA SO LUONG CAU HOI
bool TestManager::validateTotalQuestion(const int &totalQuestion) const
{
    return totalQuestion > 0;
}

// KTRA THOI GIAN BAT DAU
bool TestManager::validateStartsAt(const string &startsAt) const
{

    if (startsAt.length() != 19)
    {
        return false;
    }

    if (startsAt[2] != ':' || startsAt[5] != ':' || startsAt[8] != ' ' || startsAt[11] != '/' || startsAt[14] != '/')
    {
        return false;
    }
    int hour = stoi(startsAt.substr(0, 2));
    int minute = stoi(startsAt.substr(3, 2));
    int second = stoi(startsAt.substr(6, 2));
    int day = stoi(startsAt.substr(9, 2));
    int month = stoi(startsAt.substr(12, 2));
    int year = stoi(startsAt.substr(15, 4));

    if (hour < 0 || hour > 23 ||
        minute < 0 || minute > 59 ||
        second < 0 || second > 59 ||
        day < 1 || day > 31 ||
        month < 1 || month > 12)
    {
        return false;
    }
    if ((month == 2 && day > 29) ||
        ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30))
    {
        return false;
    }
    if (month == 2 && day == 29)
    {
        if (!((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
        {
            return false;
        }
    }
    return true;
}

//KTRA THOI GIAN KET THUC
bool TestManager::validateEndsAt(const string &endsAt) const
{

    if (endsAt.length() != 19)
    {
        return false;
    }

    if (endsAt[2] != ':' || endsAt[5] != ':' || endsAt[8] != ' ' || endsAt[11] != '/' || endsAt[14] != '/')
    {
        return false;
    }

    int hour = stoi(endsAt.substr(0, 2));
    int minute = stoi(endsAt.substr(3, 2));
    int second = stoi(endsAt.substr(6, 2));
    int day = stoi(endsAt.substr(9, 2));
    int month = stoi(endsAt.substr(12, 2));
    int year = stoi(endsAt.substr(15, 4));

    if (hour < 0 || hour > 23 ||
        minute < 0 || minute > 59 ||
        second < 0 || second > 59 ||
        day < 1 || day > 31 ||
        month < 1 || month > 12)
    {
        return false;
    }
    if ((month == 2 && day > 29) ||
        ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30))
    {
        return false;
    }
    if (month == 2 && day == 29)
    {
        if (!((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
        {
            return false;
        }
    }
    return true;
}

// TAO BAI THI
bool TestManager::createTest(const string &teacherId, const string &title, const int &totalQuestion,
                             const string &password, const int &duration, const string &startsAt, const string &endsAt)
{
    if (testCount >= 1000)
    {
        return false;
    }
    if (!validateTeacherId(teacherId))
    {
        return false;
    }
    if (!validateTitle(title))
    {
        return false;
    }
    if (!validateTotalQuestion(totalQuestion))
    {
        return false;
    }
    if (!validatePassword(password))
    {
        return false;
    }
    if (!validateDuration(duration))
    {
        return false;
    }
    if (!validateStartsAt(startsAt))
    {
        return false;
    }
    if (!validateEndsAt(endsAt))
    {
        return false;
    }
    Test newTest(teacherId, title, totalQuestion, password, duration, startsAt, endsAt);
    TestList.add(newTest);
    TestList[testCount].setId(testCount);
    TestList[testCount].updateStatus();
    testCount++;
    saveToFile();
    return true;
}

// CAP NHAT BAI THI
bool TestManager::updateTest(const string &testId, const string &teacherId, const string &title, const int &totalQuestion,
                             const string &password, const int &duration, const string &startsAt, const string &endsAt)
{

    Test *testToUpdate = nullptr;
    for (int i = 0; i < testCount; ++i)
    {
        if (TestList[i].getId() == testId)
        {
            testToUpdate = &TestList[i];
            break;
        }
    }

    if (!testToUpdate)
    {
        return false;
    }

    if (!validateTeacherId(teacherId))
    {
        return false;
    }
    if (!validateTitle(title))
    {
        return false;
    }
    if (!validateTotalQuestion(totalQuestion)){
        return false;
    }
    if (!validatePassword(password))
    {
        return false;
    }
    if (!validateDuration(duration))
    {
        return false;
    }
    if (!validateStartsAt(startsAt))
    {
        return false;
    }
    if (!validateEndsAt(endsAt))
    {
        return false;
    }

    testToUpdate->setTeacherId(teacherId);
    testToUpdate->setTitle(title);
    testToUpdate->setTotalQuestion(totalQuestion);
    testToUpdate->setPassword(password);
    testToUpdate->setDuration(duration);
    testToUpdate->setStartsAt(startsAt);
    testToUpdate->setEndsAt(endsAt);
    testToUpdate->updateStatus();

    saveToFile();
    return true;
}

bool TestManager::checkPassword(const Test &test, const string &pass) const
{
    return test.getPassword() == pass;
}


Test TestManager::getTestAt(int index) {
    return TestList[index];
}

//TIM KIEM BAI KTRA
Test* TestManager::getTestById(const string testId) {
    for (int i = 0; i < testCount; ++i) {
        if (TestList[i].getId() == testId) {
            TestList[i].updateStatus();
            return &TestList[i];
        }
    }
    return nullptr;
}

//XOA BAI KIEM TRA
bool TestManager::deleteTestById(const string testId) {
    int index = -1;
    for (int i = 0; i < testCount; ++i) {
        if (TestList[i].getId() == testId) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        return false;
    }
    TestList[index] = Test();
    saveToFile();
    return true;
}



//CAP NHAT TRANG THAI
void Test::updateStatus() {
    tm startTime = {};
    istringstream ssStart(startsAt);
    ssStart >> get_time(&startTime, "%H:%M:%S %d/%m/%Y");

    tm endTime = {};
    istringstream ssEnd(endsAt);
    ssEnd >> get_time(&endTime, "%H:%M:%S %d/%m/%Y");


    time_t now = time(nullptr);
    tm currentTime = *localtime(&now);
    time_t currentTime_t = mktime(&currentTime);

    time_t startTime_t = mktime(&startTime);
    time_t endTime_t = mktime(&endTime);

    if (startTime_t > currentTime_t) {
        status = INCOMING;
    } else if (endTime_t < currentTime_t) {
        status = COMPLETED;
    } else if (startTime_t <= currentTime_t && endTime_t >= currentTime_t) {
        status = ONGOING;
    }

}

//DEM TEST CHUA LAM
int TestManager::countIncomingTest(string id) {
    int count = 0;
    for (int i = 0; i < testCount; ++i) {
        TestList[i].updateStatus();
        if (TestList[i].getStatus() == 0 && TestList[i].getTeacherId() == id) {
            ++count;
        }
    }
    return count;
}

//DEM TEST DANG LAM
int TestManager::countRunningTest(string id) {
    int count = 0;
    for (int i = 0; i < testCount; ++i) {
        TestList[i].updateStatus();
        if (TestList[i].getStatus() == 1 && TestList[i].getTeacherId() == id) {
            ++count;
        }
    }
    return count;
}

//DEM TEST DA LAM
int TestManager::countCompletedTest(string id) {
    int count = 0;
    for (int i = 0; i < testCount; ++i) {
        TestList[i].updateStatus();
        if (TestList[i].getStatus() == 2 && TestList[i].getTeacherId() == id) {
            ++count;
        }
    }
    return count;
}

//TIM BAI KIEM TRA THEO TEACHERID
LinkList <Test> TestManager::getTestByTeacherId(const string &teacherId, int &count) {
    LinkList <Test> teacherTests;
    count = 0;
    for (int i = 0; i < testCount; ++i) {
        if (TestList[i].getTeacherId() == teacherId) {
            teacherTests.add(TestList[i]);
            ++count;
        }
    }
    return teacherTests;
}

//SO LUONG BAI KIEM TRA
int TestManager::getTestCount() const
{
    return testCount;
}

#endif