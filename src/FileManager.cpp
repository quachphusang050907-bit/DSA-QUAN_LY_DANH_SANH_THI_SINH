#include "../include/FileManager.h"

#include <fstream>
#include <string>

using namespace std;


// ============================================================
// HÀM TRIM
// ============================================================
string FileManager::trim(
    const string& text
)
{
    size_t start =
        text.find_first_not_of(
            " \t\r\n"
        );

    if (start == string::npos)
    {
        return "";
    }

    size_t end =
        text.find_last_not_of(
            " \t\r\n"
        );

    return text.substr(
        start,
        end - start + 1
    );
}


// ============================================================
// HÀM SPLIT
// ============================================================
vector<string> FileManager::split(
    const string& line,
    char delimiter
)
{
    vector<string> parts;
    string currentPart;

    for (char character : line)
    {
        if (character == delimiter)
        {
            parts.push_back(
                trim(currentPart)
            );
            currentPart.clear();
        }
        else
        {
            currentPart += character;
        }
    }

    parts.push_back(
        trim(currentPart)
    );

    return parts;
}


// ============================================================
// HÀM LOAD FROM FILE
// ============================================================
//
//  Định dạng file thực tế:
//  examID|fullName|gender|birthDate|hometown
//
//  Ví dụ:
//  240001|Nguyễn Bảo Hải|Nam|08/04/2004|Hải Phòng
// ============================================================

vector<Candidate> FileManager::loadFromFile(
    const string& filename
)
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

        // Cần đúng 5 trường: examID|fullName|gender|birthDate|hometown
        if (parts.size() != 5)
        {
            continue;
        }

        Candidate candidate;

        // FIX: Dùng setter thay vì gán vào giá trị trả về của getter
        // FIX: Thứ tự đúng theo file: examID|fullName|gender|birthDate|hometown
        candidate.setExamID(parts[0]);
        candidate.setFullName(parts[1]);
        candidate.setGender(parts[2]);
        candidate.setBirthDate(parts[3]);
        candidate.setHometown(parts[4]);

        candidates.push_back(candidate);
    }

    inputFile.close();

    return candidates;
}


// ============================================================
// HÀM SAVE TO FILE
// ============================================================
//
//  Lưu theo đúng định dạng:
//  examID|fullName|gender|birthDate|hometown
// ============================================================

bool FileManager::saveToFile(
    const vector<Candidate>& candidates,
    const string& filename
)
{
    ofstream outputFile(filename);

    if (!outputFile.is_open())
    {
        return false;
    }

    for (const Candidate& candidate : candidates)
    {
        // FIX: Thứ tự đúng: examID|fullName|gender|birthDate|hometown
        outputFile
            << candidate.getExamID()
            << "|"
            << candidate.getFullName()
            << "|"
            << candidate.getGender()
            << "|"
            << candidate.getBirthDate()
            << "|"
            << candidate.getHometown()
            << '\n';
    }

    outputFile.close();

    return true;
}
