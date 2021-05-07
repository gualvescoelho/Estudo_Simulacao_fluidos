#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*
	Gera arquivos de saida necessários para os outros processos, todos de uma vez com intuito de não precisar gerar novamente
	adaptável para checkbutton, com fim de sair so o que o usuário deseja
*/

//------------------------------------------COMEÇO PARTE PROCESSAMENTO
struct _DADOS_ 
{
	int coluna;
	double soma_x, soma_y, soma_z;
	float x, y, z;
	struct _DADOS_ * proxima;
	struct _DADOS_ * anterior;
};
typedef struct _DADOS_ * dados;

struct _DADOS_ *inicio_colunas, *fim_colunas;
void dividir(double x);
void leitura_arquivo(char nome_in[50], int qtd_coord, int itmin, int qtd_linhas);
dados add_dados(int coluna, float x, float y,float z,double soma_x,double soma_y,double soma_z,dados anterior);
dados procurar_coluna(int coluna);
void adc_valor(double valor_x, double valor_y,double valor_z, int coluna);
void exibir_coordenadas();
void exibir_somas();
void limpar_dados();
void arq_saida(int coord, int linhas, int itmin, char nome_in[50]);
void ler_coluna(char nome_in[50],int colunas, int linhas);
//FIM

//------------------------------------------COMECO PARTE LIMPA TEXTO
struct _LETRAS_
{
	char letra;
	struct _LETRAS_ * proxima;
	struct _LETRAS_ * anterior;
};
typedef struct _LETRAS_ *letras;

void ler_caracteres();
letras add_letras(char letra, letras anterior);
letras pular_enderecos(letras aux1, char fechamento, char fechamento_2);
void retirar_letras();
void limpar_dados2(struct _LETRAS_ *lista);

struct _LETRAS_ * inicio_lista_letras, *fim_lista_letra;
struct _LETRAS_ * inicio_limpo, * fim_limpo;

void retira_parenteses(int x); //processo a ser feito apos retirar os probes ou time
//FIM

//------------------------------------------COMECO PARTE CALCULOS
void desvio_padrao(int qtd_colunas, int linhas, int itmin, int escolha, char nome_in[50], char nome_out[50], int l, int desejado); 
double media_ponto(int ponto, int escolha);

double somatorio(int desejado, int escolha, int sub, char nome_in[50],int colunas, int linhas, int itmin); //x = define se é x, y ou z
double somatorio_quadrado(int desejado, int escolha, int sub, char nome_in[50],int colunas, int linhas, int itmin);
double numerador(double soma_juntos, double somatoria_1, double somatoria_2, int sub);
double denominador(double somatoria_1, double somatoria_2, double somatoria_11, double somatoria_22, int sub);
void correlacao(int desejado_1, int desejado_2, int ponto_1, int ponto_2, int sub, char nome_in[50],int colunas, int linhas, int itmin, char nome_out[50]);
double somatorio_juntos(int desejado_1, int desejado_2, int ponto_1, int ponto_2, int sub, char nome_in[50],int colunas, int linhas, int itmin); //x = define se é x, y ou z
//FIM
void menu();

//ajuste interface
void arq_saida_vel_media_x(char nome_out[50]); //parametro passado para verificar se vai ou não ser chamado
void arq_saida_vel_media_y(char nome_out[50]);
void arq_saida_vel_media_z(char nome_out[50]);
void arq_saida_vel_media_todas(char nome_out[50]);
void arq_saida_coordenadas(char nome_out[50]);
void arq_saida_grafico_x();
void arq_saida_grafico_y();
void arq_saida_grafico_z();

//desvio padrao l = 0, desejado define se é x = 1, y = 2 ou z = 3
void arq_saida_desvio_padrao(int qtd_coord, int linhas, int itmin, char nome_in[50], char nome_out_desvio_padrao[50], int l, int desejado);

//correlação ja é a propria função em si, so precisando ser chamada
//void correlacao(int desejado_1, int desejado_2, int ponto_1, int ponto_2, int sub, char nome_in[50],int colunas, int linhas, int itmin);

