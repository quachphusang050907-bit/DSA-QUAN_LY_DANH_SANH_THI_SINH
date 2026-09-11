#include "../include/HashTable.h"
#include <iostream>
#include <algorithm>
using namespace std;

// ============================================================================
//  Buoc 1: getFirstName - lay TU CUOI CUNG trong ho ten (chinh la "ten" rieng
//  theo cach goi cua nguoi Viet, vi ho + ten dem dung truoc, ten rieng dung cuoi)
// ============================================================================
string HashTable::getFirstName(const string& fullName) {
    // Bo khoang trang thua o dau/cuoi truoc khi xu ly
    int start = 0, end = (int)fullName.size() - 1;
    while (start <= end && fullName[start] == ' ') start++;
    while (end >= start && fullName[end] == ' ') end--;
    if (start > end) return "";
    string s = fullName.substr(start, end - start + 1);

    // Duyet NGUOC tu cuoi chuoi, gap khoang trang dau tien thi dung lai
    // -> do chinh la ranh gioi giua "ho + ten dem" va "ten"
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        if (s[i] == ' ') return s.substr(i + 1);
    }
    return s; // Ho ten chi co 1 tu (khong co khoang trang) -> tra nguyen chuoi
}

// ============================================================================
//  Buoc 2: getBaseChar - lay ky tu dau tien cua "ten" va quy ve chu cai
//  KHONG DAU (A-Z). Xu ly duoc ca chu ASCII thuong lan tieng Viet co dau (UTF-8).
//
//  Nhac lai kien thuc UTF-8: 1 ky tu co dau tieng Viet chiem 2-3 BYTE, khong
//  phai 1 byte nhu ASCII. Byte dau tien cho biet ky tu do dai bao nhieu byte:
//    - byte < 0x80                  -> ky tu ASCII, 1 byte
//    - 2 bit cao cua byte la 110    -> ky tu UTF-8, 2 byte
//    - 3 bit cao cua byte la 1110   -> ky tu UTF-8, 3 byte
//  Sau khi biet so byte, ghep cac byte lai (dich bit + AND) de ra ma Unicode
//  (code point) cua ky tu, roi so voi bang ma da liet ke san de suy ra chu cai goc.
// ============================================================================
char HashTable::getBaseChar(const string& firstName) {
    if (firstName.empty()) return 'A';
    unsigned char b0 = (unsigned char)firstName[0];

    // ---- Truong hop 1: ky tu ASCII thuong (1 byte) ----
    if (b0 < 0x80) {
        if (b0 >= 'a' && b0 <= 'z') return (char)(b0 - 32); // doi hoa
        if (b0 >= 'A' && b0 <= 'Z') return (char)b0;
        return 'A'; // ky tu la (so, dau cau...) -> mac dinh nhom vao A
    }

    // ---- Truong hop 2: UTF-8 2 byte (vd: cac nguyen am co 1 dau don gian) ----
    if ((b0 & 0xE0) == 0xC0 && firstName.size() >= 2) {
        unsigned char b1 = (unsigned char)firstName[1];
        int cp = ((b0 & 0x1F) << 6) | (b1 & 0x3F);
        if (cp == 0x0102 || cp == 0x0103) return 'A';                     // Ă ă
        if (cp == 0x0110 || cp == 0x0111) return 'D';                     // Đ đ
        if (cp == 0x01A0 || cp == 0x01A1) return 'O';                     // Ơ ơ (o moc)
        if (cp == 0x01AF || cp == 0x01B0) return 'U';                     // Ư ư (u moc)
        if ((cp>=0x00C0&&cp<=0x00C3)||(cp>=0x00E0&&cp<=0x00E3)) return 'A'; // À Á Â Ã à á â ã
        if ((cp>=0x00C8&&cp<=0x00CA)||(cp>=0x00E8&&cp<=0x00EA)) return 'E'; // È É Ê è é ê
        if (cp==0x00CC||cp==0x00CD||cp==0x00EC||cp==0x00ED) return 'I';    // Ì Í ì í
        if ((cp>=0x00D2&&cp<=0x00D5)||(cp>=0x00F2&&cp<=0x00F5)) return 'O'; // Ò Ó Ô Õ ò ó ô õ
        if (cp==0x00D9||cp==0x00DA||cp==0x00F9||cp==0x00FA) return 'U';    // Ù Ú ù ú
        if (cp==0x00DD||cp==0x00FD) return 'Y';                            // Ý ý
        return 'A';
    }

    // ---- Truong hop 3: UTF-8 3 byte (cac to hop dau phuc tap hon cua tieng Viet) ----
    if ((b0 & 0xF0) == 0xE0 && firstName.size() >= 3) {
        unsigned char b1 = (unsigned char)firstName[1];
        unsigned char b2 = (unsigned char)firstName[2];
        int cp = ((b0 & 0x0F) << 12) | ((b1 & 0x3F) << 6) | (b2 & 0x3F);
        if (cp >= 0x1EA0 && cp <= 0x1EB7) return 'A'; // Ạ ả Ấ ấ Ầ ầ ... Ặ ặ
        if (cp >= 0x1EB8 && cp <= 0x1EC7) return 'E'; // Ẹ ẻ Ẽ Ế ế Ề ề ... Ệ ệ
        if (cp == 0x1EC8 || cp == 0x1EC9) return 'I'; // Ỉ ỉ
        if (cp >= 0x1ECA && cp <= 0x1ECB) return 'I'; // Ị ị
        if (cp >= 0x1ECC && cp <= 0x1EE3) return 'O'; // Ọ ỏ Ố ố Ồ ồ ... Ợ ợ
        if (cp >= 0x1EE4 && cp <= 0x1EF1) return 'U'; // Ụ ủ Ứ ứ Ừ ừ ... Ự ự
        if (cp >= 0x1EF2 && cp <= 0x1EF9) return 'Y'; // Ỳ ỳ Ỵ ỵ Ỷ ỷ Ỹ ỹ
        return 'A';
    }

    return 'A'; // Khong nhan dien duoc -> mac dinh
}

