#include "CandidateManager.h"

using namespace std;

bool CandidateManager::addCandidate(const Candidate& candidate)
{
    return hashTable.add(candidate);
}

Candidate* CandidateManager::searchCandidate(const string& examID)
{
    return hashTable.findByID(examID);
}

bool CandidateManager::removeCandidate(const string& examID)
{
    return hashTable.remove(examID);
}

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

    for (int i = 0; i < HashTable::TABLE_SIZE; i++)
    {
        vector<Candidate> group;

        const LinkedList& bucket = hashTable.getBucket(i);

        // Duyệt các node trong bucket
        Node* current = bucket.getHead();

        while (current != nullptr)
        {
            group.push_back(current->data);
            current = current->next;
        }

        groups.push_back(group);
    }

    return groups;
}

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

bool CandidateManager::saveData(const string& filename)
{
    vector<Candidate> candidates = hashTable.getAllCandidates();

    return FileManager::saveToFile(candidates, filename);
}

bool CandidateManager::loadData(const string& filename)
{
    vector<Candidate> candidates = FileManager::loadFromFile(filename);

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
