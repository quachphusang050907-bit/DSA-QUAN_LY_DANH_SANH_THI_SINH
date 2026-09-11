#include "../include/CandidateManager.h"
#include "../include/HashTable.h"
#include "../include/CandidateSorter.h"
#include "../include/GroupManager.h"
#include "../include/RoomManager.h"
#include "../include/FileManager.h"

#include <iostream>
#include <limits>
#include <cctype>
#include <chrono>

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

    int day = (text[0] - '0') * 10 + (text[1] - '0');
    int month = (text[3] - '0') * 10 + (text[4] - '0');
    int year = (text[6] - '0') * 1000 + (text[7] - '0') * 100 + (text[8] - '0') * 10 + (text[9] - '0');

    if (year < 1900)
        return false;

    if (month < 1 || month > 12)
        return false;

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

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

    while (true)
    {
        cout << "Exam ID: ";
        cin >> ws;
        getline(cin, input);

        if (!isValidExamID(input))
        {
            cout << "Invalid Exam ID! Only letters and numbers are allowed.\n";
            continue;
        }

        if (hashTable.findByID(input) != nullptr)
        {
            cout << "Exam ID already exists! Please enter another Exam ID.\n";
            continue;
        }

        candidate.setExamID(input);
        break;
    }

    while (true)
    {
        cout << "Full name: ";
        getline(cin, input);

        if (!isValidName(input))
        {
            cout << "Invalid full name! Only letters and spaces are allowed.\n";
            continue;
        }

        candidate.setFullName(input);
        break;
    }

    while (true)
    {
        cout << "Gender: ";
        getline(cin, input);

        if (!isValidGender(input))
        {
            cout << "Invalid gender! Only letters are allowed.\n";
            continue;
        }

        candidate.setGender(input);
        break;
    }

    while (true)
    {
        cout << "Birth date (DD/MM/YYYY): ";
        getline(cin, input);

        if (!isValidBirthDate(input))
        {
            cout << "Invalid birth date! Please enter a valid date in DD/MM/YYYY format.\n";
            continue;
        }

        candidate.setBirthDate(input);
        break;
    }

    while (true)
    {
        cout << "Hometown: ";
        getline(cin, input);

        if (!isValidName(input))
        {
            cout << "Invalid hometown! Only letters and spaces are allowed.\n";
            continue;
        }

        candidate.setHometown(input);
        break;
    }

    return addCandidate(candidate);
}

bool CandidateManager::addCandidate(const Candidate& candidate)
{
    return hashTable.add(candidate);
}

// ======================================================
// SEARCH CANDIDATE
// ======================================================

Candidate* CandidateManager::searchCandidate()
{
    string examID;
    cout << "Enter exam ID: ";
    cin >> examID;

    Candidate* c = hashTable.findByID(examID);
    if (c)
    {
        cout << "\nCandidate Found:\n";
        Candidate::printHeader();
        c->display();
        Candidate::printSeparator();
    }
    else
    {
        cout << "Candidate with Exam ID '" << examID << "' not found.\n";
    }
    return c;
}

Candidate* CandidateManager::searchCandidate(const string& examID)
{
    return hashTable.findByID(examID);
}

vector<Candidate> CandidateManager::searchCandidatesByName(const string& keyword) const
{
    return hashTable.findByName(keyword);
}

// ======================================================
// REMOVE CANDIDATE
// ======================================================

bool CandidateManager::removeCandidate()
{
    string examID;
    cout << "Enter Exam ID to remove: ";
    cin >> examID;

    if (removeCandidate(examID))
    {
        cout << "Candidate removed successfully.\n";
        return true;
    }
    else
    {
        cout << "Candidate not found! Removal failed.\n";
        return false;
    }
}

bool CandidateManager::removeCandidate(const string& examID)
{
    return hashTable.remove(examID);
}

// ======================================================
// GETTERS & PROCESSING
// ======================================================

vector<Candidate> CandidateManager::getAllCandidates() const
{
    return hashTable.getAllCandidates();
}

vector<Candidate> CandidateManager::getSortedCandidates() const
{
    vector<Candidate> candidates = hashTable.getAllCandidates();
    CandidateSorter::mergeSort(candidates);
    return candidates;
}

vector<vector<Candidate>> CandidateManager::groupCandidates() const
{
    vector<vector<Candidate>> groups;
    for (int i = 0; i < HashTable::TABLE_SIZE; ++i)
    {
        vector<Candidate> group;
        hashTable.getBucket(i).getAllCandidates(group);
        groups.push_back(group);
    }
    return groups;
}

vector<Room> CandidateManager::divideCandidates(int numberOfRooms)
{
    RoomManager roomMgr;
    roomMgr.distributeCandidates(hashTable, numberOfRooms);
    return roomMgr.getRooms();
}

// ======================================================
// DISPLAY FUNCTIONS
// ======================================================

void CandidateManager::displaySortedCandidates() const
{
    vector<Candidate> sorted = getSortedCandidates();
    if (sorted.empty())
    {
        cout << "No candidates in system.\n";
        return;
    }
    Candidate::printHeader();
    for (const auto& c : sorted)
    {
        c.display();
    }
    Candidate::printSeparator();
}

void CandidateManager::displayGroups() const
{
    GroupManager::displayAllGroups(hashTable);
}

void CandidateManager::distributeCandidatesToRooms()
{
    int numRooms;
    cout << "Enter number of rooms: ";
    if (!(cin >> numRooms) || numRooms <= 0)
    {
        cout << "Invalid room number!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    RoomManager roomMgr;
    auto start = chrono::high_resolution_clock::now();
    bool success = roomMgr.distributeCandidates(hashTable, numRooms);
    auto end = chrono::high_resolution_clock::now();

    if (success)
    {
        roomMgr.displayRooms();
        double elapsed = chrono::duration<double, milli>(end - start).count();
        roomMgr.printPerformanceReport(elapsed);
    }
}

// ======================================================
// SAVE & LOAD DATA
// ======================================================

bool CandidateManager::saveData()
{
    return saveData("candidates.txt");
}

bool CandidateManager::saveData(const string& filename)
{
    vector<Candidate> all = hashTable.getAllCandidates();
    return FileManager::saveToFile(all, filename);
}

bool CandidateManager::loadData()
{
    return loadData("candidates.txt");
}

bool CandidateManager::loadData(const string& filename)
{
    vector<Candidate> loaded = FileManager::loadFromFile(filename);
    if (loaded.empty())
    {
        cout << "No data loaded or file empty: " << filename << "\n";
        return false;
    }
    int count = 0;
    for (const auto& c : loaded)
    {
        if (hashTable.add(c))
        {
            count++;
        }
    }
    cout << "Successfully loaded " << count << " candidates from " << filename << ".\n";
    return true;
}