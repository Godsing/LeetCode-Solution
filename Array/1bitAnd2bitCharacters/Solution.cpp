/*************************************************************************
    > File Name: Solution.cpp
    > Author: Godsing
    > Mail: zzzpwang@gmail.com
    > Created Time: 2018-04-14
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int i = 0;
        for (; i < bits.size() - 1; ){
            if (bits[i] == 1) 
                i += 2;
            else i++;
        }
        return i == bits.size() - 1;
    }
};
