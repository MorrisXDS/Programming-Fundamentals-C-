//
//  GroupList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupList class below
#include "GroupList.h"

GroupList::GroupList(){
    head = nullptr;
}                     // sets head to nullptr
GroupList::~GroupList(){
    while(head != nullptr){
        GroupNode* temp = head;
        setHead(head->getNext());
        delete temp;
        temp = nullptr;
    }
}                     // deletes all list nodes, including all the ShapeList
// attached to each GroupNode

GroupNode* GroupList::getHead() const{
    return head;
}      // returns the head pointer
void GroupList::setHead(GroupNode* ptr){
    head = ptr;
}     // sets the head pointer to ptr
void GroupList::insert(GroupNode* s){
    GroupNode* temp = head;
    if(head == nullptr){
        head = s;
        return;
    }
    else if(temp->getNext() == nullptr){
        head->setNext(s);
        return;
    }
    while(temp->getNext() != nullptr){
       temp = temp->getNext();
    }
    temp->setNext(s);
    return;
}
// inserts the node pointed to by s at the end of the list
GroupNode* GroupList::remove(string name){
    GroupNode* ptr = head;
    GroupNode* temp = nullptr;
    if(ptr == nullptr) {
        return nullptr;
    }
    else if(name == ptr->getName()){
        setHead(head->getNext());
        return ptr;
    }
    while(ptr != nullptr){
        if(name == ptr->getName()){
            if(ptr->getNext() == nullptr){
                temp->setNext(nullptr);
            }
            else{
                temp->setNext(ptr->getNext());
            }
            // cout<<temp->getName()<<endl;
            // cout<<temp->getNext()->getName()<<endl;
            // cout<<name<<" removed"<<endl;
            return ptr;
        }
        else{
            temp = ptr;
            ptr = ptr->getNext();
        }
    }
    return nullptr;
}   // removes the group with the name "name" from the list
// and returns a pointer to the removed GroupNode
// returns nullptr is name is not found on list
void GroupList::print() const{
    GroupNode* ptr = head;
    while(ptr != nullptr){
        ptr->print();
        ptr = ptr->getNext();
    }
}




