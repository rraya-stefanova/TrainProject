#include <iostream>
#include "SkipList.hpp"
#include <string>
#include <vector>

int main()
{

    int n;
    std::cin >> n;

    Node<std::string> *head = new Node<std::string>{"",nullptr,nullptr};
    Node<std::string> *curr = head;
    for (int i = 0; i < n; i++){
        std::string name;
        std::cin >> name;
        curr -> next = new Node<std::string>{name,nullptr,nullptr};
        curr = curr -> next;
    }

    SkipList<std::string> *sl1 = new SkipList<std::string>(head -> next);
    sl1->addConnection("Sofia", "Plovdiv");
    sl1->addConnection("Plovdiv", "NovaZagora");
    sl1->addConnection("Dimitrovgrad", "NovaZagora");
    sl1->addConnection("StaraZagora", "Yambol");
    sl1->addConnection("NovaZagora", "Burgas");

    Node<std::string> *wn1 = new Node<std::string>{"Plovdiv", nullptr, nullptr};
    Node<std::string> *wn2 = new Node<std::string>{"StaraZagora", nullptr, nullptr};
    Node<std::string> *wn3 = new Node<std::string>{"Yambol", nullptr, nullptr};

    wn1->next = wn2;
    wn2->next = wn3;

    curr = head -> next;
    Node<std::string> *wishedDestination = wn1;

    std::vector<Node<std::string>*> finalRoute;

    while (wishedDestination != nullptr)
    {
        if (curr->value == wishedDestination->value)
        {
            // destination reached
            wishedDestination = wishedDestination->next;
        }
        else if (curr->nextOptional->nodeIndex <= sl1->getNodeIndex(wishedDestination))
        {
            // will miss the wanted destination by "jumping"
            finalRoute.push_back(curr);
            curr = curr->nextOptional;
        }
        else
        {
            finalRoute.push_back(curr);
            curr = curr->next;
        }
    }
    while (curr != nullptr)
    {
       
        finalRoute.push_back(curr);
        curr = curr->next;
    }

    for( Node<std::string>* r : finalRoute){
        std::cout << r->value << " ";
    }
    return 0;
}