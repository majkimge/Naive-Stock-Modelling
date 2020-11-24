#include <bits/stdc++.h>
#include <string>
#define lld long long
#define mp make_pair
#define f first
#define s second
#define pb push_back
#define MAX 230000
#define dok 40

using namespace std;

ifstream infile;
ofstream outfile;

string data[MAX];
string newdata[MAX];

double ndata[MAX][10];
int n,s11,ile,dlsell,whatnow;

pair<double,int> dp[MAX][4];
vector<int>selllen;

int stat[MAX];
double boi[MAX],bois[MAX];
vector<int> trans;

priority_queue<pair<double,int> > sel;
priority_queue<pair<double,int> > ser;
priority_queue<pair<double,int> > bul;
priority_queue<pair<double,int> > bur;

void smoother(int buy, int sell, double goa, int act){

    while(!bul.empty()){
        bul.pop();
    }
    while(!sel.empty()){
        sel.pop();
    }
    goa+=0.00026;
    int indi=1000000;

    int br=buy;
    int bl=buy;
    int sl=sell;
    int sr=sell;
    int obr=br;
    int obl=bl;
    int osl=sl;
    int osr=sr;
    //cout<<act;
    //cout<<goa<<endl;
    for(int i=max(0,sell-10);i<=min(sell+10,n-1);++i){
        sel.push(mp((double)-1*act*ndata[i][0],i));
    }

    for(int i=max(0,buy-10);i<=min(buy+10,n-1);++i){
        bul.push(mp((double)act*ndata[i][0],i));
    }
    sl=max(0,sell-10);
    sr=min(sell+10,n-1);
    bl=max(0,buy-10);
    br=min(buy+10,n-1);

    while((double)-sel.top().f-bul.top().f<goa){
        //cout<<-sel.top().f-bul.top().f<<endl;
        //cout<<bl<<" "<<br<<" "<<sl<<" "<<sr<<endl;
        if((double)(-abs(sel.top().f)+ndata[sell][0])*act>(double)(abs(bul.top().f)-ndata[buy][0])*act){
            if(sel.top().s>sell){
                sr=min(sr,sel.top().s);
                sr=max(sr,sell);

            }else{
                sl=max(sl,sel.top().s);
                sl=min(sl,sell);
            }
            if(sel.top().s==sell)cout<<"XDD"<<(-abs(sel.top().f)+ndata[sell][0])*act<<endl;
            sel.pop();
        }else{
            if(bul.top().s>buy){
                br=min(br,bul.top().s);
                br=max(br,buy);
            }else{
                bl=max(bl,bul.top().s);
                bl=min(bl,buy);
            }
            if(bul.top().s==buy)cout<<"XD"<<ndata[buy][0]-ndata[sell][0]<<endl;
            bul.pop();
        }
        while((sel.top().s<sl||sel.top().s>sr)){
            sel.pop();
        }

        while((bul.top().s<bl||bul.top().s>br)){
            bul.pop();
        }
    }
    //cout<<"S";

    for(int i=bl;i<=br;++i){
        if(act==1){
            stat[i]=1;
            boi[i]=-ndata[buy][0]+ndata[i][0];
        }else{
            stat[i]=2;
            boi[i]=ndata[buy][0]-ndata[i][0];
        }
    }

    for(int i=sl;i<=sr;++i){
        if(act==1){
            if(stat[i]==0||(stat[i]==1&&ndata[sell][0]-ndata[i][0]<boi[i]))stat[i]=-1;

        }else{
            if(stat[i]==0||(stat[i]==2&&-ndata[sell][0]+ndata[i][0]<boi[i]))stat[i]=-2;

        }
    }



}

