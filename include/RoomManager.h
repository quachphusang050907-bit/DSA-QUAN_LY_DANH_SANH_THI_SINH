#pragma once

#include <string>
#include <vector>
#include "Candidate.h"

/**
 * @brief Lớp hỗ trợ đọc/ghi dữ liệu danh sách thí sinh từ/vào file text.
 * 
 * Định dạng dòng dữ liệu: fullName|gender|examID|birthDate|hometown
 * Ví dụ: Nguyen Van An|Nam|TS001|01/01/2005|Nghe An
 */
class FileManager {
public:
    // Đọc danh sách thí sinh từ file
    static std::vector<Candidate> loadFromFile(const std::string& filename = "candidates.txt");

    // Ghi danh sách thí sinh vào file (trả về true nếu thành công)
    static bool saveToFile(const std::vector<Candidate>& candidates, const std::string& filename = "candidates.txt");

private:
    // Tách chuỗi theo ký tự phân cách delimiter
    static std::vector<std::string> split(const std::string& line, char delimiter);

    // Cắt bỏ khoảng trắng ở hai đầu chuỗi
    static std::string trim(const std::string& text);
};