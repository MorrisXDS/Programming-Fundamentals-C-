//
//  ShapeNode.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeNode class below
#include "ShapeNode.h"

ShapeNode::ShapeNode(){
    myShape = nullptr;
    next = nullptr;
}                 // sets myShape and next to nullptr
ShapeNode::~ShapeNode(){
    if(myShape != nullptr){
    delete myShape;
    myShape = nullptr;
    }
}                  // deletes the shape pointed to by myShape
Shape* ShapeNode::getShape() const{
    return myShape;
}       // returns myShape
void ShapeNode::setShape(Shape* ptr){
    myShape = ptr;
}     // sets myShape to ptr
ShapeNode* ShapeNode::getNext() const{
    return next;
}    // returns next
void ShapeNode::setNext(ShapeNode* ptr){
    next = ptr;
}  // sets next to ptr
void ShapeNode::print() const{
    this->getShape()->draw();
}
