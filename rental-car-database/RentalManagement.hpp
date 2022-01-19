#pragma once

#include "Car.hpp"
#include <vector> 
#include <iostream>

class RentalManagement {
    std::vector<Car> cars;
public:
    RentalManagement();
    RentalManagement(std::vector<Car> carList) : cars(carList) {}
    
    std::vector<Car> getList() { return cars; }

    bool carExist(int id){
        if (!validateID(id))
            return false;
        else {
            for (auto e : cars){
                if (e.getID() == id){
                    return true;
                }
            }
        }
        return false;
    }

    // Returns index of Car with the given id
    int locateCar(int id){
        if (!validateID(id))
            std::cout << "Invalid ID." << std::endl << std::endl;
        else {
            int idx = 0;
            for (auto e : cars){
                if (e.getID() == id){
                    return idx;
                }
                idx++;
            }

            std::cerr << "Car not found." << std::endl;  
        }
        
        return -1;   
    }

    // Returns the Car with the given id and prints information
    void searchByID(int id) { 
        if (!validateID(id))
            std::cout << "Invalid ID." << std::endl << std::endl;
        else {
            bool found = false;
            for (auto e : cars)
                if (e.getID() == id){
                    e.print();
                    found = true;
                }
            if (!found)
                std::cout << "Car not found." << std::endl << std::endl;
        }
    }

    // Returns Cars with the given make
    void searchByMake(std::string make) {
        bool found = false;
        for (auto e : cars)
            if (e.getMake() == make){
                e.print();
                found = true;
            }
        if (!found)
            std::cout << "Cars not found." << std::endl << std::endl;
    }

    void searchByModel(std::string model) {
        bool found = false;
        for (auto e : cars)
            if (e.getModel() == model){
                e.print();
                found = true;
            }
        if (!found)
            std::cout << "Cars not found." << std::endl << std::endl;
    }

    // Adds a car to the rental management directory using the given parameters
    void add(int id, std::string make, std::string model){
        // Verifies that ID is valid and car does not exist
        if (validateID(id))
            if(!carExist(id))
                cars.push_back(Car(id,make,model));

    }

    // Delete car from directory with corresponding id
    void del(int id) {
        if (locateCar(id) != -1){
            cars.erase(cars.begin() + locateCar(id));
            std::cout << "Removing car from directory.." << std::endl << std::endl;
        } 
    }

    // Print all cars in rental management directory
    void printCars() {
        for (auto e : cars){
            e.print();
        }
    }

    bool validateID(int id) { return id > 0 ? true : false; }
};
