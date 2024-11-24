#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

string getTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << setw(2) << setfill('0') << ltm->tm_hour << ":"
       << setw(2) << setfill('0') << ltm->tm_min << ":"
       << setw(2) << setfill('0') << ltm->tm_sec << " "
       << setw(2) << setfill('0') << ltm->tm_mday << "/"
       << setw(2) << setfill('0') << 1 + ltm->tm_mon << "/"
       << 1900 + ltm->tm_year;
    return ss.str();
}

int main(){
    string Time = getTime();
    cout << "Time: " << Time;

}