#pragma once

#include <string>
#include <vector>

#include "Candidate.h"

class CandidateSorter {
public:
    static std::string getFirstName(const std::string& fullName);
    static bool compareCandidate(const Candidate& a, const Candidate& b);
    static void mergeSort(std::vector<Candidate>& candidates);

private:
    static void merge(std::vector<Candidate>& candidates, int left, int mid, int right);
    static void mergeSort(std::vector<Candidate>& candidates, int left, int right);
};