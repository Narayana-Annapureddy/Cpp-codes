#include<bits/stdc++.h>
using namespace std;

// if we have zero in matrix then make that row and col also 0's.
void set_zeros(vector<vector<int>> m) {
    // we need to consider row 0 as array to store col numbers to remember which col has 0's.
    // also consider col 0 as array to store row numbers to remember which row has 0's.
    // so first take two variables row and col to check whether row 0 and col 0 has origianlly zeros.

        int col=1, row=1, i, j;
        for(i=0; i<m[0].size(); i++) {
            if (m[0][i] == 0) {
                row = 0;
                break;
            }
        }
        for(i=0; i<m.size(); i++) {
            if (m[i][0] == 0) {
                col = 0;
                break;
            }
        }
        
        for(i=1; i<m.size(); i++) {
            for(j=1; j<m[i].size(); j++) {
                if (m[i][j] == 0) {
                    m[0][j] = 0;
                    m[i][0] = 0;
                }
            }
        }
        
        for(i=1; i<m[0].size(); i++) {  // start from col 1 only ...
            if (m[0][i] == 0) {
                for(j=1; j<m.size(); j++) {
                    m[j][i] = 0;
                }
            }
        }
        
        for(i=1; i<m.size(); i++) {   // start from row 1 only...
            if (m[i][0] == 0) {
                for(j=1; j<m[i].size(); j++) {
                    m[i][j] = 0;
                }
            }
        }
         
        if (row == 0) {              // now check col 0
            for(i=0; i<m[0].size(); i++) {
                m[0][i] = 0;
            }
        }
        
        if (col == 0) {             // now check row 0
            for(i=0; i<m.size(); i++) {
                m[i][0] = 0;
            }
        }
}
