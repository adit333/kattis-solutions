"""https://open.kattis.com/problems/namethatpermutation
"""

"""
# Idea: we know the most significant value j is greatest j such that
#   j*(n-1)! <= k. So find it, fix it, and repeat with the remaining places
#  (having reduced k by j*(n-1)!)
# The only trick is that instead using j itself in the position, we use the j'th
# largest remaining value from {1, 2, ..., n} that has not yet been used.
"""

# generate all factorials ahead of time, probably not necessary
# (could probably use math.factorial)
fact = [1]
for i in range(1, 51):
    fact.append(fact[-1]*i)

while True:
    try:
        n, k = map(int, input().split())
    except:
        break

    numbers = list(range(1, n+1))
    ans = []
    for i in range(n):
        # find the largest j that where fact[n-i-1]*j <= k
        j = 0
        while fact[n-i-1]*(j+1) <= k: j += 1

        # append the j'th largest remaining number
        ans.append(numbers[j])

        # remove this number and reduce k
        numbers.remove(numbers[j])
        k -= fact[n-i-1]*j

    print(*ans)