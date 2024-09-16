//partners: devdp2, loganeh2
//Aryan Shah
//ECE 220 FA22


#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include <iomanip>    
#include<vector>
using namespace std;

//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
    //Base class' constructor should be called in derived classes'
    //constructor to initizlize Shape's private variable 
    Shape(string name) {
        name_=name;
    }
    
    string getName() {
        return name_;
    }
    
    virtual double getArea() const = 0;
    virtual double getVolume() const = 0;
    
private:
  string name_;


};

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
template <class T>
class Rectangle : public Shape{
public:
    Rectangle<T>(T width, T length):Shape("Rectangle") {
        width_ = width;
        length_ = length;
    }

    double getArea() const {
        return getWidth() * getLength();
    }
    
    double getVolume() const {
        return 0;
    }
    
    Rectangle<T> operator + (const Rectangle<T>& rec) {
        double width2 = getWidth()+rec.getWidth();
        double length2 = getLength()+rec.getLength();
        if (width2 < 0){
            width2=0;
        }
        if (length2 < 0){
            length2=0;
        }
        Rectangle r = Rectangle(width2,length2);
        return r;
    }
    
    Rectangle<T> operator - (const Rectangle<T>& rec) {
        double width2 = getWidth()-rec.getWidth();
        double length2 = getLength()-rec.getLength();
        if (width2 < 0){
            width2=0;
        }
        if (length2 < 0){
            length2=0;
        }
        Rectangle r = Rectangle(width2,length2);
        return r;
    } 
    
    T getWidth() const { 
        return width_;
    }
    
    T getLength() const { 
        return length_;
    }
private:
    T width_;
    T length_;

};

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape{
public:
    Circle(double radius):Shape("Circle") {
        radius_ = radius; //assigns passed radius value to a private variable for use
    }
    
    double getArea() const{
        return(radius_ * radius_ * M_PI); //pir^2 area function
    }
    
    double getVolume() const{
        return 0; //circle has no volume
    }
    
    Circle operator + (const Circle& cir){
        return Circle(radius_ + cir.getRadius()); //recursively call Circle() to return a circle with added radii
    }
    
    Circle operator - (const Circle& cir){
        double rad1 = getRadius(); //get radius
        double rad2 = cir.radius_; //get passed circle radius
        double rad3 = rad1 - rad2; //calculate radius subtraction
        if(rad3 < 0) //check if new radius is negative
        {
            rad3 = 0; //then set radius to 0
        }
        return Circle(rad3); //return circle with new radius
    } 

    double getRadius() const { 
        return radius_; //return radius
    }
    
private:
    double radius_;

};



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape{
public:
    Sphere(double radius):Shape("Sphere") {
        radius_ = radius; //assigns passed radius value to a private variable for use
    }

    double getVolume() const {
        return ((4.0 / 3.0) * radius_ * radius_ * radius_ * M_PI); //volume is 4/3pir^3, use 4.0/3.0 for double type division
    }   
    
    double getArea() const {
        return (4 * M_PI * radius_ * radius_); //area is 4pir^2
    }

    Sphere operator + (const Sphere& sph) {
        return Sphere(radius_ + sph.getRadius()); //recursively call Sphere() to return a circle with added radii
    }

    Sphere operator - (const Sphere& sph) {
        double rad1 = getRadius(); //get radius
        double rad2 = sph.radius_; //get passed sphere radius
        double rad3 = rad1 - rad2; //calculate sphere subtraction
        if(rad3 < 0) //check if new sphere is negative
        {
            rad3 = 0; //then set radius to 0
        }
        return Sphere(rad3); //return sphere with new radius
    } 
    
    double getRadius() const {
        return radius_;
    }

private:
    double radius_;

};

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape{
public:
    RectPrism(double width, double length, double height):Shape("RectPrism") {
        width_=width;
        length_=length;
        height_=height;
    }
    
    double getVolume() const {
        return getWidth()*getHeight()*getLength();
    }
    
    double getArea() const {
        double one = getWidth()*getLength()*2;
        double two = getLength()*getHeight()*2;
        double three = getWidth()*getHeight()*2;
        return one+two+three;
    }
    
    RectPrism operator + (const RectPrism& rectp){
        double temp1 = getWidth()+rectp.getWidth();
        double temp2 = getLength()+rectp.getLength();
        double temp3 = getHeight()+rectp.getHeight();
        if(temp1 <0){
            temp1=0;
        }
        if(temp2 <0){
            temp2=0;
        }
        if(temp3 <0){
            temp3=0;
        }
        RectPrism r = RectPrism(temp1,temp2,temp3);
        return r;
    }
    
    RectPrism operator - (const RectPrism& rectp){
        double temp1 = getWidth()-rectp.getWidth();
        double temp2 = getLength()-rectp.getLength();
        double temp3 = getHeight()-rectp.getHeight();
        if(temp1 <0){
            temp1=0;
        }
        if(temp2 <0){
            temp2=0;
        }
        if(temp3 <0){
            temp3=0;
        }
        RectPrism r = RectPrism(temp1,temp2,temp3);
        return r;
    }   
    
    double getWidth() const { 
        return width_;
    }
    
    double getLength() const { 
        return length_;
    }
    
    double getHeight() const { 
        return height_;
    }
  
private:
    double length_;
    double width_;
    double height_;

};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
static list<Shape*> CreateShapes(char* file_name) {
    //@@Insert your code here
    list<Shape*> vec;
    string curshape;
    int vecsize;
    double param1, param2, param3;
    Shape* shapePointer;
    //Shape* head = shapePointer;
    ifstream ifs(file_name, std::ifstream::in);
    ifs >> vecsize; // store
    while (vecsize>0){
        ifs>>curshape;
        if(curshape=="Rectangle"){
            ifs >> param1;
            ifs >> param2;
            Shape* shapePointer = new Rectangle<double>(param1,param2);
            vec.push_back(shapePointer);
        }
        if(curshape=="Circle"){
            ifs >> param1;
            Shape* shapePointer = new Circle(param1);
            vec.push_back(shapePointer);
        }
        if(curshape=="RectPrism"){
            ifs >> param1;
            ifs >> param2;
            ifs >> param3;
            Shape* shapePointer = new RectPrism(param1,param2,param3);
            vec.push_back(shapePointer);
        }
        if(curshape=="Sphere"){
            ifs >> param1;
            Shape* shapePointer = new Sphere(param1);
            vec.push_back(shapePointer);
        }
        vecsize = vecsize-1;
        shapePointer++;

    }
    ifs.close();
    return vec;
}

// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
    double max_area = 0;
    //@@Insert your code here
    for(list<Shape*>::iterator it =shapes.begin(); it != shapes.end(); it++) {
        if((*it)->getArea() > max_area){
            max_area = (*it)->getArea();
        }
    }
    return max_area; //return final max_area value
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
    double max_volume = 0;
    //@@Insert your code here
    for(list<Shape*>::iterator it =shapes.begin(); it != shapes.end(); it++) {
        if((*it)->getVolume() > max_volume){
            max_volume = (*it)->getVolume();
        }
    }
    
    /*for(int i = 0; i < shapes.size(); i++) //loop thru every shape
    {
        if(shapes[i]->getVolume() > max_volume) //if the volume of the shape is > max volume
        {
            max_volume = shapes[i]->getVolume(); //set the max_volume to the new larger volume
        }
    }*/
    return max_volume; //return final max_volume value
}
#endif