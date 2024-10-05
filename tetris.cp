#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Function to calculate the number of complete lines
int calculateCompleteLines(const vector<int>& columns) {
    if (columns.empty()) return 0;
    int maxHeight = *max_element(columns.begin(), columns.end());
    int completeLines = 0;

    for (int level = 1; level <= maxHeight; ++level) {
        bool complete = true;
        for (int height : columns) {
            if (height < level) {
                complete = false;
                break;
            }
        }
        if (complete) completeLines++;
    }

    return completeLines;
}

// Function to handle piece type 'L'
int pieceTypeL(const vector<int>& columns, int base, int occurrencesBase, int basePosition) {
    // 'L' piece can have multiple orientations. For simplicity, we'll consider a single orientation.
    // You can expand this to handle all rotations as needed.

    // Determine possible positions for 'L' piece placement
    // 'L' occupies two columns: basePosition and basePosition + 1
    // It adds blocks to these columns to simulate the 'L' shape

    // Check boundaries
    if (basePosition < 0 || basePosition >= columns.size() - 1) {
        return 0;
    }

    // Simulate placing the 'L' piece
    // 'L' piece adds blocks to make one column higher by 2 and the adjacent column by 1
    vector<int> newColumns = columns;
    newColumns[basePosition] += 2;       // Taller column
    newColumns[basePosition + 1] += 1;   // Adjacent column

    // Calculate complete lines after placement
    int completeLines = calculateCompleteLines(newColumns);

    return completeLines;
}

// Function to handle piece type 'J'
int pieceTypeJ(const vector<int>& columns, int base, int occurrencesBase, int basePosition) {
    // Similar to 'L', but mirrored

    // Check boundaries
    if (basePosition < 1 || basePosition >= columns.size()) {
        return 0;
    }

    // Simulate placing the 'J' piece
    // 'J' piece adds blocks to make one column higher by 2 and the adjacent column by 1
    vector<int> newColumns = columns;
    newColumns[basePosition] += 2;       // Taller column
    newColumns[basePosition - 1] += 1;   // Adjacent column

    // Calculate complete lines after placement
    int completeLines = calculateCompleteLines(newColumns);

    return completeLines;
}

// Function to handle piece type 'I'
int pieceTypeI(const vector<int>& columns, int base, int occurrencesBase) {
    // 'I' piece can be placed vertically or horizontally

    // For vertical placement
    // It occupies one column and adds 4 blocks
    // We'll simulate vertical placement
    vector<int> newColumns = columns;
    int verticalCompleteLines = 0;
    // Find the position to place vertically
    for (size_t pos = 0; pos < columns.size(); ++pos) {
        vector<int> tempColumns = newColumns;
        tempColumns[pos] += 4;
        int lines = calculateCompleteLines(tempColumns);
        verticalCompleteLines = max(verticalCompleteLines, lines);
    }

    // For horizontal placement
    // It occupies four consecutive columns and adds 1 block to each
    int horizontalCompleteLines = 0;
    for (size_t pos = 0; pos <= columns.size() - 4; ++pos) {
        vector<int> tempColumns = newColumns;
        for (size_t i = 0; i < 4; ++i) {
            tempColumns[pos + i] += 1;
        }
        int lines = calculateCompleteLines(tempColumns);
        horizontalCompleteLines = max(horizontalCompleteLines, lines);
    }

    return max(verticalCompleteLines, horizontalCompleteLines);
}

// Function to handle piece type 'O'
int pieceTypeO(const vector<int>& columns, int base, int occurrencesBase, int basePosition) {
    // 'O' piece is a 2x2 square. It occupies two consecutive columns and adds 2 blocks to each.

    // Check boundaries
    if (basePosition < 0 || basePosition >= columns.size() - 1) {
        return 0;
    }

    // Simulate placing the 'O' piece
    vector<int> newColumns = columns;
    newColumns[basePosition] += 2;
    newColumns[basePosition + 1] += 2;

    // Calculate complete lines after placement
    int completeLines = calculateCompleteLines(newColumns);

    return completeLines;
}

