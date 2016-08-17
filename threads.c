#include <pthread.h>
#include <stdio.h>

int sum = -1;

void *runner(void *param);

int main(int argc, char *argv[])
{
	pthread_t tid;
	pthread_attr_t attr;
	
	if(argc != 2)
	{
		fprintf(stderr, "usage: a.out <integer value>\n");
		return -1;
	}
	if(atoi(argv[1]) < 0)
	{
		fprintf(stderr, "%d must be >=0\n", atoi(argv[1]));
		return -1;
	}
	
	if(pthread_attr_init(&attr) != 0)//inicializa o objeto que contém os atributos da thread com default
	{
		fprintf(stderr, "Erro ao iniciar os atributos da thread para o sistema\n", atoi(argv[1]));
		return -1;
	}
	
	if(pthread_create(&tid, &attr, runner, argv[1]) != 0)//cria uma nova thread, com ID armazenado em TID.
	{
		fprintf(stderr, "Erro ao criar a thread\n", atoi(argv[1]));
		return -1;
	}
	
	/*if(pthread_join(tid, NULL) != 0)//espere a thread com o ID tid terminar de executar
	{
		fprintf(stderr, "Erro ao executar pthread_join()\n", atoi(argv[1]));
		return -1;
	}*/
	
	printf("sum = %d\n", sum);
	
	printf("sum = %d\n", sum);
	
	if(pthread_attr_destroy(&attr) != 0)//destrua os parametros padrões da thread criados
	{
		fprintf(stderr, "Erro ao destruir os parametros da thread para o sistema\n", atoi(argv[1]));
		return -1;
	}
}

void *runner(void *param)
{
	int i, upper = atoi(param);
	sum = 0;
	
	for(i = 1;i <= upper;i++)
		sum += i;
		
	pthread_exit(0);//termine o processo da thread com status 0
}
