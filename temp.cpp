#include <iostream>
#include <iomanip> // std::setw, std::setfill
#include <cstdlib> // system()
#ifdef _WIN32
    #include <windows.h> // Sleep()
#else
    #include <unistd.h>  // sleep()
#endif

using namespace std;

// Hàm hiển thị bộ đếm thời gian trên terminal
void displayTimer(int seconds, const string& staticContent) {
    for (int elapsed = 0; elapsed <= seconds; ++elapsed) {
        // Xóa terminal để cập nhật nội dung
        #ifdef _WIN32
            system("cls"); // Windows
        #else
            system("clear"); // Unix/Linux/MacOS
        #endif

        // Hiển thị nội dung tĩnh
        cout << staticContent << endl;

        // Tính và hiển thị thời gian đã trôi qua
        int hours = elapsed / 3600;
        int minutes = (elapsed % 3600) / 60;
        int secs = elapsed % 60;

        cout << "Elapsed Time: "
             << setw(2) << setfill('0') << hours << ":"
             << setw(2) << setfill('0') << minutes << ":"
             << setw(2) << setfill('0') << secs << endl;

        // Dừng chương trình trong 1 giây
        #ifdef _WIN32
            Sleep(1000); // Windows: thời gian tính bằng mili-giây
        #else
            sleep(1);    // Linux/Unix/MacOS: thời gian tính bằng giây
        #endif
    }
}

int main() {
    // Nội dung tĩnh sẽ hiển thị cùng với bộ đếm thời gian
    string staticContent = "=== Welcome to the Timer Program ===\n"
                           "This program demonstrates a live timer\n";

    // Gọi hàm hiển thị timer
    int duration = 10; // Thời gian đếm trong giây
    displayTimer(duration, staticContent);

    cout << "\nTimer completed. Exiting..." << endl;
    return 0;
}
