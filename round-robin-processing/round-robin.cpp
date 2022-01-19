// Name: Ian Thomas
// Date: 7/9/2021
// Description: Simulate round robin process with STL queue

#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>
#include <list>

using std::endl;
using std::cout;
using std::cin;

struct Process{
    Process() : id(0), arrival_time(0), time_needed(0), finished_time(-1) {}
    Process(int id, int arrival, int needed) : id(id), arrival_time(arrival), time_needed(needed) {}
    int id;
    int arrival_time;
    int time_needed;
    int finished_time;
}; 

int main()
{
    std::ifstream infile;
    infile.open("round_robin.txt");
    if (!infile){
        std::cerr << "File not found." << endl;
        return -1;
    }

    std::queue<Process> tasks;
    std::queue<Process> pQueue;
    std::vector<Process> complete;

    // Read processes from file into queue
    std::string line;
    int id;
    int arrival;
    int needed;
    std::getline(infile,line);                          // Read header line
    while (std::getline(infile,line)){
        std::stringstream ss;
        ss << line;
        ss >> id >> arrival >> needed;
        tasks.push(Process(id, arrival, needed));
    }

    unsigned int numTask = tasks.size();                // Total number of tasks
    int time = 0;
    Process processing;

    // Processes tasks with CPU
    while (complete.size() < numTask){
        while (!tasks.empty())
            if (time >= tasks.front().arrival_time){
                pQueue.push(tasks.front());
                tasks.pop();
            } else {
                break;
            }

        
        // Process top of pQueue
        if (!pQueue.empty()){
            processing = pQueue.front();
            pQueue.pop();
            time += 4;                                  // CPU time frame
            if (processing.time_needed - 4 <= 0){
                processing.time_needed = 0;
                processing.finished_time = time;
                complete.push_back(processing);
            } else {
                processing.time_needed -= 4;
                pQueue.push(processing);
            }
        } else
            time += 4;
    }

    for (auto e : complete)
        cout << "Process " << e.id << ": " << e.finished_time << endl;


    return 0;
    
}