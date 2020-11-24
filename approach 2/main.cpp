#include <bits/stdc++.h>
#define lld long long
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define MAX 1000009

using namespace std;

int n,kk=1,czy,odk;
pair<int,pair<int,int> >lasty[MAX];
pair<int,pair<int,int> >last;
lld ppp;
int tab[1000009];
int gdz[1000009];
int coj[MAX];
int coj1[MAX];
int tree[2100000];

void add(int gdzie){
    gdzie+=kk;
    while(gdzie){
        tree[gdzie]++;
        gdzie>>=1;
    }
}

int check(int ile,int gdzie){
    while(gdzie<kk){
        //cout<<"A";
        if(tree[gdzie*2]>=ile){
            gdzie=gdzie*2;
        }else{
            ile-=tree[gdzie*2];
            gdzie=gdzie*2+1;
        }
        //gdzie<<=1;
    }
    //cout<<gdzie-kk<<endl;
    return gdzie-kk;
}

int check1(int gdzie){
    int l=kk;
    int p=kk+gdzie;
    int wyn=0;
    wyn+=tree[l];
    wyn+=tree[p];
    while(l/2!=p/2){
        if(l%2==0){
            wyn+=tree[l+1];
        }
        if(p%2==1){
            wyn+=tree[p-1];
        }
        l>>=1;
        p>>=1;
    }
    return wyn;
}

int main()
{
	scanf("%d",&n);
	while(kk<n+1)kk<<=1;
	for(int i=1;i<=n;++i){
        scanf("%d",&tab[i]);
        //tab[i]=i;
        coj[i]=tab[i];
        //gdz[tab[i]]=i;
    }
    sort(coj+1,coj+n+1);
    for(int i=1;i<=n;++i){
    	coj1[coj[i]]=i;
	}
	for(int i=1;i<=n;++i){
		//coj[i]=tab[i];
    	tab[i]=coj1[tab[i]];
    	gdz[tab[i]]=i;
	}

	//ss.insert(0);
	//ss.insert(n+1);
	add(0);
	add(n+1);
	for(int i=n;i>=1;--i){
		int czeg=check1(gdz[i]);
        //cout<<czeg<<endl;
		lasty[i]=mp(gdz[i],mp(check(czeg,1),check(czeg+1,1)));

		if(tab[gdz[i]-1]<i&&gdz[i]!=1){
			last=lasty[i];
		}
		//cout<<"X"<<gdz[i];
		add(gdz[i]);
	}
	sort(tab+last.s.f+1,tab+last.f);
	sort(tab+last.f+1,tab+last.second.s);
	swap(tab[last.f],tab[last.f-1]);
	//cout<<last.f
	//ss.clear();
	for(int i=1;i<=n;++i){
		coj1[i]=0;
	}//cout<<"X";
	for(int i=n;i>tab[last.first-1];--i){
		if(gdz[i]<last.first&&coj1[lasty[i].first]==0){
			sort(tab+lasty[i].s.f+1,tab+lasty[i].f);
			for(int j=lasty[i].s.f+1;j<lasty[i].f;++j){
				coj1[j]=1;
			}
		}
	}
	for(int i=1;i<=n;++i){
        printf("%d ",coj[tab[i]]);
    }
	return 0;
}
