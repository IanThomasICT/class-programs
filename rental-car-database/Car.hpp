#pragma once

#include <iostream>

class Car {
    int _id;
    std::string _make;
    std::string _model;
public:
    Car() : _id(-1), _make("Ford"), _model("F150") {}
    Car(int id, std::string make, std::string model) : _id(id), _make(make), _model(model) {}
    void print() { 
        std::cout << "\tID: " << _id << std::endl 
             << "\tMake: " << _make << std::endl 
             << "\tModel: " << _model << std::endl << std::endl; 
    }

    int getID() { return _id; }
    std::string getMake()  { return _make; }
    std::string getModel() { return _model; }

    void setID(int id) { _id = id; }
    void setMake(std::string make) { _make = make; }
    void setModel(std::string model) { _model = model; }   
};