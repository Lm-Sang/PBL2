#ifndef QUESTION_H
#define QUESTION_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <ctime>  
#include <iomanip> 
#include "chapter.h"
#include "subject.h"
#include "Linklist.h" // Thêm tập tin LinkList.h
using namespace std;

class Question {
private:
    string id;
    string teacherId;
    string chapterId;
    string subjectId;
    string questionText;
    int numberOfOptions;
    LinkList<string> options; 
    int correctAnswerId;
    void formattedId(int id);

public:
    Question();
    Question(const string &id, const string &teacherId, const string &chapterId,const string &subjectId,
             const string &questionText, int numberOfOptions, LinkList<string> options,
             int correctAnswerId);
    const string &getId() const;
    void setId(int id);
    void setId(string id);
    const string &getTeacherId() const;
    void setTeacherId(const string &teacherId);
    const string &getSubjectId() const;
    void setSubjectId(const string &subjectId);
    const string &getChapterId() const;
    void setChapterId(const string &chapterId);
    string getQuestionText() const;
    void setQuestionText(const string &questionText);
    string getOption(int index) const;
    void setOption(int index, const string &option);
    int getNumberOfOptions() const;
    void setNumberOfOptions(int numberOfOptions);
    int getCorrectAnswerId() const;
    void setCorrectAnswerId(int correctAnswerId);
};

class QuestionBank {

public:
    LinkList<Question> questions; 
    int questionCount = 0;
    bool addQuestion(const string &teacherId, const string &chapterId,const string &subjectId,
                     const string &questionText, int numberOfOptions, const string options[],
                     int correctAnswerId);
    QuestionBank();
    int getQuestionCount() const;
    Question *getQuestionById(const string &id);
    LinkList<Question> getQuestionByChapterId(const string &chapterId, int &foundCount) const;
    bool updateQuestion(const string &id, const string &teacherId, const string &chapterId,const string &subjectId,
                        const string &questionText, int numberOfOptions, const string options[],
                        int correctAnswerId);
    bool deleteQuestion(const string &id);
    int getTotalQuestionByTeacherId(const string &teacherId) const;
    Question getQuestionAt(int index);
    void loadFromFile();
    void saveToFile() const;
    ~QuestionBank();
};



void Question::formattedId(int id) {
    stringstream tmp;
    tmp << "QUE" << setw(3) << setfill('0') << id;
    this->id = tmp.str();
}

Question::Question()
    : teacherId(""), chapterId(""),subjectId(""), questionText(""), numberOfOptions(0), correctAnswerId(0) {}

Question::Question(const string &id, const string &teacherId, const string &chapterId,const string &subjectId,
                   const string &questionText, int numberOfOptions, LinkList<string> options,
                   int correctAnswerId)
    : id(id), teacherId(teacherId), chapterId(chapterId), questionText(questionText), subjectId(subjectId),
      numberOfOptions(numberOfOptions), options(options), correctAnswerId(correctAnswerId) {
    
}

const string &Question::getId() const {
    return id;
}

void Question::setId(int id) {
    formattedId(id);
}

void Question::setId(string id) {
    this->id = id;
}

const string &Question::getTeacherId() const {
    return teacherId;
}

void Question::setTeacherId(const string &teacherId) {
    this->teacherId = teacherId;
}
const string &Question::getSubjectId() const {
    return subjectId;
}
void Question::setSubjectId(const string &subjectId) {
    this->subjectId = subjectId;
}
const string &Question::getChapterId() const {
    return chapterId;
}

void Question::setChapterId(const string &chapterId) {
    this->chapterId = chapterId;
}

string Question::getQuestionText() const {
    return questionText;
}

void Question::setQuestionText(const string &questionText) {
    this->questionText = questionText;
}

string Question::getOption(int index) const {
    if (index >= 0 && index < options.getSize()) {
        return options[index]; // Lấy option từ LinkList
    }
    return "";
}

void Question::setOption(int index, const string &option) {
    if (index >= 0 && index < options.getSize()) {
        options.update(index, option); // Cập nhật option trong LinkList
    }
}

int Question::getNumberOfOptions() const {
    return numberOfOptions;
}

void Question::setNumberOfOptions(int numberOfOptions) {
    this->numberOfOptions = numberOfOptions;
}

int Question::getCorrectAnswerId() const {
    return correctAnswerId;
}

void Question::setCorrectAnswerId(int correctAnswerId) {
    this->correctAnswerId = correctAnswerId;
}