// ============================================================================
//  Buoc 3: hashIndex - CHINH LA "cong thuc bam". Anh xa 1-1 tu 26 chu cai
//  sang 26 so nguyen 0-25.
// ============================================================================
int HashTable::hashIndex(char c) {
    if (c < 'A' || c > 'Z') return 0;
    return c - 'A';
}

// Gop 3 buoc tren thanh 1 ham bam duy nhat - day la ham HashTable thuc su goi
int HashTable::computeIndex(const string& fullName) const {
    string firstName = getFirstName(fullName);
    char   base      = getBaseChar(firstName);
    return hashIndex(base);
}

// ============================================================================
//  add - them 1 thi sinh moi. O(1) TRUNG BINH, khong co vong lap nao ca.
// ============================================================================
bool HashTable::add(const Candidate& c) {
    if (idSet.count(c.examID)) return false;   // Da ton tai -> tu choi, O(1)
    int idx = computeIndex(c.fullName);          // Bam ra chi so 0-25, O(1)
    buckets[idx].insertBack(c);                   // Them vao dung bucket, O(1) nho tail
    idSet.insert(c.examID);
    totalCount++;
    return true;
}

// ============================================================================
//  remove - xoa theo ma du thi. O(n/26) trung binh (phai tim dung bucket).
// ============================================================================
bool HashTable::remove(const string& examID) {
    if (!idSet.count(examID)) return false;      // O(1): khong co thi thoat ngay
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (buckets[i].remove(examID)) {
            idSet.erase(examID);                   // DUNG QUEN dong nay!
            totalCount--;
            return true;
        }
    }
    return false;
}

// ============================================================================
//  findByID - tim theo ma du thi.
//  Luu y quan trong: idSet chi giup tra loi "co ton tai hay khong" trong O(1).
//  Muon LAY RA doi tuong Candidate thuc su, van phai quet toi da 26 bucket vi
//  khoa bam cua bang nay la CHU CAI DAU TEN, khong phai examID.
// ============================================================================
Candidate* HashTable::findByID(const string& examID) {
    if (!idSet.count(examID)) return nullptr;      // O(1)
    for (int i = 0; i < TABLE_SIZE; i++) {          // O(n/26) trung binh
        Node* found = buckets[i].findByID(examID);
        if (found) return &(found->data);
    }
    return nullptr;
}

// findByName - tim gan dung theo ten, phai duyet HET 26 bucket vi khong the
// dung chi so bam de "doan" ten can tim nam o bucket nao khi chi biet 1 phan ten
vector<Candidate> HashTable::findByName(const string& keyword) const {
    vector<Candidate> results;
    for (int i = 0; i < TABLE_SIZE; i++) {
        buckets[i].findByName(keyword, results);
    }
    return results;
}

// getAllCandidates - lay toan bo thi sinh, duyet bucket theo thu tu 0->25 (A->Z)
// nen ket qua tra ve da "gan nhu" duoc nhom theo van A->Z
vector<Candidate> HashTable::getAllCandidates() const {
    vector<Candidate> all;
    all.reserve(totalCount); // Cap phat truoc, tranh vector phai cap phat lai nhieu lan
    for (int i = 0; i < TABLE_SIZE; i++) {
        buckets[i].getAllCandidates(all);
    }
    return all;
}

// printStats - thong ke so thi sinh trong tung bucket, ve bieu do thanh don gian
// -> dung de CHUNG MINH bang mat viec phan bo khong deu giua cac chu cai
void HashTable::printStats() const {
    cout << "\n===== THONG KE PHAN BO HASH TABLE (26 bucket) =====\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        int cnt = buckets[i].getCount();
        if (cnt == 0) continue;                 // Bo qua bucket rong cho gon
        char letter = (char)('A' + i);            // Nghich dao cua hashIndex: chi so -> chu cai
        string bar(min(cnt, 40), '#');
        cout << "  [" << letter << "] (" << cnt << "): " << bar << "\n";
    }
    cout << "Tong so thi sinh: " << totalCount << "\n";
    cout << "=====================================================\n";
}
