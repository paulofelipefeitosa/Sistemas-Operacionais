#include <bits/stdc++.h>
using namespace std;
int main()
{
	char names[4000][200];
	char str[200], c;
	int pt = 0, tam;
	FILE *arq_in, *arq_out;
	arq_in = fopen("grep_out.txt", "r+w");
	arq_out = fopen("sch_out.txt", "w");
	if(arq_in != NULL && arq_out != NULL)
	{
		while(fscanf(arq_in, "%[^\n]s", str) != EOF)
		{
			fgetc(arq_in);
			printf("%s\n", str);
			tam = strlen(str);
			if(str[tam-1] == 'c')
				memcpy(names[pt++], str, tam);
		}
		for(int i=0;i<pt;i++)
			fprintf(arq_out, "%s\n", names[i]);
		fclose(arq_in);
		fclose(arq_out);
	}
	return 0;
}