/*
menu:
 	1- limpar texto - Pode ser um software a parte
 	
 	2- a partir do uso do 2 saber o que vai querer que utilize a memoria ram
uso memoria ram: arquivos de saida (coordenada e velocidades:grafico ou saida apenas)

	3- desvio padrao - nao precisa da memoria ram, tornar a parte
	
	4- serie temporal - software a parte, desde que não utiliza a leitura de dados
	
	5- correlacao - sera um software a parte, nao precisa de memoria ram
*/

void main(int argc, char *argv[])
{
	int qtd_coord, itmin, qtd_linhas, ok_desvio_padrao_x, ok_desvio_padrao_y, ok_desvio_padrao_z;
	
	qtd_coord = atoi(argv[2]);
	itmin = atoi(argv[3]);
	qtd_linhas = atoi(argv[4]);
	ok_desvio_padrao_x = atoi(argv[5]);
	ok_desvio_padrao_y = atoi(argv[6]);
	ok_desvio_padrao_z = atoi(argv[7]);
	
	//calcular sub = qtd_linhas - itmin + 1
	
	leitura_arquivo(argv[1], qtd_coord, itmin, qtd_linhas);
	
	//saida vel obrigatoria, apenas escolher nome
	arq_saida_vel_media_x("vel_media/vel_media_x");
	
	arq_saida_vel_media_y("vel_media/vel_media_y");

	arq_saida_vel_media_z("vel_media/vel_media_z");

	arq_saida_vel_media_todas("vel_media/vel_media_geral");
	
	arq_saida_coordenadas("coordenadas/coordenadas");
		
	arq_saida_grafico_x();

	arq_saida_grafico_y();
	
	arq_saida_grafico_z();
	
	
	//gerar um checkbox semelhante ao do saida graficos
	if(ok_desvio_padrao_x == 1) 
		arq_saida_desvio_padrao(qtd_coord, qtd_linhas, itmin, argv[1], "desvio_padrao_x", 0, 1);
		
	if(ok_desvio_padrao_y == 2)
		arq_saida_desvio_padrao(qtd_coord, qtd_linhas, itmin, argv[1], "desvio_padrao_y", 0, 2);
			
	if(ok_desvio_padrao_z == 3)
		arq_saida_desvio_padrao(qtd_coord, qtd_linhas, itmin, argv[1], "desvio_padrao_z", 0, 3);
	
	/*
	if(ok_correlacao == 1)
		correlacao(desejado_1, desejado_2, ponto_1, ponto_2, sub, nome_in[50], colunas, linhas, itmin, nome_out[50]);
	*/
	
	limpar_dados(inicio_colunas); //fazer limpeza ao final automaticameente
}

void arq_saida_vel_media_x(char nome_out[50]) //parametro passado para verificar se vai ou não ser chamado
{
	struct _DADOS_ *aux;
	aux = inicio_colunas;
	FILE *arq;
	
	arq = fopen(nome_out,"w+b");
	
	fprintf(arq,"Ux\n"); 
	while(aux != NULL)
	{
		fprintf(arq,"%.30lf \n",aux->soma_x);
		aux = aux->proxima;
	}
	fclose(arq);
}

void arq_saida_vel_media_y(char nome_out[50]) //parametro passado para verificar se vai ou não ser chamado
{
	struct _DADOS_ *aux;
	aux = inicio_colunas;
	FILE *arq;
	
	arq = fopen(nome_out,"w+b");
	
	fprintf(arq,"Uy\n"); 
	while(aux != NULL)
	{
		fprintf(arq,"%.30lf \n",aux->soma_y);
		aux = aux->proxima;
	}
	fclose(arq);
}

void arq_saida_vel_media_z(char nome_out[50]) //parametro passado para verificar se vai ou não ser chamado
{
	struct _DADOS_ *aux;
	aux = inicio_colunas;
	FILE *arq;
	
	arq = fopen(nome_out,"w+b");
	
	fprintf(arq,"Uz\n"); 
	while(aux != NULL)
	{
		fprintf(arq,"%.30lf \n",aux->soma_z);
		aux = aux->proxima;
	}
	fclose(arq);
}

void arq_saida_vel_media_todas(char nome_out[50])
{
	struct _DADOS_ *aux;
	aux = inicio_colunas;
	FILE *arq;
	
	arq = fopen(nome_out,"w+b");
	
	fprintf(arq,"Ux\tUy\tUz\t\n"); 
	while(aux != NULL)
	{
		fprintf(arq,"%.30lf\t%.30lf\t%.30lf\n",aux->soma_x,aux->soma_y,aux->soma_z);
		
		aux = aux->proxima;
	}
	fclose(arq);	
}

