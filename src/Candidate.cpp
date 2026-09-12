#include "../include/Candidate.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// ==================== SETTER ====================

void Candidate::setFullName(const string& fullName)
{
    this->fullName = fullName;
}

void Candidate::setGender(const string& gender)
{
    this->gender = gender;
}

void Candidate::setExamID(const string& examID)
{
    this->examID = examID;
}

void Candidate::setBirthDate(const string& birthDate)
{
    this->birthDate = birthDate;
}

void Candidate::setHometown(const string& hometown)
{
    this->hometown = hometown;
}


// ==================== GETTER ====================

string Candidate::getFullName() const
{
    return fullName;
}

string Candidate::getGender() const
{
    return gender;
}

string Candidate::getExamID() const
{
    return examID;
}

string Candidate::getBirthDate() const
{
    return birthDate;
}

string Candidate::getHometown() const
{
    return hometown;
}


// ==================== DISPLAY ====================

// Hàm đếm số ký tự UTF-8 thực tế (không phải số byte)
size_t utf8_length(const std::string& str) {
    size_t len = 0;
    for (char c : str) {
        if ((c & 0xC0) != 0x80) { // Bắt đầu một ký tự UTF-8
            len++;
        }
    }
    return len;
}

void Candidate::display() const
{
    // Tính khoảng bù byte cho từng chuỗi tiếng Việt
    int padName     = 35 + (fullName.length() - utf8_length(fullName));
    int padGender   = 12 + (gender.length() - utf8_length(gender));
    int padExamID   = 15 + (examID.length() - utf8_length(examID));
    int padBirth    = 18 + (birthDate.length() - utf8_length(birthDate));

    std::cout << std::left
              << std::setw(padName) << fullName 
              << std::setw(padGender) << gender     
              << std::setw(padExamID) << examID      
              << std::setw(padBirth) << birthDate   
              << hometown << '\n';
}

void Candidate::printHeader()
{
    cout << left
         << setw(35) << "Full Name"
         << setw(12) << "Gender"
         << setw(15) << "Exam ID"
         << setw(18) << "Birth Date"
         << "Hometown\n";
}

void Candidate::printSeparator()
{
    cout << string(100, '-') << '\n'; 
}