#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>

#include "Candidate.h"

using namespace std;


/*
    ============================================================
                        CLASS FILE MANAGER
    ============================================================

    Lớp FileManager dùng để:

    1. Đọc danh sách thí sinh từ file.
    2. Ghi danh sách thí sinh vào file.


    Định dạng file:

    fullName|gender|examID|birthDate|hometown


    Ví dụ:

    Nguyen Van An|Nam|TS001|01/01/2005|Nghe An
*/

class FileManager
{
public:

    /*
        Đọc dữ liệu từ file.

        Nếu không truyền tên file
        thì mặc định sử dụng:

        candidates.txt
    */
    static vector<Candidate> loadFromFile(
        const string& filename =
        "candidates.txt"
    );


    /*
        Ghi dữ liệu vào file.

        Trả về:
        true  -> ghi thành công
        false -> ghi thất bại
    */
    static bool saveToFile(
        const vector<Candidate>& candidates,
        const string& filename =
        "candidates.txt"
    );


private:

    /*
        Tách một dòng thành nhiều phần
        dựa trên ký tự '|'.
    */
    static vector<string> split(
        const string& line,
        char delimiter
    );


    /*
        Xóa khoảng trắng ở đầu
        và cuối chuỗi.
    */
    static string trim(
        const string& text
    );
};

#endif
