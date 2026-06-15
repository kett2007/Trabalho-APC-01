#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h> 

#define MAX 10

struct Musica {
    int id;
    char titulo[100];
    char artista[80];
    int ano;
};

int main(void) {

    struct Musica catalogo[MAX];
    int total = 0;
    int opcao, i;
    char buf[200];

    do {
        system("cls"); // Limpa a tela
        
        // menu principal com estrutura de repeticao
        printf("==================================================\n"); Sleep(60); // delay no menu para efeito visual
        printf("               CATALOGO DE MUSICAS                \n"); Sleep(60);
        printf("==================================================\n"); Sleep(60);
        printf("  1 - Cadastrar Musica\n"); Sleep(60);
        printf("  2 - Listar Catalogo\n"); Sleep(60);
        printf("  3 - Buscar por ID\n"); Sleep(60);
        printf("  4 - Atualizar Musica\n"); Sleep(60);
        printf("  5 - Remover Musica\n"); Sleep(60);
        printf("  0 - Sair do Sistema\n"); Sleep(60);
        printf("-------------------------------------------------------\n"); Sleep(60);
        printf("Selecione uma opcao: ");
        
        // validaçao contra letras no menu principal
        if (scanf("%d", &opcao) != 1) {
            printf("\n Opcao invalida! Digite apenas numeros.\n");
            while (getchar() != '\n'); // Limpa o buffer do teclado
            Sleep(1800); // Pausa para leitura do aviso
            continue;
        }

        // ------ CADASTRAR ------
        if (opcao == 1) {
            system("cls");
            printf("======================================================\n");
            printf("               CADASTRAR NOVA MUSICA              \n");
            printf("======================================================\n\n");

            if (total >= MAX) {
                printf(" A lista de musicas esta cheia (Maximo: %d).\n", MAX); //mostra que o banco de dados esta cheio
                Sleep(1800);
            } else {
                int novo_id;
                printf("[Aviso] O ID deve ser obrigatoriamente um NUMERO.\n");
                printf("Digite o ID: ");
                
                // verifica se o ID eh um numero valido
                if (scanf("%d", &novo_id) != 1) {
                    printf("\n[erro] Entrada invalida! O ID precisa ser numerico.\n");
                    while (getchar() != '\n');
                    Sleep(1800);
                    continue;
                }

                // verifica se o ID já está no sistema para evitar duplicidade
                int achou = 0;
                for (i = 0; i < total; i++) {
                    if (catalogo[i].id == novo_id) {
                        achou = 1;
                        break;
                    }
                }

                if (achou) {
                    printf("\n[Erro] Esse ID ja esta cadastrado no sistema.\n");
                    Sleep(1800);
                } else {
                    getchar(); // Limpa o \n residual do scanf
                    
                    printf("Titulo: ");
                    fgets(buf, sizeof(buf), stdin);
                    buf[strcspn(buf, "\n")] = '\0';
                    if (strlen(buf) == 0) { // garante que a string nn fique vazia
                        printf("\n[Erro] O titulo nao pode ser vazio.\n");
                        Sleep(1800);
                        continue;
                    }
                    strcpy(catalogo[total].titulo, buf);

                    printf("Artista: ");
                    fgets(buf, sizeof(buf), stdin);
                    buf[strcspn(buf, "\n")] = '\0';
                    if (strlen(buf) == 0) { // garante que a string nao fique vazia
                        printf("\n[Erro] O artista nao pode ser vazio.\n");
                        Sleep(1800);
                        continue;
                    }
                    strcpy(catalogo[total].artista, buf);
                    printf("Ano: ");
                    int ano;
                    
                    // valida se o ano eh um numero dentro do intervalo
                    if (scanf("%d", &ano) != 1) {
                        printf("\n[Erro] Ano invalido! Digite apenas numeros.\n");
                        while (getchar() != '\n');
                        Sleep(1800);
                        continue;
                    }

                    if (ano < 1900 || ano > 2100) {
                        printf("\n[Erro] Ano fora do limite permitido (1900-2100).\n");
                        Sleep(1800);
                    } else {
                        catalogo[total].id = novo_id;
                        catalogo[total].ano = ano;
                        total++;
                        printf("\n[Sucesso] Musica cadastrada com sucesso\n");
                        Sleep(1800);
                    }
                }
            }

        // ------ LISTAR ------
        } else if (opcao == 2) {
            system("cls");
            if (total == 0) {
                printf("\n========================================================\n");
                printf("Nenhuma musica cadastrada ainda.\n");
                printf("==========================================================\n");
                Sleep(1800);
            } else {
                // Listagem com cabeçalho e linhas aparecendo ritmadamente
                printf("\n%-5s %-35s %-25s %s\n", "ID", "Titulo", "Artista", "Ano"); Sleep(60);
                printf("-----------------------------------------------------------------------\n"); Sleep(60);
                for (i = 0; i < total; i++) {
                    printf("%-5d %-35s %-25s %d\n",
                        catalogo[i].id,
                        catalogo[i].titulo,
                        catalogo[i].artista,
                        catalogo[i].ano);
                    Sleep(60); // Efeito linha por linha
                }
                printf("-----------------------------------------------------------------------\n");
                printf("\nPressione ENTER para voltar ao menu...");
                getchar(); // Captura o \n anterior
                getchar(); // Aguarda o usuario pressionar ENTER
            }

        // ------ BUSCAR ------
        } else if (opcao == 3) {
            system("cls");
            printf("==================================================\n");
            printf("                 BUSCAR POR ID                    \n");
            printf("==================================================\n\n");

            if (total == 0) {
                printf("Nenhuma musica cadastrada no sistema.\n");
                Sleep(1800);
            } else {
                int id;
                printf("[Aviso] O ID deve ser um numero.\n");
                printf("Digite o ID para busca: ");
                
                if (scanf("%d", &id) != 1) {
                    printf("\n[erro] Entrada invalida! Digite apenas numeros.\n");
                    while (getchar() != '\n');
                    Sleep(1800);
                    continue;
                }

                int achou = 0;
                for (i = 0; i < total; i++) {
                    if (catalogo[i].id == id) {
                        printf("\n-----------------------------------\n"); Sleep(60);
                        printf("ID: %d\n", catalogo[i].id); Sleep(60);
                        printf("Titulo: %s\n", catalogo[i].titulo); Sleep(60);
                        printf("Artista: %s\n", catalogo[i].artista); Sleep(60);
                        printf("Ano: %d\n", catalogo[i].ano); Sleep(60);
                        printf("-----------------------------------\n");
                        achou = 1;
                        break;
                    }
                }
                if (!achou) {
                    printf("\n[Aviso] ID nao encontrado no catalogo.\n");
                }
                
                printf("\nPressione ENTER para continuar...");
                getchar(); getchar();
            }

        // ------ ATUALIZAR ------
        } else if (opcao == 4) {
            system("cls");
            printf("==================================================\n");
            printf("               ATUALIZAR CADASTRO                 \n");
            printf("==================================================\n\n");

            if (total == 0) {
                printf("Nenhuma musica cadastrada no sistema.\n");
                Sleep(1800);
            } else {
                int id;
                printf("[Aviso] O ID deve ser um numero.\n");
                printf("ID da musica para alterar: ");
                
                if (scanf("%d", &id) != 1) {
                    printf("\n[Erro] Entrada invalida. Digite apenas numeros.\n");
                    while (getchar() != '\n');
                    Sleep(1800);
                    continue;
                }

                int pos = -1; // comeca com valor invalido para indicar que nao encontrou
                for (i = 0; i < total; i++) {
                    // salva o indice da musica encontrada para atualizar depois do loop
                    if (catalogo[i].id == id) { pos = i; break; }
                }

                if (pos == -1) {
                    printf("\n[AVISO] ID nao encontrado.\n");
                    Sleep(1800);
                } else {
                    printf("\nMusica Atual: %s - %s (%d)\n\n",
                        catalogo[pos].titulo, catalogo[pos].artista, catalogo[pos].ano);

                    getchar(); // Limpa o buffer
                    printf("Novo titulo (Pressione ENTER para manter): ");
                    fgets(buf, sizeof(buf), stdin);
                    buf[strcspn(buf, "\n")] = '\0';
                    if (strlen(buf) > 0) strcpy(catalogo[pos].titulo, buf);

                    printf("Novo artista (Pressione ENTER para manter): ");
                    fgets(buf, sizeof(buf), stdin);
                    buf[strcspn(buf, "\n")] = '\0';
                    if (strlen(buf) > 0) strcpy(catalogo[pos].artista, buf);

                    printf("Novo ano (Digite 0 para manter - Apenas numeros): ");
                    int ano;
                    if (scanf("%d", &ano) != 1) {
                        printf("\n[erro] Entrada invalida! O ano nao foi alterado.\n");
                        while (getchar() != '\n');
                        Sleep(1800);
                        continue;
                    }
                    
                    if (ano != 0) {
                        if (ano < 1900 || ano > 2100) {
                            printf("[Aviso] Ano invalido. Alteracao descartada para este campo.\n");
                        } else {
                            catalogo[pos].ano = ano;
                        }
                    }

                    printf("\n[Sucesso] Cadastro atualizado!\n");
                    Sleep(1800);
                }
            }

        // ------ REMOVER ------
        } else if (opcao == 5) {
            system("cls");
            printf("==================================================\n");
            printf("                REMOVER REGISTRO                  \n");
            printf("==================================================\n\n");

            if (total == 0) {
                printf("Nenhuma musica cadastrada no sistema.\n");
                Sleep(1800);
            } else {
                int id;
                printf("[Aviso] O ID deve ser um numero.\n");
                printf("ID da musica para remover: ");
                
                if (scanf("%d", &id) != 1) {
                    printf("\n[Erro] Entrada invalida! Digite apenas numeros.\n");
                    while (getchar() != '\n');
                    Sleep(1800);
                    continue;
                }

                int pos = -1;
                for (i = 0; i < total; i++) {
                    if (catalogo[i].id == id) { pos = i; break; }
                }

                if (pos == -1) {
                    printf("\n[Avisa] ID nao encontrado.\n");
                    Sleep(1800);
                } else {
                    printf("\nRemovendo registro: %s...\n", catalogo[pos].titulo);
                    
                    // deslocamento para manter a consistência fisica do vetor
                    for (i = pos; i < total - 1; i++) {
                        //puxa a proxima musica para a tras para cobrir o espaco da musica removida
                        catalogo[i] = catalogo[i + 1];
                    }
                    total--; // diminui a qtd total de musica cadastradas
                    printf("[Sucesso] Musica removida com sucesso!\n");
                    Sleep(1800);
                }
            }

        } else if (opcao != 0) {
            printf("\n[aviso] Opcao invalida no menu.\n");
            Sleep(1800);
        }

    } while (opcao != 0);

    system("cls");
    printf("\n==================================================\n");
    printf("Encerando o sistema...\n");
    printf("==================================================\n\n");
    return 0;
}