#pragma once
#include "Node.h" 
#include <vector> 
#include <string> 
using namespace std; 
 
// Danh sách liên kết đơn chứa Candidate
// Dùng làm từng bucket trong Hash Table
class LinkedList { 
private: 
    Node* head;   // Node đầu
    Node* tail;   // Node cuối
    int   count;  // Số phần tử 
 
public: 
    LinkedList();                          // Hàm khởi tạo
    ~LinkedList();                         // Hàm hủy
 
    // Không cho phép copy, tránh double-free
    LinkedList(const LinkedList&) = delete; 
    LinkedList& operator=(const LinkedList&) = delete; 
 
    void insertBack(const Candidate& c);   // Thêm vào cuối danh sách
    bool remove(const string& examID);     // Xóa theo examID
    Node* findByID(const string& examID) const; // Tìm theo examID
 
    // Tìm tên gần đúng, kết quả lưu vào vector
    void findByName(const string& keyword, vector<Candidate>& results) const; 
 
    void getAllCandidates(vector<Candidate>& out) const; // Lấy tất cả Candidate
    void display() const;                                // Hiển thị danh sách
 
    // ── Accessors 
    Node* getHead()  const { return head; }      // Lấy Node đầu
    int   getCount() const { return count; }     // Lấy số lượng Node
    bool  isEmpty()  const { return head == nullptr; } // Kiểm tra rỗng
}; 
