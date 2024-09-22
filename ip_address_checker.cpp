#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

// Function to check if a string is a valid integer in the range 0 to 255
bool isValidOctet(const string& octet) {
    // Check if octet is numeric
    if (octet.empty() || (octet.size() > 1 && octet[0] == '0') || octet.size() > 3)
        return false;
    
    for (char c : octet) {
        if (!isdigit(c))
            return false;
    }
    
    int value = stoi(octet);
    return value >= 0 && value <= 255;
}

// Function to check if an IP address is valid and classify it into a region
int classifyIPAddress(const string& ip) {
    stringstream ss(ip);
    string octet;
    vector<string> octets;
    
    // Split the IP address by '.'
    while (getline(ss, octet, '.')) {
        octets.push_back(octet);
    }
    
    // An IPv4 address should have exactly 4 octets
    if (octets.size() != 4)
        return -1;
    
    // Validate each octet
    for (const string& o : octets) {
        if (!isValidOctet(o))
            return -1;
    }
    
    // Convert the first octet to an integer
    int firstOctet = stoi(octets[0]);
    
    // Classify into regions based on the first octet
    if (firstOctet >= 0 && firstOctet <= 127)
        return 1; // Class 1: 0.0.0.0 - 127.255.255.255
    else if (firstOctet >= 128 && firstOctet <= 191)
        return 2; // Class 2: 128.0.0.0 - 191.255.255.255
    else if (firstOctet >= 192 && firstOctet <= 223)
        return 3; // Class 3: 192.0.0.0 - 223.255.255.255
    else if (firstOctet >= 224 && firstOctet <= 239)
        return 4; // Class 4: 224.0.0.0 - 239.255.255.255
    else if (firstOctet >= 240 && firstOctet <= 255)
        return 5; // Class 5: 240.0.0.0 - 255.255.255.255
    else
        return -1; // Invalid case (shouldn't reach here)
}

// Function to process a list of IP addresses
vector<int> getRegions(vector<string> ip_addresses) {
    vector<int> classifications;
    
    for (const string& ip : ip_addresses) {
        classifications.push_back(classifyIPAddress(ip));
    }
    
    return classifications;
}
