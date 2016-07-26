#include <bits/stdc++.h>
using namespace std;
int main()
{
	char str[5005];
	string strcpp;
	stringstream ss;
	FILE *psaux, *pids;
	int c_line = 0, c_col = 0;
	
	system("ps aux > out");
	
	psaux = fopen("out", "r");
	if(psaux == NULL)
	{
		puts("Erro ao abrir o arquivo de entrada");
		return 1;
	}
	
	pids = fopen("pids", "w");
	if(pids == NULL)
	{
		puts("Erro ao abrir o arquivo de saida");
		return 2;
	}
	
	while(fscanf(psaux, "%[^\n]s", str)!=EOF)
	{
		fgetc(psaux);
		strcpp = str;
		ss << strcpp;
		while(ss >> strcpp)
		{
			if(c_line && c_col == 1)
				fprintf(pids, "%s\n", strcpp.c_str());
			c_col++;
		}
		c_line++;
		c_col = 0;
		ss.clear();
	}
	return 0;
}
