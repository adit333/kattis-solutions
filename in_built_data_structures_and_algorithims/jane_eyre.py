""" https://ualberta.kattis.com/sessions/jot9wq/problems/janeeyre
"""

import sys
import heapq
from typing import List, Tuple

def jane_eyre(num_of_books: int, num_of_new_books: int, num_of_pages_jane: int,
    books_pq: List[Tuple[str, int]], new_books_pq: List[Tuple[int, str, int]]) -> None:

    books_pq.append(("Jane Eyre", num_of_pages_jane))
    heapq.heapify(books_pq)
    heapq.heapify(new_books_pq)
    current_time = 0
    finished_jane_eyre = False

    while not finished_jane_eyre:
        while new_books_pq and current_time >= new_books_pq[0][0]: # Update books to read if new books have arrived
            next_new_book = heapq.heappop(new_books_pq)
            heapq.heappush(books_pq, next_new_book[1:])
        next_book_to_read = heapq.heappop(books_pq)
        current_time += next_book_to_read[1]
        if next_book_to_read[0] == "Jane Eyre":
            print(current_time)
            return


def main():
    input_lines = sys.stdin.read().splitlines()
    num_of_books, num_of_new_books, num_of_pages_jane = list(map(int, input_lines[0].split()))
    books, new_books = [], []
    i = 1
    for _ in range(num_of_books):
        book = input_lines[i].split('"')
        books.append((book[1], int(book[2])))
        i += 1
    for _ in range(num_of_new_books):
        new_book = input_lines[i].split('"')
        new_books.append((int(new_book[0]), new_book[1], int(new_book[2])))
        i += 1
    jane_eyre(num_of_books, num_of_new_books, num_of_pages_jane,
        books, new_books
    )
    # jane_eyre(2, 2, 592,
    #     [("Pride and Predjudice", 432), ("Don Quixote", 863)],
    #     [(863, "Great Gatsby", 218), (1082, "Crime and Punishment", 545)]
    # )

if __name__ == '__main__':
    main()
