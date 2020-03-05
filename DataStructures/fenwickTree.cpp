#include<bits/stdc++.h>
using namespace std;

void printTree(int *arr, int n) {
    for (int i=1; i<= n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int findSum(int *fenwickTree, int n, int l, int r) {
    
    // find sum1 upto index r
    int idx = r, sum1 = 0;
    while (idx > 0) {
        sum1 += fenwickTree[idx];
        idx -= (idx & (-idx));
    }
    
    // find sum2 upto index l
    idx = l-1;
    int sum2 = 0;
    while(idx > 0) {
        sum2 += fenwickTree[idx];
        idx -= (idx & (-idx));
    }
    
    // return the difference
    return (sum1 - sum2);
}

void updateTree(int *fenwickTree, int n, int idx, int val, int flag) {
    
    int i = idx;
    int change = val;
    if (flag) {
        // flag == 1 means, the update was called by query, not by the maker
        change -= fenwickTree[idx];    
    }
    
    while(i <= n) {
        fenwickTree[i] += change;
        i += (i & (-i));
    }
    
}

void maker(int *fenwickTree, int n, int *arr) {
    
    // create the sums
    for (int i=1; i<=n; i++) {
        // until the maxindex is reached, find the parent of this node `i` and add this value to it's parent 
        updateTree(fenwickTree, n, i, arr[i], 0);
    }
    
    // print this sum
    printTree(fenwickTree, n);
    
}

int main() {
    
    // iters
    int i,j,k;
    
    // get array size and no of queries
    int n, q;
    scanf("%d%d", &n, &q);
    
    // get the array
    int arr[n+1];
    for (i=1;i<=n;i++) {
        scanf("%d", arr + i);
    }
    
    // make the tree
    int fenwickTree[n+1] = {0};
    maker(fenwickTree, n, arr);

    // start reading queries
    int choice;
    while (q--) {
        // get user choice
        scanf("%d", &choice);
        
        if (choice == 1) {
            // get sum of the range
            int l, r;
            scanf("%d%d", &l, &r);
            printf("Range Sum between l = %2d and r = %2d is %3d\n", l, r, findSum(fenwickTree, n, l, r));
        }
        else {
            // get the index and value of update
            int idx, val;
            scanf("%d%d", &idx, &val);
            
            updateTree(fenwickTree, n, idx, val, 1);
            printf("The new Fenwick Tree is...\n");
            printTree(fenwickTree, n);
        }
    }
    
    
    
    
    return 0;
}
                