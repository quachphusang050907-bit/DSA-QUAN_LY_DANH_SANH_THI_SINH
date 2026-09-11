#include "../include/CandidateManager.h"
#include "../include/HashTable.h"

#include <iostream>
#include <limits>
#include <cctype>
#include <sstream>
#include <iomanip>

using namespace std;
// ======================================================
// VALIDATE EXAM ID
// ======================================================
bool isValidExamID(const string& examID)
{
    if (examID.empty())
        return false;

    for (char c : examID)
    {
        if (!isalnum(static_cast<unsigned char>(c)))
            return false;
    }

    return true;
}
// ======================================================
// VALIDATE FULL NAME
// ======================================================
bool isValidName(const string& name)
{
    if (name.empty())
        return false;

    bool hasLetter = false;

    for (char c : name)
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
// ======================================================
// VALIDATE GENDER
// Only: girl / boy
// ======================================================
bool isValidGender(string& gender)
{
    if (gender.empty())
        return false;

    for (char& c : gender)
    {
        c = static_cast<char>(
            tolower(static_cast<unsigned char>(c))
        );
    }

    return gender == "girl" || gender == "boy";
}
// ======================================================
// VALIDATE BIRTH DATE
// Accept:
// 3/2/2000
// 03/2/2000
// 3/02/2000
// 03/02/2000
//
// Convert to:
// 03/02/2000
// ======================================================
bool isValidBirthDate(string& birthDate)
{
    int day, month, year;
    char slash1, slash2;

    stringstream ss(birthDate);

    if (!(ss >> day >> slash1 >> month >> slash2 >> year))
        return false;

    // Must use /
    if (slash1 != '/' || slash2 != '/')
        return false;

    // No extra characters
    char extra;
    if (ss >> extra)
        return false;

    // Basic year condition
    if (year < 1900 || year > 2100)
        return false;

    // Month condition
    if (month < 1 || month > 12)
        return false;

    // Days in each month
    int daysInMonth[] =
    {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    // Leap year
    bool leapYear =
        (year % 400 == 0) ||
        (year % 4 == 0 && year % 100 != 0);

    if (leapYear)
        daysInMonth[1] = 29;

    if (day < 1 || day > daysInMonth[month - 1])
        return false;

    // Normalize to DD/MM/YYYY
    stringstream formatted;

    formatted << setfill('0')
              << setw(2) << day
              << "/"
              << setw(2) << month
              << "/"
              << setw(4) << year;

    birthDate = formatted.str();

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
            cout << "Invalid Exam ID. "
                 << "Please use letters and numbers only.\n";
            continue;
        }

        if (hashTable.findByID(input) != nullptr)
        {
            cout << "Exam ID already exists. "
                 << "Please enter another ID.\n";
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
            cout << "Invalid full name. "
                 << "Please enter letters and spaces only.\n";
            continue;
        }

        candidate.setFullName(input);
        break;
    }
    // --------------------------------------------------
    // GENDER
    // Only girl / boy
    // --------------------------------------------------
    while (true)
    {
        cout << "Gender (girl/boy): ";
        getline(cin, input);

        if (!isValidGender(input))
        {
            cout << "Invalid gender. "
                 << "Please enter girl or boy.\n";
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
            cout << "Invalid birth date. "
                 << "Please enter a valid date.\n";
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

        if (input.empty())
        {
            cout << "Hometown cannot be empty. "
                 << "Please enter again.\n";
            continue;
        }

        candidate.setHometown(input);
        break;
    }


    return addCandidate(candidate);
}
// ======================================================
// ADD CANDIDATE DIRECTLY
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
// ======================================================
// REMOVE CANDIDATE
// ======================================================
bool CandidateManager::removeCandidate()
{
    string examID;

    cout << "Enter exam ID to remove: ";
    cin >> examID;

    return removeCandidate(examID);
}
bool CandidateManager::removeCandidate(const string& examID)
{
    return hashTable.remove(examID);
}
// ======================================================
// GET ALL CANDIDATES
// ======================================================
vector<Candidate> CandidateManager::getAllCandidates() const
{
    return hashTable.getAllCandidates();
}
// ======================================================
// GET SORTED CANDIDATES
// ======================================================
vector<Candidate> CandidateManager::getSortedCandidates() const
{
    vector<Candidate> candidates =
        hashTable.getAllCandidates();

    CandidateSorter::mergeSort(candidates);

    return candidates;
}
// ======================================================
// GROUP CANDIDATES
// ======================================================
vector<vector<Candidate>> CandidateManager::groupCandidates() const
{
    vector<vector<Candidate>> groups;

    for (int i = 0; i < HashTable::TABLE_SIZE; i++)
    {
        vector<Candidate> group;

        const LinkedList& bucket =
            hashTable.getBucket(i);

        const Node* current =
            bucket.getHead();

        while (current != nullptr)
        {
            group.push_back(current->data);
            current = current->next;
        }

        groups.push_back(group);
    }

    return groups;
}
// ======================================================
// DIVIDE CANDIDATES INTO ROOMS
// ======================================================
vector<Room> CandidateManager::divideCandidates(int numberOfRooms)
{
    vector<Room> result;

    if (numberOfRooms <= 0)
        return result;

    RoomManager roomManager;

    if (roomManager.distributeCandidates(
            hashTable, numberOfRooms))
    {
        result = roomManager.getRooms();
    }

    return result;
}
// ======================================================
// DISPLAY SORTED CANDIDATES
// ======================================================
void CandidateManager::displaySortedCandidates() const
{
    vector<Candidate> candidates =
        getSortedCandidates();

    if (candidates.empty())
    {
        cout << "No candidates found.\n";
        return;
    }

    Candidate::printHeader();
    Candidate::printSeparator();

    for (const Candidate& candidate : candidates)
    {
        candidate.display();
    }
}
// ======================================================
// DISPLAY GROUPS
// ======================================================
void CandidateManager::displayGroups() const
{
    GroupManager::displayAllGroups(hashTable);
}
// ======================================================
// DISTRIBUTE CANDIDATES TO ROOMS
// ======================================================
void CandidateManager::distributeCandidatesToRooms()
{
    int numberOfRooms = 0;

    cout << "Enter number of rooms: ";

    while (!(cin >> numberOfRooms) ||
           numberOfRooms <= 0)
    {
        cout << "Invalid input. "
             << "Please enter a positive integer: ";

        cin.clear();

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );
    }

    RoomManager roomManager;

    if (roomManager.distributeCandidates(
            hashTable, numberOfRooms))
    {
        roomManager.displayRooms();
    }
}
// ======================================================
// SAVE DATA
// ======================================================
bool CandidateManager::saveData()
{
    return saveData("data/candidates_100.txt");
}


bool CandidateManager::saveData(const string& filename)
{
    vector<Candidate> candidates =
        hashTable.getAllCandidates();

    return FileManager::saveToFile(
        candidates,
        filename
    );
}
// ======================================================
// LOAD DATA
// ======================================================
bool CandidateManager::loadData()
{
    return loadData("data/candidates_100.txt");
}

bool CandidateManager::loadData(const string& filename)
{
    vector<Candidate> candidates =
        FileManager::loadFromFile(filename);

    bool success = true;

    for (const Candidate& candidate : candidates)
    {
        if (!hashTable.add(candidate))
        {
            success = false;
        }
    }

    return success;
}
