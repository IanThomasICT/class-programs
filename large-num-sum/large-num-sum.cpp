// Name: Ian Thomas
// Date: 6/22/2021
// Description: Calculate sum of numbers from a text file using a single linked list

#include <iostream>
#include <fstream>
#include <string>
#include <list>

using std::endl;
using std::cout;
using std::cin;


std::list<int> addList(std::list<int> list, size_t bottomRowSize);

int main() {
    std::ifstream infile;
    infile.open("nums.txt");
    if (!infile){
        std::cerr << "File not found." << endl;
        return -1;
    }

    std::string line;
    std::list<int> result;
    

    // Reads first line into the list
    std::getline(infile, line);
    for (unsigned int i = 0; i < line.size(); i++){
            result.push_back(line[i]-48); // convert char* to int
        }

    // Stores the next line into the linked list, returns the sum, repeats
    while(std::getline(infile, line)){
        for (unsigned int i = 0; i < line.size(); i++){
            result.push_back(line[i]-48); // convert char* to int
        }
        
        result = addList(result, line.size());
    }

	infile.close();

    // Print total summation and the first 10 digits
    std::list<int>::iterator it = result.begin();
    for (int i = 0; i < 10; i++){
        cout << *it++;
    }
    cout << endl;

    for (auto e : result){
        cout << e;
    }
    cout << endl;

    return 0;
}









/*  Calculates the sum of two strings of integers stored in one std::list
 *  Parameters:
 *      list         : std::list<int>, list of both strings of integers
 *      bottomRowSize: size_t, size of the bottom string of integers
 */
std::list<int> addList(std::list<int> list, size_t bottomRowSize){
    list.push_front(0); // Represents the end of the summation: list.begin()
    std::list<int> result;
    
    std::list<int>::iterator it1 = --list.end();
    std::list<int>::iterator it2 = --list.end(); // End of bottom string of ints

    // Sets first iterator at the end of the top string of integers
    for (size_t i = 0; i < bottomRowSize; ++i){
        it1--;
    }

    bool carry = false;
    int carryInt = 0;
    int total, top, bot;
    size_t it2_count = 0;
    while (it1 != list.begin() && it2 != list.begin()){
        if (it1 == list.begin()){               // Finished adding top row values
            top = 0;
            bot = *it2;
        } else if (it2_count >= bottomRowSize){ // Finished adding bottom row values
            top = *it1;
            bot = 0;  
        } else {
            top = *it1;
            bot = *it2;
        }
        
        carryInt = carry ? 1 : 0; // Determines if the previous sum had a carry (i.e. total > 9)
        total = top + bot + carryInt;
        result.push_front(total % 10);

        if (total >= 10)
            carry = true;
        else 
            carry = false;

        it1--; it2--; it2_count++;
    }

    if (carry)
        result.push_front(1);

    return result;    
}
