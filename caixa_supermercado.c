#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "Dados.h"

int main(){

	setlocale(LC_ALL,"Portuguese");
	Produto produto;
	Venda venda;
	FILE *pro, *vendas;
	int op;
	int pos_produtos, pos_vendas;
	
	if((pro = fopen("arquivo_produtos.bin","r+b")) == NULL){
		pro = fopen("arquivo_produtos.bin","w+b");
	}
	
	if(pro==NULL){
		printf("Erro na abertura do arquivo produto!!\n");
	}
	
	if((vendas = fopen("arquivo_vendas.bin","r+b"))== NULL){
		vendas = fopen("arquivo_vendas.bin","w+b");
	}
	
	if(vendas==NULL){
		printf("Erro na abertura do arquivo venda!!\n");
	}

	pos_produtos = atualiza_posicao_produtos(pro);
	pos_vendas = atualiza_posicao_vendas(vendas);
	
	menu(op,pos_produtos,pos_vendas,pro,vendas);

	fclose(pro);
	fclose(vendas);

	return 0;
}

int menu(int op, int pos_produtos, int pos_vendas, FILE *pro, FILE *vendas){
	
	//int *pcont;
	
	do{
		printf("\t----Supermercado----\n\n");
		printf("[1]-Cadastrar produto\n");
		printf("[2]-Listar produtos\n");
		printf("[3]-Consultar produto\n");
		printf("[4]-Editar produto\n");
		printf("[5]-Excluir produto\n");
		printf("[6]-Realizar venda\n");
		printf("[7]-Listar vendas\n");
		printf("[8]-Consultar venda\n");
		printf("[9]-Créditos do sistema\n");
		printf("[10]-Sair\n");
		scanf("%d", &op);
		
		system("cls");
		
		switch(op){
			case 1:
				cadastrar_produto(&pos_produtos, pro);
			break;
			case 2:
				listar_produtos(pro);
			break;
			case 3:
				consultar_produto(pro);
			break;
			case 4:
				editar_produto(pro);
			break;
			case 5:
				excluir_produto(pro);
			break;
			case 6:
				realizar_vendas(vendas,pro,&pos_vendas);
			break;
			case 7:
				listar_vendas(vendas);
			break;
			case 8:
				consultar_venda(vendas);
			break;
			case 9:
				dados();
			break;
			case 10:
				printf("\n");
				printf("\t...Saindo do sistema...\n");
			break;
		}
		
	}while(op<=9);
	
	return op, pos_produtos, pos_vendas;
}

int atualiza_posicao_produtos(FILE *pro){
	 
	Produto produto;
	int posicao = 0;
	
	do{
		fread(&produto,sizeof(Produto),1,pro);
		if(feof(pro)){
			break;
		}
		posicao++;
	}while(!feof(pro));
	rewind(pro);
	
	return posicao;
}

int atualiza_posicao_vendas(FILE *vendas){
	 
	Venda venda;
	int posicao_registro = 0;
	
	do{
		fread(&venda,sizeof(Venda),1,vendas);
		if(feof(vendas)){
			break;
		}
		posicao_registro++;
	}while(!feof(vendas));
	rewind(vendas);
	
	return posicao_registro;
}

void cadastrar_produto(int *pos_ult, FILE *pro){
	
	Produto produto;
	produto.codigo_item = (*pos_ult)+1;
	
	printf("Código do produto: %d\n", produto.codigo_item);
	
	printf("Digite o nome do produto:\n");
	scanf(" %[^\n]", produto.nome_produto);
	
	printf("Digite a quantidade:\n");
	scanf("%d", &produto.quantidade);
	setbuf(stdin, NULL);
	
	printf("Digite o valor da compra:\n");
	scanf("%f", &produto.valor_compra);
	setbuf(stdin, NULL);
	
	printf("Digite o valor da venda:\n");
	scanf("%f", &produto.valor_venda);
	setbuf(stdin, NULL);
	
	printf("Digite a data da compra:\n");
	scanf(" %[^\n]", produto.data_compra);
	setbuf(stdin, NULL);
	
	printf("Digite a data de validade do produto:\n");
	scanf(" %[^\n]", produto.data_validade);
	setbuf(stdin, NULL);
	
	fwrite(&produto,sizeof(Produto),1,pro);
	(*pos_ult)++;
	
	system("cls");
}

void listar_produtos(FILE *pro){
	
	Produto produto;
	rewind(pro);
	int posicao = 0;
	
	printf("----Dados dos produtos:----\n\n");
	
	do{
		fread(&produto,sizeof(Produto),1,pro);
		if(feof(pro)) break;
			if((produto.codigo_item)!=0){
				printf("\tNome: %s\n", produto.nome_produto);
				printf("\tCódigo do produto: %d\n", produto.codigo_item);
				printf("\tQuantidade: %d\n", produto.quantidade);
				printf("\tValor da compra: %.1f\n", produto.valor_compra);
				printf("\tValor da venda: %.1f\n", produto.valor_venda);
				printf("\tData da compra: %s\n", produto.data_compra);
				printf("\tData de validade: %s\n\n", produto.data_validade);
			}
	}while(!feof(pro));
	
	
}

