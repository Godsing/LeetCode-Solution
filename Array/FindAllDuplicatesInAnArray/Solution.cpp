#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> result;
        int i = 0;
        for (i = 0; i < nums.size(); ) {
            if (nums[i] != nums[nums[i]-1]) // loop until current value equals to corresponded value of position(current value minus 1). That is to say, the position has the right value(position_plus_one) or duplicated value.
              swap(nums[i], nums[nums[i] - 1]);
            else // the position corresponded to current_value_minus_one has been put appropriate value(aka. position_plus_one) 
                i++; 
        } // after the loop, every position has been put the most suitable value.
        for (i = 0; i < nums.size(); i++) {
            if (i != (nums[i] - 1) ) {
                result.emplace_back(nums[i]);
            }
        }
        return result;
    }
};

