#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Function to handle piece type 'L'
int pieceTypeL(const vector<int>& columns, int base, int occurrencesBase, int basePosition) {
    int nodesMinHeight = INT_MAX;
    for (int n : columns) {
        if (n != base) {
            nodesMinHeight = min(nodesMinHeight, n);
        }
    }

    if (occurrencesBase == 1 && columns[basePosition - 1] == 2) {
        return -1;  // Placeholder for "TODO"
    } else if (occurrencesBase == 1) {
        return -1;  // Placeholder for "TODO"
    } else {
        return 0;
    }
}

// Function to handle piece type 'J'
int pieceTypeJ(const vector<int>& columns, int base, int occurrencesBase, int basePosition) {
    if (occurrencesBase == 2 &&
        (columns[basePosition + 1] == base || columns[basePosition - 1] == base)) {
        return 1;
    } else if (occurrencesBase == 1) {
        int borderMinHeight = min(columns[basePosition - 1], columns[basePosition + 1]);
        int nodesMinHeight = INT_MAX;
        for (int n : columns) {
            if (n != base) {
                nodesMinHeight = min(nodesMinHeight, n);
            }
        }

        if (nodesMinHeight >= borderMinHeight) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

// Function to handle piece type 'I'
int pieceTypeI(const vector<int>& columns, int base, int occurrencesBase) {
    if (occurrencesBase == 1) {
        int nodesMinHeight = INT_MAX;
        for (int n : columns) {
            if (n != base) {
                nodesMinHeight = min(nodesMinHeight, n);
            }
        }
        return nodesMinHeight;
    } else {
        return 0;
    }
}

// Process piece based on type
int processPiece(char piece, const vector<int>& columns, int base, int occurrencesBase, int basePosition) {
    switch (piece) {
        case 'I':
            return pieceTypeI(columns, base, occurrencesBase);
        case 'J':
            return pieceTypeJ(columns, base, occurrencesBase, basePosition);
        case 'L':
            return pieceTypeL(columns, base, occurrencesBase, basePosition);
        default:
            return 0;
    }
}

// Main TetrisMove function
int TetrisMove(vector<string> strArr) {
    char piece = strArr[0][0];  // Extract piece type (first element)
    
    // Convert the remaining elements to integers (board columns)
    vector<int> columns;
    for (size_t i = 1; i < strArr.size(); ++i) {
        columns.push_back(stoi(strArr[i]));
    }

    // Find the base (minimum height) and its occurrences
    int base = *min_element(columns.begin(), columns.end());
    int occurrencesBase = count(columns.begin(), columns.end(), base);
    int basePosition = find(columns.begin(), columns.end(), base) - columns.begin();

    if (occurrencesBase >= 1 && occurrencesBase < 3) {
        return processPiece(piece, columns, base, occurrencesBase, basePosition);
    } else {
        return 0;
    }
}

int main() {
    // Example inputs
    vector<string> inputL = {"L", "3", "4", "4", "5", "6", "2", "0", "6", "5", "3", "6", "6"};
    vector<string> inputI = {"I", "2", "4", "3", "4", "5", "2", "0", "2", "2", "3", "3", "3"};
    vector<string> inputJ = {"J", "5", "6", "7", "8", "6", "7", "0", "5", "5", "8", "7", "9"};

    cout << "Answer for inputJ: " << TetrisMove(inputJ) << endl;

    return 0;
}
