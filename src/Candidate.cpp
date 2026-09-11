#include "../include/Candidate.h"

#include <iomanip>
#include <iostream>

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

void Candidate::display() const
{
    cout << left
        << setw(25) << fullName
        << setw(10) << gender
        << setw(12) << examID
        << setw(15) << birthDate
        << hometown << '\n';
}

void Candidate::printHeader()
{
    cout << left
        << setw(25) << "Full Name"
        << setw(10) << "Gender"
        << setw(12) << "Exam ID"
        << setw(15) << "Birth Date"
        << "Hometown\n";
}

void Candidate::printSeparator()
{
    cout << string(80, '-') << '\n';
}