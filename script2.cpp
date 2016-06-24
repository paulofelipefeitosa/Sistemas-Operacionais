#include <bits/stdc++.h>
using namespace std;
char lookingfor[][20] = {{"schedule("}, {"preempt_schedule("}, {"effective_prio("}, {"recalc_task_prio("}, {"activate_task("}, {"sleep_on_timeout("}, {"sleep_on("}};
char str[200], comando[500];
string strcpp;
set<string> adresses;
int main()
{
	FILE *arq_in1, *arq_in2, *arq_out;
	
	arq_in1 = fopen("out.txt", "r");
	if(arq_in1 == NULL)
		return 1;
		
	arq_in2 = fopen("sch_out.txt", "r");
	if(arq_in2 == NULL)
	{
		fclose(arq_in1);
		return 1;
	}
	
	arq_out = fopen("saida.txt", "w");
	if(arq_out == NULL)
	{
		fclose(arq_in1);
		fclose(arq_in2);
		return 1;
	}
	
	while(fscanf(arq_in1, "%[^\n]s", str)!=EOF)
	{
		fgetc(arq_in1);
		strcpp = str;
		adresses.insert(strcpp);
	}
	while(fscanf(arq_in2, "%[^\n]s", str)!=EOF)
	{
		fgetc(arq_in2);
		strcpp = str;
		adresses.insert(strcpp);
	}
	
	for(int i=0;i<7;i++)
		printf("grep -c '%s'\n", lookingfor[i]);
	
	for(set<string>::iterator it = adresses.begin();it != adresses.end();it++)
	{
		strcpy(str, (*it).c_str());
		for(int i=0;i<7;i++)
		{
			sprintf(comando, "grep -n '%s' %s >> out.out\n", lookingfor[i], str);
			system(comando);
		}
	}
	
	fclose(arq_in1);
	fclose(arq_in2);
	fclose(arq_out);
	return 0;
}
