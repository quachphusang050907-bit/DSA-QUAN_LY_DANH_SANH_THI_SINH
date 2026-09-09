#pragma once
#include "Room.h"
#include "HashTable.h"
#include <vector>
#include <iostream>

class RoomManager {
private:
    std::vector<Room> rooms;

public:
    RoomManager() = default;

    // Chức năng chính: Chia thí sinh vào n phòng bằng Round-Robin (Greedy)
    bool distributeCandidates(const HashTable& hashTable, int numRooms);

    // Hiển thị danh sách các phòng
    void displayRooms() const;

    // Đánh giá Conflict Score (Số cặp thí sinh trùng chữ cái đầu tên trong cùng 1 phòng)
    int calculateConflictScore() const;

    // Báo cáo chi tiết hiệu năng & mức độ phân bổ
    void printPerformanceReport(double executionTimeMs) const;

    const std::vector<Room>& getRooms() const { return rooms; }
};


