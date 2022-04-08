"""https://ualberta.kattis.com/sessions/vg7m4t/problems/bundles

Aprroach:
We will use dynamic programming.
The importatnt thing to note here is the follwoing observation:
    For any two bundles A and B, either every dessert in A is also in B, 
    every dessert in B is also in A, or there is no dessert in both A and B.

This means we should naturally use a bottom-up DP solution: for each bundle,
    to get the items in that bundle we either buy that bundle,
    or we buy smaller bundles that make up the items in the bundles.
    We know such smaller bundles exist, as guaranteed by the question.

We will process out bundles bottom-up, starting from bundles of smaller sizes going to
larger sizes. We will also add an artificial bundle of our own that contains all the desserts,
we want to know the cost of obtating the items in this bundle.

After each iteration of proocessing a particular bundle, we will know what is the cheapest way
to items included in that bundle.
"""

import sys
from typing import List


bundles: List[List[int]]
bundle_costs: List[int]
buckets_for_bundles: List[List[int]]
last_bundle_this_dessert_was_considered: List[int]


def find_cheapest_way_to_get_desserts_in_bundle(bundle_id: int):
    global bundles, bundle_costs, buckets_for_bundles, last_bundle_this_dessert_was_considered

    total_cost = 0
    for dessert in bundles[bundle_id]:
        if last_bundle_this_dessert_was_considered[dessert] == -1:
            # If this dessert was never seen in a smaller bundle before, the cost of
            # getting all the items in this bundle is the bundle cost itself
            total_cost = bundle_costs[bundle_id]
            last_bundle_this_dessert_was_considered[dessert] = bundle_id
        
        elif last_bundle_this_dessert_was_considered[dessert] != bundle_id:
            total_cost += bundle_costs[last_bundle_this_dessert_was_considered[dessert]]
            # Now we mark all the other desserts found in the bundle as considered, since
            # if one dessert of the smaller bundle si present in this bundle, all other
            # desserts of the smaller bundle are also present in this larger bundle
            for other_dessert_in_bundle in bundles[last_bundle_this_dessert_was_considered[dessert]]:
                last_bundle_this_dessert_was_considered[other_dessert_in_bundle] = bundle_id
        
    # We either buy smaller bundles, or buy this bundle itself
    bundle_costs[bundle_id] = min(total_cost, bundle_costs[bundle_id])
    


def bundles_of_joy(num_desserts: int, num_bundles: int) -> None:
    global bundles, bundle_costs, buckets_for_bundles, last_bundle_this_dessert_was_considered

    last_bundle_this_dessert_was_considered = [-1] * (num_desserts+1)   # desserts are 1-indexed

    mega_bundle = [i for i in range(1, num_desserts+1)]     # Bundle of all desserts
    bundles.append(mega_bundle)
    bundle_costs.append(100000000)                          # Very very expensive
    buckets_for_bundles[num_desserts].append(num_bundles)     # Bundle id of mega_bundle is num_bundles

    for bucket in buckets_for_bundles:  # Bottom-up, small to big bundle sizes
        for bundle_id in bucket:
            find_cheapest_way_to_get_desserts_in_bundle(bundle_id)

    print(bundle_costs[num_bundles])    # Cost of the mega bundle


def main():
    global bundles, bundle_costs, buckets_for_bundles

    input_lines = sys.stdin.read().splitlines()
    test_cases = int(input_lines[0])
    i = 1
    while test_cases:
        num_desserts, num_bundles = list(map(int, input_lines[i].split()))
        i += 1

        bundles = [None for _ in range(num_bundles)]
        bundle_costs = [0 for _ in range(num_bundles)]
        buckets_for_bundles = [[] for _ in range(num_desserts+1)]  # records bucket size each bundle falls into
        bundle_id = 0

        while bundle_id < num_bundles:
            line = list(map(int, input_lines[i].split()))
            bundle_costs[bundle_id], bundle_size = line[:2]
            bundles[bundle_id] = line[2:]
            buckets_for_bundles[bundle_size].append(bundle_id)

            i += 1
            bundle_id += 1
        
        bundles_of_joy(num_desserts, num_bundles)
        test_cases -= 1


if __name__ == '__main__':
    main()
