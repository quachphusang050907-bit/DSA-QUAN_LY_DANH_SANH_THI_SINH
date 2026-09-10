#pragma once
#include "HashTable.h"


//  Class GroupManager – Hiển thị danh sách thí sinh theo nhóm chữ cái đầu
//  (Đọc trực tiếp từ các bucket của Hash Table)

class GroupManager {
public:
    // Hiển thị tất cả nhóm A-Z (chỉ in nhóm có thí sinh)
    static void displayAllGroups(const HashTable& ht);

    // Hiển thị một nhóm cụ thể theo chữ cái (vd: 'A')
    static void displayGroup(const HashTable& ht, char letter);
};


