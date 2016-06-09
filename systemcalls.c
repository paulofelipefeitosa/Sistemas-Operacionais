#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_SIZE 100

#define STREAM_STDERRO 2
#define STREAM_STDOUT 1
#define STREAM_STDIN 0

int main()
{
	char input_file[MAX_SIZE], output_file[MAX_SIZE], buffer[MAX_SIZE];

	char msg_erro[] = "Erro ao abrir o arquivo ";
	char msg_suce[] = "Sucesso ao abrir o arquivo ";
	char msg_read_erro[] = "Erro ao ler o arquivo ";
	char msg_input[] = "Informe o nome do arquivo ";
	char in[] = "de entrada";
	char out[] = "de saida";
	char erro_stdin[] = "Erro ao ler o nome do arquivo\n";
	char suce_stdin[] = "Sucesso ao ler o nome do arquivo\nNome do arquivo: ";
	char copy[] = "Memoria copiada: ";
	char msg_end[] = "Operacoes concluidas com sucesso\n";

	int file_size_bytes = 0, retorno, input_file_size, output_file_size;
	
	///LER O NOME DO ARQUIVO DE ENTRADA
	
	write(STREAM_STDOUT, msg_input, sizeof(msg_input));
	write(STREAM_STDOUT, in, sizeof(in));
	write(STREAM_STDOUT, ": ", 2);
	
	input_file_size = read(STREAM_STDIN, input_file, sizeof(input_file));
		
	if(input_file_size <= 0)
	{
		write(STREAM_STDERRO, erro_stdin, sizeof(erro_stdin));
		return 1;
	}
	else
	{
		input_file[input_file_size - 1] = '\0'; //fim da string
		write(STREAM_STDOUT, suce_stdin, sizeof(suce_stdin));
		write(STREAM_STDOUT, input_file, input_file_size);
		write(STREAM_STDOUT, "\n", 1);
	}
	
	///LER O NOME DO ARQUIVO DE SAÍDA
	
	write(STREAM_STDOUT, msg_input, sizeof(msg_input));
	write(STREAM_STDOUT, out, sizeof(out));
	write(STREAM_STDOUT, ": ", 2);
	
	output_file_size = read(STREAM_STDIN, output_file, sizeof(output_file));
	
	if(output_file_size <= 0)
	{
		write(STREAM_STDERRO, erro_stdin, sizeof(erro_stdin));
		return 1;
	}
	else
	{
		output_file[output_file_size - 1] = '\0'; //fim da string
		write(STREAM_STDOUT, suce_stdin, sizeof(suce_stdin));
		write(STREAM_STDOUT, output_file, output_file_size);
		write(STREAM_STDOUT, "\n", 1);
	}
	
	///ABRIR O ARQUIVO DE ENTRADA
	
	int file = open(input_file, O_RDONLY);//READ ONLY
	
	if(file < 0)
	{
		write(STREAM_STDERRO, msg_erro, sizeof(msg_erro));
		write(STREAM_STDOUT, in, sizeof(in));
		write(STREAM_STDOUT, "\n", 1);
		return 1;
	}
	else
	{
		write(STREAM_STDOUT, msg_suce, sizeof(msg_suce));
		write(STREAM_STDOUT, in, sizeof(in));
		write(STREAM_STDOUT, "\n", 1);
	}
		
	///CRIAR O ARQUIVO DE SAIDA
		
	int file_copy = open(output_file, O_WRONLY | O_CREAT | O_EXCL | O_APPEND, S_IRWXU);//CRIE O ARQUIVO E SE O PATHNAME JÁ EXISTE, RETORNE ERRO.
	
	if(file_copy < 0)
	{
		write(STREAM_STDERRO, msg_erro, sizeof(msg_erro));
		write(STREAM_STDOUT, out, sizeof(out));
		write(STREAM_STDOUT, "\n", 1);
		return 1;
	}
	else
	{
		write(STREAM_STDOUT, msg_suce, sizeof(msg_suce));
		write(STREAM_STDOUT, out, sizeof(out));
		write(STREAM_STDOUT, "\n", 1);
	}
	
	///LEITURA E ESCRITA NO ARQUIVO
	
	do
	{
		retorno = read(file, buffer, sizeof(buffer));
		if(retorno < 0)
		{
			write(STREAM_STDERRO, msg_read_erro, sizeof(msg_read_erro));
			return 1;
		}
		else if(retorno > 0)
		{
			write(file_copy, buffer, retorno);
			write(STREAM_STDOUT, copy, sizeof(copy));
			write(STREAM_STDOUT, buffer, retorno);
		}
	}while(retorno > 0);
	
	close(file);
	close(file_copy);
	
	write(STREAM_STDOUT, msg_end, sizeof(msg_end));
	
	return 0;
}
