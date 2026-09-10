#pragma once

#include "HashTable.h"
#include "CandidateSorter.h"
#include "GroupManager.h"
#include "RoomManager.h"
#include "FileManager.h"

class CandidateManager {
private:
    HashTable hashTable;

public:
    bool addCandidate(const Candidate& candidate);

    Candidate* searchCandidate(const string& examID);

    bool removeCandidate(const string& examID);

    vector<Candidate> getAllCandidates() const;

    vector<Candidate> getSortedCandidates() const;

    vector<vector<Candidate>> groupCandidates() const;

    vector<Room> divideCandidates(int numberOfRooms);

    bool saveData(const string& filename);

    bool loadData(const string& filename);
};
