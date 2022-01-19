// Name: Ian Thomas
// Date: 7/21/2021
// Description: Encode a text file using a Huffman Coding Tree


#include <iostream> 
#include <fstream>          // std::ifstream
#include <string>
#include <list>
#include <utility>          // std::pair
#include <unordered_map>
#include <queue>            // BFS encoding

using namespace std;        

// Binary Tree Node with encoded string for Huffman values
struct Node{
    pair<char,int> data;
    Node* left;
    Node* right;
    string encoded = ""; 
    Node(pair<char,int> val) : data(val), left(nullptr), right(nullptr) {}
    Node(pair<char,int> val, Node* l, Node* r) : data(val), left(l), right(r) {}
};

Node* leaflet(Node* l, Node* r);
list<Node*> sortedList(unordered_map<char,int> &M);
void insertSorted(list<Node*> &l, Node* ins);
void BFSencode(Node* &node, unordered_map<char,string> &M);

int main() {
    // Read text from file
    ifstream infile;
    infile.open("Pride_and_Prejudice.txt");
    if (!infile){
        cerr << "File not found" << endl;
        return -1;
    }

    // Map number of each character occurrences
    unordered_map<char, int> occ;
    char ch;
    while (infile.get(ch)){
        occ[char(ch+256)]++;
    }
    infile.close();


    // Create sorted list of unordered map elements
    list<Node*> sorted = sortedList(occ);

    // Construct tree from bottom up
    Node* root;    
    list<Node*>::iterator it;                                     
    while (sorted.size() > 1){
        it = sorted.begin();
        Node* left = (*it++);                             
        Node* right = (*it++);                            
        root = leaflet(left,right);                        
        sorted.pop_front(); sorted.pop_front();              
        insertSorted(sorted, root);     
    }

    // Encode Huffman values into binary tree and insert nodes into an unordered map
    unordered_map<char,string> encoded;
    BFSencode(root, encoded);
    std::vector<pair<string,string>> extendedAscii;     // Used for convenience when printing ext. ascii from tree

    
    // Writes the Huffman tree into a file
    ofstream outfile;
    outfile.open("huff.sch");

    for (auto e : encoded)
        if (e.first == '\n')
             outfile << "\\n" << " " << e.second << endl; 
        else if (e.first == '#')
            continue;
        else
            outfile << e.first << " " << e.second << endl;

    outfile.close();

    // Convert text file into a string of huffman values and write into new file
    outfile.open("pride.huff");
    infile.open("Pride_and_Prejudice.txt");
    while (infile.get(ch)){
        if (ch == '\n'){             // Separates bitstrings by line for readability
            outfile << encoded[ch];
            outfile << ch;
        } else {
            outfile << encoded[ch];
        }
        
    }
    infile.close();
    outfile.close();

    return 0; 
}









// Inserts a node appropriately into a sorted list of Binary tree nodes according to its data.second value
void insertSorted(list<Node*> &l, Node* ins) {
    list<Node*>::iterator it;
    for (it = l.begin(); it != l.end(); it++){
        if ((*it)->data.second >= ins->data.second){
            l.insert(it,ins);
            return;
        }
    }
    l.insert(it,ins);
}

// Constructs a new '#' tree Node as the parent of two passed child nodes
Node* leaflet(Node* l, Node* r){
    Node* parent = new Node(make_pair('#',l->data.second+r->data.second),l, r);
    return parent;    
}

// Constructs a sorted list of tree nodes from a passed std::unordered_map<char,int>
list<Node*> sortedList(unordered_map<char,int> &M){
    list<Node*> sorted;
    list<Node*>::iterator it;
    
    char max = ']';
    int maxVal = 0;
    for (auto e : M){
        if (e.second > maxVal){
            max = e.first;
            maxVal = e.second;
        }
    }

    // Insert max into list
    sorted.push_back(new Node(make_pair(max,M[max])));
    M.erase(max);
    for (auto e : M){
        for (it = sorted.begin(); it != sorted.end(); it++) {
            if (e.second <= (*it)->data.second){
                sorted.insert(it, new Node(make_pair(e.first, e.second)));
                break;
            }
        }
    }

    return sorted;

}

// Adds encoded Huffman values to tree nodes and adds them to the passed std::unordered_map<char,string>
void BFSencode(Node* &node, unordered_map<char,string> &M){
    queue<Node*> queue;

    if (node != nullptr){
        queue.push(node);
    }

    while (!queue.empty()){
        Node* curr = queue.front();
        queue.pop();
        if (curr->left) {
            curr->left->encoded = curr->encoded + '0';
            M[curr->left->data.first] = curr->left->encoded;    // Map Huffman value for char
            queue.push(curr->left);
        }
        if (curr->right) {
            curr->right->encoded = curr->encoded + '1';
            M[curr->right->data.first] = curr->right->encoded;
            queue.push(curr->right);
        }
    }

    return;
    
}