#pragma once
#include <vector>
#include <string>
#include "Candidate.h"

using namespace std;

/*
    ============================================================
                    CLASS CANDIDATE SORTER
    ============================================================

    Lớp CandidateSorter dùng để sắp xếp danh sách thí sinh.

    Quy tắc sắp xếp:
    1. Sắp xếp theo TÊN của thí sinh.
       Ví dụ:
       "Nguyen Van An" -> tên là "An"

    2. Nếu hai thí sinh trùng tên:
       -> So sánh họ tên đầy đủ.

    3. Nếu họ tên cũng giống nhau:
       -> So sánh mã dự thi.

    Thuật toán sử dụng:
    -> Merge Sort

    Độ phức tạp:
    -> O(n log n)
*/

class CandidateSorter
{
public:

    /*
        Hàm chính dùng để sắp xếp danh sách thí sinh.

        Tham số:
        candidates:
        -> Danh sách thí sinh cần sắp xếp.
    */
    static void mergeSort(
        vector<Candidate>& candidates
    );


private:

    /*
        Merge Sort đệ quy.

        left:
        -> Vị trí bắt đầu.

        right:
        -> Vị trí kết thúc.
    */
    static void mergeSort(
        vector<Candidate>& candidates,
        int left,
        int right
    );


    /*
        Hàm trộn hai đoạn đã được sắp xếp.
    */
    static void merge(
        vector<Candidate>& candidates,
        int left,
        int mid,
        int right
    );


    /*
        Lấy tên của thí sinh từ fullName.

        Ví dụ:
        "Nguyen Van An"
        -> "An"
    */
    static string getFirstName(
        const string& fullName
    );


    /*
        So sánh hai thí sinh.

        Trả về:
        true  -> a đứng trước b
        false -> a không đứng trước b
    */
    static bool compareCandidate(
        const Candidate& a,
        const Candidate& b
    );
};

