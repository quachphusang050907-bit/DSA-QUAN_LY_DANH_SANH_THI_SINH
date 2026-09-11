#include "../include/FileManager.h"

#include <fstream>
#include <string>

using namespace std;

string FileManager::trim(const string& text)
{
    size_t start = text.find_first_not_of(" \t\r\n");
    if (start == string::npos)
    {
        return "";
    }
    size_t end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}

vector<string> FileManager::split(const string& line, char delimiter)
{
    vector<string> parts;
    string currentPart;

    for (char character : line)
    {
        if (character == delimiter)
        {
            parts.push_back(trim(currentPart));
            currentPart.clear();
        }
        else
        {
            currentPart += character;
        }
    }

    parts.push_back(trim(currentPart));
    return parts;
}

vector<Candidate> FileManager::loadFromFile(const string& filename)
{
    vector<Candidate> candidates;
    ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        return candidates;
    }

    string line;

    while (getline(inputFile, line))
    {
        if (trim(line).empty())
        {
            continue;
        }

        vector<string> parts = split(line, '|');

        if (parts.size() != 5)
        {
            continue;
        }

        Candidate candidate;

        // Dùng Setter để lưu thông tin vào candidate
        candidate.setFullName(parts[0]);
        candidate.setGender(parts[1]);
        candidate.setExamID(parts[2]);
        candidate.setBirthDate(parts[3]);
        candidate.setHometown(parts[4]);

        candidates.push_back(candidate);
    }

    inputFile.close();
    return candidates;
}

bool FileManager::saveToFile(const vector<Candidate>& candidates, const string& filename)
{
    ofstream outputFile(filename);

    if (!outputFile.is_open())
    {
        return false;
    }

    for (const Candidate& candidate : candidates)
    {
        outputFile
            << candidate.getFullName()
            << "|"
            << candidate.getGender()
            << "|"
            << candidate.getExamID()
            << "|"
            << candidate.getBirthDate()
            << "|"
            << candidate.getHometown()
            << '\n';
    }

    outputFile.close();
    return true;
}