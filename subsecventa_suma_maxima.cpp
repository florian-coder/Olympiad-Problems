#include <iostream>
#include <fstream>

#define dim  6000005
using namespace std;

ifstream in("ssm.in");
ofstream out("ssm.out");
int org[dim], copys[dim];

int main()
{
    int n,i,j;
    in>>n;
    for(i=0;i<n;i++)
    {
        in>>org[i];
    }
    int maxi=org[0],save = 0,finish = 0;
    copys[0] = maxi;
    for(j=1;j<n;j++)
    {
        if(copys[j-1]+org[j]>org[j])
            copys[j]=copys[j-1]+org[j];
        else 
        {
            copys[j]=org[j];
            // save=j+1;
        }
        //cout<<copys[j]<<" ";
        if(maxi<copys[j])
        {
            maxi=copys[j];
            finish=j;
        }
    }

    int s = org[finish];
    int idx = finish;
    while(s != maxi) {
        idx--;
        s += org[idx];
    }

    /*for(i=finish;i>=0;i--)
    {
        save = copys[i]-copys[i-1];
        copys[i-1]=save;
        if(save==0)
            save=i-1;
    }*/
    

    out<<maxi<<" "<<idx+1<<" "<<finish+1<<endl;
    return 0;
}