int main()
{
    infile.open("TA11.csv");                //read data
    int xx=0;

    while(getline(infile,data[xx])){

        ++xx;
    }
    for(int i=1;i<xx;++i){
        ndata[i][0]=1;
        double mult=1.0/10.0;
        char ter='1';
        int ite=2;
        while(ter!=','){
            ter=data[i][ite];
            //if(i==1)cout<<ter;
            ndata[i][0]+=mult*(double)(ter-'0');
            ++ite;
            mult=mult/10;
        }
    }
    //cout<<ndata[1][0];
    n=xx;
    //cout<<n<<endl;
    dp[1][0]=mp(0.0000000,0);
    dp[1][1]=mp(0.0000000,1);
    dp[1][2]=mp(0.0000000,1);
    for(int i=2;i<n;++i){
        if(dp[i-1][1].f+(ndata[i][0]-ndata[i-1][0])>dp[i-1][0].f){                      //bought before
            dp[i][1].f=dp[i-1][1].f+(ndata[i][0]-ndata[i-1][0]);
            dp[i][1].s=dp[i-1][1].s;
        }else{
            //if(i<=20)cout<<i<<endl;
            dp[i][1].f=dp[i-1][0].f;
            dp[i][1].s=i;
        }

        if(dp[i-1][1].f+(ndata[i][0]-ndata[i-1][0])-0.00026>dp[i-1][0].f&&dp[i-1][1].f+(ndata[i][0]-ndata[i-1][0])-0.00026>dp[i-1][2].f-(ndata[i][0]-ndata[i-1][0])-0.00026){              //sold now from 1
            dp[i][0].f=dp[i-1][1].f+(ndata[i][0]-ndata[i-1][0])-0.00026;
            dp[i][0].s=i;
            //if(i==2)cout<<ndata[2][0];
        }else if(dp[i-1][0].f>dp[i-1][2].f-(ndata[i][0]-ndata[i-1][0])-0.00026){
            dp[i][0].f=dp[i-1][0].f;
            dp[i][0].s=dp[i-1][0].s;
        }else{
            dp[i][0].f=dp[i-1][2].f-(ndata[i][0]-ndata[i-1][0])-0.00026;
            dp[i][0].s=i;
        }

        if(dp[i-1][2].f-(ndata[i][0]-ndata[i-1][0])>dp[i-1][0].f){                      //state 2
            dp[i][2].f=dp[i-1][2].f-(ndata[i][0]-ndata[i-1][0]);
            dp[i][2].s=dp[i-1][2].s;
        }else{
            //if(i<=20)cout<<i<<endl;
            dp[i][2].f=dp[i-1][0].f;
            dp[i][2].s=i;
        }
    }
    cout<<dp[n-1][0].f<<endl;
    cout<<n<<endl;
    int iter=n-1;
    int akt=-1;
    int il=0;
    int ost=iter;
    while(iter>0){
            //cout<<iter<<" ";
            ++il;
        if(akt==-1){
            ost=dp[iter][0].s;
            //stat[dp[iter][0].s]=-1;
            int sold=dp[iter][0].s;
            akt=1;
            iter=dp[iter][0].s-1;

            int bought=dp[iter][1].s;
            double income = ndata[sold][0]-ndata[bought][0]-0.00026;
            double goal = income*0.0152;
            if(income<=0.0003){

            }                                                                    //Efficiency of given program
            //if(income>=0.0003)smoother(bought,sold,goal);                                                  //Only consider trades with income higher than 3 pips

        }else{
            trans.pb(ost-dp[iter][1].s);
            //stat[dp[iter][1].s]=1;
            akt=-1;
            iter=dp[iter][1].s-1;
        }

    }

    iter=n-1;
    akt=-1;
    il=0;
    ost=iter;
    int obi=1;
    while(iter>0){
            //cout<<iter<<" ";
            ++il;
        if(akt==-1){
            int sold=dp[iter][0].s;
            int bought=dp[dp[iter][0].s-1][1].s;
            int bought1=dp[dp[iter][0].s-1][2].s;
            if(ndata[sold][0]-ndata[bought][0]-0.00026+dp[bought][1].f>-ndata[sold][0]+ndata[bought1][0]-0.00026+dp[bought1][2].f){
                double income = abs(ndata[sold][0]-ndata[bought][0])-0.00026;
                //cout<<income<<endl;;
                whatnow=1;
                //ost=dp[iter][0].s;
                //stat[dp[iter][0].s]=-1;
                if(income<0.0003){
                    stat[dp[iter][0].s]=0;
                }

                //akt=1;
                //iter=dp[iter][0].s-1;
                iter=bought-1;

                if(income<0.0003){
                    stat[bought]=0;
                }
                double goal = income*0.0152;                                                                    //Efficiency of given program
                if(goal>0.000001)smoother(bought,sold,goal,whatnow);
            }else{
                double income = abs(ndata[sold][0]-ndata[bought1][0])-0.00026;
                //cout<<-ndata[sold][0]+ndata[bought1][0]<<endl;;
                whatnow=-1;
                //ost=dp[iter][0].s;
                //stat[dp[iter][0].s]=-1;
                if(income<0.0003){
                    stat[dp[iter][0].s]=0;
                }

                //akt=1;
                //iter=dp[iter][0].s-1;
                iter=bought1-1;

                if(income<0.0003){
                    stat[bought]=0;
                }
                double goal = income*0.0152;                                                                    //Efficiency of given program
                if(goal>0.000001)smoother(bought1,sold,goal,whatnow);

            }
                                                            //Only consider trades with income higher than 3 pips

        }else{
            trans.pb(ost-dp[iter][1].s);
            //stat[dp[iter][1].s]=1;
            akt=-1;
            iter=dp[iter][1].s-1;
        }

    }




    int buysig=0;
    int sellsig=0;
    int bought=0;
    int revBuy=0;
    int revSell=0;
    double boughtfor=0.0000000;
    double prof=0.000000;
    int ntrans=0;
    for(int i=1;i<n-1;++i){
        if(stat[i]==1){
            buysig++;
            if(bought==0){
                bought=1;
                boughtfor=ndata[i][0];
                //cout<<"B: "<<i<<endl;
            }else if(bought==-1){
                prof+=-ndata[i][0]+boughtfor-0.00026;
                //bought=1;
                bought=0;
                ntrans++;
                //boughtfor=ndata[i][0];
            }
        }
        if(stat[i]==-1){
            sellsig++;
            if(bought==1){
                prof+=ndata[i][0]-boughtfor-0.00026;
                bought=0;
                ntrans++;
                //cout<<"S: "<<i<<endl;
            }
        }

        if(stat[i]==2){
            revBuy++;
            if(bought==0){
                bought=-1;
                boughtfor=ndata[i][0];
                //cout<<"B: "<<i<<endl;
            }else if(bought==1){
                prof+=ndata[i][0]-boughtfor-0.00026;
                //bought=1;
                bought=0;
                ntrans++;
                //boughtfor=ndata[i][0];
            }
        }
        if(stat[i]==-2){
            revSell++;
            if(bought==-1){
                prof+=-ndata[i][0]+boughtfor-0.00026;
                bought=0;
                ntrans++;
                //cout<<"S: "<<i<<endl;
            }
        }
    }
    cout<<endl<<"BUY: "<<buysig<<endl;
    cout<<"SELL: "<<sellsig<<endl;
    cout<<endl<<"REV BUY: "<<revBuy<<endl;
    cout<<"REV SELL: "<<revSell<<endl;
    cout<<"PROFIT: "<<prof<<endl;
    cout<<"Transactions: "<<ntrans<<endl;
    sort(selllen.begin(),selllen.end());
    //cout<<"AVG length of sell trend: "<<selllen[selllen.size()/2]<<endl;
    //Smoothing out stat

    cout<<s11<<endl;

    //cout<<il;
    sort(trans.begin(),trans.end());
    //cout<<trans[trans.size()/5];
    data[0].append(",Status");
    outfile.open("TA25.csv");
    //cout<<data[0];
    for(int j=1;j<=60;++j){
        data[0].append(",Price in minute -");
        stringstream ss;
        string sss;

        ss<<j;
        ss>>sss;
        data[0].append(sss);
    }
    //cout<<data[0]<<endl;
    outfile<<data[0]<<endl;
    for(int i=1;i<n;++i){
        //cout<<stat[i]<<endl;
        if(i!=1)data[i].append(",");
        if(i==1)data[i].append("0,");
        if(stat[i]==-1){
            data[i].append("-1");
        }else if(stat[i]==0){
            data[i].append("0");
        }else if(stat[i]==1){
            data[i].append("1");
        }else if(stat[i]==2){
            data[i].append("2");
        }else if(stat[i]==-2){
            data[i].append("-2");
        }
        for(int j=1;j<=60;++j){
            data[i].append(",");
            stringstream ss;
            string sss;

            ss<<ndata[max(1,i-j)][0];
            ss>>sss;
            data[i].append(sss);
        }



        outfile<<data[i]<<endl;
    }
    cout<<data[1]<<endl;
    for(int i=1;i<n;++i){
        //cout<<stat[i]<<endl;

    }
    //cout<<data[2];
    outfile.close();
    infile.close();

    return 0;
}


