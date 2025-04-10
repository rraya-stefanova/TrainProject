#include <iostream>
#include "SkipList.hpp"
#include <string>

int main()
{


    Node<std::string>* n1 = new Node<std::string>{"Sofia",nullptr,nullptr};
    Node<std::string>* n2 = new Node<std::string>{"Pazardjik",nullptr,nullptr};
    Node<std::string>* n3 = new Node<std::string>{"Plovdiv",nullptr,nullptr};
    Node<std::string>* n4 = new Node<std::string>{"Dimitrovgrad",nullptr,nullptr};
    Node<std::string>* n5 = new Node<std::string>{"StaraZagora",nullptr,nullptr};
    Node<std::string>* n6 = new Node<std::string>{"NovaZagora",nullptr,nullptr};
    Node<std::string>* n7 = new Node<std::string>{"Yambol",nullptr,nullptr};
    Node<std::string>* n8 = new Node<std::string>{"Karnobat",nullptr,nullptr};
    Node<std::string>* n9 = new Node<std::string>{"Burgas",nullptr,nullptr};

    n1 -> next = n2;
    n2 -> next = n3;
    n3 -> next = n4;
    n4 -> next = n5;
    n5 -> next = n6;
    n6 -> next = n7;
    n7 -> next = n8;
    n8 -> next = n9;

    SkipList<std::string>* sl1 = new SkipList<std::string>(n1);
    sl1->addConnection("Sofia","Plovdiv");
    sl1->addConnection("Plovdiv","NovaZagora");
    sl1->addConnection("Dimitrovgrad","NovaZagora");
    sl1->addConnection("StaraZagora","Yambol");
    sl1->addConnection("NovaZagora","Burgas");

    Node<std::string>* wn1 = new Node<std::string>{"Plovdiv",nullptr,nullptr};
    Node<std::string>* wn2 = new Node<std::string>{"StaraZagora",nullptr,nullptr};
    Node<std::string>* wn3 = new Node<std::string>{"Yambol",nullptr,nullptr};


    wn1 -> next = wn2;
    wn2 -> next = wn3;

    Node<std::string>* curr = n1;
    Node<std::string>* wishedDestination = wn1;
    while(wishedDestination != nullptr){
        if(curr -> value == wishedDestination -> value ){
            // destination reached
            wishedDestination = wishedDestination -> next;
            
        }
        else if(curr -> nextOptional -> nodeIndex <= sl1->getNodeIndex(wishedDestination)){
            // will miss the wanted destination by "jumping"
            std::cout << curr -> value << " ";
            curr = curr -> nextOptional;
            
        }
        else{
            std::cout << curr -> value << " ";
            curr = curr -> next;
        }
    }
    while( curr != nullptr){
        
        std::cout << curr -> value << " ";
        curr = curr -> next;
    }
    std::cout << std::endl;
    return 0;
}