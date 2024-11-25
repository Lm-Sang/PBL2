#ifndef STUDENTATTEMPT_H
#define STUDENTATTEMPT_H

#include <iostream>
#include <string>
#include <ctime>
#include "question.h"
#include "Linklist.h"
#include <sstream>
#include <bits/stdc++.h>
#include <ctime>
#include <random>
#include <iomanip>
#include <sstream>
#include "TestQuestionSelection.h"

using namespace std;

class StudentAttempt
{
private:
    string id;
    string testId;
    string studentId;
    int studentAnswer[100];
    LinkList<string> questionId;
    int totalQuestions;
    int correctAnswer;
    int time;
    time_t startsAt;
    time_t finishedAt;
    void formatId(int id);
    void generateQuestionId();

public:
    StudentAttempt();
    StudentAttempt(int id, string testId, string studentId, int totalQuestions, int time);
    ~StudentAttempt();

    string getId() const;
    string getTestId() const;
    string getStudentId() const;
    string getQuestionId(int index) const;
    int getCorrectAnswer() const;
    string getStartsAt() const;
    string getFinishedAt() const;
    void setEndsAt();
    void setStudentAnswer(int index, int studentAnswer);
    int getSudentAnswer(int index) const;
    void setCorrectAnswer();
    bool setCorretAnswer(int correctAnswer);
    int getTotalQuestions() const;
    int getStudentAnswer(int index) const;
    void setId(string id);
    void setTestId(string testId);
    void setStudentId(string studentId);
    void setTotalQuestions(int totalQuestions);
    void setStartsAt(time_t startsAt);
    void setFinishedAt(time_t finishedAt);
    void setQuestionId(string questionId);
};

class StudentAttemptManager
{
private:
    LinkList<StudentAttempt> attempts;
    int attemptCount;

    bool validateTestId(const string &testId) const;
    bool validateStudentId(const string &studentId) const;
    bool validateStudentAnswer(const string &studentAnswer) const;

public:
    StudentAttemptManager();
    ~StudentAttemptManager();
    void saveToFile() const;
    void loadFromFile();
    bool addAttempt(const StudentAttempt &attempt);
    int getAttemptCount() const;

    LinkList<StudentAttempt> getAttemptsByStudentId(const string &studentId, int &foundCount) const;
    StudentAttempt getAttemptsAt(int index);
    StudentAttempt getAttemptById(const string &id);
    LinkList<StudentAttempt> getAttemptByTestId(const string &testId, int &foundCount) const;
    StudentAttempt getAttemptByQuestionId(const string &questionId);
    bool setStudentAnswer(StudentAttempt attempt, int index, int studentAnswer);
    StudentAttempt createAttempt(const string &testId, const string &studentId, int totalQuestion, int time);
    void setFinishedAtForLastAttempt();
};

StudentAttempt::StudentAttempt()
{
    // memset(questionId, 0, sizeof(questionId));
}
void StudentAttempt::formatId(int id)
{
    stringstream ss;
    ss << "STA" << setfill('0') << setw(3) << id;
    this->id = ss.str();
}

void StudentAttempt::generateQuestionId()
{
    int isNotEnough = 0;
    QuestionBank questionBank;
    TestQuestionSelectionManager testQuestionSelectionManager;
    int testQuestionSelectionCount = 0;

    // Lấy danh sách chương theo testId
    TestQuestionSelection *testQuestionSelectionByTestId =
        testQuestionSelectionManager.getTestQuestionSelectionByTestId(testId, testQuestionSelectionCount);

    if (testQuestionSelectionCount == 0)
    {
        std::cerr << "Khong tim thay " << testId << std::endl;
        return;
    }
    for (int i = 0; i < testQuestionSelectionCount; i++)
    {
        int questionCount = 0;
        LinkList<Question> questionByChapterId = questionBank.getQuestionByChapterId(
            testQuestionSelectionByTestId[i].getChapterId(), questionCount);
        LinkList<Question> questionsByChapterId;
        for (int j = 0; j < questionCount; j++)
        {
            questionsByChapterId.add(questionByChapterId[j]);
        }
        int requiredQuestions = testQuestionSelectionByTestId[i].getNumberOfQuestions();

        if (questionCount < requiredQuestions)
        {
            isNotEnough += requiredQuestions - questionCount;
            for (int j = 0; j < questionCount; j++)
            {
                questionId.add(questionsByChapterId[j].getId());
            }
            while (questionId.getSize() < requiredQuestions)
            {
                questionId.add(questionsByChapterId[questionId.getSize() % questionCount].getId());
            }
        }
        else
        {
            std::random_device rd;
            std::mt19937 gen(rd());

            for (int j = questionCount - 1; j > 0; j--)
            {
                std::uniform_int_distribution<> dis(0, j);
                int randomIndex = dis(gen);
                questionByChapterId.swapNodes(j, randomIndex);
            }

            for (int j = 0; j < requiredQuestions; j++)
            {
                questionId.add(questionsByChapterId[j].getId());
            }
        }
    }

    if (isNotEnough > 0)
    {
        std::cerr << "Thiếu tổng cộng " << isNotEnough << " câu hỏi cho bài kiểm tra!" << std::endl;
    }

    int totalQuestions = questionId.getSize();
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = totalQuestions - 1; i > 0; i--)
    {
        std::uniform_int_distribution<> dis(0, i);
        int randomIndex = dis(gen);
        questionId.swapNodes(i, randomIndex);
    }

    // delete[] testQuestionSelectionByTestId; // Giải phóng nếu cần
}

