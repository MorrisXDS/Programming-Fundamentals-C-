//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
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

// This is the shape array, to be dynamically allocated
Shape** shapesArray;



// The number of shapes in the database, to be incremented 
int shapeCount = 0;
int SCcopy = 0;
bool isinitialized = false;

int shpaeCountdeleted = 0;

// The value of the argument to the maxShapes command
int max_shapes;

int ifAllDeleted = 0;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
void ErrorArray(int num);
void commandIdentifier(string command,stringstream &lineStream);
void ArrayInitilization(stringstream &lineStream);
void recordTheShape(stringstream &lineStream);
bool CommandValid(string command);
bool ArgValid(stringstream &lineStream, string command);
void moveCommand(stringstream &lineStream);
void rotateCommand(stringstream &lineStream);
void drawCommand(stringstream &lineStream);
void deleteCommand(stringstream &lineStream);
bool NameValid(stringstream &lineStream, string command);
bool NameExist(stringstream &lineStream, string command);
bool typeValid(stringstream &lineStream, string command);
bool valueValid(stringstream &lineStream, string command);
bool argTooMany(stringstream &lineStream, string command);
bool argTooFew(stringstream &lineStream, string command);
bool ArrayisFull();
bool isNumber(float comp, string test);
bool isExist(string name);
bool dotpoint(stringstream& linestream);

int main() {
    
    string line;
    string command;
    
    cout << "> ";
    ifstream infile;
    infile.open("test.txt");
    if(infile.is_open()){
        getline(infile,line);
    }
    else{
        getline(cin, line);
    }         // Prompt for input

    while ( !cin.eof () ) {
        // cin.ignore(1000,'\n');
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here

        if(CommandValid(command) == true && command!=""){
            commandIdentifier(command,lineStream);
            // cin.ignore(1000,'\n');
        }
        else{
            cout<<"Error: invalid command"<<endl;
            
        }
        
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";       // Prompt for input
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
        }          // Prompt for input
     }  // End input loop until EOF.
    
    return 0;
}

void ErrorArray(int num){
    cout<<"Error: ";
    if(num==1){
        cout<<"invalid argument"<<endl;
        return;
    }
    else if(num==2){
        cout<<"invalid shape name"<<endl;
        return;
    }
    else if(num==3){
        return;
    }
    else if(num==4){
        return;
    }
    else if(num==5){
        cout<<"invalid shape type"<<endl;
        return;
    }
    else if(num==6){
        cout<<"invalid value"<<endl;
        return;
    }
    else if(num==7){
        cout<<"too many arguments"<<endl;
        return;
    }
    else if(num==8){
        cout<<"too few arguments"<<endl;
        return;
    }
    else if(num==9){
        cout<<"shape array is full"<<endl;
        return;
    }
    return;
}

void commandIdentifier(string command,stringstream &lineStream){
    if(command == "maxShapes"){
        ArrayInitilization(lineStream);
    }
    else if(command == "create"){
        recordTheShape(lineStream);
    }
    else if(command == "move"){
        moveCommand(lineStream);
    }
    else if(command == "rotate"){
        rotateCommand(lineStream);
    }
    else if(command == "draw"){
        drawCommand(lineStream);
    }
    else if(command == "delete"){
        deleteCommand(lineStream);
    }
    return;
}

void ArrayInitilization(stringstream &lineStream){
    stringstream streamtester(lineStream.str());
    string filler;
    string max;
    streamtester>>filler;
    streamtester>>max;
    if(ArgValid(lineStream,"maxShapes") == false && max !=""){
        ErrorArray(1);
        return;
    }
    else if(valueValid(lineStream,"maxShapes") == false){
        ErrorArray(6);
        return;
    }
    else if(argTooMany(lineStream,"maxShapes") == true){
        ErrorArray(7);
        return;
    }
    else if(argTooFew(lineStream,"maxShapes") == true){
        ErrorArray(8);
        return;
    }

    if(filler==""){
        return;
    }

    lineStream>>max_shapes;
    if(shapesArray == NULL){
        shapesArray = new Shape *[max_shapes];
    for(int i=0;i< max_shapes;i++){
        shapesArray[i] =NULL;
    }
    cout<<"New database: max shapes is "<<max_shapes<<endl;
    }
    else{
        for (int i = 0; i < shapeCount; i++)
            {
                if(shapesArray[i]){
                    delete shapesArray[i];
                    shapesArray[i] = NULL;
                }
            }
            delete shapesArray;
            shapesArray = NULL;
            shapeCount=0;
        shapesArray = new Shape *[max_shapes];
        for(int i=0;i< max_shapes;i++){
            shapesArray[i] = NULL;
        }
        cout<<"New database: max shapes is "<<max_shapes<<endl;
    }
    isinitialized = true;
    
}

