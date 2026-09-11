#include "../include/CandidateManager.h"
#include "../include/HashTable.h"
#include <iostream>
#include <limits>
#include <cctype>

using namespace std;
// ======================================================
// VALIDATION FUNCTIONS
// ======================================================
bool isValidName(const string& text)
{
    if (text.empty())
        return false;

    bool hasLetter = false;

    for (char c : text)
    {
        if (isalpha(static_cast<unsigned char>(c)))
        {
            hasLetter = true;
        }
        else if (c != ' ')
        {
            return false;
        }
    }

    return hasLetter;
}

bool isValidGender(const string& text)
{
    if (text.empty())
        return false;

    for (char c : text)
    {
        if (!isalpha(static_cast<unsigned char>(c)))
            return false;
    }

    return true;
}

bool isValidExamID(const string& text)
{
    if (text.empty())
        return false;

    for (char c : text)
    {
        if (!isalnum(static_cast<unsigned char>(c)))
            return false;
    }

    return true;
}

bool isLeapYear(int year)
{
    return (year % 400 == 0) ||
        (year % 4 == 0 && year % 100 != 0);
}

bool isValidBirthDate(const string& text)
{
    if (text.length() != 10)
        return false;

    if (text[2] != '/' || text[5] != '/')
        return false;

    for (int i = 0; i < 10; i++)
    {
        if (i == 2 || i == 5)
            continue;

        if (!isdigit(static_cast<unsigned char>(text[i])))
            return false;
    }

    int day =
        (text[0] - '0') * 10 +
        (text[1] - '0');

    int month =
        (text[3] - '0') * 10 +
        (text[4] - '0');

    int year =
        (text[6] - '0') * 1000 +
        (text[7] - '0') * 100 +
        (text[8] - '0') * 10 +
        (text[9] - '0');

    if (year < 1900)
        return false;

    if (month < 1 || month > 12)
        return false;

    int daysInMonth[] =
    {
        31, 28, 31, 30,
        31, 30, 31, 31,
        30, 31, 30, 31
    };

    if (month == 2 && isLeapYear(year))
        daysInMonth[1] = 29;

    if (day < 1 || day > daysInMonth[month - 1])
        return false;

    return true;
}

// ======================================================
// ADD CANDIDATE
// ======================================================

bool CandidateManager::addCandidate()
{
    Candidate candidate;
    string input;

    // --------------------------------------------------
    // EXAM ID
    // --------------------------------------------------
    while (true)
    {
        cout << "Exam ID: ";
        cin >> ws;
        getline(cin, input);

        if (!isValidExamID(input))
        {
            cout << "Invalid Exam ID! "
                << "Only letters and numbers are allowed.\n";
            continue;
        }

        if (hashTable.findByID(input) != nullptr)
        {
            cout << "Exam ID already exists! "
                << "Please enter another Exam ID.\n";
            continue;
        }

        candidate.setExamID(input);
        break;
    }

    // --------------------------------------------------
    // FULL NAME
    // --------------------------------------------------
    while (true)
    {
        cout << "Full name: ";
        getline(cin, input);

        if (!isValidName(input))
        {
            cout << "Invalid full name! "
                << "Only letters and spaces are allowed.\n";
            continue;
        }

        candidate.setFullName(input);
        break;
    }

    // --------------------------------------------------
    // GENDER
    // --------------------------------------------------
    while (true)
    {
        cout << "Gender: ";
        getline(cin, input);

        if (!isValidGender(input))
        {
            cout << "Invalid gender! "
                << "Only letters are allowed.\n";
            continue;
        }

        candidate.setGender(input);
        break;
    }

    // --------------------------------------------------
    // BIRTH DATE
    // --------------------------------------------------
    while (true)
    {
        cout << "Birth date (DD/MM/YYYY): ";
        getline(cin, input);

        if (!isValidBirthDate(input))
        {
            cout << "Invalid birth date! "
                << "Please enter a valid date in DD/MM/YYYY format.\n";
            continue;
        }

        candidate.setBirthDate(input);
        break;
    }

    // --------------------------------------------------
    // HOMETOWN
    // --------------------------------------------------
    while (true)
    {
        cout << "Hometown: ";
        getline(cin, input);

        if (!isValidName(input))
        {
            cout << "Invalid hometown! "
                << "Only letters and spaces are allowed.\n";
            continue;
        }

        candidate.setHometown(input);
        break;
    }

    return addCandidate(candidate);
}

// ======================================================
// ADD CANDIDATE TO HASH TABLE
// ======================================================

bool CandidateManager::addCandidate(const Candidate& candidate)
{
    return hashTable.add(candidate);
}

// ======================================================
// SEARCH BY EXAM ID
// ======================================================

Candidate* CandidateManager::searchCandidate()
{
    string examID;

    cout << "Enter exam ID: ";
    cin >> examID;

    return hashTable.findByID(examID);
}

Candidate* CandidateManager::searchCandidate(const string& examID)
{
    return hashTable.findByID(examID);
}

// ======================================================
// SEARCH BY NAME
// ======================================================

vector<Candidate> CandidateManager::searchCandidatesByName(
    const string& keyword) const
{
    return hashTable.findByName(keyword);
}