#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

vector<int>bit(5, 0);

void update(int idx , int val){
    while(idx <= 4){
        bit[idx] += val;

        idx += (idx & -idx);
    }
}
int get(int idx){
    int sum = 0 ;
    while(idx > 0){
        sum += bit[idx];
        idx -= (idx & -idx);
    }
    return sum;
}
void solve() {
    
    update(1 , 1);
    update(2 , 2);
    update(3 , 3);
    update(4 , 4);
    cout<<get(3);
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
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}
