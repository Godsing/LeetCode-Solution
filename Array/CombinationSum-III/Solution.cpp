/*************************************************************************
    > File Name: Solution.cpp
    > Author: Godsing
    > Mail: zzzpwang@gmail.com
    > Created Time: 2018-04-23
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
private:
    vector<vector<int> > all_sol;
    vector<int> one_sol;
    void combination(int cur, int k, int n) {
        if (k == 1) {
            if (n > cur && n <= 9) {
                one_sol.emplace_back(n);
                all_sol.emplace_back(one_sol);
                one_sol.pop_back();
            }
            return;
        }
        int upper_bound = (n - k * (k - 1) / 2) / k;
        for (int e = cur + 1; e <= min(upper_bound, 9); e++) {
            one_sol.emplace_back(e);
            combination(e, k - 1, n - e);
            one_sol.pop_back();
        }
    }

public:
    vector<vector<int> > combinationSum3(int k, int n) {
        combination(0, k, n);
        return all_sol;
    }
};
