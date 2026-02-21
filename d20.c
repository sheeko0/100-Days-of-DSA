/*Problem: Given an array of integers, count the number of subarrays whose sum is equal to zero.

Input:
- First line: integer n
- Second line: n integers

Output:
- Print the count of subarrays having sum zero

Example:
Input:
6
1 -1 2 -2 3 -3

Output:
6

Explanation: A subarray is a continuous part of the array. For the input array 1 -1 2 -2 3 -3, the following subarrays have sum zero: [1, -1], [2, -2], [3, -3], [1, -1, 2, -2], [2, -2, 3, -3], and [1, -1, 2, -2, 3, -3]. Since there are 6 such subarrays, the output is 6.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long key;
    int count;
    int used;
} Node;

int hash(long long x, int size) {
    x ^= (x >> 33);
    x *= 0xff51afd7ed558ccd;
    x ^= (x >> 33);
    return (int)(x % size + size) % size;
}

int main() {
    int n;
    scanf("%d", &n);

    long long arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }

    int size = 2 * n + 1;
    Node* table = (Node*)calloc(size, sizeof(Node));

    long long prefix = 0;
    long long result = 0;

    int idx = hash(0, size);
    while (table[idx].used) idx = (idx + 1) % size;
    table[idx].used = 1;
    table[idx].key = 0;
    table[idx].count = 1;

    for (int i = 0; i < n; i++) {
        prefix += arr[i];
        idx = hash(prefix, size);

        while (table[idx].used && table[idx].key != prefix)
            idx = (idx + 1) % size;

        if (table[idx].used) {
            result += table[idx].count;
            table[idx].count++;
        } else {
            table[idx].used = 1;
            table[idx].key = prefix;
            table[idx].count = 1;
        }
    }

    printf("%lld", result);
    free(table);
    return 0;
}
