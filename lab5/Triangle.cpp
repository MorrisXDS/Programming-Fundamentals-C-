//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright Â© 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Rectangle here
#include "Triangle.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

#include "Shape.h"


// Build a Circle object
Triangle::Triangle(string n, float xcent, float ycent, float x_1, float y_1, float x_2, float y_2, float x_3, float y_3):Shape(n, xcent, ycent) {
    //name = n;
    //x_centre = xcent;
    //y_centre = ycent;
    x1 = x_1;
    y1 = y_1;
    x2 = x_2;
    y2 = y_2;
    x3 = x_3;
    y3 = y_3;
}

Triangle::~Triangle() {
    // Nothing to do
}

// Accessor
// Accessor
float Triangle::getX1() const{
        return x1;
    }
    
float Triangle::getY1() const{
        return y1;
    }
    
float Triangle::getX2() const{
        return x2;
    } 
    
float Triangle::getY2() const{
        return y2;
    } 
    
float Triangle::getX3() const{
        return x3;
    } 
    
float Triangle::getY3() const{
        return y3;
    }        // Returns the radius of the circle

    // Mutator
void Triangle::setVertices(float x_1, float y_1, float x_2, float y_2, float x_3, float y_3){
        x1 = x1;
        y1 = y1;
        x2 = x2;
        y2 = y2;
        x3 = x3;
        y3 = y3;
}       // Sets the radius of the circle
    
    // Utility methods
void Triangle::draw() const{
    cout << std::fixed;
    cout << std::setprecision(2);

    cout<<"triangle: "<<name<<" "<<x_centre<<" "<<y_centre<<" "<<
    x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<x3<<" "<<y3<<" "<<computeArea()
    <<endl;
}
                                     // Draws thye circle; for the assignment it
                                   // prints the information of the circle
    
float Triangle::computeArea() const{
    float result = x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2);
    result = result/2;
    return (abs(result));
}  // Computes the area of the triangle
    
Shape* Triangle::clone() const {
    return (new Triangle(*this));
}


