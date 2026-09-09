#ifndef NODE_H
#define NODE_H
// Tránh file Node.h bị khai báo nhiều lần

#include "Candidate.h"
// Sử dụng kiểu dữ liệu Candidate


// Struct Node – đại diện cho một nút trong danh sách liên kết đơn
struct Node {

    Candidate data;
    // Lưu thông tin của một thí sinh

    Node* next;
    // Con trỏ trỏ đến Node tiếp theo


    explicit Node(const Candidate& c) : data(c), next(nullptr) {}
    // Hàm khởi tạo Node
    // data(c): lưu thông tin thí sinh c vào Node
    // next(nullptr): ban đầu chưa trỏ đến Node nào
};

#endif
// Kết thúc Include Guard