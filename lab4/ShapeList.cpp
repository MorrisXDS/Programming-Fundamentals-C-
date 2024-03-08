//
//  ShapeList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeList class below
#include "ShapeList.h"

ShapeList::ShapeList(){
    head = nullptr;
}                       // sets head to nullptr
ShapeList::~ShapeList(){
    if(head == nullptr){
        delete head;
    }
    else{
        while(head != nullptr){
            ShapeNode* ptr = head;
            head = head->getNext();
            delete ptr;
        }
    }
}                       // deletes all list nodes starting
// with head plus associated Shapes

ShapeNode* ShapeList::getHead() const{
    return head;
}         // returns the head pointer
void ShapeList::setHead(ShapeNode* ptr){
    head = ptr;
}       // sets the head pointer to ptr

ShapeNode* ShapeList::find(string name) const{
    ShapeNode* ptr = head;
    if(ptr == nullptr){
        return nullptr;
    }
    while(ptr != nullptr){
        if(ptr->getShape()->getName() == name){
            return ptr;
        }
        else {
            ptr = ptr->getNext();
        }
    }
    return nullptr;
} // finds a shape node with the specified shape name
// returns a pointer to the node if found, otherwise
// returns nullptr if the node is not found
void ShapeList::insert(ShapeNode* s){
    ShapeNode* temp = head;
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
}          // inserts the node pointed to by s at the end
// of the list; s should never be nullptr
ShapeNode* ShapeList::remove(string name){
    ShapeNode* ptr = head;
    ShapeNode* temp = nullptr;
    if(ptr == nullptr){
        return nullptr;
    }
    else if(name == head->getShape()->getName()){
        setHead(head->getNext());
        return ptr;
    }
    while(ptr != nullptr){
        if(ptr->getShape()->getName() == name){
            temp->setNext(ptr->getNext());
            return ptr;
        }
        else {
            temp = ptr;
            ptr = ptr->getNext();
        }
    }
    return nullptr;
}    // removes the node with the shape called name
// returns a pointer to the removed node or
// nullptr is a node with name does not exist
void ShapeList::print() const{
    ShapeNode* ptr = head;
    while(ptr != nullptr){
        ptr->getShape()->draw();
        ptr = ptr->getNext();
    }
}                 // prints the list

