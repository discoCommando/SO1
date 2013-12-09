#include<vector>
#include<cstdio>
#include<set>
#include<list>
#include<bitset>
#include<map>

using namespace std;
const static int MAKS = 500001;
const static long long MAKSWARTOSC = 1000000002;

static int n, m;
bitset<MAKS> R, L;
const static int w[MAKS];
map<pair<int, int>, int> wagiKrawedzi;

struct wezel
{
	list<int> sasiedzi; // para wierzcholek, waga 
};
const static wezel wezly[MAKS];

void init(int zrodlo)
{
	for(int i = 0; i < n; i++)
	{
		R[i] = 1;
		w[i] = MAKSWARTOSC;
	}
	R[zrodlo] = 0;
	
	for(int v: wezly[zrodlo].sasiedzi)
	{
		w[v] = wagiKrawedzi. (make_pair(zrodlo, v))
	}
	
}

void wczytajDane()
{
	n = m = 0;
	scanf("%i %i", n, m);
	
	init(0);
	
	int skad, dokad, waga;
	for(int i = 0; i < m; i++)
	{
		skad = dokad = waga = 0;
		scanf("%lli %lli %lli", &skad, &dokad, &waga);
		
	}
}


int main()
{
	wczytajDane();
}