#pragma once

#include <string>
#include <vector>

#include "Candidate.h"
#include "HashTable.h"
#include "CandidateSorter.h"
#include "GroupManager.h"
#include "RoomManager.h"
#include "FileManager.h"

class CandidateManager {
private:
    HashTable hashTable;

public:
    bool addCandidate();
    bool addCandidate(const Candidate& candidate);
    Candidate* searchCandidate();
    Candidate* searchCandidate(const std::string& examID);

    std::vector<Candidate> searchCandidatesByName(const std::string& keyword) const;

    bool removeCandidate();
    bool removeCandidate(const std::string& examID);

    std::vector<Candidate> getAllCandidates() const;
    std::vector<Candidate> getSortedCandidates() const;
    std::vector<std::vector<Candidate>> groupCandidates() const;
    std::vector<Room> divideCandidates(int numberOfRooms);

    void displaySortedCandidates() const;
    void displayGroups() const;
    void distributeCandidatesToRooms();

    bool saveData();
    bool saveData(const std::string& filename);
    bool loadData();
    bool loadData(const std::string& filename);
};