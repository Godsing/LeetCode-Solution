#!/usr/bin python
#-*- coding: utf-8 -*-
 
# File Name: Solution.py
# Author: Godsing
# mail: zzzpwang@gmail.com
# Created Time: 2018-04-26
class Solution:
    def twoSum(self, numbers, target):
        """
        :type numbers: List[int]
        :type target: int
        :rtype: List[int]
        """
        l, r = 0, len(numbers) - 1
        while l < r:
            s = numbers[l] + numbers[r]
            if s == target:
                return [l+1, r+1]
            elif s < target:
                l += 1
            else:
                r -= 1


if __name__ == '__main__':
    nums = [2, 4, 7, 9]
    tar = 9
    s = Solution()
    a = s.twoSum(nums, tar)
    print(a)
