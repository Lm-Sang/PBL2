#include <iostream>
#include <thread> // Thư viện cần thiết cho std::thread và std::this_thread
#include <chrono> // Thư viện cần thiết cho std::chrono
#include <atomic> // Thư viện cần thiết cho std::atomic
using namespace std;

atomic<bool> time_up(false); // Biến báo hiệu khi hết giờ

void countdown(int seconds) {
    while (seconds > 0 && !time_up) {
        cout << "\rTime remaining: " << seconds << " seconds" << flush;
        this_thread::sleep_for(chrono::seconds(1)); // Sử dụng std::this_thread để tạm dừng luồng
        seconds--;
    }
    if (seconds == 0) {
        time_up = true;
        cout << "\nTime's up!" << endl;
    }
}

void ask_question(const string& question, int time_limit) {
    thread timer(countdown, time_limit); // Khởi chạy bộ đếm thời gian trong luồng riêng
    string answer;

    cout << question << endl;
    cout << "Your answer: ";
    
    while (!time_up) {
        if (cin >> answer) { // Đọc câu trả lời từ người dùng
            time_up = true; // Dừng bộ đếm thời gian khi người dùng trả lời
            break;
        }
    }

    if (!time_up) {
        cout << "\nYou answered: " << answer << endl;
    } else {
        cout << "\nYou ran out of time!" << endl;
    }

    timer.join(); // Đợi luồng bộ đếm thời gian kết thúc
}

int main() {
    int time_limit = 10; // Giới hạn thời gian 10 giây cho mỗi câu hỏi
    ask_question("What is the capital of France?", time_limit);
    ask_question("What is 2 + 2?", time_limit);
    return 0;
}
