#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

class SegmentTree {
    vector <int> tree;
    vector <int> lazy;
    public : 

    SegmentTree(int n) {
        tree.assign(4*n, 0);
        lazy.assign(4*n, 0);
    }

    int build (int ss, int se, int si, vector<int> &vec) {
        if (ss == se) {
            return tree[si] = vec[ss];
        }

        int mid = (ss + se) / 2;

        int left = build (ss, mid, 2*si+1, vec);
        int right = build (mid+1, se, 2*si+2, vec);

        return tree[si] = (left + right);
    }

    void propogate (int ss, int se, int si) {
        if (lazy[si] != 0) {
            tree[si] += (se - ss + 1) * lazy[si];

            if (ss != se) {
                lazy[2*si+1] += lazy[si];
                lazy[2*si+2] += lazy[si];
            }

            lazy[si] = 0;
        }
    }

    int update (int us, int ue, int ss, int se, int val, int si) {
        
        propogate(ss, se, si);

        if (ue < ss || us > se) return tree[si];

        if (us <= ss && ue >= se) {
            lazy[si] += val;
            propogate(ss, se, si);
            return tree[si];
        }

        int mid = (ss + se) / 2;

        int left = update(us, ue, ss, mid, val, 2*si+1);
        int right = update(us, ue, mid+1, se, val, 2*si+2);

        return tree[si] = (left + right);
    }

    int query (int qs, int qe, int ss, int se, int si) {

        propogate(ss, se, si);

        if (qe < ss || qs > se) return 0;

        if (qs <= ss && qe >= se) return tree[si];

        int mid = (ss + se) / 2;

        int left = query (qs, qe, ss, mid, 2*si+1);
        int right = query (qs, qe, mid+1, se, 2*si+2);

        return (left + right);
    }
};
 
void solve() {
    ll n , q;
    cin >> n >> q;

    vector<int> vec(n);

    for (int & v : vec) cin >> v;

    SegmentTree segmentTree(n);

    segmentTree.build (0, n-1, 0, vec);
    
    while (q--) {
        int type;
        cin >> type;
        int l, r;
        cin >> l >> r;
        l-- ; r--;      // => making 0 based index

        if (type == 1) {
            int val;
            cin >> val ;
            segmentTree.update (l, r, 0, n-1, val, 0);
        }
        else {
            cout << segmentTree.query(l, r, 0, n-1, 0) << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    ll T = 1;
    // cin >> T; 
    while (T--) {
        solve();
    }
    return 0;
}
