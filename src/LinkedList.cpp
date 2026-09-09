#include "LinkedList.h"       // Include LinkedList
#include <iostream> 
using namespace std; 
 
// Constructor / Destructor 
LinkedList::LinkedList() : head(nullptr), tail(nullptr), count(0) {}
// Khởi tạo danh sách rỗng
 
LinkedList::~LinkedList() {               // Hàm hủy
    Node* cur = head;                     // Bắt đầu từ Node đầu
    while (cur) {                         // Duyệt khi còn Node
        Node* next = cur->next;           // Lưu Node tiếp theo
        delete cur;                       // Xóa Node hiện tại
        cur = next;                       // Chuyển sang Node kế tiếp
    }
} 
 
// Thêm vào cuối danh sách – O(1) nhờ tail pointer 
void LinkedList::insertBack(const Candidate& c) { // Thêm Candidate vào cuối
    Node* newNode = new Node(c);                  // Tạo Node mới

    if (!head) { 
        head = tail = newNode;                    // Rỗng → Node mới là đầu và cuối
    } 
    else {
        tail->next = newNode;                     // Node cuối trỏ tới Node mới
        tail = newNode;                           // Cập nhật tail
    } 

    count++;                                      // Tăng số lượng Node
} 
 
// Xoá theo examID – O(n) với cập nhật tail 
bool LinkedList::remove(const string& examID) {   // Xóa theo examID
    if (!head) return false;                      // Danh sách rỗng → không xóa
 
    // Trường hợp xoá node đầu 
    if (head->data.examID == examID) {             // Kiểm tra Node đầu
        Node* del = head;                          // Lưu Node cần xóa
        head = head->next;                         // Đưa head sang Node kế

        if (!head) tail = nullptr;                // Xóa hết → tail cũng rỗng

        delete del;                               // Xóa Node
        count--;                                  // Giảm số lượng
        return true;                              // Xóa thành công
    } 
 
    // Tìm node trước node cần xoá 
    Node* prev = head;                            // Node đứng trước
    Node* cur  = head->next;                      // Node đang xét

    while (cur) {                                 // Duyệt danh sách
        if (cur->data.examID == examID) {         // Tìm thấy examID

            prev->next = cur->next;               // Bỏ qua Node cur

            if (cur == tail) tail = prev;         // Xóa Node cuối → cập nhật tail

            delete cur;                           // Xóa Node
            count--;                              // Giảm số lượng
            return true;                          // Xóa thành công
        }

        prev = cur;                               // prev tiến lên
        cur  = cur->next;                         // cur tiến lên
    }

    return false;                                 // Không tìm thấy
} 
 
// Tìm theo examID – O(n) 
Node* LinkedList::findByID(const string& examID) const { // Tìm theo examID
    Node* cur = head;                                     // Bắt đầu từ đầu

    while (cur) {                                         // Duyệt danh sách
        if (cur->data.examID == examID) return cur;       // Tìm thấy → trả về Node
        cur = cur->next;                                  // Sang Node kế tiếp
    }

    return nullptr;                                       // Không tìm thấy
} 
 
// Tìm theo tên (gần đúng) – O(n) 
void LinkedList::findByName(const string& keyword, vector<Candidate>& results) const { // Tìm theo tên
    Node* cur = head;                                                            // Bắt đầu từ đầu

    while (cur) {                                                                // Duyệt danh sách
        // Tìm trong fullName (không phân biệt hoa/thường ASCII) 
        string fn = cur->data.fullName;                                         // Lấy tên
        string kw = keyword;                                                    // Lấy từ khóa

        for (char& ch : fn) if (ch>='A'&&ch<='Z') ch+=32;                      // Đổi tên → chữ thường
        for (char& ch : kw) if (ch>='A'&&ch<='Z') ch+=32;                      // Đổi keyword → chữ thường

        if (fn.find(kw) != string::npos)                                      // Kiểm tra tên có chứa keyword
            results.push_back(cur->data);                                      // Có → thêm vào kết quả

        cur = cur->next;                                                       // Sang Node kế tiếp
    }
} 
 
// Lấy tất cả vào vector 
void LinkedList::getAllCandidates(vector<Candidate>& out) const {              // Lấy toàn bộ Candidate
    Node* cur = head;                                                           // Bắt đầu từ đầu

    while (cur) {                                                               // Duyệt danh sách
        out.push_back(cur->data);                                               // Thêm Candidate vào vector
        cur = cur->next;                                                        // Sang Node kế tiếp
    }
} 
 
// Hiển thị danh sách 
void LinkedList::display() const {                       // Hiển thị danh sách
    if (!head) {                                         // Nếu danh sách rỗng
        cout << "  (Trong)\n"; return;                   // In thông báo rồi thoát
    }

    Node* cur = head;                                    // Bắt đầu từ Node đầu

    while (cur) {                                        // Duyệt từng Node
        cur->data.display();                             // Hiển thị thông tin Candidate
        cur = cur->next;                                 // Sang Node kế tiếp
    }
}