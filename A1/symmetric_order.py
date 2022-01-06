"""
https://ualberta.kattis.com/sessions/xq7r95/problems/symmetricorder
Algorithm:
- First add the front of the list using by skipping over element by 1,
- Than, adjust where to start the reverse index depending on whether there are odd no. of elements,
- Add the elements in reverse order by skipping over 1 element.
"""

def symmetric_order(elements):
    n = len(elements)
    result = []
    i = 0
    for i in range(0, n, 2):
        result.append(elements[i])

    if n % 2 == 0:  # n is even
        last = n - 1
    else:           # n is odd
        last = n - 2

    for j in range(last, 0, -2):
        result.append(elements[j])

    print(result)


def main():
    symmetric_order([1, 2, 3, 4, 5])


if __name__ == '__main__':
    main()