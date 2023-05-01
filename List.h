#pragma once
#include <iostream>

template <typename T>
class Node
{
public:
    T value;
    Node<T>* next;
    Node<T>* previous;

    Node()
    {
        this->value = 0;
        this->next = nullptr;
        this->previous = nullptr;
    }
    Node(T value)
    {
        this->value = value;
        this->next = nullptr;
        this->previous = nullptr;
    }
};

template <typename T> class MyList {
public:
    Node<T>* head;
    Node<T>* last;

    MyList() {
        this->head = nullptr;
        this->last = nullptr;
    }

    int size() {
        Node<T>* current = head;
        int s = 0;
        while (current != nullptr) {
            s++;
            current = current->next;
        }
        return s;
    };

    Node<T>* elementAt(int index) {
        Node<T>* tmp = head;
        for (int i = 0; i < index; i++) {
            tmp = tmp->next;
        }
        return tmp;
    };

    T valueAt(int index) {
        return elementAt(index)->value;
    }

    void add(Node<T>* node) {
        if (head == nullptr) {
            head = node;
            last = node;
        }
        else {
            last->next = node;
            node->previous = last;
            last = node;
        }
    };

    void add(T value) {
        Node<T>* node = new Node<T>(value);
        add(node);
    }


    void deleteAt(int index) {
        Node<T>* node = elementAt(index);
        if (node->previous == nullptr && node->next == nullptr) {
            head = nullptr;
            last = nullptr;
        }
        else if (node->previous == nullptr) {
            node->next->previous = nullptr;
            head = node->next;

        }
        else if (node->next == nullptr) {
            node->previous->next = nullptr;
            last = node->previous;
        }
        else {
            //Node<T>* tmp = node->previous;
            //tmp->next=.....
            node->previous->next = node->next;
            node->next->previous = node->previous;

        }
    };

    Node<T>* find(T value) {
        Node<T>* tmp = head;
        while (tmp != nullptr) {
            if (tmp->value == value) {
                return tmp;
            }
            tmp = tmp->next;
        }
        return nullptr;
    }

    int findindex(T value) {
        int index = 0;
        Node<T>* tmp = head;
        while (tmp != nullptr) {
            if (tmp->value == value) {
                return index;
            }
            tmp = tmp->next;
            index++;
        }
        return index;
    }

    Node<T>* findBack(T value) {
        Node<T>* tmp = last;
        while (tmp != nullptr) {
            if (tmp->value == value) {

                return tmp;
            }
            tmp = tmp->previous;
        }
        return nullptr;
    }

    void toString(std::ostream& os) const
    {
        os << "[";
        Node<T>* current = head;
        while (current != nullptr)
        {
            os << current->value;
            if (current != last)
            {
                os << ", ";
            }
            current = current->next;
        }
        os << "]";
    }



};

template <typename T>
std::ostream& operator<<(std::ostream& os, const MyList<T>& list) {
    list.toString(os);
    return os;
}
