#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "CurrentUser.h"
#include "teacher.h"
#include "student.h"
#include "vector"
using namespace std;

void displayMenu(const string &title, const vector<string> &options, int currentSelection) {
    system("cls");
    cout << "===== " << title << " =====" << endl;
    for (size_t i = 0; i < options.size(); ++i) {
        cout << (currentSelection == i ? "-> " : "   ") << options[i] << endl;
    }
}

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

bool handleLogin(bool isTeacher) {
    bool check = true;
    do {
        system("cls");
        cout << (isTeacher ? "===== LOGIN GIAO VIEN =====" : "===== LOGIN HOC SINH =====") << endl;
        cout << "Ten dang nhap: ";
        string username;
        cin >> username;
        cout << "Mat khau: ";
        string password;
        cin >> password;
        // string password = getHiddenPassword();
        CurrentUser user;
        teacherManager teacherObj;
        studentManager studentObj;

        check = (isTeacher ? teacherObj.login(username, password, user)
                            : studentObj.login(username, password, user));
        if (check) {
            system("cls");
            cout << check;
            cout << "===== DANG NHAP THANH CONG =====" << endl;
            cout << "Nhan phim bat ky de tiep tuc..." << endl;
            _getch();
            return 0;
        } else {
            system("cls");
            cout << check;
            cout << "===== TAI KHOAN HOAC MAT KHAU KHONG CHINH XAC =====" << endl;
            cout << "Nhan phim bat ky de thu lai..." << endl;
            _getch();
        }
    } while (!check);
}

bool handleSignup(bool isTeacher) {
    do {
        system("cls");
        cout << (isTeacher ? "===== SIGNUP GIAO VIEN =====" : "===== SIGNUP HOC SINH =====") << endl;
        cout << (isTeacher ? "Ten giao vien: " : "Ten hoc sinh: ");
        string name;
        cin >> name;
        cout << "Ten dang nhap: ";
        string username;
        cin >> username;
        cout << "Mat khau: ";
        string password;
        cin >> password;
        // string password = getHiddenPassword();
        CurrentUser user;
        teacherManager teacherObj;
        studentManager studentObj;

        bool check = isTeacher ? teacherObj.registerTeacher(name, username, password)
                               : studentObj.registerStudent(name, username, password);
        if (check) {
            system("cls");
            cout << "===== DANG KY THANH CONG =====" << endl;
            cout << "Nhan phim bat ky de tiep tuc..." << endl;
            _getch();
            return true;
        } else {
            system("cls");
            cout << "===== TAI KHOAN HOAC MAT KHAU KHONG HOP LE =====" << endl;
            cout << "Nhan phim bat ky de thu lai..." << endl;
            _getch();
        }
    } while (true);
}

int main() {
    int currentSelection = 0;
    bool inLogin = false;
    bool inSignup = false;

    do {
        if (!inLogin && !inSignup) {
            displayMenu("MAIN MENU", {"Dang nhap tai khoan", "Dang ky tai khoan"}, currentSelection);
            char key = _getch();
            if (key == 72) {
                currentSelection = (currentSelection - 1 + 2) % 2;
            } else if (key == 80) {
                currentSelection = (currentSelection + 1) % 2;
            } else if (key == 13) {
                if (currentSelection == 0) inLogin = true;
                else if (currentSelection == 1) inSignup = true;
                currentSelection = 0;
            }
        } else if (inLogin) {
            displayMenu("LOGIN MENU", {"GIAO VIEN", "HOC SINH"}, currentSelection);
            char key = _getch();
            if (key == 72) {
                currentSelection = (currentSelection - 1 + 2) % 2;
            } else if (key == 80) {
                currentSelection = (currentSelection + 1) % 2;
            } else if (key == 13) {
                bool success = handleLogin(currentSelection == 0);
                if (success) return 0;
                else inLogin = false;
            }
        } else if (inSignup) {
            displayMenu("SIGNUP MENU", {"GIAO VIEN", "HOC SINH"}, currentSelection);
            char key = _getch();
            if (key == 72) {
                currentSelection = (currentSelection - 1 + 2) % 2;
            } else if (key == 80) {
                currentSelection = (currentSelection + 1) % 2;
            } else if (key == 13) {
                bool success = handleSignup(currentSelection == 0);
                if (success) return 0;
                else inSignup = false;
            }
        }
    } while (true);

    return 0;
}