void consultar_produto(FILE *pro){
	
	Produto produto;
	int buscar_produto;
	rewind(pro);
	
	setbuf(stdin, NULL);
	printf("\t----Consultar produto:----\n\n");
	printf("Digite o código do produto que você deseja consultar:\n");
	scanf("%d", &buscar_produto);
	
	fseek(pro,(buscar_produto-1)*sizeof(Produto),SEEK_SET);
	fread(&produto,sizeof(Produto),1,pro);
	
	if(feof(pro)){
		printf("Produto não encontrado!!\n");
	}
	
	printf("\nNome: %s\n", produto.nome_produto);
	printf("\tCódigo do produto: %d\n", produto.codigo_item);
	printf("\tQuantidade: %d\n", produto.quantidade);
	printf("\tValor da compra: %.1f\n", produto.valor_compra);
	printf("\tValor da venda: %.1f\n", produto.valor_venda);
	printf("\tData da compra: %s\n", produto.data_compra);
	printf("\tData de validade: %s\n", produto.data_validade);
	
}

void editar_produto(FILE *pro){
	
	Produto produto = {0, 0, 0, 0, "",""};
	int editar;
	char altera[2];
	rewind(pro);
	
	printf("\t----Edição do produto:----\n\n");
	printf("Digite o código do produto que você deseja editar:\n");
	scanf("%d", &editar);
	setbuf(stdin, NULL);
	
	fseek(pro,(editar-1)*sizeof(Produto),SEEK_SET);
	fread(&produto,sizeof(Produto),1,pro);
	
	if(produto.codigo_item == 0){
		printf("Produto inexistente!!\n");
	}else{
		fflush(stdin);
        printf("Deseja atualizar:\n");
        printf("Nome: (s / n)\n ");
        scanf("%s", &altera);
        if(strcmp(altera, "s") == 0){
            printf("Nome Atual: %s\n", produto.nome_produto);
            fflush(stdin);
            printf("Entre com o novo nome:\n");
            gets(produto.nome_produto);
        }
        fflush(stdin);
        printf("Valor da compra: (s / n)\n");
        scanf("%s", &altera);
        if(strcmp(altera, "s") == 0){
		    printf("valor da compra Atual %.2f \n", produto.valor_compra);
		    fflush(stdin);
		    printf("Entre com o novo valor da compra:\n");
			scanf("%f", &produto.valor_compra);
        }
		fflush(stdin);
		printf("Deseja atualizar: \n");
		printf("Data da compra: (s / n)\n");
		scanf("%s", &altera);
		if(strcmp(altera, "s") == 0){
		    printf("Data da compra Atual: %s\n", produto.data_compra);
		    fflush(stdin);
		    printf("Entre com o novo nome:\n");
		    gets(produto.data_compra);
	    }
		fflush(stdin);
		printf("Deseja atualizar: \n");
		printf("Quantidade do produto: (s / n)\n");
		scanf("%s", &altera);
        if(strcmp(altera, "s") == 0){
		    printf("Quantidade Atual: %d\n", produto.quantidade);
		    fflush(stdin);
		    printf("Entre com a nova quantidade do produto:\n");
		    scanf("%d", &produto.quantidade);
        }
		fflush(stdin);
		printf("Deseja atualizar:\n");
		printf("Validade do produto: (s / n)\n");
		scanf("%s", &altera);
        if(strcmp(altera, "s") == 0){
            printf("Validade Atual: %s\n", produto.data_validade);
            fflush(stdin);
            printf("Entre com a nova validade:\n");
            gets(produto.data_validade);
        }
        		// contato.num_registro = reg;
        		// rewind(parq);
        fseek(pro, (editar-1)*sizeof(Produto),SEEK_SET);
        printf("...Atualizando cadastro aguarde...\n");

        fwrite(&produto, sizeof(Produto),1,pro);
    		
	}
	
	
}

