#include "teacher.h"
#include <iostream>

using namespace std;

int main(){
    teacherManager tm;
    cout << "===== TEACHER MANAGER =====" << endl;
    bool check = tm.registerTeacher("Nguyen Vannnnnnn", "nga12356", "aaaa1234567");
    if (check) {
        cout << "Dang ky thanh cong!" << endl;
    }
    else {
        cout << "Dang ky that bai!" << endl;
    }
}