#include "GroupManager.h"       // Include GroupManager
#include <iostream>
#include <iomanip>
using namespace std;


// Hiển thị tất cả nhóm có thí sinh 
void GroupManager::displayAllGroups(const HashTable& ht) {

    cout << "\nDANH SACH THI SINH THEO NHOM CHU CAI DAU\n";
    // In tiêu đề

    bool anyGroup = false;                  // Kiểm tra có nhóm nào có thí sinh

    for (int i = 0; i < HashTable::TABLE_SIZE; i++) { // Duyệt các bucket
        const LinkedList& bucket = ht.getBucket(i);   // Lấy bucket hiện tại

        if (bucket.isEmpty()) continue;                // Nhóm rỗng → bỏ qua
        anyGroup = true;                               // Có nhóm có dữ liệu

        char letter = (char)('A' + i);                 // Đổi chỉ số thành chữ cái

        cout << "\nNhom [" << letter << "] - "
             << bucket.getCount() << " thi sinh\n";
        // In tên nhóm và số lượng thí sinh

        Candidate::printHeader();          // In tiêu đề bảng
        bucket.display();                   // Hiển thị thí sinh
        Candidate::printSeparator();       // In đường phân cách
    }

    if (!anyGroup)
        cout << "  (Chua co thi sinh nao trong he thong)\n";
        // Không có thí sinh → thông báo

    cout << "\nTong cong: " << ht.getTotalCount() << " thi sinh.\n";
    // In tổng số thí sinh
}


// Hiển thị nhóm cụ thể theo chữ cái 
void GroupManager::displayGroup(const HashTable& ht, char letter) {

    letter = toupper((unsigned char)letter); // Đổi chữ cái thành chữ hoa

    if (letter < 'A' || letter > 'Z') {       // Kiểm tra chữ cái hợp lệ
        cout << "  Chu cai khong hop le!\n";
        return;
    }

    int idx = letter - 'A';                   // Đổi A-Z thành chỉ số 0-25

    const LinkedList& bucket = ht.getBucket(idx); // Lấy bucket tương ứng

    cout << "\nNhom [" << letter << "] - "
         << bucket.getCount() << " thi sinh\n";
    // In tên nhóm và số lượng

    if (bucket.isEmpty()) {
        cout << "  (Khong co thi sinh nao trong nhom nay)\n";
        return;
    }
    // Nhóm rỗng → thông báo rồi thoát

    Candidate::printHeader();                 // In tiêu đề bảng
    bucket.display();                         // Hiển thị thí sinh
    Candidate::printSeparator();              // In đường phân cách
}