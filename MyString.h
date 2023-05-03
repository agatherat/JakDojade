#pragma once
#include <iostream>
#include <cstring>

class MyString
{
private:
    int size;
    char* data;

public:
    MyString() {
        size = 0;
        data = nullptr;
    }

    MyString(const char* str) {
        size = strlen(str);
        data = new char[size];
        for (int i = 0; i < size; i++) {
            data[i] = str[i];
        }
    }

    MyString(const MyString& other) {
        size = other.size;
        data = new char[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    MyString operator+(const char ch) {
        MyString created;
        created.size = size + 1;
        created.data = new char[created.size];

        for (int i = 0; i < size; i++) {
            created.data[i] = data[i];
        }
        created.data[created.size - 1] = ch;
        return created;
    }

    MyString& operator=(const MyString& other) {
        if (this != &other) {
            if (data != nullptr) {
                delete[] data;
            }
            size = other.size;
            data = new char[size];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    char& operator[](int index) {
        return data[index];
    }

    int length() {
        return size;
    }

    bool operator==(const MyString& other) const {
        if (other.size != size) return false;

        for (int i = 0; i < size; i++) {
            if (other.data[i] != data[i]) {
                return false;
            }
        }
        return true;
    }

    ~MyString() {
        if (data != nullptr)
            delete[] data;
    }

    friend std::ostream& operator<<(std::ostream& os, const MyString& str) {
        for (int i = 0; i < str.size; ++i) {
            os << str.data[i];
        }
        return os;
    } 

    //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    friend std::istream& operator>>(std::istream& is, MyString& str) {
        char buffer[1024];
        is >> buffer;
        str = MyString(buffer);
        return is;
    }

};