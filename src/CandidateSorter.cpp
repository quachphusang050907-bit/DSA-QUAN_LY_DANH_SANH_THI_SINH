#include "../include/CandidateSorter.h"
#include <cctype>

using namespace std;

namespace {
    // Hàm nội bộ: Chuyển chuỗi thành chữ thường để so sánh không phân biệt hoa/thường
    string toLowerString(const string& text) {
        string result = text;
        for (char& c : result) {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }
        return result;
    }
}

string CandidateSorter::getFirstName(const string& fullName) {
    size_t position = fullName.find_last_of(' ');
    if (position == string::npos) {
        return fullName;
    }
    return fullName.substr(position + 1);
}

bool CandidateSorter::compareCandidate(const Candidate& a, const Candidate& b) {
    // 1. So sánh Tên
    string nameA = toLowerString(getFirstName(a.getFullName()));
    string nameB = toLowerString(getFirstName(b.getFullName()));
    if (nameA != nameB) {
        return nameA < nameB;
    }

    // 2. So sánh Họ tên đầy đủ
    string fullNameA = toLowerString(a.getFullName());
    string fullNameB = toLowerString(b.getFullName());
    if (fullNameA != fullNameB) {
        return fullNameA < fullNameB;
    }

    // 3. So sánh Mã dự thi
    return a.getExamID() < b.getExamID();
}

void CandidateSorter::merge(vector<Candidate>& candidates, int left, int mid, int right) {
    vector<Candidate> temp;
    temp.reserve(right - left + 1); // Cấp phát tĩnh bộ nhớ để tối ưu hiệu năng

    int i = left;
    int j = mid + 1;

    // Trộn hai nửa đã sắp xếp
    while (i <= mid && j <= right) {
        if (compareCandidate(candidates[i], candidates[j])) {
            temp.push_back(candidates[i++]);
        } else {
            temp.push_back(candidates[j++]);
        }
    }

    // Đưa các phần tử còn lại của 2 nửa vào temp
    while (i <= mid) {
        temp.push_back(candidates[i++]);
    }
    while (j <= right) {
        temp.push_back(candidates[j++]);
    }

    // Ghi ngược kết quả từ temp về mảng chính
    for (size_t k = 0; k < temp.size(); ++k) {
        candidates[left + k] = temp[k];
    }
}

void CandidateSorter::mergeSort(vector<Candidate>& candidates, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    mergeSort(candidates, left, mid);
    mergeSort(candidates, mid + 1, right);
    merge(candidates, left, mid, right);
}

void CandidateSorter::mergeSort(vector<Candidate>& candidates) {
    if (candidates.size() <= 1) {
        return;
    }
    mergeSort(candidates, 0, static_cast<int>(candidates.size()) - 1);
}