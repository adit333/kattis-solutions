"""
https://ualberta.kattis.com/sessions/xq7r95/problems/integerdivision
Algorithm:
- Iterate over the array, divide each element by the divisor;
 place any new divisor in a hash map, with quotient as key and increment value by 1.
 Basically, we are simply counting how many elements have a quotient.
 - Then, iterate over the hash map, if value>1 (i.e. there are more than 2 indices 
 with same quotient value) do valueC2 and add it to the result.
 """
 
import math
from typing import List


def nCr(n,r):
    f = math.factorial
    return f(n) // f(r) // f(n-r)


def integer_divison(n: int, divisor: int, nums: List[int]) -> int:
    quotient_index_map = {}
    for i in range(len(nums)):
        quotient = nums[i] // divisor
        if quotient in quotient_index_map:
            quotient_index_map[quotient] += 1
        else:
            quotient_index_map[quotient] = 1
    
    result = 0
    for value in quotient_index_map.values():
        if value > 1:
            result += nCr(value, 2)
    print(result)


def main():
    # integer_divison(5, 4, [4, 5, 6, 7, 8])
    # integer_divison(5, 1, [4, 5, 6, 7, 8])
    # integer_divison(6, 1, [1, 2, 1, 2, 1, 2])
    n, divisor = map(int, input().split())
    nums = list(map(int, input().split()))
    integer_divison(n, divisor, nums)


if __name__ == '__main__':
    main()
