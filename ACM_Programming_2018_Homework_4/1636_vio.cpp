#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 100005
int sum[7][maxn],n,q,a[7];
char s[maxn];

inline int read(void)
{
    int x=0;
    char ch=getchar();
    while (ch>'9'||ch<'0') ch=getchar();
    while (ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x;
}

int main()
{
    freopen("1636.in", "r", stdin);
    scanf("%s",s+1);
    n=strlen(s+1);
    for (int i=1;i<=n;++i) sum[s[i]-'A'][i]++;
    for (int i=0;i<=6;++i)
        for (int j=1;j<=n;++j)
            sum[i][j]+=sum[i][j-1];
    q=read();
    for (int i=1;i<=q;++i)
    {
        int l=read(),r=read();
        int pos=-1;bool pd=1;
        for (int j=0;j<=6;++j)
        {
            a[j]=sum[j][r]-sum[j][l-1];
            if (a[j]&1)
                if (pos<0) pos=j;
                else {pd=0;break;}
        }
        if (!pd) continue;
        for (int j=0;j<=6;++j) memset(sum[j]+l,0,(r-l+1)*4);
        register int pl=l,pr=r;
        for (int j=0;j<=6;++j)
        {
            a[j]>>=1;
            for (int k=1;k<=a[j];++k)
                sum[j][pl++]=1,sum[j][pr--]=1;
        }
        if (pos>=0)
            sum[pos][pl]=1;
        for (int j=0;j<=6;j++)
            for (int k=l;k<=r;k++)
                sum[j][k]+=sum[j][k-1];
        for (int _i=1;_i<=n;_i++)
            for (int j=0;j<=6;j++)
                if (sum[j][_i]>sum[j][_i-1]) printf("%c",'A'+j);
        printf("\n");
    }
    //printf("%d\n",n);

    return 0;
}
