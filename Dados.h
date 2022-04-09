#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct{
	int codigo_venda;
	int codigo_item;
	int quantidade_venda;
	float valor_total_venda;
	char data_venda[10];
	char nome_venda[30];
}Venda;

typedef struct{
	char nome_produto[20];
	int codigo_item;
	float valor_compra;
	float valor_venda;
	int quantidade;
	char data_compra[10];
	char data_validade[10];
}Produto;

int menu(int op, int pos_produtos, int pos_vendas, FILE *, FILE*);
int atualiza_posicao_produtos(FILE *);
int atualiza_posicao_vendas(FILE *);
void cadastrar_produto(int *, FILE *);
void listar_produtos(FILE *);
void excluir_produto(FILE *);
void consultar_produto(FILE *);
void editar_produto(FILE *);
void dados();
void listar_vendas(FILE *);
void realizar_vendas(FILE *, FILE *, int *);
void consultar_venda(FILE *);
