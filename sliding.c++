#include <bits/stdc++.h>
using namespace std;

// Max frequency after atmost k operations in which for every operation we can increment ele by 1
int maxFrequency(vector<int>& nums, int k) {

    // If we sort the array we can do operation on left side of arr[i] and can't do operation on rightside
    // If pointer is at arr[i] then we are trying to make all elements of array from 
    // start index to index i to element at arr[i] if valid increase window size else increment start
    
    sort(nums.begin(), nums.end());
    long long currSum = nums[0], maxlen = 1,  start = 0;
    
    for (int i=1; i<nums.size(); i++) {
        
        currSum += nums[i];
        long long totSum = nums[i] * (i - start + 1);  
        
        while (currSum + k < totSum) {   // until it is less move start pointer rightside
            totSum -= nums[i];           // decrement total sum by nums[i]
            currSum -= nums[start];      // and decrement currSum bu nums[start]
            start++;
        }
        
        maxlen = max(maxlen, i-start+1);
        
    }
    
    return maxlen;
}
