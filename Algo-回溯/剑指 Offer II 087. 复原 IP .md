## 题目

**有效 IP 地址** 正好由四个整数（每个整数位于 `0` 到 `255` 之间组成，且不能含有前导 `0`），整数之间用 `'.'` 分隔。

- 例如：`"0.1.2.201"` 和` "192.168.1.1"` 是 **有效** IP 地址，但是 `"0.011.255.245"`、`"192.168.1.312"` 和 `"192.168@1.1"` 是 **无效** IP 地址。

给定一个只包含数字的字符串 `s` ，用以表示一个 IP 地址，返回所有可能的**有效 IP 地址**，这些地址可以通过在 `s` 中插入 `'.'` 来形成。你 **不能** 重新排序或删除 `s` 中的任何数字。你可以按 **任何** 顺序返回答案。

 

**示例 1：**

```
输入：s = "25525511135"
输出：["255.255.11.135","255.255.111.35"]
```

**示例 2：**

```
输入：s = "0000"
输出：["0.0.0.0"]
```

**示例 3：**

```
输入：s = "101023"
输出：["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
```

 

**提示：**

- `1 <= s.length <= 20`
- `s` 仅由数字组成



注意：本题与主站 93 题相同：https://leetcode-cn.com/problems/restore-ip-addresses/ 



## 题解

本题细节很多：

- 需要解析出 4 个符合要求的 IP 片段，且第 4 个片段必须刚好是到达输入字符串 s 的末尾；
- 需要注意判断每一个 IP 片段是否符合要求：
  - 长度必须为 1~3；
  - 长度大于等于 2 时，不能有前导 0；
  - 长度为 3 时，不能超过 255；
- 可以添加剪枝进行优化：
  - 假设剩余字符串长度 n，剩余需要寻找的 IP 片段有 m 个，则要求 $m \le n \le 3 \times m$，否则剪枝。

```c++
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<int> dot_indices;  // 每个 IP 地址片段的结尾字符的索引
        vector<string> res;
        backtracking(s, dot_indices, res);
        return res;
    }

    void backtracking(string& s, vector<int>& dot_indices, vector<string>& res) {
        if (dot_indices.size() == 4) {
            string ip = s.substr(0, dot_indices[0]+1) + '.';
            ip += s.substr(dot_indices[0]+1, dot_indices[1]-dot_indices[0]) + '.';
            ip += s.substr(dot_indices[1]+1, dot_indices[2]-dot_indices[1]) + '.';
            ip += s.substr(dot_indices[2]+1);
            res.push_back(ip);
            return ;
        }
        int start_idx = dot_indices.empty() ? 0 : dot_indices.back()+1;
        for (int len = 1; len <= 3 && (start_idx + len <= s.size()); len++) {
            if (len >= 2 && s[start_idx] == '0') break;  // 存在前导 0，后续的都不用考虑了
            if (len == 3 && s.substr(start_idx, 3) > "255") continue;  // 超过 255 不用考虑
            int end_idx = start_idx + len - 1;
            if (dot_indices.size() == 3 && end_idx != s.size() - 1) continue;  // 第 4 个点(我虚拟的)，必须是 s 的最后一个字符，否则不用考虑
            int rest_ip_part = 3 - dot_indices.size();
            int rest_s_len = s.size() - 1 - end_idx;
            if (rest_s_len < rest_ip_part || rest_s_len > rest_ip_part*3) continue;  // 剩余字符串不够或太长，则剪枝

            dot_indices.push_back(end_idx);
            backtracking(s, dot_indices, res);
            dot_indices.pop_back();
        }
    }
};
// 运行耗时：0 ms，说明多剪枝还是有用的
```

