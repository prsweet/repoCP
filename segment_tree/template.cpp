#include <bits/stdc++.h>
using namespace std;

struct Node {
    int sum;
    bool identity;

    Node(bool identity = true) {
        this->identity = identity;
    }

    Node (int val) {
        identity = false;
        sum = val;
    }
};

struct SegTree {
    int n;
    vector<Node> tree;
    
private:
    Node queryHelper(int nodeidx, int start, int end, int l, int r) {
        if (r < start || end < l) return Node();
        if (l <= start && end <= r)  return tree[nodeidx];
        
        int mid = start + (end - start)/2;
        Node leftResult = queryHelper(2 * nodeidx, start, mid, l, r);
        Node rightResult = queryHelper(2 * nodeidx + 1, mid + 1, end, l, r);
        return merge(leftResult, rightResult);
    }

    void updateHelper(int nodeidx, int start, int end, int idx, Node val) {
        if (start == end) tree[nodeidx] = val;
        else {
            int mid = start + (end - start)/2;
            if (idx <= mid) updateHelper(2 * nodeidx, start, mid, idx, val);
            else updateHelper(2 * nodeidx + 1, mid + 1, end, idx, val);
            tree[nodeidx] = merge(tree[2 * nodeidx], tree[2 * nodeidx + 1]);
        }
    }
    
public:
    SegTree(int n) {
        this->n = n;
        tree.resize(4 * n);
    }

    Node merge(const Node &l, const Node &r) {
        if (l.identity) return r;
        if (r.identity) return l;
        
        Node parent(false);

        parent.sum = l.sum + r.sum;
        
        return parent;
    }

    Node query(int l, int r) {
        return queryHelper(1, 0, n-1, l, r);
    }

    void update(int idx, Node val) {
        updateHelper(1, 0, n-1, idx, val);
    }
};

int main()
{
    int n; cin >> n;
    vector<int> v(n);
    for (int &i : v) cin >> i;

    SegTree tree(n);
    for (int i = 0; i < n; i++) tree.update(i, { v[i] });
}

/*
    HOW TO USE THIS TEMPLATE (code part only, theory is in doc.md):

    1. struct Node fields:
       - Add whatever the problem needs: sum / mn, mx / ans, l, r, sz etc.
    2. Node() default:
       - `bool identity = true;` marks empty/out-of-range.
    3. Node(val) leaf:
       - change signature to match your Node.
       - Must set identity = false here.
    4. merge(l, r) body after the two identity checks:
       - write the problem logic here.
       - Construct parent via leaf constructor so identity stays false,
*/