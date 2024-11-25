#include "TestQuestionSelection.h"

int main() {
    // Khởi tạo TestQuestionSelectionManager
    TestQuestionSelectionManager manager;

    // Thêm một số TestQuestionSelection
    manager.addTestQuestionSelection("TID001", "CHA001", 10);
    manager.addTestQuestionSelection("TID002", "CHA002", 10);
    manager.addTestQuestionSelection("TID003", "CHA001", 20);
    
    cout << "Added 3 TestQuestionSelections" << endl;

    // Hiển thị danh sách TestQuestionSelection
    for (int i = 0; i < manager.getCount(); i++) {
        TestQuestionSelection tqs = manager.getTestQuestionSelectionAt(i);
        cout << "ID: " << tqs.getId() 
             << ", Test ID: " << tqs.getTestId() 
             << ", Chapter ID: " << tqs.getChapterId() 
             << ", Number of Questions: " << tqs.getNumberOfQuestions() << endl;
    }

    // Cập nhật một TestQuestionSelection
    cout << "\nUpdating TestQuestionSelection with ID 'TQS001'..." << endl;
    manager.updateTestQuestionSelection("TQS001", "Test01", "Chapter03", 25);

    // Kiểm tra lại sau khi cập nhật
    TestQuestionSelection updatedTQS = manager.getTestQuestionSelection("TQS001");
    cout << "Updated TestQuestionSelection: "
         << "ID: " << updatedTQS.getId() 
         << ", Test ID: " << updatedTQS.getTestId() 
         << ", Chapter ID: " << updatedTQS.getChapterId() 
         << ", Number of Questions: " << updatedTQS.getNumberOfQuestions() << endl;

    // Xóa một TestQuestionSelection
    cout << "\nDeleting TestQuestionSelection with ID 'TQS002'..." << endl;
    manager.deleteTestQuestionSelection("TQS002");

    // Kiểm tra lại sau khi xóa
    cout << "\nRemaining TestQuestionSelections:" << endl;
    for (int i = 0; i < manager.getCount(); i++) {
        TestQuestionSelection tqs = manager.getTestQuestionSelectionAt(i);
        cout << "ID: " << tqs.getId() 
             << ", Test ID: " << tqs.getTestId() 
             << ", Chapter ID: " << tqs.getChapterId() 
             << ", Number of Questions: " << tqs.getNumberOfQuestions() << endl;
    }

    // Lấy tất cả TestQuestionSelections theo Test ID
    cout << "\nGetting TestQuestionSelections by Test ID 'Test01'..." << endl;
    int count = 0;
    TestQuestionSelection* selectionsByTestId = manager.getTestQuestionSelectionByTestId("Test01", count);
    for (int i = 0; i < count; i++) {
        TestQuestionSelection tqs = selectionsByTestId[i];
        cout << "ID: " << tqs.getId() 
             << ", Test ID: " << tqs.getTestId() 
             << ", Chapter ID: " << tqs.getChapterId() 
             << ", Number of Questions: " << tqs.getNumberOfQuestions() << endl;
    }

    // Giải phóng bộ nhớ đã cấp phát động
    delete[] selectionsByTestId;

    return 0;
}
