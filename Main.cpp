#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <ctime>  
#include <iomanip> 
#include <string>
#include <windows.h>
#include "TestQuestionSelection.h"
#include "studentAttempt.h"
#include "CurrentUser.h"
#include "chapter.h"
#include "subject.h"
#include "question.h"
#include "testInfo.h"
#include "student.h"
#include "teacher.h"
#include "Linklist.h"
using namespace std;

string getHiddenPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != 13) {
        if (ch == 8 && !password.empty()) { 
            password.pop_back();
            cout << "\b \b"; 
        } else if (ch != 8) {
            password.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

void displayTimer(int &seconds) {
    for (int elapsed = seconds; elapsed >=0; --elapsed) {
            system("cls"); 
        

        int hours = elapsed / 3600;
        int minutes = (elapsed % 3600) / 60;
        int secs = elapsed % 60;

        cout << "Thoi gian con lai: "
             << setw(2) << setfill('0') << hours << ":"
             << setw(2) << setfill('0') << minutes << ":"
             << setw(2) << setfill('0') << secs << endl;

        
            Sleep(1000); 
    }
        cout << "Ban da het thoi gian lam bai!" << endl;
        cout << "Nhan phim bat ky de thoat..." << endl;
        _getch();
}

void login(int currentSelection){
    system("cls");
    cout << "===== LOGIN =====" << endl;
    cout << (currentSelection == 0 ? "->" : "  ") << "Dang nhap tai khoan" << endl;
    cout << (currentSelection == 1 ? "->" : "  ") << "Dang ky tai khoan" << endl;
}

void LoginMenu(int currentSelection){
    system("cls");
    cout << "===== LOGIN =====" << endl;
    cout << (currentSelection == 0 ? "->" : "  ") << "Giao vien" << endl;
    cout << (currentSelection == 1 ? "->" : "  ") << "Hoc sinh" << endl;
}

void SignupMenu(int currentSelection){
    system("cls");
    cout << "===== SIGNUP =====" << endl;
    cout << (currentSelection == 0 ? "->" : "  ") << "Giao vien" << endl;
    cout << (currentSelection == 1 ? "->" : "  ") << "Hoc sinh" << endl;
}

void XemLichSuBailam(CurrentUser user) {
    system("cls");
    cout << "===== LICH SU BAI LAM =====" << endl;
    StudentAttemptManager newManager;
    int foundCount = 0;
    LinkList<StudentAttempt> attemptsByStudent = newManager.getAttemptsByStudentId(user.getId(), foundCount);
    cout << "So luong bai thi cua sinh vien " << user.getId() << ": " << foundCount << endl;
    for (int i = 0; i < foundCount; i++)
    {
        cout << "Bai thi " << attemptsByStudent[i].getId() << ": " << attemptsByStudent[i].getTestId()<< endl;
        cout << "Diem so: " << attemptsByStudent[i].getCorrectAnswer() << endl;
    }
    cout << "Nhan phim bat ky de thoat..." << endl;
    _getch();
}

void LamBai(CurrentUser user) {
    bool check = false;
    Test test;
    do {
        system("cls");
        cout << "===== LAM BAI KIEM TRA=====" << endl;
        cout << "Nhap ma de thi: ";
        string testId;  
        cin >> testId;
        TestManager testManager;
        test = testManager.getTestById(testId);
        if(test.getId() == "") {
            cout << "Ma de thi khong ton tai!" << endl;
            cout << "Nhan phim bat ki de quay lai!...." << endl;
            _getch();
        }
        else {
            cout << "Nhap mat khau de thi: ";
            string password;
            cin >> password;
            if (test.getPassword() == password) {
                check = true;
            }
            else {
                cout << "Mat khau khong chinh xac!" << endl;
                cout << "Nhan phim bat ki de quay lai!...." << endl;
                _getch();
            }
        }
    }while (!check);

    system("cls");
    cout << "===== THONG TIN BAI KIEM TRA =====" << endl;
    cout << "Ma de thi: " << test.getId() << endl;
    cout << "Ten de thi: " << test.getTitle() << endl;
    cout << "So cau hoi: " << test.getTotalQuestion()<< endl;
    cout << "Thoi gian lam bai: " << test.getDuration() << " phut" << endl;
    cout << "Thoi gian bat dau: " << test.getStartsAt() << endl;
    cout << "Thoi gian ket thuc: " << test.getEndsAt() << endl;
    cout << "Trang thai: " << (test.getStatus() == Test::INCOMING ? "Chua bat dau" : (test.getStatus() == Test::ONGOING ? "Dang lam bai" : "Da ket thuc")) << endl;
    if (test.getStatus() == Test::ONGOING) {
        QuestionBank questionBank;
        cout << "Nhan Enter de bat dau lam bai!" << endl;
        char key =_getch();
        if (key == 13){
            StudentAttemptManager attemptManager;
            StudentAttempt Attempt = attemptManager.createAttempt(test.getId(), user.getId(), test.getTotalQuestion(), test.getDuration());
            int duration = test.getDuration() * 60;
            for (int i = 0; i < Attempt.getTotalQuestions(); ++i) {
                system("cls");
                cout << "===== LAM BAI KIEM TRA =====" << endl;
                // displayTimer(duration);
                cout << "Cau " << i + 1 << ": " << questionBank.getQuestionById(Attempt.getQuestionId(i)).getQuestionText() << endl;
                for (int j = 0; j < questionBank.getQuestionById(Attempt.getQuestionId(i)).getNumberOfOptions(); ++j) {
                    if (j == 0) cout << "A.";
                    else if (j == 1) cout << "B.";
                    else if (j == 2) cout << "C.";
                    else if (j == 3) cout << "D.";
                    cout << questionBank.getQuestionById(Attempt.getQuestionId(i)).getOption(j) << endl;
                }
                cout << "Cau tra loi cua ban: ";
                string answerStr;
                cin >> answerStr;
                int answer;
                if (answerStr == "A") answer = 0;
                else if (answerStr == "B") answer = 1;
                else if (answerStr == "C") answer = 2;
                else if (answerStr == "D") answer = 3;
                Attempt.setStudentAnswer(i, answer);
                Attempt.setCorrectAnswer();
            }
            time_t currentTime = time(nullptr);
            Attempt.setFinishedAt(currentTime);
            attemptManager.saveToFile();
            cout << "Ban da hoan thanh bai kiem tra!" << endl;
            cout << "So cau tra loi dung: " << Attempt.getCorrectAnswer() << endl;
        }
    }
    else if (test.getStatus() == Test::COMPLETED) {
        cout << "Bai kiem tra da qua han!" << endl;
    }
    else if (test.getStatus() == Test::INCOMING) {
        cout << "Bai kiem tra chua bat dau!" << endl;
    }
    cout << "Nhan phim bat ki de quay lai!...." << endl;
    _getch();
}

void TaoDeThi(CurrentUser user) {
    bool check = false; // Biến kiểm tra trạng thái thành công
    do {
        system("cls");
        cout << "===== TAO DE THI =====" << endl;

        cout << "Nhap ten de thi: ";
        string name;
        cin.ignore(); 
        getline(cin, name);
        cout << "Nhap so luong cau hoi: ";
        int numQuestions;
        cin >> numQuestions;
        cout << "Nhap chuong can thi: ";
        int chapter;
        cin >> chapter;
        stringstream tmp;
        tmp << "CHA" << setw(3) << setfill('0') << chapter - 1;
        string chapterStr= tmp.str();
        cout << "Nhap thoi gian lam bai (phut): ";
        int duration;
        cin >> duration;
        cin.ignore(); 
        cout << "Nhap mat khau de thi: ";
        string password;
        getline(cin, password);
        cout << "Nhap thoi gian bat dau (vd: 12:00:00 01/01/2024): ";
        string startTime;
        getline(cin, startTime);
        cout << "Nhap thoi gian ket thuc (vd: 12:00:00 01/01/2024): ";
        string endTime;
        getline(cin, endTime);
        TestManager testManager;
        cout << user.getId() << endl;
        TestQuestionSelectionManager selectionManager;
        check = testManager.createTest(user.getId(), name, numQuestions, password, duration, startTime, endTime);
        selectionManager.addTestQuestionSelection(testManager.getTestAt(testManager.getTestCount() - 1).getId(), chapterStr, numQuestions);

        cout << "Nhan phim bat ky de tiep tuc..." << endl;
        system("cls");
        if (check) {
            cout << "===== TAO DE THI THANH CONG =====" << endl;
        } else {
            cout << "===== TAO DE THI THAT BAI =====" << endl;
            cout << "Vui long kiem tra lai thong tin va thu lai." << endl;
        }

        cout << "Nhan phim bat ky de tiep tuc..." << endl;
        _getch();
    } while (!check);
}

void XemDeThi(CurrentUser user) {
    TestManager tem;
    LinkList<Test> tests;
    cout << "Danh sach cac de thi da tao" << endl;
    for (int i = 0; i < tem.getTestCount(); i++) {
        if(tem.getTestAt(i).getTeacherId() == user.getId()) {
            cout << tests[i].getId() << "|" << tests[i].getTitle() << "|" 
            << tests[i].getTotalQuestion() << "|" << tests[i].getDuration() << "|" 
            << tests[i].getStartsAt() << "|" << tests[i].getEndsAt() << "|" 
            << tests[i].getStatus() << endl;
        }
    }       
    cout << "Nhap ma de thi can xem chi tiet: ";
    string id;
    cin >> id;
    studentManager sm;
    LinkList<student> students;
    
}


void ChinhSuaThongTin(int currentSelection, CurrentUser user){
    bool Ten = false;
    bool MKhau = false;
    do {
        if (!Ten && !MKhau) {
            system("cls");
            cout << "===== CHINH SUA THONG TIN CA NHAN =====" << endl;
            cout << (currentSelection == 0 ? "->" : "  ") << "Thay doi ten: "  << endl;
            cout << (currentSelection == 1 ? "->" : "  ") << "Thay doi mat khau: "  << endl;
            char key = _getch();
            if (key == 72) {
                currentSelection = (currentSelection - 1 + 2) % 2;
            } else if (key == 80) {
                currentSelection = (currentSelection + 1) % 2;
            } else if (key == 13) {
                switch (currentSelection) {
                    case 0: Ten = true; currentSelection = 0; break;
                    case 1: MKhau = true; currentSelection = 0; break;
                }
            }
        } else if (Ten) {
            system("cls");
            cout << "===== CHINH SUA THONG TIN CA NHAN =====" << endl;
            cout << "Nhap ten moi: ";
            string newName;
            cin >> newName;
            string id = user.getId();
            string password = user.getPassword();
            if (user.getRole() == "teacher") {
                teacherManager tm;
                tm.update(id, password, newName);
            }
            else {
                studentManager sm;
                sm.update(id, password, newName);
            }
            cout << "Ban da doi ten thanh cong!" << endl;
            cout << "Nhan phim bat ky de tiep tuc..." << endl;
            _getch();
            Ten = false;
        } else if (MKhau) {
            cout << "Nhap mat khau cu: ";
            string oldPassword = getHiddenPassword();
            if (user.getPassword() == oldPassword) {
                cout << "Nhap mat khau moi: ";
                string newPassword = getHiddenPassword();
                if (user.getRole() == "teacher") {
                    teacherManager tm;
                    tm.update(user.getId(),newPassword, user.getFullname());
                }
                else {
                    studentManager sm;
                    sm.update(user.getId(),newPassword, user.getFullname());
                }
                cout << "Ban da doi mat khau thanh cong!" << endl;
            }
            else {
                cout << "Mat khau cu khong chinh xac!" << endl;
            }
            cout << "Nhan phim bat ky de tiep tuc..." << endl;
            _getch();
            MKhau = false;
        }
    } while (true);
}

void NHCH(CurrentUser user) {
    bool ThemCH = false;
    bool SuaCH = false;
    bool XoaCH = false;
    bool XemCH = false;
    int currentSelection = 0;
    do {
        if (!ThemCH && !SuaCH && !XoaCH && !XemCH) {
            system("cls");
            cout << "===== NGAN HANG CAU HOI =====" << endl;
            cout << (currentSelection == 0 ? "->" : "  ") << "Them cau hoi" << endl;
            cout << (currentSelection == 1 ? "->" : "  ") << "Sua cau hoi" << endl;
            cout << (currentSelection == 2 ? "->" : "  ") << "Xoa cau hoi" << endl;
            cout << (currentSelection == 3 ? "->" : "  ") << "Xem cau hoi" << endl;
            char key = _getch();
            if (key == 72) {
                currentSelection = (currentSelection - 1 + 4) % 4;
            } else if (key == 80) {
                currentSelection = (currentSelection + 1) % 4;
            } else if (key == 13) {
                switch (currentSelection) {
                    case 0: ThemCH = true; currentSelection = 0; break;
                    case 1: SuaCH = true; currentSelection = 0; break;
                    case 2: XoaCH = true; currentSelection = 0; break;
                    case 3: XemCH = true; currentSelection = 0; break;
                }
            }
        } else if (ThemCH) {
            system("cls");
            cout << "===== NGAN HANG CAU HOI =====" << endl;
            cout << "Nhap mon ban muon them cau hoi: " << endl;
            string subjectName;
            cin >> subjectName;
            SubjectManager sm;
            LinkList<Subject> subjectList;
            string subjectId;
            for (int i = 0; i < sm.getSubjectCount(); i++) {
                if(sm.getSubjectAt(i).getName() == subjectName) {
                    subjectId = sm.getSubjectAt(i).getId();
                }
            }
            cout << "Nhap chuong ban muon them cau hoi: " << endl;
            int chapter;
            cin >> chapter;
            stringstream tmp;
            tmp << "CHA" << setw(3) << setfill('0') << chapter - 1;
            string chapterStr= tmp.str();
            cout << "Nhap cau hoi: " << endl;
            string question;
            cin.ignore();
            getline(cin, question);
            cout << "Nhap so luong dap an: " << endl;
            int answerCount;
            cin >> answerCount;
            LinkList<string> options;
            for (int i = 0; i < answerCount; i++) {
                string option;
                cout << "Nhap dap an " << i + 1 << ": " ;
                cin >> option;
                options.add(option);
            }
            cout << "Nhap dap an dung: " << endl;
            int correctAnswer;
            cin >> correctAnswer;
            correctAnswer--;
            QuestionBank qb;
            qb.addQuestion(user.getId(), chapterStr, subjectId, question, answerCount, options, correctAnswer);
            cout << "Nhan phim bat ky de tiep tuc..." << endl;
            _getch();
            ThemCH = false;
        } else if (SuaCH) {

            SuaCH = false;
        } else if (XoaCH) {
            system("cls");
            cout << "===== NGAN HANG CAU HOI =====" << endl;
            cout << "Nhap ma cau hoi ban muon xoa: " ;
            string tmp;
            cin >> tmp;
            QuestionBank qb;
            qb.deleteQuestion(tmp);
            XoaCH = false;
        } else if (XemCH) {
            SubjectManager sm;
            LinkList<Subject> subjectList;
            for (int i = 0; i < sm.getSubjectCount(); i++) {
                if (sm.getSubjectAt(i).getUserId() == user.getId()) {
                    subjectList.add(sm.getSubjectAt(i));
                }
            }
            do {
                system("cls");
                cout << "===== NGAN HANG CAU HOI =====" << endl;
                cout << "CHON MON HOC: " << endl;
                for (int i = 0; i < subjectList.getSize(); i++) {
                    cout << (currentSelection == i ? "->" : "  ") << subjectList[i].getName() << endl;
                }
                char key = _getch();
                if (key == 72) {
                    currentSelection = (currentSelection - 1 + subjectList.getSize()) % subjectList.getSize();
                } else if (key == 80) {
                    currentSelection = (currentSelection + 1) % subjectList.getSize();
                } else if (key == 13) {
                    system("cls");
                    cout << "===== NGAN HANG CAU HOI =====" << endl;
                    int k = currentSelection;
                    currentSelection = 0;
                    ChapterManager cm;
                    LinkList<Chapter> chapterList;
                    for (int i = 0; i < cm.getChapterCount(); i++) {
                        if (cm.getChapterAt(i).getSubjectId() == subjectList[k].getId()) {
                            chapterList.add(cm.getChapterAt(i));
                        }
                    }
                    QuestionBank qb;
                    for (int i = 0; i < chapterList.getSize(); i++) {
                        cout << chapterList[i].getName() << endl;
                        for (int j = 0; j < qb.getQuestionCount(); j++) {
                            if (qb.getQuestionAt(j).getChapterId() == chapterList[i].getId()
                                && qb.getQuestionAt(j).getSubjectId() == subjectList[k].getId() 
                                && qb.getQuestionAt(j).getTeacherId() == user.getId()) {
                                cout << qb.getQuestionAt(j).getId() << ": " << qb.getQuestionAt(j).getQuestionText() << endl;
                                for (int l = 0; l < qb.getQuestionAt(j).getNumberOfOptions(); l++) {
                                    if (l == 0) cout << "A. ";
                                    if (l == 1) cout << "B. ";
                                    if (l == 2) cout << "C. ";
                                    if (l == 3) cout << "D. ";
                                    if (l == 4) cout << "E. ";
                                    cout << qb.getQuestionAt(j).getOption(l) << endl;
                                }
                                cout << "Cau tra loi dung: ";
                                cout << qb.getQuestionAt(j).getOption(qb.getQuestionAt(j).getCorrectAnswerId()) << endl;
                            }
                        }
                    }
                    cout << "Nhan phim bat ky de tiep tuc..." << endl;
                    _getch();
                    break;
                }
            } while (true); // Thêm điều kiện kết thúc vòng lặp
            XemCH = false;
        }
    } while (true);
}

void ChucNangGV(int currentSelection, CurrentUser user) {
    bool TaoBT = false;
    bool ChinhSuaBT = false;
    bool NganHangCH = false;
    bool XemLichSuBT = false;
    bool ChinhSuaTT = false;
    
    do {
        if (!TaoBT && !ChinhSuaBT && !NganHangCH && !XemLichSuBT && !ChinhSuaTT) {
            system("cls");
            cout << "===== GIAO VIEN =====" << endl;
            cout << (currentSelection == 0 ? "->" : "  ") << "Tao de thi" << endl;
            cout << (currentSelection == 1 ? "->" : "  ") << "Chinh sua de thi" << endl;
            cout << (currentSelection == 2 ? "->" : "  ") << "Ngan hang cau hoi" << endl;
            cout << (currentSelection == 3 ? "->" : "  ") << "Xem lich su de thi da tao" << endl;
            cout << (currentSelection == 4 ? "->" : "  ") << "Chinh sua thong tin ca nhan" << endl;
            char key = _getch();
            if (key == 72) { // Arrow Up
                currentSelection = (currentSelection - 1 + 5) % 5;
            } else if (key == 80) { // Arrow Down
                currentSelection = (currentSelection + 1) % 5;
            } else if (key == 13) { // Enter
                switch (currentSelection) {
                    case 0: TaoBT = true; currentSelection = 0; break;
                    case 1: ChinhSuaBT = true; currentSelection = 0; break;
                    case 2: NganHangCH = true; currentSelection = 0; break;
                    case 3: XemLichSuBT = true; currentSelection = 0; break;
                    case 4: ChinhSuaTT = true; currentSelection = 0; break;
                }
            }
        } 
        else if (TaoBT) {
            TaoDeThi(user);
            TaoBT = false;
        } 
        else if (ChinhSuaBT) {
            ChinhSuaBT = false;
        } 
        else if (NganHangCH) {
            NHCH(user);
            NganHangCH = false;
        } 
        else if (XemLichSuBT) {
            XemLichSuBT = false;
        } 
        else if (ChinhSuaTT) {
            ChinhSuaThongTin(currentSelection, user);
            ChinhSuaTT = false;
        }
    } while (true);
}


void ChucNangHS(int currentSelection, CurrentUser user){
    bool LamDeThi = false;
    bool XemLichSu = false;
    bool ChinhSuaTT = false;
    do {
        if(!LamDeThi && !XemLichSu && !ChinhSuaTT) {
            system("cls");
            cout << "===== HOC SINH =====" << endl;
            cout << (currentSelection == 0 ? "->" : "  ") << "Lam de thi" << endl;
            cout << (currentSelection == 1 ? "->" : "  ") << "Xem lich su thi" << endl;
            cout << (currentSelection == 2 ? "->" : "  ") << "Chinh sua thong tin ca nhan" << endl;
            char key = _getch();
            if (key == 72) { 
                currentSelection = (currentSelection - 1 + 3) % 3;
            } else if (key == 80) { 
                currentSelection = (currentSelection + 1) % 3;  
            } else if (key == 13) {
                switch (currentSelection) {
                    case 0: LamDeThi = true; currentSelection = 0; break;
                    case 1: XemLichSu = true; currentSelection = 0; break;
                    case 2: ChinhSuaTT = true; currentSelection = 0; break;
                }
            }
        } 
        else if (LamDeThi) {
            LamBai(user);
            LamDeThi = false;
        } 
        else if (XemLichSu) {
            XemLichSuBailam(user);
            XemLichSu = false;
        } 
        else if (ChinhSuaTT) {
            ChinhSuaThongTin(currentSelection, user);
            ChinhSuaTT = false;
        }
    } while (true);
}


int main(){
    int currentSelection = 0;
    bool inLogin = false;
    bool inSignup = false;
    do {
        if (!inLogin && !inSignup) {
            login(currentSelection);
            char key = _getch();
            if (key == 72) {
                currentSelection = (currentSelection - 1 + 2) % 2;
            } else if (key == 80) {
                currentSelection = (currentSelection + 1) % 2;
            } else if (key == 13) {
                system("cls");
                switch (currentSelection) {
                    case 0: inLogin = true; currentSelection = 0; break;
                    case 1: inSignup = true; currentSelection = 0; break;
                }
            }
        }
        else if (inLogin) {
            bool inGV = false;
            bool inHS = false;
            do {
                if(!inGV && !inHS){
                    LoginMenu(currentSelection);
                    char key = _getch();
                    if (key == 72) {
                        currentSelection = (currentSelection - 1 + 2) % 2;
                    } 
                    else if (key == 80) {
                        currentSelection = (currentSelection + 1) % 2;
                    } 
                    else if (key == 13) {
                        system("cls");
                        switch (currentSelection) {
                            case 0: inGV = true; currentSelection = 0; break;
                            case 1: inHS = true; currentSelection = 0; break;
                        }
                    }
                }
                else if (inGV){
                    bool check = true;
                    do {
                        system("cls");  
                        cout << "===== LOGIN GIAO VIEN =====" << endl;
                        cout << "Ten dang nhap: ";
                        string username;
                        cin >> username;
                        cout << "Mat khau: ";
                        string password = getHiddenPassword();
                        CurrentUser user;
                        teacherManager teacherObj;

                        bool check =  teacherObj.login(username, password, user);
                        if (check) {
                            system("cls");
                            cout << "===== DANG NHAP THANH CONG =====" << endl;
                            cout << "Nhan phim bat ky de tiep tuc..." << endl;
                            _getch();
                            ChucNangGV(currentSelection, user);
                        }
                        else {
                            system("cls");
                            cout << "===== TAI KHOAN HOAC MAT KHAU KHONG CHINH XAC =====" << endl;
                            cout << "Nhan phim bat ky de thu lai..." << endl;
                            _getch();
                        }
                    } while (!check);
                }
                else if (inHS){
                    bool check = true;
                    do {
                        system("cls");  
                        cout << "===== LOGIN HOC SINH =====" << endl;
                        cout << "Ten dang nhap: ";
                        string username;
                        cin >> username;
                        cout << "Mat khau: ";
                        string password = getHiddenPassword();
                        CurrentUser user;
                        studentManager studentObj;

                        bool check =  studentObj.login(username, password, user);
                        if (check) {
                            system("cls");
                            cout << "===== DANG NHAP THANH CONG =====" << endl;
                            cout << "Nhan phim bat ky de tiep tuc..." << endl;
                            _getch();
                            system("cls");
                            ChucNangHS(currentSelection, user);
                        }
                        else {
                            system("cls");
                            cout << "===== TAI KHOAN HOAC MAT KHAU KHONG CHINH XAC =====" << endl;
                            cout << "Nhan phim bat ky de thu lai..." << endl;
                            _getch();
                        }
                    } while (!check);
                }
            } while (true);
        }
        else if (inSignup) {
            bool inGV = false;
            bool inHS = false;
            do {
                if(!inGV && !inHS){
                    SignupMenu(currentSelection);
                    char key = _getch();
                    if (key == 72) {
                        currentSelection = (currentSelection - 1 + 2) % 2;
                    } 
                    else if (key == 80) {
                        currentSelection = (currentSelection + 1) % 2;
                    } 
                    else if (key == 13) {
                        system("cls");
                        switch (currentSelection) { 
                            case 0: inGV = true; currentSelection = 0; break;
                            case 1: inHS = true; currentSelection = 0; break;
                        }
                    }
                }   
                else if (inGV){
                    bool check = false;
                    do {
                        system("cls");
                        cout << "===== SIGNUP GIAO VIEN =====" << endl;
                        cout << "Ten giao vien: ";
                        string name; 
                        getline(cin, name);
                        cout << "Ten dang nhap: ";
                        string username;
                        getline(cin, username);
                        cout << "Mat khau: ";
                        string password = getHiddenPassword();
                        teacherManager teacherObj;

                        check = teacherObj.registerTeacher(name, username, password);
                        cout << check << endl;
                        if (check) {
                            system("cls");
                            cout << "===== DANG KY THANH CONG =====" << endl;
                            cout << "Nhan phim bat ky de tiep tuc..." << endl;
                            inGV = false;
                            _getch();
                        }
                        else {
                            system("cls");
                            cout << "===== TAI KHOAN HOAC MAT KHAU KHONG HOP LE =====" << endl;
                            cout << "Nhan phim bat ky de thu lai..." << endl;
                            _getch();
                        }
                    } while (!check);
                }
                else if (inHS){
                    bool check = true;
                    do {
                        system("cls");
                        cout << "===== SIGNUP HOC SINH =====" << endl;
                        cout << "Ten hoc sinh: ";
                        string name;
                        getline(cin, name);
                        cout << "Ten dang nhap: ";
                        string username;
                        getline(cin, username);
                        cout << "Mat khau: ";
                        string password = getHiddenPassword();
                        studentManager studentObj;

                        bool check = studentObj.registerStudent(name, username, password);
                        if (check) {
                            system("cls");
                            cout << "===== DANG KY THANH CONG =====" << endl;
                            cout << "Nhan phim bat ky de tiep tuc..." << endl;
                            inHS = false;
                            _getch();
                        }
                        else {
                            system("cls");
                            cout << "===== TAI KHOAN HOAC MAT KHAU KHONG HOP LE =====" << endl;
                            cout << "Nhan phim bat ky de thu lai..." << endl;
                            _getch();
                        }
                    } while (!check);
                }
            } while (true);
        inSignup = false;
        } 
    }while (true);
    return 0;
}