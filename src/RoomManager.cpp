#include "../include/RoomManager.h"
#include <iostream>
#include <iomanip>
#include <chrono>

bool RoomManager::distributeCandidates(const HashTable& hashTable, int numRooms) {
    // 1. Kiểm tra điều kiện đầu vào
    if (numRooms <= 0) {
        std::cout << "[Lỗi] Số lượng phòng thi phải lớn hơn 0!\n";
        return false;
    }

    rooms.clear();
    rooms.reserve(numRooms);
    for (int i = 0; i < numRooms; ++i) {
        rooms.emplace_back(i + 1); // Đánh số phòng từ 1 đến n
    }

    int currentRoomIndex = 0;
    int totalCandidates = 0;

    // 2. Duyệt qua 26 Bucket của Hash Table (Tương ứng nhóm 'A' -> 'Z')
    for (int i = 0; i < 26; ++i) {
        Node* curr = hashTable.getBucket(i); // Hàm lấy head LinkedList tại bucket i
        while (curr != nullptr) {
            // Thêm thí sinh vào phòng hiện tại
            rooms[currentRoomIndex].candidates.push_back(curr->data);
            
            // Xoay vòng phòng (Round-Robin)
            currentRoomIndex = (currentRoomIndex + 1) % numRooms;
            
            totalCandidates++;
            curr = curr->next;
        }
    }

    if (totalCandidates == 0) {
        std::cout << "[Cảnh báo] Hệ thống chưa có dữ liệu thí sinh nào!\n";
        return false;
    }

    if (numRooms > totalCandidates) {
        std::cout << "[Cảnh báo] Số lượng phòng lớn hơn tổng số thí sinh (" 
                  << totalCandidates << " thí sinh).\n";
    }

    return true;
}

void RoomManager::displayRooms() const {
    for (const auto& room : rooms) {
        std::cout << "\n=================== PHÒNG THI " << room.roomId 
                  << " (" << room.candidates.size() << " thí sinh) ===================\n";
        std::cout << std::left 
                  << std::setw(12) << "Mã ĐT" 
                  << std::setw(25) << "Họ và Tên" 
                  << std::setw(10) << "Giới tính" 
                  << std::setw(15) << "Ngày sinh" 
                  << "Quê quán\n";
        std::cout << std::string(75, '-') << "\n";

        for (const auto& cand : room.candidates) {
            std::cout << std::left 
                      << std::setw(12) << cand.examID 
                      << std::setw(25) << cand.fullName 
                      << std::setw(10) << cand.gender 
                      << std::setw(15) << cand.birthDate 
                      << cand.hometown << "\n";
        }
    }
}

// Hàm đánh giá mức độ xung đột (Conflict Score)
// Conflict = Số cặp thí sinh có cùng chữ cái đầu của Tên trong cùng một phòng
int RoomManager::calculateConflictScore() const {
    int totalConflicts = 0;

    for (const auto& room : rooms) {
        int letterCounts[26] = {0};

        // Đếm số lượng thí sinh của mỗi chữ cái đầu trong phòng này
        for (const auto& cand : room.candidates) {
            char firstLetter = cand.getFirstNameInitial(); // Hoặc logic trích xuất ký tự đầu
            if (firstLetter >= 'A' && firstLetter <= 'Z') {
                letterCounts[firstLetter - 'A']++;
            }
        }

        // Với mỗi nhóm k thí sinh trùng chữ cái đầu, số cặp xung đột là k*(k-1)/2
        for (int i = 0; i < 26; ++i) {
            int count = letterCounts[i];
            if (count > 1) {
                totalConflicts += (count * (count - 1)) / 2;
            }
        }
    }

    return totalConflicts;
}

void RoomManager::printPerformanceReport(double executionTimeMs) const {
    std::cout << "\n---------------- BÁO CÁO HIỆU NĂNG VÀ CONFLICT ----------------\n";
    std::cout << "Thời gian thực thi thuật toán chia phòng: " << std::fixed << std::setprecision(4) 
              << executionTimeMs << " ms\n";
    std::cout << "Tổng số phòng thi: " << rooms.size() << "\n";
    std::cout << "Chỉ số xung đột (Total Conflict Score): " << calculateConflictScore() 
              << " (Càng thấp càng tối ưu)\n";
    std::cout << "---------------------------------------------------------------\n";
}