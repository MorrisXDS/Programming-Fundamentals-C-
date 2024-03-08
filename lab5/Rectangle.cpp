//
//  Rectangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class here

#include "Rectangle.h"

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

Rectangle::Rectangle (string n, float xcent, float ycent, float wid, float heit):Shape(n, xcent, ycent){
    //name = n;
    //x_centre = xcent;
    //y_centre = ycent;
    width = wid;
    height = heit;

}
    
    // Destructor
Rectangle::~Rectangle(){
    //do nothing
}
    
    // Accessor
float Rectangle::getwidth() const{
    return width;
} 
    
float Rectangle::getheight() const{
    return height;
}      // Returns the radius of the circle

    // Mutator
void Rectangle::setWidth(float kuan){
    width = kuan;
}  
    
void Rectangle::setHeight(float gao){
    height = gao;
}     // Sets the radius of the circle
    
    // Utility methods
void Rectangle::draw() const{
    cout << std::fixed;
    cout << std::setprecision(2);
    
    cout<<"rectangle: "<<name<<" "<<x_centre<<" "<<y_centre<<" "<<
    width<<" "<<height<<" "<<computeArea()<<endl;
}     // Draws thye circle; for the assignment it
                                   // prints the information of the circle
    
float Rectangle::computeArea() const{
    return height*width;
}  // Computes the area of the circle

Shape* Rectangle::clone() const{
    return (new Rectangle(*this));
}  // Clones the object
