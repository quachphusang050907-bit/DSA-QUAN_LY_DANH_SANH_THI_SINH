#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>

using namespace std;

class Candidate
{
private:
    string fullName;
    string gender;
    string examID;
    string birthDate;
    string hometown;

public:
    // Setter
    void setFullName(const string& fullName);
    void setGender(const string& gender);
    void setExamID(const string& examID);
    void setBirthDate(const string& birthDate);
    void setHometown(const string& hometown);

    // Getter
    string getFullName() const;
    string getGender() const;
    string getExamID() const;
    string getBirthDate() const;
    string getHometown() const;

    void display() const;
    static void printHeader();
    static void printSeparator();
};

#endif