// Function to handle piece type 'S'
int pieceTypeS(const vector<int>& columns, int base, int occurrencesBase, int basePosition) {
    // 'S' piece has two orientations. We'll consider horizontal placement.

    // 'S' occupies three columns: it adds 1 block to basePosition and basePosition + 1, and 2 blocks to basePosition + 2
    if (basePosition < 0 || basePosition > columns.size() - 3) {
        return 0;
    }

    vector<int> newColumns = columns;
    newColumns[basePosition] += 1;
    newColumns[basePosition + 1] += 2;
    newColumns[basePosition + 2] += 1;

    // Calculate complete lines after placement
    int completeLines = calculateCompleteLines(newColumns);

    return completeLines;
}

// Function to handle piece type 'T'
int pieceTypeT(const vector<int>& columns, int base, int occurrencesBase, int basePosition) {
    // 'T' piece has multiple orientations. We'll consider a single horizontal orientation.

    // 'T' occupies three columns: it adds 2 blocks to basePosition + 1 and 1 block to basePosition and basePosition + 2
    if (basePosition < 0 || basePosition > columns.size() - 3) {
        return 0;
    }

    vector<int> newColumns = columns;
    newColumns[basePosition] += 1;
    newColumns[basePosition + 1] += 2;
    newColumns[basePosition + 2] += 1;

    // Calculate complete lines after placement
    int completeLines = calculateCompleteLines(newColumns);

    return completeLines;
}

// Function to handle piece type 'Z'
int pieceTypeZ(const vector<int>& columns, int base, int occurrencesBase, int basePosition) {
    // 'Z' piece has two orientations. We'll consider horizontal placement.

    // 'Z' occupies three columns: it adds 2 blocks to basePosition and 1 block to basePosition + 1, and 2 blocks to basePosition + 2
    if (basePosition < 0 || basePosition > columns.size() - 3) {
        return 0;
    }

    vector<int> newColumns = columns;
    newColumns[basePosition] += 2;
    newColumns[basePosition + 1] += 1;
    newColumns[basePosition + 2] += 2;

    // Calculate complete lines after placement
    int completeLines = calculateCompleteLines(newColumns);

    return completeLines;
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
        case 'O':
            return pieceTypeO(columns, base, occurrencesBase, basePosition);
        case 'S':
            return pieceTypeS(columns, base, occurrencesBase, basePosition);
        case 'T':
            return pieceTypeT(columns, base, occurrencesBase, basePosition);
        case 'Z':
            return pieceTypeZ(columns, base, occurrencesBase, basePosition);
        default:
            return 0;
    }
}

// Main TetrisMove function
int TetrisMove(vector<string> strArr) {
    if (strArr.empty()) {
        return 0;
    }

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

    // Debugging outputs
    cout << "Piece: " << piece << endl;
    cout << "Occurrences of base (" << base << "): " << occurrencesBase << endl;
    bool baseSize = (occurrencesBase >= 2) &&
                    ((basePosition > 0 && columns[basePosition - 1] == base) ||
                     (basePosition < columns.size() - 1 && columns[basePosition + 1] == base));
    cout << "Base Size: " << baseSize << endl;
    if (basePosition > 0) {
        cout << "Left Neighbor: " << columns[basePosition - 1] << endl;
    }
    if (basePosition < columns.size() - 1) {
        cout << "Right Neighbor: " << columns[basePosition + 1] << endl;
    }
    cout << "Base Height: " << base << endl;

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
    vector<string> inputO = {"O", "4", "3", "2", "3", "5", "1", "0", "1", "2", "4", "3", "4"};
    vector<string> inputJ = {"J", "5", "6", "7", "8", "6", "7", "0", "5", "5", "8", "7", "9"};
    vector<string> inputS = {"S", "3", "4", "4", "5", "6", "3", "0", "5", "5", "4", "6", "6"};
    vector<string> inputT = {"T", "4", "4", "4", "5", "6", "2", "0", "6", "5", "3", "6", "6"};
    vector<string> inputZ = {"Z", "5", "4", "4", "5", "6", "3", "0", "6", "5", "4", "6", "6"};

    // Testing various inputs
    cout << "Answer for inputJ: " << TetrisMove(inputJ) << endl;
    cout << "Answer for inputL: " << TetrisMove(inputL) << endl;
    cout << "Answer for inputI: " << TetrisMove(inputI) << endl;
    cout << "Answer for inputO: " << TetrisMove(inputO) << endl;
    cout << "Answer for inputS: " << TetrisMove(inputS) << endl;
    cout << "Answer for inputT: " << TetrisMove(inputT) << endl;
    cout << "Answer for inputZ: " << TetrisMove(inputZ) << endl;

    return 0;
}
