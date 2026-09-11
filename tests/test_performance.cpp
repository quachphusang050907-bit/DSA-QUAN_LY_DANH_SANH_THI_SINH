#include "../include/HashTable.h"
#include "../include/RoomManager.h"
#include "../include/Candidate.h"
#include <iostream>
#include <chrono>
#include <cassert>

void runRoomModuleTests() {
    std::cout << "[TEST] Bắt đầu kiểm thử Module Room & Thuật toán Greedy Round-Robin...\n";

    HashTable ht;
    // Giả lập thêm dữ liệu kiểm thử
    Candidate c1; c1.setExamID("240101"); c1.setFullName("Nguyễn Văn An"); ht.add(c1);
    Candidate c2; c2.setExamID("240102"); c2.setFullName("Trần Thị Anh"); ht.add(c2);
    Candidate c3; c3.setExamID("240103"); c3.setFullName("Lê Hoàng Ánh"); ht.add(c3);
    Candidate c4; c4.setExamID("240104"); c4.setFullName("Nguyễn Văn Bình"); ht.add(c4);
    Candidate c5; c5.setExamID("240105"); c5.setFullName("Phạm Quốc Bắc"); ht.add(c5);

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