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
	
	do{
		printf("\t----Supermercado DEV----\n\n");
		printf("[1]-Cadastrar produto\n");
		printf("[2]-Listar produtos\n");
		printf("[3]-Consultar produto\n");
		printf("[4]-Editar produto\n");
		printf("[5]-Excluir produto\n");
		printf("[6]-Realizar venda\n");
		printf("[7]-Listar vendas\n");
		printf("[8]-Emitir comprovante da venda\n");
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
				emitir_comprovante(vendas);
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
	 
	Venda venda[10];
	int posicao_registro = 0;
	
		do{
			fread(venda,sizeof(Venda),10,vendas);
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
	
		printf("----Dados dos produtos:----\n\n");
	
		do{
			fread(&produto,sizeof(Produto),1,pro);
			if(feof(pro)) break;
				if((produto.codigo_item)!=0){
					printf("\tNome: %s\n", produto.nome_produto);
					printf("\tCódigo do produto: %d\n", produto.codigo_item);
					printf("\tQuantidade: %d\n", produto.quantidade);
					printf("\tValor da compra: %.2f\n", produto.valor_compra);
					printf("\tValor da venda: %.2f\n", produto.valor_venda);
					printf("\tData da compra: %s\n", produto.data_compra);
					printf("\tData de validade: %s\n\n", produto.data_validade);
				}
		}while(!feof(pro));
		
}

void consultar_produto(FILE *pro){

    int opcao;

	    printf("\t\t**********Opcões de consulta***********\n");
	    printf("[1] - Consulta por nome\n");
	    printf("[2] - Consulta por código do produto\n");
	    printf("[3] - Sair\n");
	    scanf("%d", &opcao);
            switch(opcao){
                case 1:
                	consulta_nome(pro);
                	break;
                
                case 2:
                	consulta_codigo(pro);
                	break;
                	
                default:
                	if (opcao != 3){
                    printf("Opcao invalida!\n");
                    system("pause");
                    system("cls");
             	}	
            }

    system("pause");
    system("cls");

}

void consulta_nome(FILE *pro){
	
	Produto produto;
	char nome_consultado[30];
		fflush(stdin);
			     	printf("digite o nome do produto\n");
			     	gets(nome_consultado);
			     	printf("\n");
	     	
	     			while (!feof(pro)){
	         			fread(&produto, sizeof(Produto), 1, pro);
	        				if (strstr(produto.nome_produto,nome_consultado)){
					            printf("Nome: %s\n",produto.nome_produto);
					            printf("codigo do produto: %d\n", produto.codigo_item);
					            printf("valor da compra: %.2f\n", produto.valor_compra);
					            printf("data da compra: %s\n", produto.data_compra);
					            printf("quantidade: %d\n", produto.quantidade);
					            printf("validade do produto: %s\n", produto.data_validade);
					            printf("\n-------------------\n");             
	         				}
     				}
	
	
}

void consulta_codigo(FILE *pro){
	
	Produto produto;
	int buscar_produto;
	
		printf("Digite o código do produto que você deseja consultar:\n");
					scanf("%d", &buscar_produto);
					
					fseek(pro,(buscar_produto-1)*sizeof(Produto),SEEK_SET);
					fread(&produto,sizeof(Produto),1,pro);
				
					if(feof(pro)){
						printf("Produto não encontrado!!\n");
					}
		
					printf("\tNome: %s\n", produto.nome_produto);
					printf("\tCódigo do produto: %d\n", produto.codigo_item);
					printf("\tQuantidade: %d\n", produto.quantidade);
					printf("\tValor da compra: %.2f\n", produto.valor_compra);
					printf("\tValor da venda: %.2f\n", produto.valor_venda);
					printf("\tData da compra: %s\n", produto.data_compra);
					printf("\tData de validade: %s\n\n", produto.data_validade);
	
}

void editar_produto(FILE *pro){
	
	Produto produto = {0, 0, 0, 0, 0, 0};
	int editar;
	int altera;
	
	rewind(pro);
	
		printf("\n\t----Edição do produto:----\n\n");
		printf("Digite o código do produto que você deseja editar:\n");
		scanf("%d", &editar);
		setbuf(stdin, NULL);
	
		fseek(pro,(editar-1)*sizeof(Produto),SEEK_SET);
		fread(&produto,sizeof(Produto),1,pro);
	
		if(produto.codigo_item == 0){
		printf("Produto não cadastrado!!\n");
		}else{
			fflush(stdin);
	        printf("Deseja atualizar:\n");
	        printf("Nome: [1]-Sim ou [2]-Não\n ");
	        scanf("%d", &altera);
	        if(altera == 1){
	            printf("Nome Atual: %s\n", produto.nome_produto);
	            fflush(stdin);
	            printf("Entre com o novo nome:\n");
	            gets(produto.nome_produto);
	        }
	        
	        fflush(stdin);
	        printf("Deseja atualizar:\n");
	        printf("Valor da compra: [1]-Sim ou [2]-Não\n ");
	        scanf("%d", &altera);
	        if(altera == 1){
			    printf("Valor da compra Atual %.2f \n", produto.valor_compra);
			    fflush(stdin);
			    printf("Entre com o novo valor da compra:\n");
				scanf("%f", &produto.valor_compra);
	        }
	        
			fflush(stdin);
			printf("Deseja atualizar:\n");
	        printf("Data da compra: [1]-Sim ou [2]-Não\n ");
	        scanf("%d", &altera);
	        if(altera == 1){
			    printf("Data da compra Atual: %s\n", produto.data_compra);
			    fflush(stdin);
			    printf("Entre com a nova data:\n");
			    gets(produto.data_compra);
		    }
		    
			fflush(stdin);
			printf("Deseja atualizar:\n");
	        printf("Quantidade: [1]-Sim ou [2]-Não\n ");
	        scanf("%d", &altera);
	        if(altera == 1){
			    printf("Quantidade Atual: %d\n", produto.quantidade);
			    fflush(stdin);
			    printf("Entre com a nova quantidade do produto:\n");
			    scanf("%d", &produto.quantidade);
	        }
		        
			fflush(stdin);
			printf("Deseja atualizar:\n");
	        printf("Validade do produto: [1]-Sim ou [2]-Não\n ");
	        scanf("%d", &altera);
	        if(altera == 1){
	            printf("Validade Atual: %s\n", produto.data_validade);
	            fflush(stdin);
	            printf("Entre com a nova validade:\n");
	            gets(produto.data_validade);
	        }
        
	        fseek(pro, (editar-1)*sizeof(Produto),SEEK_SET);
	        printf("...Atualizando cadastro aguarde...\n");
	
	        fwrite(&produto, sizeof(Produto),1,pro);  		
		}
	
	
}

void excluir_produto(FILE *pro){
	
	Produto produto;
	Produto nulo = {0, 0, 0, 0, 0, 0};
	int busca;
	char escolha;
	rewind(pro);
	
		printf("\n\t----Exclusão do produto:----\n\n");
		printf("Digite o codigo do produto que você deseja excluir:\n");
		scanf("%d", &busca);
		setbuf(stdin, NULL);
	
		fseek(pro,(busca-1)*sizeof(Produto),SEEK_SET);
	
			if(fread(&produto,sizeof(Produto),1,pro)!=1){
				printf("Produto não encontrado!!\n");
				return;
			}
	
		printf("\tNome: %s\n", produto.nome_produto);
		printf("\tCódigo do produto: %d\n", produto.codigo_item);
		printf("\tQuantidade: %d\n", produto.quantidade);
		printf("\tValor da compra: %.2f\n", produto.valor_compra);
		printf("\tValor da venda: %.2f\n", produto.valor_venda);
		printf("\tData da compra: %s\n", produto.data_compra);
		printf("\tData de validade: %s\n", produto.data_validade);
	
		setbuf(stdin, NULL);
		printf("\nVocê deseja excluir esse produto?: [s] - sim ou [n] - não\n");
		scanf("%c", &escolha);
	
			if(escolha == 's'){
				fseek(pro,(busca-1)*sizeof(Produto),SEEK_SET);
				fwrite(&nulo,sizeof(Produto),1,pro);
				printf("Produto excluído com sucesso!!\n");
			}
	
}

void listar_vendas(FILE *vendas){
	
	Produto produto;
	Venda venda[10];
	rewind(vendas);
	int i;
	
		printf("\n\t----Lista de Vendas:----\n\n");
	
		do{
			fread(&venda,sizeof(Venda),10,vendas);
			if(feof(vendas))			 
				break;
				printf("\tCódigo da venda: %d\n", venda[0].codigo_venda);
				for(i=0; i<10; i++){
					if(venda[i].codigo_item!=0){
						printf("Nome: %s\n", venda[i].nome_venda);
			        	printf("Código do produto: %d\n", venda[i].codigo_item);
				    	printf("Data da venda: %s\n", venda[i].data_venda);
				    	printf("Quantidade vendida: %d\n", venda[i].quantidade_venda);
				    	printf("Valor da venda: %.2f\n\n", venda[i].valor_total_venda);
					}
				}
			printf("\n-------------------\n");
		}while(!feof(vendas));
	

}

void realizar_vendas(FILE *vendas, FILE *pro, int *pcont){
	
	Produto produto;
	Venda *venda;
	int cod, verifica=0, cont=0;
	
		venda = (Venda *) malloc(10*(sizeof(Venda)));	
		if(venda == NULL){
		printf("ERRO na memória!!\n");
		}
	
		while(verifica != 2){
			venda[cont].codigo_venda=(*pcont)+1;
			printf("Código da venda: %d\n", venda[cont].codigo_venda); 
			printf("Digite o código do produto que você deseja comprar:\n");
			scanf("%d", &cod);
	
			fseek(pro,(cod-1)*sizeof(Produto),SEEK_SET);
			fread(&produto,sizeof(Produto),1,pro);
	
			if(produto.codigo_item != cod){
				printf("Produto inexistente!!");
			}else{
				venda[cont].codigo_item=cod;
				printf("Nome: %s\n", produto.nome_produto);
				strcpy(venda[cont].nome_venda, produto.nome_produto);
				printf("Código da venda: %d\n", venda[cont].codigo_venda);
				printf("Digite a data que voce está realizando essa venda:\n");
				scanf(" %[^\n]", venda[cont].data_venda);
				printf("Digite a quantidade que você quer comprar deste produto:\n");
				scanf("%d", &venda[cont].quantidade_venda);
		
				if(venda[cont].quantidade_venda>produto.quantidade){
          			printf("\nQuantidade de produto digitada é maior do que a do estoque\n");
        		}else{
					printf("Digite o valor da venda:\n");
					scanf("%f", &venda[cont].valor_total_venda);
					produto.quantidade = produto.quantidade - venda[cont].quantidade_venda;
					printf("Compra do produto realizada com sucesso!!\n");
					cont++;
       			}
       		
       			printf("Deseja comprar mais alguma coisa?: [1]- SIM ou [2]- NÃO\n");		        
		    	scanf("%d", &verifica);
				if(verifica == 1){
					verifica=1;
				}else{
					verifica=2;
				}
			}
			fseek(pro,(cod-1)*sizeof(Produto),SEEK_SET);
	    	fwrite(&produto,sizeof(Produto),1,pro);
		}
	

	    fwrite(venda,sizeof(Venda),10,vendas);
	    printf("Compra realizada com sucesso!!\n");
	    (*pcont)++;
    
    	free(venda);
	
	system("cls");
	
}

void emitir_comprovante(FILE *vendas){
	
	Venda venda;
	int busca_venda;
	char decisao;
	rewind(vendas);
	
		printf("\n\t----Comprovante de venda:----\n\n");
		printf("Digite o código da venda que você deseja emitir o comprovante:\n");
		scanf("%d", &busca_venda);
	
		fseek(vendas,(busca_venda-1)*sizeof(Venda),SEEK_SET);
		fread(&venda, sizeof(Venda), 1, vendas);
	
			if(feof(vendas)){
				printf("Venda não cadastrada!!\n");
				return;
			}
	
		printf("\tNome: %s\n", venda.nome_venda);
		printf("\tCódigo: %d\n", venda.codigo_item);
		printf("\tCódigo da venda: %d\n", venda.codigo_venda);
		printf("\tData da venda: %s\n", venda.data_venda);
		printf("\tQuantidade: %d\n", venda.quantidade_venda);
		printf("\tValor total da venda: %.2f\n", venda.valor_total_venda);
		printf("\t-------------------\n");
	
		setbuf(stdin, NULL);
		printf("Você quer emitir o comprovante dessa venda?: [s] - sim ou [n] - não\n");
		scanf("%c", &decisao);
	
			if(decisao == 's'){
				fseek(vendas,(busca_venda-1)*sizeof(Venda),SEEK_SET);
				fread(&venda, sizeof(Venda), 1, vendas);
			
				printf("\t----Supermercado DEV - Comprovante da venda: Cód %d----\n\n", venda.codigo_venda);
				printf("\t\tCódigo do produto: %d\n", venda.codigo_item);
				printf("\t\tData da venda: %s\n", venda.data_venda);
				printf("\t\tQuantidade: %d\n", venda.quantidade_venda);
				printf("\t\tValor total da venda: %.2f\n\n", venda.valor_total_venda);
			}
	
}

void dados(){
	
	printf("\n");
	printf("\tDesenvolvedores: João Paulo C. Arquim e Felipe Ferreira\n");
	printf("\tCurso: ADS 2019.2 - Estrutura de Dados");
	printf("\n\n");
	
}