void arq_saida_grafico_x()
{
	struct _DADOS_ *aux;
	aux = inicio_colunas;
	FILE *arq;
	int contador_y = 0, aux_cont_y = 0;
	
	arq = fopen("vel_media_grafico/geracao_grafico_x","w+b");		
				
	while(aux != NULL)
		{
			fprintf(arq,"/%.30lf",aux->soma_x);
			aux = aux->proxima;
			contador_y++;
		}
		
		fprintf(arq,"/y");
		while(aux_cont_y < contador_y)
		{
			fprintf(arq,"/%d",aux_cont_y);
			aux_cont_y++;	
		}
		
		fclose(arq);
}

void arq_saida_grafico_y()
{
	struct _DADOS_ *aux;
	aux = inicio_colunas;
	FILE *arq;
	int contador_y = 0, aux_cont_y = 0;
	
	arq = fopen("vel_media_grafico/geracao_grafico_y","w+b");		
				
	while(aux != NULL)
		{
			fprintf(arq,"/%.30lf",aux->soma_y);
			aux = aux->proxima;
			contador_y++;
		}
		
		fprintf(arq,"/y");
		while(aux_cont_y < contador_y)
		{
			fprintf(arq,"/%d",aux_cont_y);
			aux_cont_y++;	
		}
		
		fclose(arq);
}

void arq_saida_grafico_z()
{
	struct _DADOS_ *aux;
	aux = inicio_colunas;
	FILE *arq;
	int contador_y = 0, aux_cont_y = 0;
	
	arq = fopen("vel_media_grafico/geracao_grafico_z","w+b");		
				
	while(aux != NULL)
		{
			fprintf(arq,"/%.30lf",aux->soma_z);
			aux = aux->proxima;
			contador_y++;
		}
		
		fprintf(arq,"/y");
		while(aux_cont_y < contador_y)
		{
			fprintf(arq,"/%d",aux_cont_y);
			aux_cont_y++;	
		}
		
		fclose(arq);
}

void arq_saida_coordenadas(char nome_out[50])
{
	struct _DADOS_ *aux;
	aux = inicio_colunas;
	FILE *arq;
	int i = 0;
	
	arq = fopen(nome_out,"w+b");	
	fprintf(arq,"x\ty\tz\t\n"); 
	while(aux != NULL)
	{
		fprintf(arq,"%d\t%f\t%f\t%f \n",i, aux->x, aux->y, aux->z);
		aux = aux->proxima;
		i++;
	}
	fclose(arq);
}

