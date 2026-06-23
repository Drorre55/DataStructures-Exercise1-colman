// Q1.h
#ifndef Q1_H
#define Q1_H

#include "DS.h"
#include <algorithm>
#include <vector>
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
            
            if (maxCurrentPossibleArm <= best.arm) continue;
            
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
    return best;
}

CrossResult BigCross2(const Matrix& M, int m) {
    CrossResult best = {-1, -1, 0};
    
    std::vector<int> consecutiveFromLeft(m * m, 0);
    std::vector<int> consecutiveFromUp(m * m, 0);
    std::vector<int> consecutiveFromRight(m * m, 0);
    std::vector<int> consecutiveFromDown(m * m, 0);

    for (int row = 1; row < m; row++) {
        for (int col = 1; col < m; col++) {
            int currentIdx = (row * m) + col;
            if (M.get(row, col)) {
                consecutiveFromLeft[currentIdx] = consecutiveFromLeft[(row * m) + (col - 1)] + 1;
                consecutiveFromUp[currentIdx] = consecutiveFromUp[((row - 1) * m) + col] + 1;
            }
        }
    }
    for (int row = m - 2; row > 0; row--) {
        for (int col = m - 2; col > 0; col--) {
            int currentIdx = (row * m) + col;
            if (M.get(row, col)) {
                consecutiveFromRight[currentIdx] = consecutiveFromRight[(row * m) + (col + 1)] + 1;
                consecutiveFromDown[currentIdx] = consecutiveFromDown[((row + 1) * m) + col] + 1;
            }
            int currentArm = min({ consecutiveFromLeft[currentIdx] , consecutiveFromUp[currentIdx] , 
                consecutiveFromRight[currentIdx] , consecutiveFromDown[currentIdx] });
            if (currentArm > best.arm) {
                best.arm = currentArm;
                best.row = row;
                best.col = col;
            }
        }
    }
    return best;

}

#endif