// Q1.h
#ifndef Q1_H
#define Q1_H

#include "DS.h"
#include <algorithm>
#include <iostream>
using namespace std;
using std::min;

struct CrossResult {
    int row, col, arm; 
};


CrossResult BigCross1(const Matrix& M, int m) {
    CrossResult best = {-1, -1, 0};
    
    for (int row = 1; row < m; row++) {
        for (int col = 1; col < m; col++) {
            CrossResult current = { row, col, 0 };
            if (!M.get(current.row, current.col)) continue;
            
            int maxCurrentPossibleArm = min({ current.row, (m - 1) - current.row, current.col, (m - 1) - current.col });

            for (int i = 1; i <= maxCurrentPossibleArm; i++) {
                int leftIdx[2] = { current.row, current.col - i };
                int rightIdx[2] = { current.row, current.col + i };
                int upIdx[2] = { current.row - i, current.col };
                int downIdx[2] = { current.row + i, current.col };

                bool left = M.get(leftIdx[0], leftIdx[1]);
                bool right = M.get(rightIdx[0], rightIdx[1]);
                bool up = M.get(upIdx[0], upIdx[1]);
                bool down = M.get(downIdx[0], downIdx[1]);
                
                if (left && right && up && down) {
                    current.arm++;
                }
                else break;
            }
            if (current.arm > best.arm) {
                best.arm = current.arm;
                best.row = current.row;
                best.col = current.col;
            }
        }
    }
    cout << "m: " << m << ", access count: " << M.getAccessCount() << endl;
    return best;
}

CrossResult BigCross2(const Matrix& M, int m) {
    CrossResult best = {-1, -1, 0};

    return best;

}

#endif