void arq_saida_desvio_padrao(int qtd_coord, int linhas, int itmin, char nome_in[50], char nome_out[50], int l, int desejado)
{
	int escolha;
	
	for(escolha = 0; escolha < qtd_coord; escolha++)
	{
	desvio_padrao(qtd_coord, linhas, itmin, escolha, nome_in, nome_out, l, desejado);
	l++;
	}
}
/*
void correlacao(int desejado_1, int desejado_2, int ponto_1, int ponto_2, int sub, char nome_in[50],int colunas, int linhas, int itmin, char nome_out[50])
{
	double soma_1, soma_11, soma_2, soma_22, soma_juntos, resultado;
	FILE *arq_out;
	
	soma_1 = somatorio(desejado_1, ponto_1, sub, nome_in, colunas, linhas, itmin);
	soma_11 = somatorio_quadrado(desejado_1, ponto_1, sub, nome_in, colunas, linhas, itmin);
	soma_2 = somatorio(desejado_2, ponto_2, sub, nome_in, colunas, linhas, itmin);
	soma_22 = somatorio_quadrado(desejado_2, ponto_2, sub, nome_in, colunas, linhas, itmin);
	
	soma_juntos = somatorio_juntos(desejado_1, desejado_2, ponto_1, ponto_2, sub, nome_in, colunas, linhas, itmin);
	arq_out = fopen(nome_out,"w+b");
	
	resultado = numerador(soma_juntos, soma_1, soma_2, sub) / denominador(soma_1,soma_2,soma_11,soma_22, sub);
	printf("\n RESULTADO: %.30lf \n", resultado);
	fprintf(arq_out,"\tCorrelacao\n%.30lf",resultado);
	fclose(arq_out);
}

double numerador(double soma_juntos, double somatoria_1, double somatoria_2, int sub)
{
	double numerador_final;
								//ler o ponto_1 e o ponto_2 juntos multiplicando eles, e depois de somar eles ja multiplicados multiplicar por sub
	numerador_final = (sub * soma_juntos) - (somatoria_1 * somatoria_2);
	return numerador_final;
}

double denominador(double somatoria_1, double somatoria_2, double somatoria_11, double somatoria_22, int sub)
{
	double denominador_final, parte1, parte2, a, b;
	
	a = sub*(somatoria_11) - (pow(somatoria_1,2));
	b = sub*(somatoria_22) - (pow(somatoria_2,2));
	
	parte1 = sqrt(a);
	parte2 = sqrt(b);
	
	denominador_final = parte1 *  parte2;
	return denominador_final;
}

double somatorio_juntos(int desejado_1, int desejado_2, int ponto_1, int ponto_2, int sub, char nome_in[50],int colunas, int linhas, int itmin) //x = define se é x, y ou z
{ //fazer a operação com eles lidos separadamente!!! corrigir esse erro
	FILE *arq;
	double soma = 0, c_x = 0, c_y = 0, c_z = 0, aux = 0, val_1 = 0, val_2 = 0;
	float tempo = 0, x = 0, y = 0, z = 0;
	int i = 0, qtd_colunas = 0, aux2 = 0;
	
	arq = fopen(nome_in,"r+b");
	
	if(ponto_1 > ponto_2) //garante que o ponto 1 é menor que o 2
	{
		aux2 = ponto_2;
		ponto_2 = ponto_1;
		ponto_1 = aux2;
	}
	
	for(i = 0; i < colunas; i++) //LENDO AS COORDENADAS
	{
	fscanf(arq,"%f %f %f", &x, &y, &z);
	} //para a leitura apos as coordenadas
  	
	for(i = 2; i < linhas + 2; i++) //garante que vai parar quando chegar no final do arquivo e começar a partir do itmin considerado
	{	
	fscanf(arq,"%f",&tempo); //le o tempo inicial
			
		for(qtd_colunas = 0; qtd_colunas < colunas;  qtd_colunas++) //leitura das colunas
		{	
			fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
			
			if(i > itmin)
			{
				if(qtd_colunas == ponto_1) //seleciona o primeiro ponto em questao
				{		
					switch(desejado_1) //seleciona se é x, y ou z
					{
						case 1:
							val_1 = c_x;
						break;
						
						case 2:
							val_1 = c_y;
						break;
						
						case 3:
							val_1 = c_z;
						break;
					}
				}	
				
				if(qtd_colunas == ponto_2)
				{		
					switch(desejado_2)
					{
						case 1:
							val_2 = c_x;
						break;
						
						case 2:
							val_2 = c_y;
						break;
						
						case 3:
							val_2 = c_z;
						break;
					}	
					
					soma = soma + (val_1 * val_2);			
				}	
			}
		}
	}	
	
	return soma;
}

double somatorio_quadrado(int desejado, int escolha, int sub, char nome_in[50],int colunas, int linhas, int itmin) //x = define se é x, y ou z
{
	FILE *arq;
	double soma = 0, media = 0, c_x = 0, c_y = 0, c_z = 0, aux = 0;
	float tempo = 0, x = 0, y = 0, z = 0;
	int i = 0, qtd_colunas = 0;
	
	arq = fopen(nome_in,"r+b");
	
	for(i = 0; i < colunas; i++) //LENDO AS COORDENADAS
	{
	fscanf(arq,"%f %f %f", &x, &y, &z);
	}
	
	switch(desejado)
	{
		case 1: //x
			
			for(i = 2; i < linhas + 2; i++) //le as linhas com os valores
			{
			fscanf(arq,"%f",&tempo); //le o tempo inicial			
			
				for(qtd_colunas = 0; qtd_colunas < colunas;  qtd_colunas++) //leitura das colunas
				{	
					if(i > itmin) //pular endereços indesejados
					{
						fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
						
						if(qtd_colunas == escolha) //entrega a coluna desejada
						{	
							aux = c_x * c_x;
							soma = soma + aux;
						}
						
					}else
					{
						fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
					}		
				}
			}			
		break; 
		
		case 2: //y
			
			for(i = 2; i < linhas + 2; i++) //le as linhas com os valores
			{
			fscanf(arq,"%f",&tempo); //le o tempo inicial
			
			
				for(qtd_colunas = 0; qtd_colunas < colunas;  qtd_colunas++) //leitura das colunas
				{	
					if(i > itmin) //pular endereços indesejados
					{
						fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
						
						if(qtd_colunas == escolha) //entrega a coluna desejada
						{	
							aux = c_y * c_y;
							soma = soma + aux;
						}
						
					}else
					{
						fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
					}		
				}
			}
		break;
		
		case 3: //z
			
			for(i = 2; i < linhas + 2; i++) //le as linhas com os valores
			{
			fscanf(arq,"%f",&tempo); //le o tempo inicial
			
			
				for(qtd_colunas = 0; qtd_colunas < colunas;  qtd_colunas++) //leitura das colunas
				{	
					if(i > itmin) //pular endereços indesejados
					{
						fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
						
						if(qtd_colunas == escolha) //entrega a coluna desejada
						{	
							aux = c_z * c_z;
							soma = soma + aux;
						}
						
					}else
					{
						fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
					}		
				}
			}
		break;
	}	
	
	return soma;
}

double somatorio(int desejado, int escolha, int sub, char nome_in[50],int colunas, int linhas, int itmin) //x = define se é x, y ou z
{
	FILE *arq;
	double soma = 0, media = 0, c_x = 0, c_y = 0, c_z = 0, aux = 0;
	float tempo = 0, x = 0, y = 0, z = 0;
	int i = 0, qtd_colunas = 0;
	
	arq = fopen(nome_in,"r+b");
	
	for(i = 0; i < colunas; i++) //LENDO AS COORDENADAS
	{
	fscanf(arq,"%f %f %f", &x, &y, &z);
	}
	
	switch(desejado)
	{
		case 1: //x
			
			for(i = 2; i < linhas + 2; i++) //le as linhas com os valores
			{
			fscanf(arq,"%f",&tempo); //le o tempo inicial			
			
				for(qtd_colunas = 0; qtd_colunas < colunas;  qtd_colunas++) //leitura das colunas
				{	
					if(i > itmin) //pular endereços indesejados
					{
						fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
						
						if(qtd_colunas == escolha) //entrega a coluna desejada
						{	
							soma = soma + c_x;
						}
						
					}else
					{
						fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
					}		
				}
			}			
		break; 
		
		case 2: //y
			
			for(i = 2; i < linhas + 2; i++) //le as linhas com os valores
			{
			fscanf(arq,"%f",&tempo); //le o tempo inicial
			
			
				for(qtd_colunas = 0; qtd_colunas < colunas;  qtd_colunas++) //leitura das colunas
				{	
					if(i > itmin) //pular endereços indesejados
					{
						fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
						
						if(qtd_colunas == escolha) //entrega a coluna desejada
						{	
							soma = soma + c_y;
						}
						
					}else
					{
						fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
					}		
				}
			}
		break;
		
		case 3: //z
			
			for(i = 2; i < linhas + 2; i++) //le as linhas com os valores
			{
			fscanf(arq,"%f",&tempo); //le o tempo inicial
			
			
				for(qtd_colunas = 0; qtd_colunas < colunas;  qtd_colunas++) //leitura das colunas
				{	
					if(i > itmin) //pular endereços indesejados
					{
						fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
						
						if(qtd_colunas == escolha) //entrega a coluna desejada
						{	
							soma = soma + c_z;
						}
						
					}else
					{
						fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
					}		
				}
			}
		break;
	}	
	
	return soma;
}
*/
void ler_coluna(char nome_in[50], int colunas, int linhas)
{
	int i = 0, coluna_desejada = 0, qtd_colunas = 0;
	FILE *arq, *arq_out;
	float x,y,z,tempo;
	double c_x, c_z, c_y;	
	char nome_out[50];
	
	arq = fopen(nome_in,"r+b");
	
	for( i = 0; i < colunas; i++) //passando quantas coordenadas tem
	{
	fscanf(arq,"%f %f %f", &x, &y, &z);
	printf("%d.\t%f\t%f\t%f \n",i, x, y, z);
	}
	
	/*printf("\n Escolha, pelo numero, de qual ponto deseja a serie: ");
	scanf("%d",&coluna_desejada);
	
	printf("\n Escolha o nome de saida para essa serie temporal: ");
	scanf("%s",nome_out);*/
	
	arq_out = fopen(nome_out,"w+b");
	
	fprintf(arq_out,"Time\tUx\tUy\tUz\n"); 
	for(i = 0; i < linhas; i++) //le as linhas com os valores
	{
	fscanf(arq,"%f",&tempo); //le o tempo inicial

	fprintf(arq_out,"%f\t",tempo);	
	
		for(qtd_colunas = 0; qtd_colunas < colunas;  qtd_colunas++) //leitura das colunas
		{	
			fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
			
			if(qtd_colunas == coluna_desejada)
			{		
				fprintf(arq_out,"%.30lf\t%.30lf\t%.30lf \n",c_x, c_y, c_z);
			}		
		}
	}
	
	fclose(arq);
	fclose(arq_out);
}

