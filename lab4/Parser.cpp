//
//  parser.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

// This is a pointer to the groups list
// The list itself must be allocated
GroupList* gList;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
void commandParser(string& command,stringstream& lineStream);
void shapeCommand(stringstream& lineStream, string& command);
void groupCommand(stringstream& lineStream, string& command);
void drawCommand(stringstream& lineStream);
void moveCommand(stringstream& lineStream, string& command);
void deleteCommand(stringstream& lineStream, string& command);
bool nameValid(string& name);
bool shapeNameExist(string& name);
bool groupNameExist(string& name);
void errorArray(int Index,string& name);
bool nameExist(string& name);
ShapeNode* sNFinder(string& name);
GroupNode* gNFinder(string& name);
void shapeNodeRemover(string& name);
void listtransfer(ShapeNode*& test);


int main() {
    // Create the groups list
    gList = new GroupList();

    // Create the pool group and add it to the group list
    GroupNode *poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS - 1]);
    gList->insert(poolGroup);
    string line;
    string command;

    fstream inFile;

    cout << "> ";
    ifstream infile;
    infile.open("test.txt");
    if(infile.is_open()){
        getline(infile,line);
    }
    else{
        getline(cin, line);
    }          // Prompt for input
    // getline(cin, line);
    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream(line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        if (lineStream.fail()) {
            lineStream.clear();//clear bad bits
            lineStream.ignore(10000, '\n');//clear the buffer in the stream
        }
        else {
            commandParser(command, lineStream);//porecess commands
        }

            // Check for the command and act accordingly
            // ECE244 Student: Insert your code here

            // Once the command has been processed, prompt for the
            // next command
            // Prompt for input
            cout << "> ";
             if(infile.is_open()){
                getline(infile,line);
                if(infile.eof())
                {
               //infile.close();
                getline(cin,line);
                }
        }
        else{
            getline(cin,line);
        }  
                 // Prompt for input
            // getline(cin, line);
        }  // End input loop until EOF.

        return 0;

    //}
}


void commandParser(string& command, stringstream& lineStream){//process command
    if(command == "shape"){
        shapeCommand(lineStream,command);
    }
    else if(command == "group"){
        groupCommand(lineStream,command);
    }
    else if(command == "draw"){
        drawCommand(lineStream);
    }
    else if(command == "move"){
        moveCommand(lineStream,command);
    }
    else if(command == "delete"){
        deleteCommand(lineStream,command);
    }
}

//identify errors for command 'shape' and append the correct ShapeNode* to pool Group
void shapeCommand(stringstream& lineStream, string& command){
    string name;
    string type;
    int x_location, y_location, x_size, y_size;
    lineStream>>name;
    if(!nameValid(name)){
        errorArray(1,name);
        return;
    }
    else if(nameExist(name)){
        errorArray(2,name);
        return;
    }

    lineStream>>type;
    lineStream>>x_location>>y_location>>x_size>>y_size;
    ShapeNode* tempNode = new ShapeNode();//create ShapeNode on heap
    Shape* ptr = new Shape(name,type,x_location,y_location,x_size,y_size);//create Shape on heap
    tempNode->setShape(ptr);
    gList->getHead()->getShapeList()->insert(tempNode);
    ptr = nullptr;
    cout<<name<<": "<<type<<" "<<x_location<<" "<<y_location<<" "<<x_size<<" "<<y_size<<endl;
}

//identify errors for command 'group' and append a new group* to gList
void groupCommand(stringstream& lineStream, string& command){
    string name;
    lineStream>>name;
    if(!nameValid(name)){
        errorArray(1,name);
        return;
    }
    else if(nameExist(name)) {
        errorArray(2,name);
        return;
    }

    GroupNode* temp =new GroupNode(name);//create a GroupNode on heap
    gList->insert(temp);//append it to gList
    cout<<name<<": group"<<endl;
}

void drawCommand(stringstream& lineStream){//draw shapes in the order of shapeNode creation in pool / the order of shapeNode being moved for other groups
    cout<<"drawing:"<<endl;
    gList->print();
}

//identify errors for command 'move' and remove the target ShapeNode* from the orginal group so as to append it to the target group
void moveCommand(stringstream& lineStream, string& command){
    string shapeName, groupName;
    lineStream>>shapeName>>groupName;

    if(!nameValid(shapeName)){
        errorArray(1,shapeName);
        return;
    }
    else if(sNFinder(shapeName) == nullptr){
        errorArray(3, shapeName);
        return;
    }
    else if(!nameValid(groupName)){
        errorArray(1,groupName);
        return;
    }
    else if(gNFinder(groupName) == nullptr){
        errorArray(4,groupName);
        return;
    }

    ShapeNode* snTarget = sNFinder(shapeName); //Find the target ShapeNode*
    shapeNodeRemover(shapeName);//Remove the ShapeNode with 'shapeName' from the current group
    snTarget->setNext(nullptr);
    GroupNode* targetGN = gNFinder(groupName);//Find the target GroupNode*
    targetGN->getShapeList()->insert(snTarget);
    cout<<"moved "<<shapeName<<" "<<"to "<<groupName<<endl;
}

