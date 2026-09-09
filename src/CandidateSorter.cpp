#include "CandidateSorter.h"

#include <string>
#include <cctype>

using namespace std;


// ============================================================
// HÀM CHUYỂN CHUỖI THÀNH CHỮ THƯỜNG
// ============================================================
//
// Mục đích:
// Giúp việc so sánh không phụ thuộc chữ hoa hay chữ thường.
//
// Ví dụ:
// "AN" -> "an"
// "An" -> "an"
// ============================================================

string toLowerString(
    const string& text
)
{
    string result = text;

    for (size_t i = 0; i < result.length(); i++)
    {
        result[i] = static_cast<char>(
            tolower(
                static_cast<unsigned char>(result[i])
            )
            );
    }

    return result;
}


// ============================================================
// HÀM LẤY TÊN
// ============================================================
//
// Ví dụ:
//
// fullName = "Nguyen Van An"
//
// Kết quả:
// "An"
//
// Vì "An" là phần cuối cùng của họ tên.
// ============================================================

string CandidateSorter::getFirstName(
    const string& fullName
)
{
    // Tìm dấu cách cuối cùng.
    size_t position = fullName.find_last_of(' ');


    // Nếu không tìm thấy dấu cách
    // thì xem toàn bộ chuỗi là tên.
    if (position == string::npos)
    {
        return fullName;
    }


    // Lấy phần phía sau dấu cách cuối cùng.
    return fullName.substr(
        position + 1
    );
}


// ============================================================
// HÀM SO SÁNH HAI THÍ SINH
// ============================================================
//
// Thứ tự ưu tiên:
//
// Bước 1:
// So sánh tên.
//
// Bước 2:
// Nếu trùng tên -> so sánh họ tên đầy đủ.
//
// Bước 3:
// Nếu vẫn trùng -> so sánh mã dự thi.
// ============================================================

bool CandidateSorter::compareCandidate(
    const Candidate& a,
    const Candidate& b
)
{
    // --------------------------------------------------------
    // BƯỚC 1: LẤY TÊN
    // --------------------------------------------------------

    string nameA =
        toLowerString(
            getFirstName(a.fullName)
        );

    string nameB =
        toLowerString(
            getFirstName(b.fullName)
        );


    // --------------------------------------------------------
    // Nếu tên khác nhau
    // -> sắp xếp theo tên.
    // --------------------------------------------------------

    if (nameA != nameB)
    {
        return nameA < nameB;
    }


    // --------------------------------------------------------
    // BƯỚC 2:
    // Nếu cùng tên thì so sánh họ tên đầy đủ.
    // --------------------------------------------------------

    string fullNameA =
        toLowerString(a.fullName);

    string fullNameB =
        toLowerString(b.fullName);


    if (fullNameA != fullNameB)
    {
        return fullNameA < fullNameB;
    }


    // --------------------------------------------------------
    // BƯỚC 3:
    // Nếu họ tên giống nhau
    // -> so sánh mã dự thi.
    // --------------------------------------------------------

    return a.examID < b.examID;
}


// ============================================================
// HÀM MERGE
// ============================================================
//
// Hàm này dùng để trộn:
//
// Đoạn bên trái:
// [left ... mid]
//
// Đoạn bên phải:
// [mid + 1 ... right]
//
// Hai đoạn đã được sắp xếp trước đó.
// ============================================================

void CandidateSorter::merge(
    vector<Candidate>& candidates,
    int left,
    int mid,
    int right
)
{
    // Vector tạm dùng để lưu kết quả sau khi trộn.
    vector<Candidate> temp;


    // i dùng để duyệt nửa bên trái.
    int i = left;


    // j dùng để duyệt nửa bên phải.
    int j = mid + 1;


    // --------------------------------------------------------
    // SO SÁNH HAI NỬA
    // --------------------------------------------------------

    while (
        i <= mid &&
        j <= right
        )
    {
        // Nếu phần tử bên trái nhỏ hơn
        // hoặc đứng trước phần tử bên phải.
        if (
            compareCandidate(
                candidates[i],
                candidates[j]
            )
            )
        {
            temp.push_back(
                candidates[i]
            );

            i++;
        }
        else
        {
            // Ngược lại lấy phần tử bên phải.
            temp.push_back(
                candidates[j]
            );

            j++;
        }
    }


    // --------------------------------------------------------
    // ĐƯA CÁC PHẦN TỬ CÒN LẠI BÊN TRÁI
    // --------------------------------------------------------

    while (i <= mid)
    {
        temp.push_back(
            candidates[i]
        );

        i++;
    }


    // --------------------------------------------------------
    // ĐƯA CÁC PHẦN TỬ CÒN LẠI BÊN PHẢI
    // --------------------------------------------------------

    while (j <= right)
    {
        temp.push_back(
            candidates[j]
        );

        j++;
    }


    // --------------------------------------------------------
    // CHÉP KẾT QUẢ TỪ TEMP VỀ MẢNG BAN ĐẦU
    // --------------------------------------------------------

    for (
        int k = 0;
        k < static_cast<int>(temp.size());
        k++
        )
    {
        candidates[left + k] =
            temp[k];
    }
}


// ============================================================
// MERGE SORT ĐỆ QUY
// ============================================================
//
// Ý tưởng:
//
// 1. Chia danh sách thành 2 phần.
//
// 2. Tiếp tục chia mỗi phần thành 2.
//
// 3. Khi mỗi phần chỉ còn 1 phần tử
//    thì bắt đầu trộn lại.
//
// 4. Sau khi trộn xong
//    danh sách sẽ được sắp xếp.
// ============================================================

void CandidateSorter::mergeSort(
    vector<Candidate>& candidates,
    int left,
    int right
)
{
    // --------------------------------------------------------
    // ĐIỀU KIỆN DỪNG
    // --------------------------------------------------------
    //
    // Nếu đoạn chỉ có 1 phần tử
    // thì không cần sắp xếp.

    if (left >= right)
    {
        return;
    }


    // --------------------------------------------------------
    // TÌM VỊ TRÍ GIỮA
    // --------------------------------------------------------

    int mid =
        left + (right - left) / 2;


    // --------------------------------------------------------
    // SẮP XẾP NỬA BÊN TRÁI
    // --------------------------------------------------------

    mergeSort(
        candidates,
        left,
        mid
    );


    // --------------------------------------------------------
    // SẮP XẾP NỬA BÊN PHẢI
    // --------------------------------------------------------

    mergeSort(
        candidates,
        mid + 1,
        right
    );


    // --------------------------------------------------------
    // TRỘN HAI NỬA LẠI
    // --------------------------------------------------------

    merge(
        candidates,
        left,
        mid,
        right
    );
}


// ============================================================
// HÀM MERGE SORT CHÍNH
// ============================================================
//
// Đây là hàm mà CandidateManager có thể gọi:
//
// CandidateSorter::mergeSort(candidates);
//
// Người dùng không cần quan tâm đến left và right.
// ============================================================

void CandidateSorter::mergeSort(
    vector<Candidate>& candidates
)
{
    // Nếu danh sách rỗng
    // hoặc chỉ có 1 thí sinh
    // thì không cần sắp xếp.

    if (candidates.size() <= 1)
    {
        return;
    }


    // Gọi Merge Sort từ phần tử đầu
    // đến phần tử cuối.

    mergeSort(
        candidates,
        0,
        static_cast<int>(
            candidates.size()
            ) - 1
    );
}