void recordTheShape(stringstream &lineStream){
    string command;
    string name;
    string type;
    int x_location,y_location,x_size,y_size;
    stringstream streamtester(lineStream.str());
    streamtester>>command;
    streamtester>>name;

    if(command==""){
        cout<<"Error: invalid command"<<endl;
        return;
    }
    
    if(ArgValid(lineStream,"create") == false){
        ErrorArray(1);
        return;
    }
    else if(NameValid(lineStream,"create")== false){
        ErrorArray(2);
        return;
    }
    else if(NameExist(lineStream,"create")== true ){
        cout<<"Error: "<<"shape "<<name<<" exists"<<endl;
        return;
    }
    else if(typeValid(lineStream,"create")== false){
        ErrorArray(5);
        return;
    }
    else if(valueValid(lineStream,"create")== false && argTooFew(lineStream,"create") == false){
        ErrorArray(6);
        return;
    }
    else if(argTooMany(lineStream,"create")== true){
        ErrorArray(7);
        return;
    }
    else if(argTooFew(lineStream,"create")== true){
        ErrorArray(8);
        return;
    }
    else if(ArrayisFull()== true){
        ErrorArray(9);
        return;
    }

    lineStream>>name>>type>>x_location>>y_location>>x_size>>y_size;
    if(shapeCount>=max_shapes){
        ErrorArray(9);
        return;
    }
    shapesArray[shapeCount] = new Shape(name,type,x_location,x_size,y_location,y_size);
    shapeCount++;
    SCcopy++;
    cout<<"Created "<<name<<": "<<type<<" "<<x_location<<" "<<y_location<<" "<<x_size<<" "<<y_size<<endl;
    return;
}

void moveCommand(stringstream &lineStream){
    string name;
    int x_location,y_location;
    stringstream stream(lineStream.str());
    string buffer;
    stream>>buffer>>name;
    if(name=="" && buffer!=""){
        ErrorArray(8);
        return;
    }
    if(isExist(name) ==false && name!=""){
        cout<<"Error: "<<"shape "<<name<<" not found"<<endl;
        return;
    }
    else if(ArgValid(lineStream,"move") == false  ){
        ErrorArray(1);
        return;
    }
    else if(NameValid(lineStream,"move")== false ){
        ErrorArray(2);
        return;
    }
    else if(NameExist(lineStream,"rotate")== false && name !=""){
        cout<<"Error: "<<"shape "<<name<<" not found"<<endl;
        return;
    }
    else if(valueValid(lineStream,"move")== false){
        ErrorArray(6);
        return;
    }
    else if(argTooMany(lineStream,"move")== true){
        ErrorArray(7);
        return;
    }
    else if(argTooFew(lineStream,"move")== true){
        ErrorArray(8);
        return;
    }

    lineStream>>name>>x_location>>y_location;

    for (int i = 0; i < shapeCount; i++)
    {   
        if(shapesArray[i] == NULL){
            continue;
        }
        if(name == shapesArray[i]->getName()){
            shapesArray[i]->setXlocation(x_location);
            shapesArray[i]->setYlocation(y_location);
            cout<<"Moved "<<name<<" "<<"to "<<x_location<<" "<<y_location<<endl;
        }   }
}