void excluir_produto(FILE *pro){
	
	Produto produto;
	Produto nulo = {0, 0, 0, 0, "", ""};
	int busca;
	char escolha;
	rewind(pro);
	
	printf("\t----Exclusão do produto:----\n\n");
	printf("Digite o codigo do produto que você deseja excluir:\n");
	scanf("%d", &busca);
	setbuf(stdin, NULL);
	
	fseek(pro,(busca-1)*sizeof(Produto),SEEK_SET);
	
	if(fread(&produto,sizeof(Produto),1,pro)!=1){
		printf("Produto não encontrado!!\n");
	}
	
	printf("\nNome: %s\n", produto.nome_produto);
	printf("\tCódigo do produto: %d\n", produto.codigo_item);
	printf("\tQuantidade: %d\n", produto.quantidade);
	printf("\tValor da compra: %.1f\n", produto.valor_compra);
	printf("\tValor da venda: %.1f\n", produto.valor_venda);
	printf("\tData da compra: %s\n", produto.data_compra);
	printf("\tData de validade: %s\n", produto.data_validade);
	
	setbuf(stdin, NULL);
	printf("\nVocê deseja excluir esse produto?: [s] -sim ou [n] - não\n");
	scanf("%c", &escolha);
	
	if(escolha == 's'){
		fseek(pro,(busca-1)*sizeof(Produto),SEEK_SET);
		fwrite(&nulo,sizeof(Produto),1,pro);
		printf("Produto excluído com sucesso!!");
	}
	
}

void listar_vendas(FILE *vendas){
	
	Produto produto;
	Venda venda;
	rewind(vendas);
	
	printf("\t----Lista de Vendas:----\n\n");
	
	do{
		fread(&venda,sizeof(Venda),1,vendas);
		if(feof(vendas)) break;
		if((venda.codigo_venda)!=0){
			printf("\tNome: %s\n", venda.nome_venda);
			printf("\tCódigo: %d\n", venda.codigo_item);
			printf("\tCódigo da venda: %d\n", venda.codigo_venda);
			printf("\tData da venda: %s\n", venda.data_venda);
			printf("\tQuantidade: %d\n", venda.quantidade_venda);
			printf("\tValor total da venda: %.1f\n", venda.valor_total_venda);
			printf("\t-------------------\n");
		}
	}while(!feof(vendas));
}

void realizar_vendas(FILE *vendas, FILE *pro, int *pcont){
	
	Produto produto;
	Venda venda;
	int cod;
	
	printf("Digite o código do produto que você deseja comprar:\n");
	scanf("%d", &cod);
	
	fseek(pro,(cod-1)*sizeof(Produto),SEEK_SET);
	fread(&produto,sizeof(Produto),1,pro);
	
	if(produto.codigo_item != cod){
		printf("Produto inexistente!!");
	}else{
		venda.codigo_venda=(*pcont)+1;
		venda.codigo_item=cod;
		printf("Nome: %s\n", produto.nome_produto);
		strcpy(venda.nome_venda, produto.nome_produto);
		printf("Código da venda: %d\n", venda.codigo_venda);
		printf("Digite a data que voce está realizando essa venda:\n");
		scanf(" %[^\n]", venda.data_venda);
		printf("Digite a quantidade que você quer comprar deste produto:\n");
		scanf("%d", &venda.quantidade_venda);
		
		
		if(venda.quantidade_venda>produto.quantidade){
          	printf("\nQuantidade de produto digitada é maior do que a do estoque\n");
        }else{
			printf("Digite o valor da venda:\n");
			scanf("%f", &venda.valor_total_venda);
			produto.quantidade = produto.quantidade - venda.quantidade_venda;
       	}
       	
       	fseek(pro,(cod-1)*sizeof(Produto),SEEK_SET);
       	fwrite(&produto,sizeof(Produto),1,pro);
       	fwrite(&venda,sizeof(Venda),1,vendas);
       	printf("Compra realizada com sucesso!!\n");
       	(*pcont)++;
	}
	
	system("cls");
	
}

void consultar_venda(FILE *vendas){
	
	Venda venda;
	int busca_venda;
	rewind(vendas);
	
	printf("\t----Consultar venda:----\n\n");
	printf("Digite o código da venda que você deseja consultar:\n");
	scanf("%d", &busca_venda);
	
	fseek(vendas,(busca_venda-1)*sizeof(Venda),SEEK_SET);
	fread(&venda, sizeof(Venda), 1, vendas);
	
	if(feof(vendas)){
		printf("Venda inexistente!!\n");
	}
	
	printf("\tNome: %s\n", venda.nome_venda);
	printf("\tCódigo: %d\n", venda.codigo_item);
	printf("\tCódigo da venda: %d\n", venda.codigo_venda);
	printf("\tData da venda: %s\n", venda.data_venda);
	printf("\tQuantidade: %d\n", venda.quantidade_venda);
	printf("\tValor total da venda: %.1f\n", venda.valor_total_venda);
	printf("\t-------------------\n");
	
}

void dados(){
	
	printf("\n");
	printf("\tDesenvolvedores: João Paulo C. Arquim e Felipe Ferreira\n");
	printf("\tCurso: ADS 2019.2 - Estrutura de Dados");
	printf("\n\n");
	
}
