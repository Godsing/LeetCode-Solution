## Problem

We have two special characters. The first character can be represented by one bit `0`. The second character can be represented by two bits (`10` or `11`).

Now given a string represented by several bits. Return whether the last character must be a one-bit character or not. The given string will always end with a zero.

**Example 1:**

```
Input: 
bits = [1, 0, 0]
Output: True
Explanation: 
The only way to decode it is two-bit character and one-bit character. So the last character is one-bit character.

```

**Example 2:**

```
Input: 
bits = [1, 1, 1, 0]
Output: False
Explanation: 
The only way to decode it is two-bit character and two-bit character. So the last character is NOT one-bit character.

```

**Note:**

`1 <= len(bits) <= 1000`.

`bits[i]` is always `0` or `1`.



## Solution

由于第一个字符表示成 `0` ，第二个字符表示成 `10` 或 `11` ，那么就意味着，对于一个给定的二进制序列且结尾是 `0` ，是这么解析的：从左向右，每次遇到一个1，那么必然是第二个字符，下一个字符可以直接跳过；在这种规则下，每次遇到一个0，则必然是第一个字符（因为所有属于第二个字符的0都会被跳过）。

可以看出，在这种解析方式下，解析的结果是唯一的。因此，如果除了最后一个0，前面的序列可以被完整解析，那么最后一个0一定是属于第一个字符的。而如果前面的序列没法被完整解析，就意味着最后一个0必然属于第二个字符。

```c++
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
```

