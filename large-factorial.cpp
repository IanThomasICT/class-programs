// Name: Ian Thomas
// Date: 2/12/2021
// Description: Uses vectors to calculate the factorial of reasonably large numbers

#include <iostream>
#include <vector>
#include <algorithm>

using std::endl;
using std::cout;
using std::cin;

std::vector<int> factorial(int input);

int main()
{
    int input;

    cout << "Enter a factorial: ";
    cin >> input;

    std::vector<int> result = factorial(input);
    
    
    std::reverse(result.begin(), result.end());
    cout << "Factorial of " << input << ": ";
    for (auto e : result){
        cout << e;
    }
    cout << endl;
}







std::vector<int> factorial(int input){
    std::vector<int> result{1};
    int carry = 1; // Set to 1 for 0!
    int product;
    int numOfDigits;
    for (int j = 0; j <= input; ++j){ // Multiplier
        numOfDigits = result.size();
        for (int i = 0; i < numOfDigits; ++i){
            product = result[i] * j + carry;
            carry = product / 10; 
			if (carry > 0 && i == numOfDigits-1){ // Expands vector to include remaining carry
                result[i] = product % 10;
                while (carry != 0){
                    result.push_back(carry % 10);
                    carry = carry / 10;
                }
            } else {
                result[i] = product % 10;
            }
        }
    }

    return result;
}