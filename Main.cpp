#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <ctime>  
#include <iomanip> 
#include <string>
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
        check = testManager.createTest(user.getId(), name, numQuestions, password, duration, startTime, endTime);
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
            string newName;
            cout << "Nhap ten moi: ";
            cin >> newName;
            if (user.getRole() == "teacher") {
                teacherManager tm;
                tm.update(user.getId(),user.getPassword(), newName);
            }
            else {
                studentManager sm;
                sm.update(user.getId(),user.getPassword(), newName);
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
            ThemCH = false;
        } else if (SuaCH) {
            SuaCH = false;
        } else if (XoaCH) {
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
                        // cout << chap
                        // cout << qb.getQuestionAt(i).getChapterId() << "/" << chapterList[i].getId() << endl;
                        cout << qb.getQuestionCount() << endl;
                        for (int j = 0; j < qb.getQuestionCount(); j++) {
                            cout << "hahaha";
                        //     if (qb.getQuestionAt(j).getChapterId() == chapterList[i].getId()
                        //         && qb.getQuestionAt(j).getSubjectId() == subjectList[k].getId() 
                        //         && qb.getQuestionAt(j).getTeacherId() == user.getId()) {
                        //         cout << i << endl;
                        //         // cout << qb.getQuestionAt(j).getQuestionText() << endl;
                        //         // for (int l = 0; l < qb.getQuestionAt(j).getNumberOfOptions(); l++) {
                        //         //     cout << qb.getQuestionAt(j).getOption(l) << endl;
                        //         // }
                        //         // cout << "Cau tra loi dung: ";
                        //         // cout << qb.getQuestionAt(j).getOption(qb.getQuestionAt(j).getCorrectAnswerId()) << endl;
                        //     }
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
            // QuestionBank q;
            // SubjectManager sm;
            // do {
            //     string id;
            //     int k;
            //     system("cls");
            //     cout << "===== NGAN HANG CAU HOI =====" << endl;
            //     int x = sm.getSubjectCount();
            //     for (int i = 0; i < x; i++) {
            //         cout << (currentSelection == i ? "->" : "  ") << sm.getSubjectById(i).getName() << endl;
            //     }
            //     char key = _getch();
            //     if (key == 72) { 
            //         currentSelection = (currentSelection - 1 + x) % x;
            //     } else if (key == 80) {
            //         currentSelection = (currentSelection + 1) % x;
            //     } else if (key == 13) { 
            //         system("cls");
            //         cout << "===== NGAN HANG CAU HOI =====" << endl;
            //         cout << sm.getSubjectById(currentSelection).getName() << endl;
            //         k = currentSelection;
            //         currentSelection = 0;
            //         ChapterManager cm;
            //         LinkList<Chapter> chapterList;
            //         for (int i = 0; i < cm.getChapterCount(); i++) {
            //             if (cm.getChapterAt(i).getSubjectId() == sm.getSubjectById(k).getId()) {
            //                 chapterList.add(cm.getChapterAt(i));
            //             }
            //         }
            //         do {
            //             system("cls");
            //             cout << "===== NGAN HANG CAU HOI =====" << endl; 
            //             for (int i = 0; i < chapterList.getSize(); i++) {
            //                 cout << (currentSelection == i ? "->" : "  ") << chapterList[i].getName() << endl;
            //             }   
            //             char key = _getch();
            //             if (key == 72) {
            //                 currentSelection = (currentSelection - 1 + chapterList.getSize()) % chapterList.getSize();
            //             } else if (key == 80) { 
            //                 currentSelection = (currentSelection + 1) % chapterList.getSize();
            //             } else if (key == 13) {
            //                 system("cls");
            //                 cout << "===== NGAN HANG CAU HOI =====" << endl;
            //                 cout << chapterList[currentSelection].getName() << endl;
            //                 id = chapterList[currentSelection].getId();
            //                 currentSelection = 0;
            //                 for (int i = 0; i < q.getQuestionCount(); i++) {
            //                     if (q.questions[i].getChapterId() == id && q.questions[i].getSubjectId() == sm.getSubjectById(k).getId()) {
            //                         for (int j = 0; j < q.questions[i].getNumberOfOptions(); j++){
            //                             cout << j << ". " << q.questions[i].getOption(j) << endl;
            //                         }
            //                         cout << "Correct answer: " << q.questions[i].getOption(q.questions[i].getCorrectAnswerId()) << endl;
            //                     }
            //                 }
            //                 cout << "Nhan phim bat ky de tro lai menu..." << endl;
            //                 _getch();
            //             }
            //             else if (key == 27) {
            //                 currentSelection = 0;
            //                 break;
            //             }
            //         } while (true);
            //     }
            //     else if (key == 27) {
            //         currentSelection = 0;
            //         break;
            //     }
            // } while (true);
            NganHangCH = false;
            break;
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


void ChucNangHS(int currentSelection){
    system("cls");
    cout << "===== HOC SINH =====" << endl;
    cout << (currentSelection == 0 ? "->" : "  ") << "Lam bai thi" << endl;
    cout << (currentSelection == 1 ? "->" : "  ") << "Xem lich su cac bai da lam" << endl;
    cout << (currentSelection == 2 ? "->" : "  ") << "Chinh sua thong tin ca nhan" << endl;
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
                        cin >> password;
                        CurrentUser user;
                        studentManager studentObj;

                        bool check =  studentObj.login(username, password, user);
                        if (check) {
                            system("cls");
                            cout << "===== DANG NHAP THANH CONG =====" << endl;
                            cout << "Nhan phim bat ky de tiep tuc..." << endl;
                            _getch();
                            system("cls");
                            return 0;
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
                        cin.ignore(); 
                        getline(cin, name);
                        cout << "Ten dang nhap: ";
                        string username;
                        cin.ignore(); 
                        getline(cin, username);
                        cout << "Mat khau: ";
                        string password = getHiddenPassword();
                        teacherManager teacherObj;

                        check = teacherObj.registerTeacher(name, username, password);
                        if (check) {
                            system("cls");
                            cout << "===== DANG KY THANH CONG =====" << endl;
                            cout << "Nhan phim bat ky de tiep tuc..." << endl;
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
                        cin.ignore(); 
                        getline(cin, name);
                        cout << "Ten dang nhap: ";
                        string username;
                        cin.ignore(); 
                        getline(cin, username);
                        cout << "Mat khau: ";
                        string password = getHiddenPassword();
                        studentManager studentObj;

                        bool check = studentObj.registerStudent(name, username, password);
                        if (check) {
                            system("cls");
                            cout << "===== DANG KY THANH CONG =====" << endl;
                            cout << "Nhan phim bat ky de tiep tuc..." << endl;
                            _getch();
                            system("cls");
                            return 0;
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
        } 
    }while (true);
    return 0;
}