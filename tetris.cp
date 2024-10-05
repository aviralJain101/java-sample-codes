#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int pieceTypeL(const vector<int>& columns, int base, int occurrencesBase, int basePosition) {
    int nodesMinHeight = INT_MAX;
    for (int col : columns) {
        if (col != base) {
            nodesMinHeight = min(nodesMinHeight, col);
        }
    }

    if (occurrencesBase == 1 && columns[basePosition - 1] == 2) {
        return 1;  // Placeholder for "TODO"
    } else if (occurrencesBase == 1) {
        return 1;  // Placeholder for "TODO"
    } else {
        return 0;
    }
}

int pieceTypeJ(const vector<int>& columns, int base, int occurrencesBase, int basePosition) {
    if (occurrencesBase == 2 &&
        (columns[basePosition + 1] == base || columns[basePosition - 1] == base)) {
        return 1;
    } else if (occurrencesBase == 1) {
        int borderMinHeight = min(columns[basePosition - 1], columns[basePosition + 1]);

        int nodesMinHeight = INT_MAX;
        for (int col : columns) {
            if (col != base) {
                nodesMinHeight = min(nodes​⬤
