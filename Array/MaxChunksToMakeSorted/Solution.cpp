/*************************************************************************
    > File Name: Solution.cpp
    > Author: Godsing
    > Mail: zzzpwang@gmail.com
    > Created Time: 2018-04-21
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int tempmax = arr[0];
        int tempstart = 0;
        int count = 0;
        int i = 0;
        while (1) {
            for (i = tempstart; i <= tempmax; i++) {
                if (arr[i] > tempmax) tempmax = arr[i];
            }
            count++;
            if (i < arr.size() - 1) {
                tempstart = i;
                tempmax = arr[i];            
            }else break;
        }
        return count;
    }
};
