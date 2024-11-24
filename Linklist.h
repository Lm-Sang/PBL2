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
        ~LinkList();     
        bool update(int index, const T& newData);   
        void add(const T& value);
        void remove(int index); 
        T get(int index) const;       
        int getSize() const;       
        T& operator[] (int index) const;   
        void clear();
};

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