void rotateCommand(stringstream &lineStream){
    string name;
    string extra;
    string flush;
    int angle;
    stringstream streamtester(lineStream.str());
    streamtester>>flush;
    streamtester>>name;
    streamtester>>extra;
    if(name=="" && flush!=""){
        ErrorArray(8);
        return;
    }

    if(isExist(name) ==false && name!=""){
        cout<<"Error: "<<"shape "<<name<<" not found"<<endl;
        return;
    }
    else if(ArgValid(lineStream,"rotate") == false){
        ErrorArray(1);
        return;
    }
    else if(NameValid(lineStream,"rotate") == false){
        ErrorArray(2);
        return;
    }
    else if(NameExist(lineStream,"rotate")== false  && name != "" ){
        cout<<"Error: "<<"shape "<<name<<" not found"<<endl;
        return;
    }
    else if(valueValid(lineStream,"rotate")== false){
        ErrorArray(6);
        return;
    }
    else if(argTooMany(lineStream,"rotate")== true){
        ErrorArray(7);
        return;
    }
    else if(argTooFew(lineStream,"rotate")== true){
        ErrorArray(8);
        return;
    }

    lineStream>>name>>angle;

    for (int i = 0; i < shapeCount; i++)
    {
        if(name == shapesArray[i]->getName()){
            shapesArray[i]->setRotate(angle);
            cout<<"Moved "<<name<<" by "<<angle<<" degrees"<<endl;
        }
    }
}

void drawCommand(stringstream &lineStream){
    string name;
    string extra;
    string flush;
    stringstream streamtester(lineStream.str());
    streamtester>>flush;
    streamtester>>name;
    streamtester>>extra;

    if(ArgValid(lineStream,"draw") == false){
        ErrorArray(1);
        return;
    }
    else if(NameValid(lineStream,"rotate") == false && name != "all"){
        ErrorArray(2);
        return;
    }
    else if(NameExist(lineStream,"draw")== false && name != "" && name !="all"){
        cout<<"Error: "<<"shape "<<name<<" not found"<<endl;
        return;
    }
    else if(argTooMany(lineStream,"draw")== true ){
        ErrorArray(7);
        return;
    }
    else if(argTooFew(lineStream,"draw")== true){
        ErrorArray(8);
        return;
    }

    lineStream>>name;
    if(name != "all"){
        for (int i = 0; i < (shapeCount); i++)
        {
            if(shapesArray[i] != NULL && name == shapesArray[i]->getName()){
                cout<<"Drew ";
                shapesArray[i]->draw();

            }
        }
    }
    else{
        if(SCcopy==0 ){
            cout<<"Drew all shapes"<<endl; 
            return;      
        }
        cout<<"Drew all shapes"<<endl; 
        for (int i = 0; i < (shapeCount+shpaeCountdeleted); i++)
        {   
            if(shapesArray[i]==NULL){
            continue;
            }
            if (shapesArray[i] != NULL) {
                shapesArray[i]->draw();
            }
        }
    }
}

void deleteCommand(stringstream &lineStream){
    string name;
    string extra;
    string flush;
    stringstream streamtester(lineStream.str());
    streamtester>>flush;
    streamtester>>name;
    streamtester>>extra;

    if(flush==""){
        cout<<"Error: invalid command"<<endl;
        return;
    }
    if(ArgValid(lineStream,"delete") == false){
        ErrorArray(1);
        return;
    }
    else if(NameValid(lineStream,"rotate") == false && name != "all"){
        ErrorArray(2);
        return;
    }
    else if(NameExist(lineStream,"delete")== false && name != "" && name !="all"){
        cout<<"Error: "<<"shape "<<name<<" not found"<<endl;
        return;
    }
    else if(argTooMany(lineStream,"delete")== true){
        ErrorArray(7);
        return;
    }
    else if(argTooFew(lineStream,"delete")== true){
        ErrorArray(8);
        return;
    }

    lineStream>>name;


    if(name != "all"){  
        cout<<"Deleted shape "<<name<<endl;
        for (int i = 0; i < shapeCount; i++)
        {
            if(shapesArray[i]){
                if(shapesArray[i]->getName() == name ){
                    delete shapesArray[i];
                    shapesArray[i] = NULL;
                    SCcopy--;
                }
            }
        }
    }
    else if(name == "all"){
        cout<<"Deleted: all shapes"<<endl;
        if(SCcopy==0){
            return;
        }
        for (int i = 0; i < max_shapes; i++)
        {
            if(shapesArray[i]){
                delete shapesArray[i];
                shapesArray[i] = NULL;
            }
        }
        delete []shapesArray;
        shapesArray = NULL;
        ifAllDeleted ++;
        shapeCount=0;
        SCcopy=0;
    }
}

