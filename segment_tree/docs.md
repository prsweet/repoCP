# **Segment Tree**

A segment tree is a binary tree where:
    1. Each leaf represent single array element
    2. Each Node store a range information like (Sum, Min, Max, etc)
    3. Root is the entire array

Its best if the Segment Tree is the power of 2, so if n is not the power of 2,
we make it to the next power, so keeping the size 4n is standard because:
    if n = 2, tree_size_needed = 4 -> thats fine...
    if n = 3, tree_size_needed = 6 -> so we can take 8 as power of 2
    if n = 5, tree_size_needed = 10 -> we can do 16 which is more than 3n so to
              safe we do 4n

why we do in the power of 2:
    So that our code is free of if else for checking whether we exceed the boundaries
    with just little more space

for making this uses indexing like this:
    rootNode = 1;
    leftChild of i = 2i;
    rightChild of i = 2i + 1;
    for getting the parent of i -> [i/2];

We make it recursively where base case is LeafNode, i.e Single Element

```Cpp
    vector<int> tree(4 * n); // we store the tree information in the array;
    void makeTree(vector<int> &arr, int nodeidx, int start, int end) {
        if (start == end) tree[nodeidx] = arr[start];
        else {
            int mid = start + (end - start)/2;
            makeTree(arr, 2 * nodeidx, start, mid);
            makeTree(arr, 2 * nodeidx + 1, mid + 1, end);
            tree[nodeidx] = tree[2 * nodeidx] + tree[2 * nodeidx + 1];
            // here its just doing sum now, can store any data you need;
        }
    }
```

To query from the Tree we write the following function:

```Cpp
    int l, r; // the range we have to query
    int query(int nodeidx, int start, int end, int l, int r) {
        if (r < start || end < l) return 0; // because that is outside the range
        if (l <= start && end <= r)  {
            // this means that the current node covers the query range fully
            // so we can directly pass the value
            return tree[nodeidx];
        }
        int mid = start + (end - start)/2;
        int leftResult = query(2 * nodeidx, start, mid, l, r);
        int rightResult = query(2 * nodeidx + 1, mid + 1, end, l, r);
        return leftResult + rightResult;
    }
```

Now, for updating the values we will do the follow:

```Cpp
    void update(int nodeidx, int start, int end, int idx, int val) {
        if (start == end) tree[nodeidx] = val;
        else {
            int mid = start + (end - start)/2;
            if (idx <= mid) update(nodeidx, start, mid, idx, val);
            else update(nodeidx, mid + 1, end, idx, val);
            tree[nodeidx] = tree[2*node] + tree[2*node + 1]; // updating the sum
        }
    }
```
