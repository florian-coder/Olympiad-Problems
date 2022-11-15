#include <iostream>
#include <fstream>
#include<vector>
#include<algorithm>
#define maxn 5001
#define maxg 10001
 
using namespace std;
ifstream in("rucsac.in");
ofstream out("rucsac.out");
int W[maxn], P[maxn];
int Optim[maxg];
 
int main() {
	
	
	int N, G;
	in>>N>>G;
	
	for (int i = 1; i <= N; ++i) {
		in>>W[i]>>P[i];
	}
	
	Optim[0] = 0;
	int sol = 0;
	
	for( int i = 1; i <= N; ++i)
		for( int j = G - W[i]; j >= 0; --j) {
			if( Optim[j+W[i]] < Optim[j] + P[i] )
			{
				Optim[j+W[i]] = Optim[j] + P[i];
				if( Optim[j+W[i]] > sol)
					sol = Optim[j+W[i]];
			}
		}
	out<<sol<<"\n";
	return 0;
}