bool CommandValid(string command){
    bool isCommand = false;

    for (int i = 1; i <NUM_KEYWORDS; i++)
    {
        if(keyWordsList[i] == command)
            isCommand = true;
    }
    return isCommand;
}

bool ArgValid(stringstream &lineStream, string command){
    stringstream copy(lineStream.str());
    bool ArgValid = false;
    string name,type,Ccommand;
    int x_loc,y_loc,x_size,y_size,angle;
    float Compar;
    int comp;
    string x_loc_test,y_loc_test,x_size_test,y_size_test,angle_test,max_shapes_test;
    copy>>Ccommand;
    
    if (command == "maxShapes")
    {
        copy>>max_shapes_test;
        stringstream test(max_shapes_test);
        test>>comp;
        string extra;
        if(test.fail()){
            return ArgValid;
        }
        else if(test.peek() == '\n'){
            return !ArgValid;
        }
        else if(test.peek() == '.'){
            return ArgValid;
        }
        else if(test>>extra){
            return ArgValid;
        }
        else
        {
            return !ArgValid;
        }
        // // else if(!isNumber(Compar, max_shapes_test)){
        // //     return ArgValid;
        // // }
        // // else{
        // //     max_shapes = (int) Compar;
        // //     if(Compar != max_shapes){
        // //         return ArgValid;
        // //     }
        //     else{
        //         return !ArgValid;
        //     }

        // // }
        
    }

    if (command == "create")
    {   
        copy>>name;
        
        if(name==""){
            return !ArgValid;
        }
        copy>>type;
        if(type==""){
            return !ArgValid;
        }

        Compar = -1.1F;

        copy>>x_loc_test;
        
        if(x_loc_test==""){
            return !ArgValid;
        }
        stringstream test1(x_loc_test);
        //bool doT = !dotpoint(test1);
        test1>>comp; 
        if(test1.fail()){
            return ArgValid;
            }
        else if(test1.peek() == '.' || test1.peek() != '/n' &&  test1.peek() != -1){
            return ArgValid;
            }


        Compar = -1.1F;

        copy>>y_loc_test;
        if(y_loc_test==""){
            return !ArgValid;
        }
        stringstream test2(y_loc_test);
        test2>>comp; 
        if(test2.fail()){
            return ArgValid;
            }
        else if(test2.peek() == '.' || test2.peek() != '/n' &&  test2.peek() != -1){
            return ArgValid;
            }

        Compar = -1.1F;

        copy>>x_size_test;
        if(x_size_test==""){
            return !ArgValid;
        }
        stringstream test3(x_size_test);
        test3>>comp; 
        if(test3.fail()){
            return ArgValid;
            }
        else if(test3.peek() == '.' || test3.peek() != '/n' &&  test3.peek() != -1){
            return ArgValid;
            }

        Compar = -1.1F;

        copy>>y_size_test;
        if(y_size_test==""){
            return !ArgValid;
        }
        stringstream test4(y_size_test);
        test4>>comp; 
        if(test4.fail()){
            return ArgValid;
            }
        else if(test4.peek() == '.' || test4.peek() != '/n' &&  test4.peek() != -1){
            return ArgValid;
            }

        return !ArgValid;
    }
    if (command == "move")
    {   
        copy>>name;
        if(name==""){
            return !ArgValid;
        }
        copy>>x_loc_test;
        if(x_loc_test==""){
            return !ArgValid;
        }
        stringstream move1(x_loc_test);
        move1>>comp; 
        if(move1.fail()){
            return ArgValid;
            }
        else if(move1.peek() == '.' || move1.peek() != '/n' &&  move1.peek() != -1){
            return ArgValid;
            }

        copy>>y_loc_test;
        if(y_loc_test==""){
            return !ArgValid;
        }
        stringstream move2(y_loc_test);
        move2>>comp; 
        if(move2.fail()){
            return ArgValid;
            }
        else if(move2.peek() == '.' || move2.peek() != '/n' &&  move2.peek() != -1){
            return ArgValid;
            }
        
        return !ArgValid;
    }
    
    if (command == "rotate")
    {
        copy>>name;
        if(name==""){
            return !ArgValid;
        }
        copy>>angle_test;
        if(angle_test==""){
            return !ArgValid;
        }
        stringstream rotate1(angle_test);
        rotate1>>comp; 
        if(rotate1.fail()){
            return ArgValid;
            }
        else if(rotate1.peek() == '.' || rotate1.peek() != '/n' &&  rotate1.peek() != -1){
            return ArgValid;
            }
        
        return !ArgValid;
    }

    if (command == "draw")
    {   
        return !ArgValid;
    }

    if (command == "delete")
    {
        return !ArgValid;
    } 
   
    return ArgValid;


}

