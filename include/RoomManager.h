#pragma once
#include "Room.h"
#include "HashTable.h"
#include <vector>
#include <iostream>

class RoomManager {
private:
    std::vector<Room> rooms; // danh sách các phòng thi được quản lý

public:
    RoomManager() = default;

    // phân bố thí sinh vào n phòng bằng Round-Robin (Greedy)
    bool distributeCandidates(const HashTable& hashTable, int numRooms);

    // danh sách các phòng
    void displayRooms() const;

    // tính toán điểm xung đột 
    int calculateConflictScore() const;

    // Báo cáo chi tiết hiệu năng & mức độ phân bổ
    void printPerformanceReport(double executionTimeMs) const;

    const std::vector<Room>& getRooms() const { return rooms; }
};


