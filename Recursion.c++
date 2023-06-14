#include<bits/stdc++.h>
using namespace std;

// Three are important in recursion like (  base case,  processing,  recursive relation  )
// Two basic models i)  pick and not pick the elements
//                 ii)  picking the subsequence using for loop

// N Queens time complexity :  O(n!),   Rat in a maze: O(3^(n*n))   for every cell we have 3 choices atmost
// phone keypad :  (3^n) (Assume for every call 3 calls will be made again) 

// return nth fibonacci number
int fibonacci(int n) {
    if (n==0 || n==1) {  // base case compulsory
        return n;        
    }
    return fibonacci(n-1) + fibonacci(n-2);

}

// count no.of ways to reach nth step if we are on 0th step with 1 or 2 jumps
// To the questions asking count return 1 for base conditions
int climbStairs(int n) {
    if (n==0 || n==1) // return 1 for base case as it is counting question
        return 1;
    return climbStairs(n-1) + climbStairs(n-2); 
}

// reverse string using recursion
void Reverse(string &s, int low, int high) {
    
    if (low >= high)
        return;
    swap(s[low],s[high]);
    Reverse(s, ++low, --high);
    
}

void partitionIntoAlphabet(int n, string s, string &ds) {

    if (n == s.size()) {
        for (auto ele: ds)
            cout << ele;
        cout << endl;
        return;
    }

    int num = 0;
    for (int i=n; i<n+2 && i<s.size(); i++) {

        char c = num * 10 + s[i] + 16;
        if (isupper(c)) {
            ds.push_back(c);
            partitionIntoAlphabet(i+1, s, ds);
            ds.pop_back();
        }
    }
}

void targetSum(vector<int> &v, vector<int> &ds, int n, int tar) {

    if (n == v.size()) {
        if (tar == 0) {
            for (auto it: ds)   cout << it << " ";
            cout << endl;
        }
        return;
    }

    // pick the element only if by adding the element it will not be negative
    if (tar-v[n] >= 0) {
        ds.push_back(v[n]);
        targetSum(v, ds, n+1, tar-v[n]);
        ds.pop_back();
    }

    // not pick the element
    targetSum(v, ds, n+1, tar);
}

bool targetSumWithOneSol(vector<int> &v, vector<int> &ds, int n, int tar) {

    if (n == v.size()) {     // problems with only one solution required i.e only one subseq with given target
        if (tar == 0) {
            for (auto it: ds)   cout << it << " ";
            return true;    // in base case if condition is satisfied return true
        }
        return false;     // otherwise false i.e given condition is not fulfilled
    }

    // pick the element only if by adding the element it will not be negative
    if (tar-v[n] >= 0) {
        ds.push_back(v[n]);
        if (targetSumWithOneSol(v, ds, n+1, tar-v[n]))  return true;   // while calling use   if ( f() ) return true;
        ds.pop_back();
    }

    // not pick the element
    if (targetSumWithOneSol(v, ds, n+1, tar))  return true;     // recursive function call so use if (f()) return true;

    return false;    // Don't forget this,  always return false at last 
}

void findSumWithRep(vector<int> &v, vector<int> &ds, int n, int tar) {

    if (n == v.size()) {
        if (tar == 0) {
            for (auto it: ds)   cout << it << " ";
            cout << endl;
        }
        return ;
    }

    // pick the element
    if (tar - v[n] >= 0) {    // if it is going to neg means don't take that element so that recursion
        ds.push_back(v[n]);
        findSumWithRep(v, ds, n, tar-v[n]);
        ds.pop_back();
    }

    // not pick the element
    findSumWithRep(v, ds, n+1, tar);
}

// unique subsequence for the given target
void uniqueTargetSum(vector<int> &v, vector<int> &ds, int tar, int n) {

    // picking the subsequence after sorting the array  v = [1,1,1,2,2]
    if (tar == 0) {             // tar < 0 condition will be in the for loop i.e tar < v[i] it will break
        for (auto it: ds)
            cout << it << " ";
        cout << endl;
        return;
    }

    for (int i=n; i<v.size(); i++) {

        if (i != n && v[i] == v[i-1])
            continue;     // picking the 0th index guy or 1st index or 2nd index doesn't matter bcz same value

        if (tar < v[i])   // bcz vector is sorted if v[i] is greater than tar then next ele's are also greater
            break;

        ds.push_back(v[i]);
        uniqueTargetSum(v, ds, tar-v[i], i+1);   // the next num will be (i+1) not n+1 bcz skipping some ele
        ds.pop_back();
    }
}

// ******* IMP MODEL  ******
void uniqueCombinations(vector<int> &v, vector<int> &ds, int n) {

    // sort the array to remove duplicate combinations so we can skip some elements which start with same elements
    // at level 0 of recursion tree we generate 0 size subsets and at leve 1 we generate 1 size subsets.... so on

    for (auto it: ds)           // every time print the elements in ds vector
        cout << it << " ";      // if u wait till last index by putting n == v.size() condt
    cout << endl;               // then all combinations will not print

    for (int i=n; i<v.size(); i++) {    // for base case it will not enter the for loop

        if (i != n && v[i] == v[i-1])
            continue;

        ds.push_back(v[i]);              // if i pick the element at index i then go to next index i.e i+1 not n+1
        uniqueCombinations(v, ds, i+1);  // use (i+1) bcz in v = [1, 2, 2, 2] 
        ds.pop_back();                   // if we are at index 1 then next call will be fun(v, ds, 3)
    }
}