bool NameValid(stringstream &lineStream, string command){
    stringstream streamChecker(lineStream.str());
    bool rightCommand = true;
    bool nameValid = false;
    string name;
    string flush;
    streamChecker>>flush;
    streamChecker>>name;
    
    if(command == "maxShapes"){
        nameValid = !nameValid; 
        return nameValid;  
    }
    
    if(command == "create"){
        for (int i = 0; i < NUM_KEYWORDS; i++)
        {
            if(name == keyWordsList[i]){
                return nameValid;
            }
        }
        for (int i = 0; i < NUM_TYPES; i++)
        {
            if(name == shapeTypesList[i]){
                return nameValid;
            }
        }
    }

    if(command == "move"){
        for (int i = 0; i < NUM_KEYWORDS; i++)
        {
            if(name == keyWordsList[i]){
                return nameValid;
            }
        }
        for (int i = 0; i < NUM_TYPES; i++)
        {
            if(name == shapeTypesList[i]){
                return nameValid;
            }
        }
    }

    if(command == "rotate"){
        for (int i = 0; i < NUM_KEYWORDS; i++)
        {
            if(name == keyWordsList[i]){
                return nameValid;
            }
        }
        for (int i = 0; i < NUM_TYPES; i++)
        {
            if(name == shapeTypesList[i]){
                return nameValid;
            }
        }
    }

    if(command == "draw"){
        for (int i = 1; i < NUM_KEYWORDS; i++)
        {
            if(name == keyWordsList[i]){
                return nameValid;
            }
        }
        for (int i = 0; i < NUM_TYPES; i++)
        {
            if(name == shapeTypesList[i]){
                return nameValid;
            }
        }
    }

    if(command == "delete"){
        for (int i = 1; i < NUM_KEYWORDS; i++)
        {
            if(name == keyWordsList[i]){
                return nameValid;
            }
        }
        for (int i = 0; i < NUM_TYPES; i++)
        {
            if(name == shapeTypesList[i]){
                return nameValid;
            }
        }
    }

    nameValid = !nameValid;
    return nameValid;
}

