/************************************************  
*   memsim: Virtual Memory System Simulator     *
*   A program that simulates memory traces      *
************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>
#include <vector>


using namespace std;

// Page Table Entry Struct 
struct PTE {
    int vpn;
    bool dirty = false;
};

// Algorithm declaration
void fifo(string traceFile, unsigned int f, string mode);
void lru(string traceFile, unsigned int f, string mode);
void segmented_fifo(string traceFile, unsigned int f, double p, string mode);
vector<PTE>::iterator find(vector<PTE>::iterator first, vector<PTE>::iterator last, int vpn);

int main(int argc, char* argv[]) {
    if (argc < 5) 
        throw invalid_argument("Usage: memsim   <tracefile>   <nframes>   <lru|fifo|vms>  <debug|quiet>"); 
    
    // Read command line arguments
    string traceFile = argv[1];
    unsigned int f = stoi(argv[2]);
    string method = argv[3];
    double p;

    // Debug / Quiet?
    string mode;
    if (method == "vms") {
        if (argc < 6)
            throw invalid_argument("Usage: memsim   <tracefile>   <nframes>   <vms>    <p>    <debug|quiet>");
        mode = argv[5];
        p = stod(argv[4]);
    } else
        mode = argv[4];

    if (method == "fifo")
        fifo(traceFile, f, mode);
    else if (method == "lru")
        lru(traceFile, f, mode);                     
    else if (method == "vms")
        segmented_fifo(traceFile, f, p, mode);         
    else cout << "Invalid page replacement algorithm." << endl;

    return 0;
}

// First In First Out
void fifo(string traceFile, unsigned int f, string mode) {
    queue<int> pages;                   // Algorithm data structure
    vector<PTE> RAM;                    // Simulated memory

    // Trace variables
    string addr;                        
    char op;
    int tempVpn;
    unsigned int dRead = 0, dWrite = 0, faults = 0, events = 0;
    PTE tempPTE;
    vector<PTE>::iterator currPTE;      // Pointer to current accessed page
    
    // Open memory trace file
    ifstream memTrace(traceFile);
    if (memTrace.is_open()) {           // Check if file opened correctly 
        while (!memTrace.eof()){        // Check for End of File 
            events++;

            // Capture address and operation
            memTrace >> addr >> op;
            tempVpn = stoi(addr.substr(0, 5), 0, 17);

            // Check if page is loaded
            if (find(RAM.begin(), RAM.end(), tempVpn) == RAM.end()) { // Page Fault
                faults++;
                if(pages.size() < f) {  // Space available for page
                    RAM.push_back(PTE({tempVpn}));
                    pages.push(tempVpn);
                    dRead++;
                } else {                // Space unavailable for page
                    tempPTE = *find(RAM.begin(), RAM.end(), pages.front());
                    if (tempPTE.dirty)
                        dWrite++;
                    vector<PTE>::iterator i = find(RAM.begin(), RAM.end(), tempPTE.vpn);
                    RAM.erase(i);
                    RAM.insert(i, PTE{tempVpn});
                    pages.pop();
                    pages.push(tempVpn);
                    dRead++;
                }
            }
            // Here, the page will already be loaded
            currPTE = find(RAM.begin(), RAM.end(), tempVpn);
            if (op == 'W') currPTE->dirty = true;   // Check if operation is Write

            // Debug mode prints statistics per line, as well as the simulated RAM    
            if (mode == "debug") {
                cout << endl << "Trace #" << events << endl;
                cout << "Address: " << addr << endl;
                cout << "Page number: " << tempVpn << endl;
                cout << "Operation: " << op << endl;
                cout << "Faults: " << faults << endl;
                for (vector<PTE>::iterator i = RAM.begin(); i != RAM.end(); i++)
                    cout << i->vpn << " ";
                cout << endl;
            }
        }
        cout << "Total memory frames: " << f << endl;
        cout << "Events in trace: " << events << endl;
        cout << "Total disk reads: " << dRead << endl;
        cout << "Total dist writes: " << dWrite << endl;
    } else cout << "File could not be opened corectly." << endl;
}

// Least Recently Used
void lru(string traceFile, unsigned int f, string mode) {
    list<int> pages;                    // Algorithm data structure
    vector<PTE> RAM;                    // Simulated memory

    // Trace variables
    string addr;                        
    char op;
    int tempVpn;
    PTE tempPTE;
    vector<PTE>::iterator currPTE;      // Pointer to current accessed page

    // Count variables
    unsigned int dRead = 0, dWrite = 0, faults = 0, events = 0, loaded = 0;
    
    // Open memory trace file
    ifstream memTrace(traceFile);
    if (memTrace.is_open()) {           // Check if file opened correctly 
        while (!memTrace.eof()){        // Check for End of File 
            events++;

            // Capture address and operation
            memTrace >> addr >> op;
            tempVpn = stoi(addr.substr(0, 5), 0, 17);

            // Check if page is loaded
            if (find(RAM.begin(), RAM.end(), tempVpn) == RAM.end()) {   // Page fault
                faults++;
                if(loaded < f) {  // Space available for page
                    RAM.push_back(PTE({tempVpn}));
                    dRead++;
                    loaded++;
                } else {                // Space unavailable for page
                    tempPTE = *find(RAM.begin(), RAM.end(), pages.back());
                    if (tempPTE.dirty)
                        dWrite++;
                    vector<PTE>::iterator i = find(RAM.begin(), RAM.end(), tempPTE.vpn);
                    RAM.erase(i);
                    RAM.insert(i, PTE{tempVpn});
                    pages.pop_back();
                    dRead++;
                }
            }
            // Here, the page will already be loaded
            currPTE = find(RAM.begin(), RAM.end(), tempVpn);
            pages.remove(tempVpn);
            pages.push_front(currPTE->vpn);
            if (op == 'W') currPTE->dirty = true;   // Check if operation is Write
                
            // Debug mode prints statistics per line, as well as the simulated RAM    
            if (mode == "debug") {
                cout << endl << "Trace #" << events << endl;
                cout << "Address: " << addr << endl;
                cout << "Page number: " << tempVpn << endl;
                cout << "Operation: " << op << endl;
                cout << "Faults: " << faults << endl;
                for (vector<PTE>::iterator i = RAM.begin(); i != RAM.end(); i++)
                    cout << i->vpn << " ";
                cout << endl;
            }
        }
        cout << "Total memory frames: " << f << endl;
        cout << "Events in trace: " << events << endl;
        cout << "Total disk reads: " << dRead << endl;
        cout << "Total dist writes: " << dWrite << endl;
    } else cout << "File could not be opened corectly." << endl;
}

// Segmented First In First Out
void segmented_fifo(string traceFile, unsigned int f, double p, string mode){
    vector<PTE> RAM;                    // Simulated memory

    // Trace variables
    string addr;                        
    char op;
    int tempVpn;
    unsigned int dRead = 0, dWrite = 0, faults = 0, events = 0, loaded = 0;
    PTE tempPTE;
    vector<PTE>::iterator currPTE;      // Pointer to current accessed page
    
    // Open memory trace file
    ifstream memTrace(traceFile);
    if (memTrace.is_open()) {           // Check if file opened correctly 
        while (!memTrace.eof()){        // Check for End of File 
            events++;

            // Capture address and operation
            memTrace >> addr >> op;
            tempVpn = stoi(addr.substr(0, 5), 0, 17);

            // Check if page is loaded
            currPTE = find(RAM.begin(), RAM.end(), tempVpn);
            if (currPTE == RAM.end()) {   // Page fault
                faults++;
                if(loaded < f) {    // Space available for page
                    RAM.insert(RAM.begin(), PTE({tempVpn}));
                    dRead++;
                    loaded++;
                } else {            // Space unavailable for page
                    tempPTE = RAM.back();
                    if (tempPTE.dirty)
                        dWrite++;
                    RAM.pop_back();
                    RAM.insert(RAM.begin(), PTE({tempVpn}));
                    dRead++;
                }                
            }
            // Check if page is loaded in secondary buffer
            else if (currPTE >= RAM.begin() + (f * (1 - p))) {
                tempPTE = *currPTE;
                RAM.erase(currPTE);
                RAM.insert(RAM.begin(), tempPTE);
            }

            // Here, the page will already be loaded in the first buffer but we need
            // to update currPTE to point to the actual PTE in case there was a fault
            currPTE = find(RAM.begin(), RAM.end(), tempVpn);
            if (op == 'W') currPTE->dirty = true;   // Check if operation is Write
                
            // Debug mode prints statistics per line, as well as the simulated RAM    
            if (mode == "debug") {
                cout << endl << "Trace #" << events << endl;
                cout << "Address: " << addr << endl;
                cout << "Page number: " << tempVpn << endl;
                cout << "Operation: " << op << endl;
                cout << "Faults: " << faults << endl;
                if (loaded == f)
                    cout << endl << (RAM.begin() + (f * (1 - p)))->vpn << endl << endl; // ****
                for (vector<PTE>::iterator i = RAM.begin(); i != RAM.end(); i++)
                    cout << i->vpn << " ";
                cout << endl;
            }
        }
        cout << "Total memory frames: " << f << endl;
        cout << "Events in trace: " << events << endl;
        cout << "Total disk reads: " << dRead << endl;
        cout << "Total dist writes: " << dWrite << endl;
    } else cout << "File could not be opened corectly." << endl;
}

vector<PTE>::iterator find(vector<PTE>::iterator first, vector<PTE>::iterator last, int vpn){
    while (first != last) {
        if (first->vpn == vpn) return first;
        first++;
    }
    return last;
}