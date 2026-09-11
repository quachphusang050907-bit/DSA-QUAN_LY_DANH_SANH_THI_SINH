#pragma once

#include <vector>
#include <string>
#include "Candidate.h"

/**
 * @brief Lớp hỗ trợ sắp xếp danh sách thí sinh bằng thuật toán Merge Sort.
 * 
 * Quy tắc ưu tiên: 1. Tên -> 2. Họ và tên đầy đủ -> 3. Mã dự thi
 * Độ phức tạp: O(n log n)
 */
class CandidateSorter {
public:
    // Sắp xếp toàn bộ danh sách thí sinh
    static void mergeSort(std::vector<Candidate>& candidates);

private:
    // Merge Sort đệ quy trên đoạn [left, right]
    static void mergeSort(std::vector<Candidate>& candidates, int left, int right);

    // Trộn hai đoạn đã sắp xếp [left...mid] và [mid+1...right]
    static void merge(std::vector<Candidate>& candidates, int left, int mid, int right);

    // Trích xuất tên từ họ tên đầy đủ (ví dụ: "Nguyen Van An" -> "An")
    static std::string getFirstName(const std::string& fullName);

    // So sánh hai thí sinh (trả về true nếu a đứng trước b)
    static bool compareCandidate(const Candidate& a, const Candidate& b);
};