bool NameExist(stringstream &lineStream, string command){
    stringstream streamChecker(lineStream.str());
    bool NameExist = false;
    string name;
    string flush;
    streamChecker>>flush;
    streamChecker>>name;

    if(command == "maxShapes"){
        NameExist = !NameExist;
        return NameExist;
    }

    if(command == "create"){
        for (int i = 0; i < shapeCount; i++)
        {
            if( shapesArray[i] == NULL){
                continue;
            }
            if(name == shapesArray[i]->getName() ){
                NameExist = !NameExist;
                return NameExist;
            }
        }
    }

    if(command == "move"){

        if(shapeCount ==0){
            return NameExist;
        }
        for (int i = 0; i < shapeCount; i++)
        {   
            if( shapesArray[i] == NULL){
                continue;
            }
            if(name == shapesArray[i]->getName() ){
                NameExist = !NameExist;
                return NameExist;
            }
        }
    }

    if(command == "rotate"){
        if(shapeCount ==0){
            return NameExist;
        }
        for (int i = 0; i < shapeCount; i++)
        {   
            if( shapesArray[i] == NULL){
                continue;
            }
            if(name == shapesArray[i]->getName() ){
                NameExist = !NameExist;
                return NameExist;
            }
        }
    }

    if(command == "draw"){
        if(shapeCount ==0){
            return NameExist;
        }
        if(name =="all"){
            return !NameExist;
        }
        for (int i = 0; i < shapeCount; i++)
        {   
            if( shapesArray[i] == NULL){
                continue;
            }
            if(name == shapesArray[i]->getName()  && shapesArray[i] != NULL){
                NameExist = !NameExist;
                return NameExist;
            }
        }
        return NameExist;
    }

    if(command == "delete"){
        if(shapeCount == 0 ){
            return NameExist;
        }
        if(name =="all"){
            return !NameExist;
        }
        for (int i = 0; i < shapeCount; i++)
        {
            if( shapesArray[i] == NULL){
                continue;
            }
            if(name == shapesArray[i]->getName()){
                NameExist = !NameExist;
                return NameExist;
            }
        }
    }

    return NameExist;
}

bool typeValid(stringstream &lineStream, string command){
    bool typeValid = false;
    stringstream streamChecker(lineStream.str());
    string name;
    string type;
    string flush;
    streamChecker>>flush;
    streamChecker>>name;
    if(name ==""){
        typeValid = !typeValid;
        return typeValid;
    }

    streamChecker>>type;
    for (int i = 0; i < NUM_TYPES; i++)
    {
        if(type == shapeTypesList[i] || type ==""){
            typeValid = !typeValid;
            return typeValid;
        }
    }

    return typeValid;
}

bool valueValid(stringstream &lineStream, string command){
    string name;
    string type;
    int x_location,y_location,x_size,y_size,angle,value;
    stringstream streamChecker(lineStream.str());
    string flush;
    streamChecker>>flush;
    bool valueValid = false;

    if(command == "create"){
        streamChecker>>name;
        streamChecker>>type;
        streamChecker>>x_location;
        streamChecker>>y_location;
        streamChecker>>x_size;
        streamChecker>>y_size;
        if( x_location >= 0 && y_location>=0 && x_size>=0 && y_size>=0 ){
            if(type=="circle"){
                if(x_size==y_size){
                    valueValid = !valueValid;
                    return valueValid;
                }
                else{
                    return valueValid;
                }
            }
            else{   
                    valueValid = !valueValid;
                    return valueValid;
            } 
        }
    }

    if(command == "rotate"){
        if(streamChecker.peek() == EOF){
            return !valueValid;
        }
        streamChecker>>name;
        if(streamChecker.peek() == EOF){
            return !valueValid;
        }
        streamChecker>>angle;
        if(angle>=0 && angle<=360){
            valueValid = !valueValid;
            return valueValid;
        }
        else{
            return valueValid;
        }
    }
    
    if(command == "move"){
        streamChecker>>name;
        streamChecker>>x_location>>y_location;
        if( x_location >= 0 && y_location>=0){
            valueValid = !valueValid;
            return valueValid;
        }
        else{
            return valueValid;
        }
    }

    if(command == "maxShapes"){
        streamChecker>>value;
        if(value>=0){
            valueValid = !valueValid;
            return valueValid;
        }
        else{
            return valueValid;
        }
    } 

    return valueValid;
}

