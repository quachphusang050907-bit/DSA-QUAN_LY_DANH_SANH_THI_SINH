#pragma once
#include <string>

using namespace std;

struct Candidate {
    std::string fullName;
    std::string gender;
    std::string examID;
    std::string birthDate;
    std::string hometown;

    void display() const;
    static void printHeader();
    static void printSeparator();
};
