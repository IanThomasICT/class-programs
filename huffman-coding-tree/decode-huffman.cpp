// Name: Ian Thomas
// Date: 7/23/2021
// Description: Decode a text file using a Huffman Coding Scheme


#include <iostream> 
#include <fstream>          // std::ifstream
#include <string>
#include <unordered_map>

using namespace std;
int main() {

    // Read scheme into unordered_map<string,char>
    unordered_map<string,char> scheme;
    ifstream infile;
    infile.open("huff.sch");
    if (!infile){
        std::cerr << "Scheme not found." << endl;
        return -1;
    }

    string line;
    char ascii;
    string code;
    unsigned int minBitlength = 10;
    unsigned int maxBitlength = 0;
    while (getline(infile,line)){
        if (line[0] == '\\' && line[1] == 'n'){
            ascii = '\n';
            code = line.substr(3);
        } else{ 
            ascii = line[0];
            code = line.substr(2);
        }

        scheme[code] = ascii;
        if (code.size() < minBitlength)
            minBitlength = code.size();
        if (code.size() > maxBitlength)
            maxBitlength = code.size();
    }
    infile.close();

    // Read encoded strings content and decode into outfile
    ofstream outfile;
    outfile.open("pride_decoded.txt");
    infile.open("pride.huff");
    if (!infile){
        std::cerr << "Encoded file not found." << endl;
        return -1;
    }

    code = "";
    while (getline(infile, line)){
        for (unsigned int i = 0; i < line.size(); i++){
            code += line[i];
            if (code.size() >= minBitlength)
                if (scheme.find(code) != scheme.end()){
                    outfile << scheme[code];
                    code = "";
                }
        }
    }
    infile.close();
    outfile.close();

    return 0;

}
