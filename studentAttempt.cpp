#include "studentAttempt.h"

int main(){


    // Tạo đối tượng quản lý bài thi
    StudentAttemptManager manager;

    // Thêm một bài thi mới
    string testId = "TID001";
    string studentId = "STD001";
    int totalQuestions = 10;
    int time = 30; // Thời gian làm bài là 30 phút
    // manager.createAttempt(testId, studentId, totalQuestions, time);

    // Hiển thị thông tin bài thi đầu tiên
    cout << "=== Thong tin bai thi ===" << endl;
    StudentAttempt firstAttempt = manager.createAttempt(testId, studentId, totalQuestions, time);
    cout << "ID bai thi: " << firstAttempt.getId() << endl;
    cout << "Ma bai kiem tra: " << firstAttempt.getTestId() << endl;
    cout << "Ma sinh vien: " << firstAttempt.getStudentId() << endl;
    cout << "So cau hoi: " << firstAttempt.getTotalQuestions() << endl;
    cout << "Thoi gian bat dau: " << firstAttempt.getStartsAt() << endl;

    // Đặt câu trả lời của sinh viên
    for (int i = 0; i < totalQuestions; i++)
    {
        int answer = i + 1; // Câu trả lời mẫu
        manager.setStudentAnswer(firstAttempt, i, answer);
    }
    cout << "Thoi gian ket thuc: " << firstAttempt.getFinishedAt() << endl;

    // Cập nhật điểm số
    firstAttempt.setCorrectAnswer();
    cout << "So cau tra loi dung: " << firstAttempt.getCorrectAnswer() << endl;

    // // Lưu thông tin vào file
    // manager.saveToFile();
    // cout << "Dữ liệu đã được lưu vào file studentAttempt.txt" << endl;

    // Tải lại dữ liệu từ file
    StudentAttemptManager newManager;
    // newManager.loadFromFile();
    cout << "Du lieu da duoc tai tu file studentAttempt.txt" << endl;

    // Hiển thị danh sách các bài thi của sinh viên
    int foundCount = 0;
    LinkList<StudentAttempt> attemptsByStudent = newManager.getAttemptsByStudentId(studentId, foundCount);
    cout << "So luong bai thi cua sinh vien " << studentId << ": " << foundCount << endl;
    for (int i = 0; i < foundCount; i++)
    {
        cout << "Bai thi " << i + 1 << ": " << attemptsByStudent[i].getId() << endl;
    }

    return 0; 
}
