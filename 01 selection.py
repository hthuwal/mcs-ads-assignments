from random import randint
import sys
import time


def swap(arr, i, j):
    """Inplace swap values in an array."""
    arr[i], arr[j] = arr[j], arr[i]


def partition(arr, beg, end, pvt_idx):
    """
    Inplace partition-ing of arr[beg:end] around pivot (arr[pvt_idx]).

    Returns the updated index of pivot.
    """

    pvt = arr[pvt_idx]

    # Move pivot to the end
    swap(arr, end, pvt_idx)

    # This will store the new index of pivot
    pvt_new_idx = beg

    for idx in range(beg, end):

        # Move values smaller than pivot to the beginning of array
        if arr[idx] < pvt:
            swap(arr, idx, pvt_new_idx)
            pvt_new_idx += 1

    # Move pivot to new position
    swap(arr, end, pvt_new_idx)

    return pvt_new_idx


def median_of_medians(A, i):

    # divide A into sublists of len 5
    sublists = [A[j:j + 5] for j in range(0, len(A), 5)]
    medians = [sorted(sublist)[len(sublist) / 2] for sublist in sublists]
    if len(medians) <= 5:
        pivot = sorted(medians)[len(medians) / 2]
    else:
        # the pivot is the median of the medians
        pivot = median_of_medians(medians, len(medians) / 2)

    # partitioning step
    low = [j for j in A if j < pivot]
    high = [j for j in A if j > pivot]

    k = len(low)
    if i < k:
        return median_of_medians(low, i)
    elif i > k:
        return median_of_medians(high, i - k - 1)
    else:  # pivot = k
        return pivot


def randomized_select(arr, beg, end, k):
    """
    Returns the k-th smallest element in arr[beg:end]
    """

    # If the list has only 1 element
    if beg == end:
        return arr[beg]

    # Selection with randomized pivot selection
    pvt_new_idx = partition(arr, beg, end, pvt_idx=randint(beg, end))

    if k == pvt_new_idx:
        return arr[pvt_new_idx]
    elif k < pvt_new_idx:
        return randomized_select(arr, beg, pvt_new_idx - 1, k)
    elif k > pvt_new_idx:
        return randomized_select(arr, pvt_new_idx + 1, end, k)


if __name__ == '__main__':
    file = sys.argv[1]
    k = int(sys.argv[2])

    f = open(file, "r")
    x = map(int, f.read().strip().split("\n"))
    # x = []
    # for each in y:
    #     l = map(int, each.strip().split(" "))
    #     x = x+l

    print"Input Size : ", len(x)
    print"\nRandom"
    start = time.clock()
    ans = randomized_select(x, 0, len(x) - 1, k - 1)
    time_rand = time.clock() - start
    print "Time taken : ", time_rand
    print"Element with rank ", k, " : ", ans

    print("\nDeterministic")
    start = time.clock()
    ans = median_of_medians(x, k - 1)
    time_detr = time.clock() - start
    print "Time taken : ", time_detr
    print"Element with rank ", k, " : ", ans

    print("\nSorted")
    start = time.clock()
    ans = sorted(x)[k - 1]
    time_sort = time.clock() - start
    print "Time taken : ", time_sort
    print"Element with rank ", k, " : ", ans

    print "Random : Deterministic : Sort = %f : %f : %f\n" % (1.0, time_detr / time_rand, time_sort / time_rand)
    # print(sorted(arr))
