//
// Created by Dmitriy Pavlov on 16.03.2021.
//

int n, m;
cin >> n >> m;
vector < vector<int> > a (n, vector<int> (m));
for (int i=0; i<n; ++i)
for (int j=0; j<m; ++j)
cin >> a[i][j];

int ans = 0;
vector<int> d (m, -1), d1 (m), d2 (m);
stack<int> st;
for (int i=0; i<n; ++i) {
for (int j=0; j<m; ++j)
if (a[i][j] == 1)
d[j] = i;
while (!st.empty()) st.pop();
for (int j=0; j<m; ++j) {
while (!st.empty() && d[st.top()] <= d[j])  st.pop();
d1[j] = st.empty() ? -1 : st.top();
st.push (j);
}
while (!st.empty()) st.pop();
for (int j=m-1; j>=0; --j) {
while (!st.empty() && d[st.top()] <= d[j])  st.pop();
d2[j] = st.empty() ? m : st.top();
st.push (j);
}
for (int j=0; j<m; ++j)
ans = max (ans, (i - d[j]) * (d2[j] - d1[j] - 1));
}

cout << ans;