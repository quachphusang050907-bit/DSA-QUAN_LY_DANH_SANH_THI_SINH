#pragma once
#include "Candidate.h"
#include <vector>
// Lớp Room đại diện cho một phòng thi
struct Room {
    int roomId; // mã định danh phòng thi
    std::vector<Candidate> candidates; // danh sách thí sinh trong phòng thi

    explicit Room(int id = 0) : roomId(id) {} // khởi tạo phòng thi với mã định danh mặc định 
};


