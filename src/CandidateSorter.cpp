#include "../include/CandidateSorter.h"
#include "../include/Candidate.h"
#include <string>
#include <cctype>

using namespace std;

// Chuyển chuỗi thành chữ thường
static string toLowerString(const string& text) {
    string result = text;
    for (char& c : result) {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    return result;
}

// Lấy phần tên (từ cuối cùng trong họ tên)
string CandidateSorter::getFirstName(const string& fullName) {
    size_t pos = fullName.find_last_of(' ');
    return (pos == string::npos) ? fullName : fullName.substr(pos + 1);
}

// So sánh 2 thí sinh: Tên -> Họ tên đầy đủ -> Mã dự thi
bool CandidateSorter::compareCandidate(const Candidate& a, const Candidate& b) {
    string nameA = toLowerString(getFirstName(a.getFullName()));
    string nameB = toLowerString(getFirstName(b.getFullName()));
    if (nameA != nameB) return nameA < nameB;

    string fullNameA = toLowerString(a.getFullName());
    string fullNameB = toLowerString(b.getFullName());
    if (fullNameA != fullNameB) return fullNameA < fullNameB;

    return a.getExamID() < b.getExamID();
}

// Trộn hai đoạn đã sắp xếp [left...mid] và [mid+1...right]
void CandidateSorter::merge(vector<Candidate>& candidates, int left, int mid, int right) {
    vector<Candidate> temp;
    temp.reserve(right - left + 1);

    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (compareCandidate(candidates[i], candidates[j])) {
            temp.push_back(candidates[i++]);
        } else {
            temp.push_back(candidates[j++]);
        }
    }

    while (i <= mid) temp.push_back(candidates[i++]);
    while (j <= right) temp.push_back(candidates[j++]);

    for (size_t k = 0; k < temp.size(); ++k) {
        candidates[left + k] = temp[k];
    }
}

// Merge Sort đệ quy
void CandidateSorter::mergeSort(vector<Candidate>& candidates, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(candidates, left, mid);
    mergeSort(candidates, mid + 1, right);
    merge(candidates, left, mid, right);
}

// Hàm Wrapper chính cho Merge Sort
void CandidateSorter::mergeSort(vector<Candidate>& candidates) {
    if (candidates.size() <= 1) return;
    mergeSort(candidates, 0, static_cast<int>(candidates.size()) - 1);
}