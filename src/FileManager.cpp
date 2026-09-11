#include "../include/FileManager.h"

#include <fstream>
#include <string>

using namespace std;


// ============================================================
// HÀM TRIM
// ============================================================
//
// Công dụng:
// Xóa khoảng trắng ở đầu và cuối chuỗi.
//
// Ví dụ:
//
// "   Nguyen Van An   "
//
// trở thành:
//
// "Nguyen Van An"
// ============================================================

string FileManager::trim(
    const string& text
)
{
    // Tìm ký tự đầu tiên
    // không phải khoảng trắng.

    size_t start =
        text.find_first_not_of(
            " \t\r\n"
        );


    // Nếu toàn bộ chuỗi
    // đều là khoảng trắng.

    if (start == string::npos)
    {
        return "";
    }


    // Tìm ký tự cuối cùng
    // không phải khoảng trắng.

    size_t end =
        text.find_last_not_of(
            " \t\r\n"
        );


    // Trả về chuỗi sau khi loại bỏ
    // khoảng trắng ở đầu và cuối.

    return text.substr(
        start,
        end - start + 1
    );
}


// ============================================================
// HÀM SPLIT
// ============================================================
//
// Công dụng:
// Tách một dòng thành nhiều phần.
//
// Ví dụ:
//
// Nguyen Van An|Nam|TS001|01/01/2005|Nghe An
//
// Sau khi split:
//
// [0] Nguyen Van An
// [1] Nam
// [2] TS001
// [3] 01/01/2005
// [4] Nghe An
// ============================================================

vector<string> FileManager::split(
    const string& line,
    char delimiter
)
{
    // Vector lưu các phần sau khi tách.
    vector<string> parts;


    // Biến tạm để lưu từng phần.
    string currentPart;


    // Duyệt từng ký tự trong dòng.
    for (char character : line)
    {
        // Nếu gặp ký tự '|'
        // thì kết thúc một phần.

        if (character == delimiter)
        {
            parts.push_back(
                trim(currentPart)
            );

            // Xóa dữ liệu cũ.
            currentPart.clear();
        }
        else
        {
            // Nếu không phải '|'
            // thì thêm ký tự vào phần hiện tại.

            currentPart += character;
        }
    }

    // Thêm phần cuối cùng.
    parts.push_back(
        trim(currentPart)
    );


    return parts;
}


// ============================================================
// HÀM LOAD FROM FILE
// ============================================================
//
// Công dụng:
// Đọc toàn bộ thí sinh từ candidates.txt.
//
// Quy trình:
//
// 1. Mở file.
// 2. Đọc từng dòng.
// 3. Kiểm tra dòng.
// 4. Tách dữ liệu bằng '|'. 
// 5. Tạo Candidate.
// 6. Thêm Candidate vào vector.
// 7. Trả về vector.
// ============================================================

vector<Candidate> FileManager::loadFromFile(
    const string& filename
)
{
    // Vector lưu danh sách thí sinh.
    vector<Candidate> candidates;


    // Mở file để đọc.
    ifstream inputFile(
        filename
    );


    // Nếu không mở được file
    // thì trả về danh sách rỗng.

    if (!inputFile.is_open())
    {
        return candidates;
    }


    string line;


    // --------------------------------------------------------
    // ĐỌC TỪNG DÒNG
    // --------------------------------------------------------

    while (
        getline(
            inputFile,
            line
        )
        )
    {
        // Bỏ qua dòng trống.

        if (
            trim(line).empty()
            )
        {
            continue;
        }


        // ----------------------------------------------------
        // TÁCH DÒNG
        // ----------------------------------------------------

        vector<string> parts =
            split(
                line,
                '|'
            );


        // ----------------------------------------------------
        // KIỂM TRA SỐ LƯỢNG THÔNG TIN
        // ----------------------------------------------------
        //
        // Một Candidate có 5 thông tin:
        //
        // 1. fullName
        // 2. gender
        // 3. examID
        // 4. birthDate
        // 5. hometown

        if (parts.size() != 5)
        {
            // Dòng sai định dạng
            // thì bỏ qua.

            continue;
        }


        // ----------------------------------------------------
        // TẠO CANDIDATE
        // ----------------------------------------------------

        Candidate candidate;


        // Gán từng thông tin.

        candidate.getFullName() =
            parts[0];

        candidate.getGender() =
            parts[1];

        candidate.getExamID() =
            parts[2];

        candidate.getBirthDate() =
            parts[3];

        candidate.getHometown() =
            parts[4];


        // ----------------------------------------------------
        // THÊM VÀO DANH SÁCH
        // ----------------------------------------------------

        candidates.push_back(
            candidate
        );
    }


    // Đóng file.
    inputFile.close();


    // Trả về danh sách thí sinh.
    return candidates;
}


// ============================================================
// HÀM SAVE TO FILE
// ============================================================
//
// Công dụng:
// Ghi toàn bộ danh sách thí sinh vào file.
//
// Quy trình:
//
// 1. Mở file.
// 2. Duyệt từng Candidate.
// 3. Ghi 5 thông tin.
// 4. Các thông tin cách nhau bằng '|'. 
// 5. Xuống dòng.
// 6. Đóng file.
// ============================================================

bool FileManager::saveToFile(
    const vector<Candidate>& candidates,
    const string& filename
)
{
    // Mở file để ghi.
    ofstream outputFile(
        filename
    );


    // Kiểm tra mở file.
    if (!outputFile.is_open())
    {
        return false;
    }


    // --------------------------------------------------------
    // GHI TỪNG THÍ SINH
    // --------------------------------------------------------

    for (
        const Candidate& candidate :
        candidates
        )
    {
        // Ghi theo đúng định dạng:
        //
        // fullName|gender|examID|birthDate|hometown

        outputFile
            << candidate.getFullName()
            << "|"
            << candidate.getGender()
            << "|"
            << candidate.getExamID()
            << "|"
            << candidate.getBirthDate()
            << "|"
            << candidate.getHometown()
            << '\n';
    }


    // Đóng file.
    outputFile.close();


    // Báo ghi thành công.
    return true;
}
