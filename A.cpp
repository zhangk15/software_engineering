#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#define maxn 100005
#define LL long long
#define eps 1e-8
using namespace std;

int kase = 0;
LL tree[maxn * 4], n, m;
bool flag[maxn * 4];

void Insert(int root, int ll, int rr, int k, LL x)
{
    if (ll == rr)
    {
        tree[root] = x;
        return;
    }
    int mid = ((ll + rr) >> 1);
    int lc = (root << 1);
    int rc = lc + 1;
    if (k <= mid)
        Insert(lc, ll, mid, k, x);
    else Insert(rc, mid + 1, rr, k, x);
    tree[root] = max(tree[lc], tree[rc]);
}

void update(int root, int ll, int rr, int left, int right, LL k)
{
    if (flag[root]) return;
    if (ll == rr)
    {
        tree[root] = tree[root] / k;
        if (tree[root] == 0) flag[root] = true;
        return;
    }
    int mid = ((ll + rr) >> 1);
    int lc = (root << 1);
    int rc = lc + 1;
    if (left <= mid) update(lc, ll, mid, left, right, k);
    if (mid + 1 <= right) update(rc, mid + 1, rr, left, right, k);
    if (flag[lc] && flag[rc]) flag[root] = true;
    tree[root] = max(tree[lc], tree[rc]);
}

LL query(int root, int ll, int rr, int left, int right)
{
    if (left <= ll && rr <= right)
    {
        return(tree[root]);
    }
    int mid = ((ll + rr) >> 1);
    int lc = (root << 1);
    int rc = lc + 1;
    LL ret = 0;
    if (left <= mid) ret = max(ret, query(lc, ll, mid, left, right));
    if (mid + 1 <= right) ret = max(ret, query(rc, mid + 1, rr, left, right));
    return ret;
}

int main()
{
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    while (scanf("%d", &n) != EOF)
    {
    //    printf("Case #%d:\n", ++kase);
        int i, op, l, r;
        memset(tree, 0, sizeof(tree));
        memset(flag, 0, sizeof(flag));
        for (i = 1; i <= n; i++)
        {
            LL x;
            scanf("%lld", &x);
            Insert(1, 1, n, i, x);
        }
        scanf("%d", &m);
        for (i = 1; i <= m; i++)
        {
            scanf("%d", &op);
            if (op == 1)
            {
                LL k;
                scanf("%d%d%lld", &l, &r, &k);
                if (k != 1) update(1, 1, n, l, r, k);
            }else
            {
                scanf("%d%d", &l, &r);
                printf("%lld\n", query(1, 1, n, l, r));
            }
        }
    //    printf("\n");
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
