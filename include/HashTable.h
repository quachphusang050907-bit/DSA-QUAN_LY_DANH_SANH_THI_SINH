#pragma once
#include "LinkedList.h"
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

// ============================================================================
//  Class HashTable - bang bam 26 bucket (A-Z), xu ly dung do bang SEPARATE
//  CHAINING: moi bucket la 1 doi tuong LinkedList doc lap.
//
//  Khoa bam (key)   = ho ten day du cua thi sinh
//  Ham bam          = chu cai dau cua TU CUOI CUNG trong ho ten (vi tieng Viet,
//                      "ten" rieng nam o cuoi - "Nguyen Van An" -> ten la "An"),
//                      anh xa 'A'-'Z' -> chi so 0-25
//  TABLE_SIZE       = 26, CO DINH - vi 26 mang y nghia phan loai theo dung yeu
//                      cau de bai ("nhom thi sinh theo chu cai dau"), khong phai
//                      de toi uu do tai (load factor) nhu hash table "sach giao khoa"
// ============================================================================
class HashTable {
public:
    static const int TABLE_SIZE = 26;

private:
    LinkedList buckets[TABLE_SIZE];   // Mang TINH 26 LinkedList, moi bucket 1 chu cai
    int        totalCount;             // Tong so thi sinh dang co trong bang
    unordered_set<string> idSet;       // Tap ma du thi da ton tai -> kiem tra trung O(1)

    // ---- Cac ham phu tro cho ham bam (khong tach Utils.h rieng) ----
    static string getFirstName(const string& fullName); // Lay tu cuoi cung (ten rieng)
    static char   getBaseChar(const string& firstName);  // Quy ve chu cai goc A-Z (bo dau)
    static int    hashIndex(char c);                      // Chu cai -> chi so 0-25
    int computeIndex(const string& fullName) const;        // Gop 3 buoc tren thanh 1 ham bam

public:
    HashTable() : totalCount(0) {}

    bool add(const Candidate& c);                    // Them thi sinh moi - O(1) trung binh
    bool remove(const string& examID);                 // Xoa theo ma - O(n/26) trung binh
    Candidate* findByID(const string& examID);          // Tim chinh xac theo ma
    vector<Candidate> findByName(const string& keyword) const; // Tim gan dung theo ten
    vector<Candidate> getAllCandidates() const;           // Lay tat ca, theo thu tu bucket A->Z

    const LinkedList& getBucket(int index) const { return buckets[index]; } // Cho GroupManager/RoomManager duyet truc tiep
    int  getTotalCount() const { return totalCount; }
    bool isEmpty()        const { return totalCount == 0; }

    void printStats() const; // Thong ke so luong thi sinh trong tung bucket (bieu do thanh)
};


