// Name: Ian Thomas
// Date: 5/7/2021
// Description: Create

#include <iostream>
#include <algorithm> // std::count
#include <exception>
#include <string>

using std::endl;
using std::string;
using std::cout;
using std::cin;

class TimeFormatMistake : public std::exception {
    virtual const char* what() const throw(){
        return "There is no such time as ";
    }
} fail;

// Creates an int pair of a passed time format string
std::pair<int,int> parseTime(string &input){
    int hr;
    int min;

    // String format must have only one instance of ':'
    if (std::count(input.begin(), input.end(), ':') != 1)
        throw fail;

    // Allows for input hours with value < 10
    hr = std::stoi(input.substr(0,input.find(':')));
    min = std::stoi(input.substr(input.find(':')+1));

    if (hr < 0 || hr > 23 || min < 0 || min > 59)
        throw fail;

    std::pair<int,int> p1(hr,min);

    return p1;
}

string convertTime(const std::pair<int,int> &time24){
    string hr;
    string min;
    
    if (time24.second < 10) { 
        min = "0" + std::to_string(time24.second); 
    } else { 
        min = std::to_string(time24.second); 
    }
    
    if (time24.first % 12 != 0)
        hr = std::to_string(time24.first % 12);
    else 
        hr = "12";

    if (time24.first < 12)
        return hr + ":" + min + " AM";
    else
        return hr + ":" + min + " PM";

}



int main()
{
    string input;
    char repeat;
    do {
        try {
            cout << "Enter time in 24-hour notation:" << endl;
            std::getline(cin, input);

            string result = convertTime(parseTime(input));
            
            cout << "That is the same as" << endl
                << result << endl
                << "Again? (y/n)" << endl;
            cin >> repeat;
            cin.ignore();
        }

        catch(std::exception& fail){
            std::cerr << fail.what() << input << endl;
            cout << "Try again:" << endl;
        }
    } while (repeat != 'n');

    return 0;
}