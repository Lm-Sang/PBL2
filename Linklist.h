#ifndef LinkList_h 
#define LinkList_h
#include <iostream>
#include <stdexcept>
#include <bits/stdc++.h>

using namespace std;

template <typename T>
class LinkList {
    private:
        struct Node {
            T data;
            Node* next;
            Node(const T& d, Node* n = nullptr) : data(d), next(n) {}
        };

        Node* head;
        int size;
    public:
        LinkList();      
        LinkList(const LinkList<T>& other);            
        ~LinkList();     
        bool update(int index, const T& newData);   
        void add(const T& value);
        void remove(int index); 
        T get(int index) const;       
        int getSize() const;       
        T& operator[] (int index) const;   
        void clear();
        void swapNodes(int index1, int index2) {
            if (index1 == index2) return;  // Nếu hai chỉ số trùng nhau thì không cần hoán đổi

            // Tìm node tại index1 và index2
            Node* prev1 = nullptr;
            Node* node1 = head;
            for (int i = 0; node1 != nullptr && i < index1; i++) {
                prev1 = node1;
                node1 = node1->next;
            }

            Node* prev2 = nullptr;
            Node* node2 = head;
            for (int i = 0; node2 != nullptr && i < index2; i++) {
                prev2 = node2;
                node2 = node2->next;
            }

            // Kiểm tra nếu một trong các node không tồn tại
            if (node1 == nullptr || node2 == nullptr) {
                cout << "Invalid indices, one or both nodes do not exist!" << endl;
                return;
            }

            // Hoán đổi các node
            if (prev1 != nullptr) {
                prev1->next = node2;
            } else {
                head = node2;  // Nếu node1 là đầu danh sách, cần cập nhật head
            }

            if (prev2 != nullptr) {
                prev2->next = node1;
            } else {
                head = node1;  // Nếu node2 là đầu danh sách, cần cập nhật head
            }

            // Hoán đổi next của các node
            Node* temp = node1->next;
            node1->next = node2->next;
            node2->next = temp;
        }
};

template <typename T>
LinkList<T>::LinkList(const LinkList<T>& other) {
    head = nullptr;
    size = 0;
    Node* current = other.head;
    while (current != nullptr) {
        add(current->data);
        current = current->next;
    }
}

template <typename T>
T& LinkList<T>::operator[](int index) const {
    // if (index < 0 || index >= size) {
    //     throw std::out_of_range("Index out of range");
    // }
    Node* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
LinkList<T>::LinkList() 
{
    head = nullptr;
    size = 0;
}

template <typename T>
LinkList<T>::~LinkList() 
{
    Node* current = head;
    while (current != nullptr) 
    {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

template <typename T>
void LinkList<T>::add(const T& value) 
{
    Node* newNode = new Node(value);
    if (!head) 
    {
        head = newNode;
    } 
    else 
    {
        Node* current = head;
        while (current->next != nullptr) 
        {
            current = current->next;
        }
        current->next = newNode;
    }
    ++size;
}

template <typename T>
void LinkList<T>::clear() {
    Node* current = head;
    head = nullptr; 
    size = 0;     
}

template <typename T>
void LinkList<T>::remove(int index) {
    // Kiểm tra chỉ số hợp lệ
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }

    Node* current = head; // Con trỏ hiện tại trỏ vào đầu danh sách

    if (index == 0) { // Xóa phần tử đầu tiên
        head = head->next; // Di chuyển đầu danh sách
        delete current;    // Giải phóng bộ nhớ
    } else {
        Node* prev = nullptr;

        // Duyệt đến vị trí cần xóa
        for (int i = 0; i < index; ++i) {
            prev = current;
            current = current->next;
        }

        // Nối nút trước với nút sau nút cần xóa
        prev->next = current->next;
        delete current; // Giải phóng bộ nhớ
    }

    --size; // Giảm kích thước danh sách
}


template <typename T>
bool LinkList<T>::update(int index, const T& newData) 
{
    if (index < 0 || index >= size) 
    {
        throw out_of_range("Index out of range");
    }
    Node* current = head;
    for (int i = 0; i < index; ++i) 
    {
        current = current->next;
    }
    current->data = newData;
    return true;
}

template <typename T>
T LinkList<T>::get(int index) const 
{
    if (index < 0 || index >= size) 
    {
        throw out_of_range("Index out of range");
    }
    Node* current = head;
    for (int i = 0; i < index; ++i) 
    {
        current = current->next;
    }
    return current->data;
}

template <typename T>
int LinkList<T>::getSize() const 
{
    return size;
}
#endif
