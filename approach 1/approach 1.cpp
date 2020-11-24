#include <bits/stdc++.h>
#define lld long long
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define MAX 1000009

using namespace std;

int n,kk=1,czy,odk,counter;
lld ppp;
int tab[1000009];
pair<int,int> tree[2100000];
vector<pair<int,pair<pair<int,int> >sta;

void ustaw(int gdzie,int co){
    gdzie+=kk;
    tree[gdzie]=mp(co,gdzie-kk);
    gdzie>>=1;
    while(gdzie>0){
        if(tree[gdzie*2].f>tree[gdzie*2+1].f){
            tree[gdzie]=mp(tree[gdzie*2].f,tree[gdzie*2].s);
        }else{
            tree[gdzie]=mp(tree[gdzie*2+1].f,tree[gdzie*2+1].s);
        }

        gdzie>>=1;
    }
}

pair<int,int> check(int l,int p){
    pair<int,int> wyn=mp(0,0);
    l+=kk;
    p+=kk;
    if(tree[l].f>tree[p].f){
        wyn=mp(tree[l].f,l-kk);
    }else{
        wyn=mp(tree[p].f,p-kk);
    }
    while(l/2!=p/2){
        if(l%2==0){
            if(tree[l+1].f>wyn.f){
                wyn=mp(tree[l+1].f,tree[l+1].s);
            }
        }
        if(p%2==1){
            if(tree[p-1].f>wyn.f){
                wyn=mp(tree[p-1].f,tree[p-1].s);
            }
        }
        l>>=1;
        p>>=1;
    }

    return wyn;
}

int zad(int l, int p){
    int gdz=check(l,p).s;
    //ppp++;
    //cout<<l<<" "<<p<<" "<<gdz<<endl;
    //czy=0;
    //odk=gdz-2;
    if(gdz-1>l){
        sta.pb(mp())
        if(zad(l,gdz-1)) return 1;
    }
    //gdz=check(l,p).s;
    if(gdz+1<p){
            //cout<<"F";
        if(zad(gdz+1,p)){
            sort(tab+l,tab+gdz);
            return 1;
        }
    }
    //gdz=check(l,p).s;
    if(gdz>l){
        //cout<<gdz<<" "<<l;
        sort(tab+l,tab+gdz);
        swap(tab[gdz-1],tab[gdz]);
        sort(tab+gdz,tab+p+1);
        return 1;
    }
    return 0;

}

int main()
{
    scanf("%d",&n);
    while(kk<n){
        kk<<=1;
    }

    int pocz=-1;
    int xdd=1;
    int xdd1=0;
    for(int i=1;i<=n;++i){
        scanf("%d",&tab[i]);
        //tab[i]=i;

        //co[i]=mp(tab[i],i);

        ustaw(i,tab[i]);
    }
   // sort(co+1,co+n+1);

    for(int i=1;i<=n;++i){
        //cout<<tab[i];
    }

    zad(1,n);
    //cout<<ppp;
    for(int i=1;i<=n;++i){
        printf("%d ",tab[i]);
    }



    return 0;
}
