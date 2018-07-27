## Problem

Design a data structure that supports all following operations in *average* **O(1)** time.

1. `insert(val)`: Inserts an item val to the set if not already present.
2. `remove(val)`: Removes an item val from the set if present.
3. `getRandom`: Returns a random element from current set of elements. Each element must have the **same probability** of being returned.

**Example:**

```
// Init an empty set.
RandomizedSet randomSet = new RandomizedSet();

// Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomSet.insert(1);

// Returns false as 2 does not exist in the set.
randomSet.remove(2);

// Inserts 2 to the set, returns true. Set now contains [1,2].
randomSet.insert(2);

// getRandom should return either 1 or 2 randomly.
randomSet.getRandom();

// Removes 1 from the set, returns true. Set now contains [2].
randomSet.remove(1);

// 2 was already in the set, so return false.
randomSet.insert(2);

// Since 2 is the only number in the set, getRandom always return 2.
randomSet.getRandom();
```

 

## Solution

一开始没看懂题，参考了讨论版块其他人的解法：[AC C++ Solution. Unordered_map + Vector](https://leetcode.com/problems/insert-delete-getrandom-o1/discuss/85422/AC-C++-Solution.-Unordered_map-+-Vector) 

```cpp
class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (vi_map.find(val) != vi_map.end()) return false;
        vi_map[val] = vals.size();
        vals.emplace_back(val);
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (vi_map.find(val) == vi_map.end()) return false;
        int last_val = vals.back();
        vi_map[last_val] = vi_map[val];  //set the index of last_val to the current index of val
        vals[vi_map[val]] = last_val;  //move the last_val to the place of val
        vals.pop_back();
        vi_map.erase(val);
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return vals[rand() % vals.size()];
    }
private:
    unordered_map<int, int> vi_map;  //store the <value, index> pairs
    vector<int> vals;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
```

