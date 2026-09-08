#include "CandidateManager.h"

using namespace std;

bool CandidateManager::addCandidate(const Candidate& candidate)
{
    // Thêm candidate vào HashTable
}

Candidate* CandidateManager::searchCandidate(const string& examID)
{
    // Tìm candidate theo examID
}

bool CandidateManager::removeCandidate(const string& examID)
{
    // Xóa candidate
}

vector<Candidate> CandidateManager::getAllCandidates() const
{
    // Lấy tất cả candidate
}

vector<Candidate> CandidateManager::getSortedCandidates() const
{
    // Sắp xếp candidate theo tên
}

vector<vector<Candidate>> CandidateManager::groupCandidates() const
{
    // Nhóm candidate theo chữ cái đầu
}

vector<Room> CandidateManager::divideCandidates(int numberOfRooms)
{
    // Chia candidate vào các phòng
}

bool CandidateManager::saveData(const string& filename)
{
    // Lưu dữ liệu vào file
}

bool CandidateManager::loadData(const string& filename)
{
    // Đọc dữ liệu từ file
}
