#include "../include/Candidate.h"

#include <iomanip>
#include <iostream>

using namespace std;

void Candidate::display() const {
    cout << left
         << setw(25) << fullName
         << setw(10) << gender
         << setw(12) << examID
         << setw(15) << birthDate
         << hometown << '\n';
}

void Candidate::printHeader() {
    cout << left
         << setw(25) << "Full Name"
         << setw(10) << "Gender"
         << setw(12) << "Exam ID"
         << setw(15) << "Birth Date"
         << "Hometown\n";
}

void Candidate::printSeparator() {
    cout << string(80, '-') << '\n';
}