void desvio_padrao(int colunas, int linhas, int itmin, int escolha, char nome_in[50], char nome_out[50], int l, int desejado)
{
	FILE *arq_out, *arq;
	double soma = 0, media = 0, c_x = 0, c_y = 0, c_z = 0, aux = 0;
	float sub = 0, tempo = 0, x = 0, y = 0, z = 0;
	int i = 0, qtd_colunas = 0;
	
	sub = linhas - itmin + 1; //n no desvio padrão	
	
	arq = fopen(nome_in,"r+b");
	arq_out = fopen(nome_out,"a+b");
	
	if(l == 0)
	fprintf(arq_out,"Pontos\tDesvios\n");
	
	media = media_ponto(escolha,desejado);
	
	for(i = 0; i < colunas; i++) //LENDO AS COORDENADAS
	{
	fscanf(arq,"%f %f %f", &x, &y, &z);
	}
	
	switch(desejado)
	{
		case 1: //x
			
			for(i = 2; i < linhas + 2; i++) //le as linhas com os valores
			{
			fscanf(arq,"%f",&tempo); //le o tempo inicial			
			
				for(qtd_colunas = 0; qtd_colunas < colunas;  qtd_colunas++) //leitura das colunas
				{	
					if(i > itmin) //pular endereços indesejados
					{
						fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
						
						if(qtd_colunas == escolha) //entrega a coluna desejada
						{	
							aux = c_x - media;
							soma = soma + pow(aux, 2);
						}
						
					}else
					{
						fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
					}		
				}
			}			
		break; 
		
		case 2: //y
			
			for(i = 2; i < linhas + 2; i++) //le as linhas com os valores
			{
			fscanf(arq,"%f",&tempo); //le o tempo inicial
			
			
				for(qtd_colunas = 0; qtd_colunas < colunas;  qtd_colunas++) //leitura das colunas
				{	
					if(i > itmin) //pular endereços indesejados
					{
						fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
						
						if(qtd_colunas == escolha) //entrega a coluna desejada
						{	
							aux = c_y - media;
							soma = soma + pow(aux, 2);
						}
						
					}else
					{
						fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
					}		
				}
			}
		break;
		
		case 3: //z
			
			for(i = 2; i < linhas + 2; i++) //le as linhas com os valores
			{
			fscanf(arq,"%f",&tempo); //le o tempo inicial
			
			
				for(qtd_colunas = 0; qtd_colunas < colunas;  qtd_colunas++) //leitura das colunas
				{	
					if(i > itmin) //pular endereços indesejados
					{
						fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
						
						if(qtd_colunas == escolha) //entrega a coluna desejada
						{	
							aux = c_z - media;
							soma = soma + pow(aux, 2);
						}
						
					}else
					{
						fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
					}		
				}
			}
		break;
	}
	
	soma = sqrt(soma / sub);
	
	fprintf(arq_out,"%d\t",escolha);
	fprintf(arq_out,"%.30lf\n",soma);
	
	fclose(arq);
	fclose(arq_out);
}

