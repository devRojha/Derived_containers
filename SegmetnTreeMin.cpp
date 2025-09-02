#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;
using vi = vector<ll> ;
#define f_i(x, n)  for(ll i = x; i < n ; i++)


class Segment { 
    vector<ll> segment_tree;
    ll sz;
    public : 
    Segment(ll n) {
        segment_tree.resize((4*n), 0);
        sz = 4 * n;
    }

    ll build(ll ss, ll se, ll si, vector<ll> &vec) {
        if (ss == se) {
            segment_tree[si] = vec[ss];
            return vec[ss];
        }

        ll mid = (ss + se) / 2;

        ll left = build (ss, mid, 2*si+1, vec);
        ll right = build (mid+1, se, 2*si+2, vec);

        return segment_tree[si] = min(left, right);
    }

    ll update (ll ss, ll se, ll idx, ll val, ll si) {
        if (idx < ss || idx > se) return segment_tree[si];

        if (ss == se) {
            segment_tree[si] = val;
            return val;
        }

        ll mid = (ss + se) / 2;

        ll left = update(ss, mid, idx, val, 2*si+1);
        ll right = update(mid+1, se, idx, val, 2*si+2);

        return segment_tree[si] = min(left, right);
    }

    ll query (ll qs, ll qe, ll ss, ll se, ll si) {
        if (qs > se || qe < ss) return 1e17;

        if (qs <= ss && qe >= se) return segment_tree[si];

        ll mid = (ss + se) / 2;

        ll left = query (qs, qe, ss, mid, 2*si+1);
        ll right = query (qs, qe, mid+1, se, 2*si+2);

        return min(left, right);
    }

};
 
void solve() {
    ll n, q;

    cin >> n >> q;
    vi vec(n);
    f_i(0, n) cin >> vec[i];

    Segment segment(n);

    segment.build(0, n-1, 0, vec);

    while (q--) {
        ll type ; cin >> type;

        if (type == 1) {
            ll idx, num ; 
            cin >> idx >> num;
            segment.update(0, n-1, idx-1, num, 0);
            vec[idx-1] = num;
        }
        else {
            ll l, r; 
            cin >> l >> r;
            cout << segment.query(l-1, r-1, 0, n-1, 0) << endl;
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