StudentAttempt::StudentAttempt(int id, string testId, string studentId, int totalQuestions, int time)
{
    formatId(id);
    this->testId = testId;
    this->studentId = studentId;
    this->totalQuestions = totalQuestions;
    this->startsAt = std::time(nullptr);
    this->finishedAt = std::time(nullptr);
    this->time = time;
    srand(std::time(0));
    generateQuestionId();
    for (int i = 0; i < totalQuestions; i++)
    {
        studentAnswer[i] = 0;
    }
    correctAnswer = 0;
}

StudentAttempt::~StudentAttempt()
{
}

// CAC HAM GET
string StudentAttempt::getId() const { return id; }
string StudentAttempt::getTestId() const { return testId; }
string StudentAttempt::getStudentId() const { return studentId; }
string StudentAttempt::getQuestionId(int index) const { return questionId[index]; }
int StudentAttempt::getCorrectAnswer() const { return correctAnswer; }

string StudentAttempt::getStartsAt() const
{
    struct tm *timeinfo;
    timeinfo = localtime(&startsAt);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%H:%M:%S %d/%m/%Y", timeinfo);
    return string(buffer);
}

string StudentAttempt::getFinishedAt() const
{
    struct tm *timeinfo;
    timeinfo = localtime(&finishedAt);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%H:%M:%S %d/%m/%Y", timeinfo);
    return string(buffer);
}
void StudentAttempt::setEndsAt()
{
    finishedAt = std::time(nullptr);
}
void StudentAttempt::setStudentAnswer(int index, int studentAnswer)
{
    this->studentAnswer[index] = studentAnswer;
}
int StudentAttempt::getSudentAnswer(int index) const
{
    return studentAnswer[index];
}
void StudentAttempt::setCorrectAnswer()
{
    QuestionBank questionBank;
    int correct = 0;
    for (int i = 0; i < totalQuestions; i++)
    {
        Question question = questionBank.getQuestionById(questionId[i]);
        if (question.getCorrectAnswerId() == studentAnswer[i])
        {
            correct++;
        }
    }
    this->correctAnswer = correct;
}
bool StudentAttempt::setCorretAnswer(int correctAnswer)
{
    this->correctAnswer = correctAnswer;
    return true;
}

StudentAttemptManager::StudentAttemptManager() : attemptCount(0)
{
    loadFromFile();
}
int StudentAttempt::getTotalQuestions() const
{
    return totalQuestions;
}

StudentAttempt StudentAttemptManager::getAttemptsAt(int index) { return attempts[index]; }

// LUU VAO TEP
void StudentAttemptManager::saveToFile() const
{
    ofstream outFile("studentAttempt.txt");
    if (outFile.is_open())
    {
        for (int i = 0; i < attemptCount; ++i)
        {
            outFile << attempts[i].getId() << "|"
                    << attempts[i].getTestId() << "|"
                    << attempts[i].getStudentId() << "|"
                    << attempts[i].getTotalQuestions() << "|";
            for (int j = 0; j < attempts[i].getTotalQuestions(); ++j)
            {
                outFile << attempts[i].getQuestionId(j) << "|";
            }

            for (int j = 0; j < attempts[i].getTotalQuestions(); ++j)
                outFile << attempts[i].getStudentAnswer(j) << "|";

            outFile << attempts[i].getCorrectAnswer() << "|"
                    << attempts[i].getStartsAt() << "|"
                    << attempts[i].getFinishedAt() << '\n';
        }
        outFile.close();
    }
}
void StudentAttemptManager::loadFromFile()
{
    ifstream inFile("studentAttempt.txt");
    if (inFile.is_open())
    {
        string line;
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string id, testId, studentId, studentAnswer, startsAtStr, finishedAtStr;
            int totalQuestions, correctAnswer;
            time_t startsAt, finishedAt;
            LinkList<string> questionIds;
            LinkList<int> studentAnswers;

            getline(ss, id, '|');
            getline(ss, testId, '|');
            getline(ss, studentId, '|');
            ss >> totalQuestions;
            ss.ignore(1, '|');

            for (int i = 0; i < totalQuestions; ++i)
            {
                string questionId;
                getline(ss, questionId, '|');
                questionIds.add(questionId);
            }

            for (int i = 0; i < totalQuestions; ++i)
            {
                int answer;
                ss >> answer;
                ss.ignore(1, '|');
                studentAnswers.add(answer);
            }

            ss >> correctAnswer;
            ss.ignore(1, '|');
            getline(ss, startsAtStr, '|');
            getline(ss, finishedAtStr, '|');

            struct tm tm;
            std::istringstream startsAtStream(startsAtStr);
            startsAtStream >> std::get_time(&tm, "%H:%M:%S %d/%m/%Y");
            startsAt = mktime(&tm);

            std::istringstream finishedAtStream(finishedAtStr);
            finishedAtStream >> std::get_time(&tm, "%H:%M:%S %d/%m/%Y");
            finishedAt = mktime(&tm);

            StudentAttempt attempt;
            attempt.setId(id);
            attempt.setTestId(testId);
            attempt.setStudentId(studentId);
            attempt.setTotalQuestions(totalQuestions);
            for (int i = 0; i < totalQuestions; ++i)
            {
                attempt.setStudentAnswer(i, studentAnswers[i]);
                attempt.setQuestionId(questionIds[i]);
            }
            attempt.setStartsAt(startsAt);
            attempt.setFinishedAt(finishedAt);
            attempt.setCorretAnswer(correctAnswer);

            attempts.add(attempt);
            attemptCount++;
        }
        inFile.close();
    }
}
void StudentAttempt::setQuestionId(string questionId)
{
    this->questionId.add(questionId);
}
int StudentAttempt::getStudentAnswer(int index) const
{
    return studentAnswer[index];
}
void StudentAttempt::setId(string id)
{
    this->id = id;
}
void StudentAttempt::setTestId(string testId)
{
    this->testId = testId;
}
void StudentAttempt::setStudentId(string studentId)
{
    this->studentId = studentId;
}
void StudentAttempt::setTotalQuestions(int totalQuestions)
{
    this->totalQuestions = totalQuestions;
}
void StudentAttempt::setStartsAt(time_t startsAt)
{
    this->startsAt = startsAt;
}
void StudentAttempt::setFinishedAt(time_t finishedAt)
{
    this->finishedAt = finishedAt;
}

