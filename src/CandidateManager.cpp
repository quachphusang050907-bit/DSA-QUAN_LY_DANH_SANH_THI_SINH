#include "../include/CandidateManager.h"
#include "../include/HashTable.h"
#include "../include/LinkedList.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <chrono>
#include <cctype>

using namespace std;
using namespace chrono;

// ======================================================
// VALIDATION FUNCTIONS
// ======================================================

// FIX: Cho phép byte >= 0x80 (ký tự UTF-8 đa byte tiếng Việt như ễ, ắ, ữ...)
bool isValidName(const string& text)
{
    if (text.empty())
        return false;

    bool hasLetter = false;

    for (unsigned char c : text)
    {
        if (c >= 0x80)
        {
            // Byte thuộc chuỗi UTF-8 đa byte → coi là ký tự hợp lệ
            hasLetter = true;
        }
        else if (isalpha(c))
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

// FIX: Tương tự, gender có thể là "Nữ" (ký tự UTF-8)
bool isValidGender(const string& text)
{
    if (text.empty())
        return false;

    for (unsigned char c : text)
    {
        if (c >= 0x80) continue;  // UTF-8 multi-byte → hợp lệ
        if (!isalpha(c))
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
        cout << "Gender (Nam/Nu): ";
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
// SEARCH BY EXAM ID (programmatic)
// ======================================================
Candidate* CandidateManager::searchCandidate(const string& examID)
{
    return hashTable.findByID(examID);
}

// ======================================================
// SEARCH INTERACTIVE – sub-menu: by ID hoặc by Name
// Cả hai đều có đo thời gian thực thi
// ======================================================
Candidate* CandidateManager::searchCandidate()
{
    cout << "\nSearch by:\n";
    cout << "  1. Exam ID\n";
    cout << "  2. Full Name\n";
    cout << "Choice: ";

    int searchChoice;
    if (!(cin >> searchChoice))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "[Error] Invalid choice.\n";
        return nullptr;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // --------------------------------------------------
    // SEARCH BY EXAM ID
    // --------------------------------------------------
    if (searchChoice == 1)
    {
        string examID;
        cout << "Enter exam ID: ";
        cin >> ws;
        getline(cin, examID);

        auto start = high_resolution_clock::now();
        Candidate* candidate = searchCandidate(examID);
        auto end   = high_resolution_clock::now();

        double ms = duration<double, milli>(end - start).count();
        double us = duration<double, micro>(end - start).count();

        if (candidate != nullptr)
        {
            cout << "\n========== CANDIDATE FOUND ==========\n";
            cout << "Exam ID   : " << candidate->getExamID()   << "\n";
            cout << "Full Name : " << candidate->getFullName()  << "\n";
            cout << "Gender    : " << candidate->getGender()    << "\n";
            cout << "Birth Date: " << candidate->getBirthDate() << "\n";
            cout << "Hometown  : " << candidate->getHometown()  << "\n";
            cout << "======================================\n";
        }
        else
        {
            cout << "\n[Not Found] Exam ID '" << examID << "' does not exist.\n";
        }

        cout << fixed << setprecision(4);
        cout << "\n[Hash Table Lookup] Execution time: "
             << ms << " ms (" << us << " us)\n";

        cout << "\nPress Enter to continue...";
        cin.get();

        return candidate;
    }

    // --------------------------------------------------
    // SEARCH BY FULL NAME
    // --------------------------------------------------
    if (searchChoice == 2)
    {
        string keyword;
        cout << "Enter name keyword: ";
        cin >> ws;
        getline(cin, keyword);

        auto start   = high_resolution_clock::now();
        vector<Candidate> results = searchCandidatesByName(keyword);
        auto end     = high_resolution_clock::now();

        double ms = duration<double, milli>(end - start).count();
        double us = duration<double, micro>(end - start).count();

        if (results.empty())
        {
            cout << "\n[Not Found] No candidates with name containing '"
                 << keyword << "'.\n";
        }
        else
        {
            cout << "\n========== SEARCH RESULTS ("
                 << results.size() << " candidate(s) found) ==========\n";
            Candidate::printHeader();
            Candidate::printSeparator();
            for (const Candidate& c : results)
            {
                c.display();
            }
            Candidate::printSeparator();
        }

        cout << fixed << setprecision(4);
        cout << "\n[Linear Search by Name] Execution time: "
             << ms << " ms (" << us << " us)\n";

        cout << "\nPress Enter to continue...";
        cin.get();

        return nullptr;
    }

    cout << "\n[Error] Invalid choice.\n";
    cout << "\nPress Enter to continue...";
    cin.get();
    return nullptr;
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
    cin >> ws;
    getline(cin, examID);

    if (removeCandidate(examID))
    {
        cout << "[OK] Candidate with exam ID '" << examID << "' has been removed.\n";
        return true;
    }
    else
    {
        cout << "[Error] Candidate with exam ID '" << examID << "' not found.\n";
        return false;
    }
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
// GET SORTED CANDIDATES (không đo thời gian – dùng nội bộ)
// ======================================================
vector<Candidate> CandidateManager::getSortedCandidates() const
{
    vector<Candidate> candidates = hashTable.getAllCandidates();
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

        const LinkedList& bucket = hashTable.getBucket(i);

        const Node* current = bucket.getHead();

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
    {
        return result;
    }

    RoomManager roomManager;

    if (roomManager.distributeCandidates(hashTable, numberOfRooms))
    {
        result = roomManager.getRooms();
    }

    return result;
}


// ======================================================
// DISPLAY SORTED CANDIDATES – có đo thời gian Merge Sort
// ======================================================
void CandidateManager::displaySortedCandidates() const
{
    vector<Candidate> candidates = hashTable.getAllCandidates();

    if (candidates.empty())
    {
        cout << "No candidates found.\n";
        return;
    }

    cout << "Total candidates to sort: " << candidates.size() << "\n";
    cout << "Running Merge Sort...\n";

    // Đo thời gian thuật toán Merge Sort
    auto start = high_resolution_clock::now();
    CandidateSorter::mergeSort(candidates);
    auto end   = high_resolution_clock::now();

    double ms = duration<double, milli>(end - start).count();
    double us = duration<double, micro>(end - start).count();

    // Hiển thị kết quả với đúng định dạng bảng
    Candidate::printHeader();
    Candidate::printSeparator();
    for (const Candidate& candidate : candidates)
    {
        candidate.display();
    }
    Candidate::printSeparator();

    cout << fixed << setprecision(4);
    cout << "\n[Merge Sort] Execution time: "
         << ms << " ms (" << us << " us)"
         << "  |  Complexity: O(n log n)"
         << "  |  n = " << candidates.size() << "\n";
}


// ======================================================
// DISPLAY GROUPS
// ======================================================
void CandidateManager::displayGroups() const
{
    GroupManager::displayAllGroups(hashTable);
}


// ======================================================
// DISTRIBUTE CANDIDATES TO ROOMS – có đo thời gian
// ======================================================
void CandidateManager::distributeCandidatesToRooms()
{
    int numberOfRooms = 0;

    cout << "Enter number of rooms: ";

    while (!(cin >> numberOfRooms) || numberOfRooms <= 0)
    {
        cout << "Invalid input. Please enter a positive integer: ";

        cin.clear();

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );
    }

    RoomManager roomManager;

    // Đo thời gian phân phòng
    auto start = high_resolution_clock::now();
    bool ok    = roomManager.distributeCandidates(hashTable, numberOfRooms);
    auto end   = high_resolution_clock::now();

    double ms = duration<double, milli>(end - start).count();

    if (ok)
    {
        roomManager.displayRooms();
        roomManager.printPerformanceReport(ms);  // FIX: gọi hàm đã có sẵn nhưng chưa được dùng
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
    vector<Candidate> candidates = hashTable.getAllCandidates();

    return FileManager::saveToFile(candidates, filename);
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