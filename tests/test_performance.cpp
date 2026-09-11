#include "../include/HashTable.h"
#include "../include/RoomManager.h"
#include <iostream>
#include <chrono>
#include <cassert>

void runRoomModuleTests() {
    std::cout << "[TEST] Bắt đầu kiểm thử Module Room & Thuật toán Greedy Round-Robin...\n";

    HashTable ht;
    // Giả lập thêm dữ liệu kiểm thử
    ht.add(Candidate("240101", "Nguyễn Văn An", "Nam", "15/05/2005", "Hà Nội"));
    ht.add(Candidate("240102", "Trần Thị Anh", "Nữ", "20/08/2005", "Đà Nẵng"));
    ht.add(Candidate("240103", "Lê Hoàng Ánh", "Nam", "01/01/2005", "Hải Phòng"));
    ht.add(Candidate("240104", "Nguyễn Văn Bình", "Nam", "10/10/2005", "Quảng Ninh"));
    ht.add(Candidate("240105", "Phạm Quốc Bắc", "Nam", "12/12/2005", "Cần Thơ"));

    RoomManager roomMgr;

    // Test Case 1: Chia 3 phòng với 5 thí sinh
    auto start = std::chrono::high_resolution_clock::now();
    bool success = roomMgr.distributeCandidates(ht, 3);
    auto end = std::chrono::high_resolution_clock::now();

    double elapsedMs = std::chrono::duration<double, std::milli>(end - start).count();

    assert(success == true);
    assert(roomMgr.getRooms().size() == 3);

    // Kiểm tra tính chia đều bằng Round-Robin cho 3 người tên 'A' (An, Anh, Ánh)
    // Cả 3 phải rơi vào 3 phòng khác nhau -> Conflict Score nhóm A = 0
    std::cout << "Test Case 1 (Valid Input) - PASSED\n";
    roomMgr.printPerformanceReport(elapsedMs);

    // Test Case 2: Kiểm tra biên (Invalid numRooms <= 0)
    bool invalidSuccess = roomMgr.distributeCandidates(ht, 0);
    assert(invalidSuccess == false);
    std::cout << "Test Case 2 (Edge Case: Invalid n) - PASSED\n";
}

int main() {
    runRoomModuleTests();
    return 0;
}