// THEM MOT BAI THI
bool StudentAttemptManager::addAttempt(const StudentAttempt &attempt)
{
    attempts.add(attempt);
    attemptCount++;
    return true;
}

// LAY SO LUONG BAI THI
int StudentAttemptManager::getAttemptCount() const { return attemptCount; }

// LAY BAI THI THEO ID
StudentAttempt StudentAttemptManager::getAttemptById(const string &id)
{
    for (int i = 0; i < attemptCount; ++i)
    {
        if (attempts[i].getId() == id)
        {
            return attempts[i];
        }
    }
}

LinkList<StudentAttempt> StudentAttemptManager::getAttemptsByStudentId(const string &studentId, int &foundCount) const
{
    LinkList<StudentAttempt> foundAttempts;
    foundCount = 0;
    for (int i = 0; i < attemptCount; ++i)
    {   
        cout << "atm count" << attemptCount << endl;
        if (attempts[i].getStudentId() == studentId)
        {
            foundAttempts.add(attempts[i]);
            foundCount++;
        }
        cout << "doundcount" << foundCount << endl;
    }
    return foundAttempts;
}

// LAY BAI THI THEO ID BAI KIEM TRA
LinkList<StudentAttempt> StudentAttemptManager::getAttemptByTestId(const string &testId, int &foundCount) const
{
    LinkList<StudentAttempt> foundAttempts;
    foundCount = 0;
    for (int i = 0; i < attemptCount; ++i)
    {
        if (attempts[i].getTestId() == testId)
        {
            foundAttempts.add(attempts[i]);
            foundCount++;
        }
    }
    return foundAttempts;
}

// LAY BAI THI THEO ID CAU HOI
StudentAttempt StudentAttemptManager::getAttemptByQuestionId(const string &questionId)
{
    for (int i = 0; i < attemptCount; ++i)
    {
        for (int j = 0; j < 1000; ++j)
        {
            if (attempts[i].getQuestionId(j) == questionId)
            {
                return attempts[i];
            }
        }
    }
}

// CAC HAM VALIDATE
bool StudentAttemptManager::validateTestId(const string &testId) const
{
    regex pattern("^TID\\d{3}$");
    return regex_match(testId, pattern);
}

bool StudentAttemptManager::validateStudentId(const string &studentId) const
{
    regex pattern("^STD\\d{3}$");
    return regex_match(studentId, pattern);
}

bool StudentAttemptManager::validateStudentAnswer(const string &studentAnswer) const
{
    return true;
}

// TAO BAI THI
StudentAttempt StudentAttemptManager::createAttempt(const string &testId, const string &studentId, int totalQuestion, int time)
{
    // if (!validateTestId(testId) || !validateStudentId(studentId))
    // {
    //     return StudentAttempt();
    // }
    StudentAttempt newAttempt(attemptCount, testId, studentId, totalQuestion, time);
    attempts.add(newAttempt);
    attemptCount++;
    // saveToFile();
    return attempts[attemptCount - 1];
}
bool StudentAttemptManager::setStudentAnswer(StudentAttempt attempt, int index, int studentAnswer)
{
    attempt.setStudentAnswer(index, studentAnswer);
    attempt.setCorrectAnswer();
    saveToFile();
    return true;
}
StudentAttemptManager::~StudentAttemptManager()
{
}
void StudentAttemptManager::setFinishedAtForLastAttempt()
{
    attempts[attemptCount - 1].setEndsAt();
    saveToFile();
}

#endif