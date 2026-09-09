#pragma once
#include "Candidate.h"
#include <vector>

struct Room {
    int roomId;
    std::vector<Candidate> candidates;

    explicit Room(int id = 0) : roomId(id) {}
};


