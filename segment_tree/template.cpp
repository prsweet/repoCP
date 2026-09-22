#include <bits/stdc++.h>
using namespace std;

// this hold all the data needed by the query
struct Node {
    int sum;
    // you can create other vars like min max and all
public:
    Node() {
        sum = 0;
    }

    Node(int val) {
        sum = val;
    }
};

struct SegTree {
    vector<Node> tree;
public:
    SegTree(int n) {
        tree.resize(4 * n);
    }

    Node merge(const Node &l, const Node &r) {
        Node parent;
        parent.sum = l.sum + r.sum;
        // other ops
        return parent;
    }
    
    void makeTree(vector<int> &arr, int nodeidx, int start, int end) {
        if (start == end) tree[nodeidx] = Node(arr[start]);
        else {
            int mid = start + (end - start)/2;
            makeTree(arr, 2 * nodeidx, start, mid);
            makeTree(arr, 2 * nodeidx + 1, mid + 1, end);
            tree[nodeidx] = merge(tree[2 * nodeidx], tree[2 * nodeidx + 1]);
        }
    }

    Node query(int nodeidx, int start, int end, int l, int r) {
        if (r < start || end < l) return Node();
        if (l <= start && end <= r)  return tree[nodeidx];
        
        int mid = start + (end - start)/2;
        Node leftResult = query(2 * nodeidx, start, mid, l, r);
        Node rightResult = query(2 * nodeidx + 1, mid + 1, end, l, r);
        return merge(leftResult, rightResult);
    }

    void update(int nodeidx, int start, int end, int idx, int val) {
        if (start == end) tree[nodeidx] = Node(val);
        else {
            int mid = start + (end - start)/2;
            if (idx <= mid) update(2 * nodeidx, start, mid, idx, val);
            else update(2 * nodeidx + 1, mid + 1, end, idx, val);
            tree[nodeidx] = merge(tree[2 * nodeidx], tree[2 * nodeidx + 1]);
        }
    }
};