//identify errors for command 'delete' and determine if it's ShapeNode*/GroupNode* then process accordingly
void deleteCommand(stringstream& lineStream, string& command){
    string name;
    lineStream>>name;
    if(!nameValid(name)){
        errorArray(1,name);
        return;
    }
    else if(!nameExist(name)){
        errorArray(3,name);
        return;
    }

    cout<<name<<": deleted"<<endl;
    if(sNFinder(name) != nullptr){
        ShapeNode* shapeD = sNFinder(name);//find the ShapeNode*
        shapeNodeRemover(name);//remove the shapeNode* from the current group, build up a bridge betwee nthe previous node and next one
        shapeD->setNext(nullptr);//set next to nullptr as its safer
        delete shapeD;//delete the shape pointed to by shapeD
    }
    else{
        GroupNode* toDel = gNFinder(name);//find the GroupNode
        gList->remove(name);//remove the GroupNode from gList so the list works good in logic when pointing to the next of the node prior the deleted one
        ShapeNode* insert = toDel->getShapeList()->getHead();//shapeNode* of the groupNode*
        while(insert != nullptr){
            listtransfer(insert);//append the shapeNodes* of the groupNode* to the poolGroup*
            insert = insert->getNext();
        }
        delete toDel;//delete the group
    }
    
}

//check if the names valid, if valid return true otherwise false
bool nameValid(string& name){
    bool nameValid = true;
    for (int i = 0; i < NUM_KEYWORDS; ++i) {
        if(keyWordsList[i] == name){//check if the name's one of the key words
            return !nameValid;
        }
    }

    for (int i = 0; i < NUM_TYPES; ++i) {//check if the name's one of the shapes keywords
        if(shapeTypesList[i] == name){
            return !nameValid;
        }
    }
    return nameValid;
}

//error output array to reduce amounts of code written
void errorArray(int Index,string& name){
    if(Index == 1){
        cout<<"error: invalid name"<<endl;
    }
    else if(Index == 2){
        cout<<"error: name "<<name<<" exists"<<endl;
    }
    else if(Index == 3){
        cout<<"error: shape "<<name<<" not found"<<endl;
    }
    else if(Index == 4){
        cout<<"error: group "<<name<<" not found"<<endl;
    }
}

//return the ShapeNode* with name if found otherwise return null pointer
ShapeNode* sNFinder(string& name){
    GroupNode* temp = gList->getHead();
    ShapeNode* target = nullptr;
    while(temp != nullptr){
        if(temp->getShapeList()->find(name) != nullptr){
            target = temp->getShapeList()->find(name);
            return target;
        }
        else{
            temp = temp->getNext();
        }
    }
    return nullptr;
}

//return the GroupNode* with name if found,r eturn null pointer otherwise
GroupNode* gNFinder(string& name){
   GroupNode* GNtemp = gList->getHead();
   GroupNode* targetGN = nullptr;
   while(GNtemp != nullptr){
       if(name == GNtemp->getName()){
           targetGN = GNtemp;
           return targetGN;
       }
       else{
           GNtemp = GNtemp->getNext();
       }
   }
   return nullptr;
}

//returns true if there is the name used for either a groupNode* or a shapeNode*
bool nameExist(string& name){
    bool nameExist = false;
    if(gNFinder(name) != nullptr || sNFinder(name) != nullptr){
        return !nameExist;
    }
    return nameExist;
}

//removes a ShapeNode* from its group
void shapeNodeRemover(string& name) {
    GroupNode *tempHead = gList->getHead();
    while(tempHead != nullptr){
        if(tempHead->getShapeList()->find(name) != nullptr){
            tempHead->getShapeList()->remove(name);
        }
        else{
            tempHead = tempHead->getNext();
        }
    }
}

//copies the content of the shapesArray of the to-be-deketed groupnode* and append it to the poolGroup
void listtransfer(ShapeNode*& test){//test: the head pointer of the  shapelist of the to_be_deleted group
        string name = test->getShape()->getName();
        string type = test->getShape()->getType();
        int x_loc = test->getShape()->getXlocation();
        int y_loc = test->getShape()->getYlocation();
        int x_sz = test->getShape()->getXsize();
        int y_sz = test->getShape()->getYsize();
        ShapeNode* newNode = new ShapeNode();
        Shape* newShapes = new Shape(name,type,x_loc,y_loc,x_sz,y_sz);
        newNode->setShape(newShapes);
        gList->getHead()->getShapeList()->insert(newNode);
}
