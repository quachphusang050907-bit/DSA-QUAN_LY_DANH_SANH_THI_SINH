#include "../include/CandidateManager.h"
#include "../include/HashTable.h"
#include <iostream>
#include <limits>

using namespace std;

bool CandidateManager::addCandidate()
{
    Candidate candidate;

    cout << "Exam ID: ";
    cin >> ws; 
    getline(cin, candidate.examID);

    cout << "Full name: ";
    getline(cin, candidate.fullName);

    cout << "Gender: ";
    getline(cin, candidate.gender);

    cout << "Birth date: ";
    getline(cin, candidate.birthDate);

    cout << "Hometown: ";
    getline(cin, candidate.hometown);

    return addCandidate(candidate);
}

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
// DISPLAY SORTED CANDIDATES
// ======================================================
void CandidateManager::displaySortedCandidates() const
{
    vector<Candidate> candidates = getSortedCandidates();

    if (candidates.empty())
    {
        cout << "No candidates found.\n";
        return;
    }

    for (const Candidate& candidate : candidates)
    {
        cout << candidate.fullName << " | "
             << candidate.gender << " | "
             << candidate.examID << " | "
             << candidate.birthDate << " | "
             << candidate.hometown << endl;
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

    if (roomManager.distributeCandidates(hashTable, numberOfRooms))
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
