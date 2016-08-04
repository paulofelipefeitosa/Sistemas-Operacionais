#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

struct EDGE
{
	int v1, v2, w;
};

int main()
{
	int segment_id;
	
	struct EDGE* struct_sh_mem;
	
	char* shared_memory;

	const int segment_size = 4096;
	
	//shmget(key, size, shmflg)
	segment_id = shmget(IPC_PRIVATE, segment_size*sizeof(struct EDGE), S_IRUSR | S_IWUSR);//criar o segmento de memória e receber o ID do segmento, além disso ele seta as permissões dentro do segmento
	
	//shmat(shmid, shmaddr, shmflg) -> //se shmaddr == NULL ele vai para primeira posição no espaço de memoria disponivel // ftok() ->  dá uma key única para o segment_id // shmflg só é usado se shmaddr não é NULL.
	struct_sh_mem = (struct EDGE *) shmat(segment_id, NULL, 0);//"anexar o segmento a esse processo"
	printf("shared memory segment %d attached at address %p\n", segment_id, struct_sh_mem);
	
	int i;
	
	for(i = 0;i < segment_size;i++)
		struct_sh_mem[i].v1 = 1,  struct_sh_mem[i].v2 = 2, struct_sh_mem[i].w = 3;
		
	for(i = 0;i < segment_size;i++)
		printf("%d %d %d\n", struct_sh_mem[i].v1, struct_sh_mem[i].v2, struct_sh_mem[i].w);

	//sprintf(shared_memory, "Hi there!");

	//printf("*%s*\n", shared_memory);
	
	
	//shmdt(shmaddr) -> shared memory desattachment
	if ( shmdt(struct_sh_mem) == -1) {//desanexar o segmento a esse processo
		fprintf(stderr, "Unable to detach\n");
	}

	//shmctl( , COMANDO, Ponteiro para a estrutura)    -> Destruir o segmento de memória
	shmctl(segment_id, IPC_RMID, NULL); //A função semctl() é utilizada para examinar e modificar as informações relativas ao segmento de memória compartilhada. De maneira intuitiva, ela permite ao usuário de receber informações relativas ao segmento, de setar o proprietário ou grupo, de especificar as permissões de acesso, e finalmente, de destruir o segmento. 

	return 0;
}