double media_ponto(int ponto, int decisao)
{
	struct _DADOS_ *aux;
	double resultado;
	
	aux = procurar_coluna(ponto);
	
	switch(decisao)
	{
		case 1:			
			resultado = aux->soma_x;
		break;
		
		case 2:
			resultado = aux->soma_y;
		break;
		
		case 3:
			resultado = aux->soma_z;
		break;
	}
	
	return resultado;
}


void leitura_arquivo(char nome_in[50], int qtd_coord, int itmin, int qtd_linhas) 
{
	FILE *arq;
	float x, y, z, tempo;
	int i, qtd_colunas, j = 0, inicio;
	double c_x, c_z, c_y, sub;
	struct _DADOS_ *aux;
	char teste = 'c';
	
	arq = fopen(nome_in,"r+b");
	
	inicio = ftell(arq);
	fread(&teste,8,1,arq);
	
	if(teste == '#')
	{
		printf("\nTEXTO SUJO, LIMPE O TEXTO!!\n");	
		system("pause");	
	}else
	{
	
		fseek(arq,inicio,SEEK_SET);
		
		while(!arq)
		{
			printf("\nArquivo vazio, tente novamente: ");
			
			printf("\nInforme o nome do arquivo a ser lido: ");
			scanf("%s",nome_in);
			arq = fopen(nome_in,"r+b");
		}
			
		for( i = 0; i < qtd_coord; i++) //passando quantas coordenadas tem
		{
		fscanf(arq,"%f %f %f", &x, &y, &z);
		
			if(j != 0)
			{
				aux->proxima = add_dados(i,x,y,z,0,0,0,aux); //adicionando as coordenadas na lista
				aux = aux->proxima;
			}else
			{
				inicio_colunas = add_dados(i,x,y,z,0,0,0,NULL); //criando lista inicial
				aux = inicio_colunas;
				j++;
			}
		}
		
		for(i = 2; i < qtd_linhas + 2; i++) //le as linhas com os valores
		{
			fscanf(arq,"%f",&tempo); //le o tempo inicial
			printf("Timestep: %f %c", tempo,13); //exibicao do tempo durante o processo
			
			for(qtd_colunas = 0; qtd_colunas < qtd_coord;  qtd_colunas++) //leitura das colunas
			{	
				if(i > itmin)
				{
					fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
					adc_valor(c_x,c_y,c_z,qtd_colunas);				
				}
				else
				{				
					fscanf(arq,"%lf %lf %lf",&c_x, &c_y, &c_z);	
				}
				
			}
		}
		fclose(arq);
		
		fim_colunas = aux;
		
		sub = (qtd_linhas - itmin + 1);
	
		dividir(sub);
	}
	
	system("cls || clear");
}

