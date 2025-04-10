#pragma once
#include <String>

template <typename T>
struct Node {

    T value;
    Node* next = nullptr;
    Node* nextOptional = nullptr;
    inline static int indexInList = 0;
    int nodeIndex = 0;

    Node(T value,Node* next, Node* nextOpt) {
        this -> value = value;
        this -> next = next;
        nextOptional = nextOpt;

        this -> nodeIndex = indexInList++;
    }

};



template <typename T>
class SkipList {

    Node<T>* head;

public: 

    SkipList() {
        this -> head = new Node<T>();
    }

    SkipList(Node<T>*& headNode){
        head = headNode;
    }

    void addConnection(T stopOne, T stopTwo) {

        Node<T>* curr = head;
        Node<T>* stopOneNode = nullptr, *stopTwoNode = nullptr;

        while(curr != nullptr) {

            if(curr->value == stopOne){
                stopOneNode = curr;
            }
            else if(curr->value == stopTwo){
                stopTwoNode = curr;
                break;
            }
            curr = curr -> next;

        }

        stopOneNode -> nextOptional = stopTwoNode;
    }


    int getNodeIndex(Node<T>*& wantedNode) {

        Node<T>* curr = head;
        while(curr != nullptr){
            if(curr -> value == wantedNode -> value){
                return curr -> nodeIndex;
            }
            curr = curr -> next;
        }

        return -1;
    }
};