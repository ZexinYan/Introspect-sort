//
// Created by 颜泽鑫 on 24/02/2017.
//

#include <iostream>
using namespace std;
#define threshold 16

template <class RandomAccessIterator>
inline void sort(RandomAccessIterator first,
                 RandomAccessIterator last);

template <class Size>
inline Size __lg(Size n);

template <class value_type>
value_type __median(value_type a,
                    value_type b,
                    value_type c);

template <class RandomAccessIterator, class Size>
void __introsort_loop(RandomAccessIterator first,
                      RandomAccessIterator last,
                      Size depth_limit);

template <class RandomAccessIterator>
void __unguarded_insertion_sort(RandomAccessIterator first,
                                RandomAccessIterator last);

template <class RandomAccessIterator>
void __unguarded_insertion_sort(RandomAccessIterator first,
                                RandomAccessIterator last);

template <class RandomAccessIterator>
void __final_insertion_sort(RandomAccessIterator first,
                            RandomAccessIterator last);

template <class RandomAccessIterator, class value_type>
void ___unguarded_linear_insert(RandomAccessIterator last,
                                value_type value);

template <class RandomAccessIterator, class value_type>
RandomAccessIterator __unguarded_partiton(RandomAccessIterator first,
                                          RandomAccessIterator last,
                                          value_type pivot);


template <class RandomAccessIterator>
inline void sort(RandomAccessIterator first, RandomAccessIterator last) {
    if (first != last) {
        __introsort_loop(first, last, __lg(last - first) * 2);
        __final_insertion_sort(first, last);
    }
}

template <class Size>
inline Size __lg(Size n) {
    Size k = 0;
    for (k = 0; n > 1; n >>= 1) {
        k++;
    }
    return k;
}

template <class value_type>
value_type __median(value_type a, value_type b, value_type c) {
    if (a < b) {
        if (a < c) {
            return b < c ? b : c;
        } else {
            return a;
        }
    } else {
        if (c < b) {
            return b;
        } else {
            return a < c ? a : c;
        }
    }
}

template <class RandomAccessIterator, class Size>
void __introsort_loop(RandomAccessIterator first,
                      RandomAccessIterator last,
                      Size depth_limit) {
    while (last - first > threshold) {
        if (depth_limit == 0) {
            partial_sort(first, last, last);
            return;
        }
        depth_limit--;
        RandomAccessIterator cur =
                __unguarded_partiton(first,
                                     last,
                                     __median(*first,
                                              *(last - 1),
                                              *(first + (last - first) / 2)));
        __introsort_loop(cur, last, depth_limit);
        last = cur;
    }
};

template <class RandomAccessIterator>
void __unguarded_insertion_sort(RandomAccessIterator first,
                                RandomAccessIterator last) {
    for (RandomAccessIterator iter = first; iter != last; iter++) {
        ___unguarded_linear_insert(iter, *iter);
    }
}

template <class RandomAccessIterator>
void __final_insertion_sort(RandomAccessIterator first,
                            RandomAccessIterator last) {
    if (last - first > threshold) {
        ___insert_sort(first, first + threshold);
        __unguarded_insertion_sort(first + threshold, last);
    } else {
        ___insert_sort(first, last);
    }
}

template <class RandomAccessIterator, class value_type>
void ___unguarded_linear_insert(RandomAccessIterator last, value_type value) {
    RandomAccessIterator next = last;
    next--;

    while (value < *next) {
        *last = *next;
        last = next;
        next--;
    }
    *last = value;
};

template <class RandomAccessIterator>
void ____linear_insert(RandomAccessIterator first, RandomAccessIterator last) {
    auto value = *last;
    if (value < *last) {
        copy_backward(first, last, last + 1);
        *first = value;
    } else {
        ___unguarded_linear_insert(last, value);
    }
}

template <class RandomAccessIterator>
void ___insert_sort(RandomAccessIterator first, RandomAccessIterator last) {
    if (first == last) { return; }
    for (RandomAccessIterator iter = first + 1; iter != last; iter++) {
        ____linear_insert(first, iter);
    }
}

template <class RandomAccessIterator, class value_type>
RandomAccessIterator __unguarded_partiton(RandomAccessIterator first,
                                          RandomAccessIterator last,
                                          value_type pivot) {
    while (true) {
        while (*first < pivot) { first++; }
        last--;
        while (*last > pivot) { last--; }
        if (first >= last) { return first; }
        iter_swap(first, last);
        first++;
    }
};
