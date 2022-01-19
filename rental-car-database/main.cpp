// Name: Ian Thomas 
// Data: 6/10/2021
// Description: Rental car company program

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Car.hpp"
#include "RentalManagement.hpp"

using std::endl;
using std::cout;
using std::cin;


void printMenu();
void searchByID(RentalManagement rentals);
void searchByMake(RentalManagement rentals);
void searchByModel(RentalManagement rentals);
void addCar(RentalManagement &rentals);
void deleteCar(RentalManagement &rentals);
void listDirectory(RentalManagement rentals);


int main(){

    bool exit = false;
    std::vector<Car> carList;

    // Import Cars data
    std::ifstream infile;
    infile.open("cars.data");

    if (!infile){
        std::cerr << "Unable to import car data" << endl;
        return -1;
    }

    int carNum;
    infile >> carNum;
    infile.ignore();

    std::string line;
    std::vector<std::string> carInfo(3);
    for (int i = 0; i < carNum; i++) {
        for (int j = 0; j < 3; j++) {
            std::getline(infile, line);
            carInfo[j] = line;
        }
        carList.push_back( Car(std::stoi(carInfo[0]),carInfo[1], carInfo[2]));
    } 
    infile.close();

    RentalManagement rentals(carList);

    // Management System Header/UI
    cout << "----------------------------" << endl
         << "CAR RENTAL MANAGEMENT SYSTEM" << endl;
    
    do {
        int input;
        cout << "----------------------------" << endl;
        printMenu();
        cin >> input;
        if (input > 0 && input < 7){
            cin.ignore();
            switch(input){
                case 1 :
                    searchByID(rentals);    
                    break;
                case 2 :
                    searchByMake(rentals);
                    break;
                case 3 :
                    searchByModel(rentals);
                    break;
                case 4 :
                    addCar(rentals);
                    break;
                case 5 :
                    deleteCar(rentals);
                    break;
                case 6 :
                    listDirectory(rentals);
                    break;
            }
        } else {
            exit = true;
        }
        
    } while (!exit);

    // Write carList into file
    std::ofstream outfile;
    outfile.open("cars.data");

    carList = rentals.getList();
    outfile << carList.size() << endl;
    for (unsigned int i = 0; i < carList.size(); ++i){
        outfile << carList[i].getID() << endl;
        outfile << carList[i].getMake() << endl;
        outfile << carList[i].getModel() << endl;
    }

    outfile.close();

    return 0;
}






void printMenu() {
    cout << "Options: " << endl
         << "\t 1. Search by ID" << endl
         << "\t 2. Search by Make" << endl
         << "\t 3. Search by Model" << endl
         << "\t 4. Add Car to List" << endl
         << "\t 5. Delete Car from list" << endl
         << "\t 6. Car Directory" << endl
         << "\t 0. Save and Exit" << endl
         << "Enter selection: "; 
}

void searchByID(RentalManagement rentals){
    int id;
    cout << "----------------------------" << endl << endl;
    cout << "Enter Car ID: ";
    cin >> id;
    rentals.searchByID(id);
}
void searchByMake(RentalManagement rentals) {
    std::string make;
    cout << "----------------------------" << endl << endl;
    cout << "Enter Car Make: ";
    std::getline(cin, make);
    rentals.searchByMake(make);
}
void searchByModel(RentalManagement rentals){
    std::string model;
    cout << "----------------------------" << endl << endl;
    cout << "Enter Car Model: ";
    std::getline(cin, model);
    rentals.searchByModel(model);
}

void addCar(RentalManagement &rentals){
    int id;
    std::string make;
    std::string model;
    cout << "----------------------------" << endl << endl;
    cout << "Enter Car Details:" << endl
            << "\tCar ID: ";
    cin >> id;
    cin.ignore();
    int tries = 0;
    // Request valid information for new car
    while (rentals.carExist(id) || !rentals.validateID(id)){
        if (!rentals.validateID(id)) {
            cout << "\tInvalid ID." << endl << endl
                 << "\tCar ID: ";
            cin  >> id;
            cin.ignore();
        } else {
            cout << "\tCar ID already exists." << endl << endl;
            cout << "\tCar ID: ";
            cin  >> id;
            cin.ignore();
        }
        ++tries;
        
        if (tries > 3) {
            cout << "\tToo many attempts. Exiting to menu." << endl << endl;
            return;
        }
    }

    cout << "\tCar Make: ";
    std::getline(cin, make);
    cout << "\tCar Model: ";
    std::getline(cin, model);
    rentals.add(id, make, model);
}

void deleteCar(RentalManagement &rentals) {
    int id;
    char choice;
    cout << "----------------------------" << endl << endl
         << "Enter Car ID: ";
    cin  >> id;
    if (!rentals.carExist(id)){
        cout << "Car not found." << endl << endl;
    } else {
        cout << "Are you sure you want to delete this car?" << endl;
        rentals.searchByID(id);
        cout << "(Y/N) : ";
        cin >> choice;
        choice = std::toupper(choice);

        if (choice == 'Y')
            rentals.del(id);
    }
}

void listDirectory(RentalManagement rentals) {
    cout << "----------------------------" << endl << endl;
    rentals.printCars();
}