bool argTooMany(stringstream &lineStream, string command){
    bool arg2Many = false;
    string name;
    string type;
    int x_location,y_location,x_size,y_size,angle,value;
    stringstream streamChecker(lineStream.str());
    string flush;
    streamChecker>>flush;
    string test;

    if(command == "maxShapes"){
        streamChecker>>value;
        streamChecker>>test;
        if(!lineStream.fail() && test !=""){
            arg2Many = !arg2Many;
            return arg2Many;
        }
    }

    if(command == "create"){
        streamChecker>>name>>type>>x_location>>y_location>>x_size>>y_size;
        streamChecker>>test;
        if(!lineStream.fail() && test !=""){
            arg2Many = !arg2Many;
            return arg2Many;
        }
    }

    if(command == "move"){
        streamChecker>>name>>x_location>>y_location;
        streamChecker>>test;
        if(!lineStream.fail() && test !=""){
            arg2Many = !arg2Many;
            return arg2Many;
        }
    }

    if(command == "rotate"){
        streamChecker>>name>>angle;
        streamChecker>>test;
        if(!lineStream.fail() && test !=""){
            arg2Many = !arg2Many;
            return arg2Many;
        }
    }

    if(command == "draw"){
        streamChecker>>name;
        streamChecker>>test;
        if(!lineStream.fail() && test !=""){
            arg2Many = !arg2Many;
            return arg2Many;
        }
    }

    if(command == "delete"){
        streamChecker>>name;
        streamChecker>>test;
        if(!lineStream.fail() && test !=""){
            arg2Many = !arg2Many;
            return arg2Many;
        }
    }
     return arg2Many;
}

bool argTooFew(stringstream &lineStream, string command){
    bool arg2Few = false;
    string name;
    string type;
    int x_location,y_location,x_size,y_size,angle,value;
    stringstream streamChecker(lineStream.str());
    string flush;
    streamChecker>>flush;
    if(flush==""){
        cout<<"Error: invalid command"<<endl;
        return false;
     }
    else{
        if(command == "maxShapes"){
        streamChecker>>value;
        if(streamChecker.fail()){
            arg2Few = !arg2Few;
            return arg2Few;
        }
    }

    if(command == "create"){
        string x_loc,y_loc,x_sz,y_sz;
        streamChecker>>name>>type>>x_loc>>y_loc>>x_sz;
        if(streamChecker.peek() == EOF){
            arg2Few = !arg2Few;
            return arg2Few;
        }
    }

    if(command == "move"){
        streamChecker>>name>>x_location>>y_location;
        if(streamChecker.fail()){
            arg2Few = !arg2Few;
            return arg2Few;
        }
    }

    if(command == "rotate"){
        streamChecker>>name>>angle;
        if(streamChecker.fail()){
            arg2Few = !arg2Few;
            return arg2Few;
        }
    }

    if(command == "draw"){
        streamChecker>>name;
        if(streamChecker.fail() || name==""){
            arg2Few = !arg2Few;
            return arg2Few;
        }
    }

    if(command == "delete"){
        streamChecker>>name;
        if(streamChecker.fail() || name==""){
            arg2Few = !arg2Few;
            return arg2Few;
        }
    }
    }

    
     return arg2Few;
}

bool ArrayisFull(){
    bool shapefull = false;
    if(shapeCount==max_shapes || !isinitialized){
        return !shapefull;
    }
    return shapefull;
}

bool isNumber(float comp, string test){
    stringstream teststream;
    bool ArgValid=false;
    teststream<<test;
    float test1;
    teststream>>test1;
    stringstream fortest;
    fortest<<test1;
    string testcomp = fortest.str();
    teststream.str("");
    teststream<<comp;
    string teststring;
    float numl;
    teststream>>teststring;
    if(teststring == testcomp){
        return ArgValid;               
    }
    else{
        return !ArgValid;
    }
    return ArgValid;
}

bool isExist(string name){
    bool isExist = false;
    if(shapeCount ==0){
        return isExist;
        }
    for (int i = 0; i < shapeCount; i++)
    {   
        if( shapesArray[i] == NULL){
            continue;
        }
        if(name == shapesArray[i]->getName() ){
        isExist = !isExist;
        return isExist;
        }
        }
        return isExist;
}

bool dotpoint(stringstream& linestream){
    stringstream kay(linestream.str());
    bool dotpoint = false;
    while(cin.peek() != ' ' ){
            continue;
            if(cin.peek() == '.'){
                return !dotpoint; 
            }
    }
    return dotpoint;
}