void dividir(double x)
{
	struct _DADOS_ *aux;
	
	aux = inicio_colunas;
	
	while(aux != NULL)
	{
		aux->soma_x = aux->soma_x / x;
		aux->soma_y = aux->soma_y / x;
		aux->soma_z = aux->soma_z / x;	
		
		aux = aux->proxima;
	}
}

void adc_valor(double valor_x, double valor_y,double valor_z, int coluna) //funcao responsavel por realizar a soma dos valores
{
	struct _DADOS_ *aux;
	aux = inicio_colunas;
	
	aux = procurar_coluna(coluna);
	aux->soma_x += valor_x;
	aux->soma_y += valor_y;
	aux->soma_z += valor_z;
}

dados procurar_coluna(int coluna) //responsavel por direcionar para a coluna certa
{
	struct _DADOS_ *aux;
	aux = inicio_colunas;
	
	while(aux->coluna != coluna)
	{
		aux = aux->proxima;
	}
	
	return aux;
}

void limpar_dados(struct _DADOS_ *colunas)
{
	struct _DADOS_ *atual, *prox;
	
	if(colunas == NULL)
	{
		return;
	}
	
	atual = colunas->proxima;
	
	while(atual != NULL)
	{
		prox = atual->proxima;
		free(atual);
		atual = prox;
	}
}

dados add_dados(int coluna, float x, float y,float z,double soma_x,double soma_y,double soma_z,dados anterior)
{
	dados M = malloc(sizeof(struct _DADOS_));
	M->coluna = coluna;
	M->x = x;
	M->y = y;
	M->z = z;
	M->soma_x = soma_x;
	M->soma_y = soma_y;
	M->soma_z = soma_z;
	M->proxima = NULL;
	M->anterior = anterior;
	
	return M;
}
//FIM

