#include <iostream>
#include <windows.h>
#include <bits/stdc++.h>

using namespace std;

char sym[3];
string a="https://stooq.pl/q/d/l/?s=";
string b="&i=d";
string res;
string line;
int i=0;
int main()
{
    ifstream myfile ("symbols.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
          //cout << line << '\n';
            sym[0]=line[0];
            sym[1]=line[1];
            sym[2]=line[2];
          //cout<<sym<<endl;
            res=a+sym+b;
            ++i;
            if(i>=709){
                //cout<<res;
          //cout<<res<<endl;
            LPSTR s = const_cast<char *>(res.c_str());
            ShellExecute(NULL, "open", s,NULL, NULL, SW_SHOWNORMAL);
            }
        }
        myfile.close();
  }






    return 0;
}