void permutations(vector<int> &v, int n) {

    // in the permuations we can choose index 0 as first ele or index 1 as first ele... 

    if (n == v.size()) {
        for (auto it: v)
            cout << it << " ";
        cout << endl;
        return;
    }

    for (int i=n; i<v.size(); i++) {
        
        // so swap first element(index n) with current index i,  i.e every ele gets chance to be in first place
        swap(v[i], v[n]);
        permutations(v, n+1); // now call the permutaions for next elements from (index n) not from index i
        swap(v[i], v[n]);
    }
}


// N Queens problem
bool isPossible(vector<vector<int>> &board, int row, int i, vector<int> &leftDiag, vector<int> &rightDiag, vector<int> &col) {

    int n = board.size();
    if (col[i] == 1 || leftDiag[row-i+n-1] == 1 || rightDiag[row+i] == 1)
        return false;
    return true;
}

void solve(int ind, vector<vector<int>> &board, vector<int> &leftDiag, vector<int> &rightDiag, vector<int> &col)  {

    int n = board.size();
    if (ind == n) {
        for (auto row: board) {
            for (auto col: row)
                cout << col << " ";
            cout << endl;
        }
        cout << endl << endl;
        return;
    }

    for (int i=0; i<n; i++) {    // for row with index (ind) we are iterating from 0 to n-1 and check possiblity

        if (isPossible(board, ind, i, leftDiag, rightDiag, col)) {

            board[ind][i] = 1;
            leftDiag[ind-i+n-1] = 1;   // for left diagonal elements row-col+n-1 are same
            rightDiag[ind+i] = 1;      // for right diagonal elements row + col is same
            col[i] = 1;             // only we need to check the column elements bcz same row is not done anytime

            solve(ind+1, board, leftDiag, rightDiag, col);

            board[ind][i] = 0;           // again remove after end of the above recursion call
            leftDiag[ind-i+n-1] = 0;
            rightDiag[ind+i] = 0;
            col[i] = 0;
        }
    }
}

int NQueens() {

    int n = 4;
    vector<int> leftDiag(2*n-1), rightDiag(2*n-1), col(n);
    vector<vector<int>> board(n, vector<int>(n, 0));
    solve(0, board, leftDiag, rightDiag, col);
    return 0;
}

// Rat in a maze problem
bool isValid(int row, int col, vector<vector<bool>> &visited, vector<vector<int>> &arr) {

    int n = arr.size();
    if ( (row >= 0 && row < n) && (col >= 0 && col < n)
        && (!visited[row][col]) && (arr[row][col]) )
            return true;
        
    return false;
}

void solve(int row, int col, vector<vector<int>> &arr, string &s,
    vector<string> &ans, vector<vector<bool>> &visited) {

        int n = arr.size();
        if (row == n-1 && col == n-1) {
            ans.push_back(s);
            return;
        }

        visited[row][col] = true;
        int dir[4][2] = { {1, 0}, {0, -1}, {0, 1}, {-1, 0}};
        char ch[4] = {'D', 'L', 'R', 'U'};

        for (int i=0; i<4; i++) {

            int nrow = row + dir[i][0];
            int ncol = col + dir[i][1];

            if (isValid(nrow, ncol, visited, arr)) {
                s.push_back(ch[i]);
                solve(nrow, ncol, arr, s, ans, visited);
                s.pop_back();
            }
        }
        visited[row][col] = false;
    }

vector<string> searchMaze(vector<vector<int>> &arr, int n) {
    
    if (arr[0][0] == 0 || arr[n-1][n-1] == 0)
        return {};

    vector<vector<bool>> visited (n, vector<bool> (n, false));
    vector<string> ans;
    string s;
    solve(0, 0, arr, s, ans, visited);

    return ans;
}

bool isSudokuSafe(int row, int col, char c, vector<vector<char>> &board) {
    
    for (int i=0; i<9; i++) {
        
        int nrow = 3*(row/3) + i/3;   // 3*(row/3) will point to 1st row in respective 3x3 grid
        int ncol = 3*(col/3) + i%3;   // i/3 increments 1 for 3 numbers and i%3 for every one num, repeats for 3
        
        if (board[i][col] == c || board[row][i] || board[nrow][ncol] == c)
            return false;
    }
    return true;
}

bool solve(vector<vector<char>>& board) {
    
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            if (board[i][j] == '.') {
                
                for (char c = '1'; c <= '9'; c++) {   // checking the values from 1 to 9
                    if (isSudokuSafe(i, j, c, board)) {
                        
                        board[i][j] = c;
                        bool res = solve(board);     // after function again it wil check from 1st cell
                        
                        if (res == true)
                            return true;
                        
                        board[i][j] = '.';
                            
                    }
                }
                return false;        // return false even if we cannot fit all the values from 1 to 9
            }
        }
    }
    
    return true;
}
  
void solveSudoku(vector<vector<char>>& board) {
    
    solve(board);
}

// Palindromic partition
bool isPalindrome(string ds) {
    
    int left = 0,  right = ds.size()-1;
    while (left < right) {
        if (ds[left] != ds[right])
            return false;
        left++;
        right--;
    }
    
    return true;
}
    
void solve(vector<vector<string>> &ans, vector<string> &ds, string &s, int n) {
    
    if (n == s.size()) {
        ans.push_back(ds);
        return ;
    }
    
    string temp = "";
    for (int i=n; i<s.size(); i++) {   // for string aabb :  a + f(abb)  |  aa + f(bb) |  aab + f(b)  |  aabb + f()
        
        temp.push_back(s[i]);
        if (isPalindrome(temp)) {
            ds.push_back(temp);     // after first partition from index n to index i then call function for (i+1)
            solve(ans, ds, s, i+1);    //  (i+1)  is important not   (n+1)
            ds.pop_back();
        }
        
    }
}
    
vector<vector<string>> allPalindromicPerms(string s) {
    // code here
    
    vector<string> ds;
    vector<vector<string>> ans;
    
    solve(ans, ds, s, 0);
    
    return ans;
}