bool QuestionBank::addQuestion(const string &teacherId, const string &chapterId, const string &subjectId,
                               const string &questionText, int numberOfOptions, const string options[],
                               int correctAnswerId) {
    if (teacherId.empty() || chapterId.empty() || subjectId.empty() || questionText.empty() ||
        numberOfOptions < 2 || correctAnswerId < 0 || correctAnswerId >= numberOfOptions) {
        return false;
    }

    for (int i = 0; i < numberOfOptions; ++i) {
        if (options[i].empty()) return false;
    }

    Question newQuestion;
    newQuestion.setId(questions.getSize());
    newQuestion.setTeacherId(teacherId);
    newQuestion.setChapterId(chapterId);
    newQuestion.setSubjectId(subjectId); // Thêm subjectId
    newQuestion.setQuestionText(questionText);
    newQuestion.setNumberOfOptions(numberOfOptions);
    newQuestion.setCorrectAnswerId(correctAnswerId);
    for (int i = 0; i < numberOfOptions; ++i) {
        newQuestion.setOption(i, options[i]);
    }

    questions.add(newQuestion);
    return true;
}

LinkList<Question> QuestionBank::getQuestionByChapterId(const string &chapterId, int &foundCount) const
{
    LinkList<Question> foundQuestions;
    foundCount = 0;
    for (int i = 0; i < questionCount; ++i)
    {
        if (questions[i].getChapterId() == chapterId)
        {
            foundQuestions[foundCount++] = questions[i];
        }
    }
    return foundQuestions;
}

int QuestionBank::getQuestionCount() const {
    return questionCount;
}


Question *QuestionBank::getQuestionById(const string &id) {
    for (int i = 0; i < questions.getSize(); ++i) {
        if (questions[i].getId() == id) {
            return &questions[i];
        }
    }
    return nullptr;
}
bool QuestionBank::updateQuestion(const string &id, const string &teacherId, const string &chapterId,
                                  const string &subjectId, const string &questionText, int numberOfOptions,
                                  const string options[], int correctAnswerId) {
    for (int i = 0; i < questions.getSize(); ++i) {
        Question q = questions[i]; 

        if (q.getId() == id) {
            q.setTeacherId(teacherId);
            q.setChapterId(chapterId);
            q.setSubjectId(subjectId); 
            q.setQuestionText(questionText);
            q.setNumberOfOptions(numberOfOptions);

            for (int j = 0; j < numberOfOptions; ++j) {
                q.setOption(j, options[j]);
            }

            q.setCorrectAnswerId(correctAnswerId);
            return true;
        }
    }

    return false;
}
bool QuestionBank::deleteQuestion(const string &id) {
    for (int i = 0; i < questions.getSize(); ++i) {
        if (questions[i].getId() == id) {
            questions.remove(i); // Xóa câu hỏi khỏi LinkList
            return true;
        }
    }
    return false;
}

int QuestionBank::getTotalQuestionByTeacherId(const string &teacherId) const {
    int count = 0;
    for (int i = 0; i < questions.getSize(); ++i) {
        if (questions[i].getTeacherId() == teacherId) {
            ++count;
        }
    }
    return count;
}

Question QuestionBank::getQuestionAt(int index){
    return questions[index];
}

void QuestionBank::loadFromFile() {
    ifstream inFile("question.txt");
    if (!inFile.is_open()) {
        cout << "File not found" << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, teacherId, chapterId, subjectId, questionText, numberOfOptionsStr, correctAnswerIdStr;

        // Đọc các trường dữ liệu chính
        getline(ss, id, '|');
        getline(ss, teacherId, '|');
        getline(ss, chapterId, '|');
        getline(ss, subjectId, '|');
        getline(ss, questionText, '|');
        getline(ss, numberOfOptionsStr, '|');
        int numberOfOptions = stoi(numberOfOptionsStr);
        LinkList<string> optionList;
        string option;

        // Đọc các lựa chọn
        for (int i = 0; i < numberOfOptions; i++) {
            getline(ss, option, '|');
            optionList.add(option);
        }

        // Đọc câu trả lời đúng
        getline(ss, correctAnswerIdStr, '|');
        int correctAnswerId = stoi(correctAnswerIdStr) - 1;

        // Tạo đối tượng Question và thêm vào danh sách
        Question q(id, teacherId, chapterId, subjectId, questionText, numberOfOptions, optionList, correctAnswerId);
        questions.add(q);
        questionCount++;
    }

    inFile.close();
}


void QuestionBank::saveToFile() const {
    ofstream outFile("question.txt");
    if (!outFile.is_open()) {
        cout << "Cannot open file for writing" << endl;
        return;
    }

    for (int i = 0; i < questions.getSize(); i++) {
        const Question &q = questions[i];

        // Ghi các trường dữ liệu chính
        outFile << q.getId() << "|" << q.getTeacherId() << "|" << q.getChapterId() << "|"
                << q.getSubjectId() << "|" << q.getQuestionText() << "|" << q.getNumberOfOptions() << "|";

        // Ghi các lựa chọn
        for (int j = 0; j < q.getNumberOfOptions(); j++) {
            outFile << q.getOption(j) << "|";
        }

        // Ghi câu trả lời đúng
        outFile << q.getCorrectAnswerId() + 1 << "\n";
    }

    outFile.close();
}

QuestionBank::~QuestionBank() {
    saveToFile();
}

QuestionBank::QuestionBank() {
    loadFromFile();
}


#endif // QUESTION_H
