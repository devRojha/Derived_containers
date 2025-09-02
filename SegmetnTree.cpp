#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;
using vi = vector<ll> ;
#define f_i(x, n)  for(ll i = x; i < n ; i++)

 
void solve() {
    
    ll n , q; cin >> n >> q;
    vi vec(n);
    f_i(0, n) cin >> vec[i];

    vi segment_tree((4 * n), 0);

    function <ll (ll,ll,ll)> build = [&](ll ss, ll se, ll si) {
        if (ss == se) {
            segment_tree[si] = vec[ss];
            return vec[ss];
        }

        ll mid = (ss + se) / 2;

        segment_tree[si] = build(ss, mid, (2*si+1)) + build(mid+1, se, (2*si+2));

        return segment_tree[si];
    };

    function <void(ll,ll,ll,ll,ll)> update = [&](ll ss, ll se, ll i, ll si, ll diff) {
        if (i < ss || i > se) return;

        segment_tree[si] += diff;

        if (se > ss) {
            ll mid = (se + ss) / 2;
            update(ss, mid, i, (2*si+1), diff);
            update(mid+1, se, i, (2*si+2), diff);
        }
    };

    function <ll (ll, ll, ll, ll, ll) > query = [&](ll qs, ll qe, ll ss, ll se, ll si) {
        if (se < qs || qe < ss) return 0LL;

        if (qs <= ss && qe >= se) {
            return segment_tree[si];
        }

        ll mid = (ss + se) / 2;

        return query(qs, qe, ss, mid, (2*si+1)) + query(qs, qe, mid+1, se, (2*si+2));
    };

    build(0, n-1, 0);

    while (q--) {
        ll type; cin >> type;
        if (type == 1) {
            ll idx, num;
            cin >> idx >> num;
            ll diff = num - vec[idx-1];
            vec[idx-1] = num;
            update(0, n-1, idx-1, 0, diff);
        }
        else {
            ll l, r; 
            cin >> l >> r;

            cout << query(l-1, r-1, 0, n-1, 0) << endl;
        }
    }
}

// DEV_R_OJHA 

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