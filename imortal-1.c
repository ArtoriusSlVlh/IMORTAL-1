#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int quantleituras() { //funcao adicional para definir a quantidade de leituras que serão feitas
    int l; //variavel que guarda quantas leituras vão ser feitas

    printf("Quantas leituras voce quer fazer (3 a 100): ");
    scanf("%d", &l);

    while (l < 3 || l > 100) { //Não permite um valor menor que 3 ou maior que 100
        printf("\033[1;31m!ERROR!\033[0m Digite um valor valido, tente novamente.\n");
        printf("Quantas leituras voce quer fazer (3 a 100): ");
        scanf("%d", &l);
    }

return l; //retorna o valor escolhido pelo usuario
}

double numAletatorio(int max) {
    // rand() gera um inteiro aleatório entre 0 e RAND_MAX
    // double) rand() / RAND_MAX transorma o valor entre 0.0 e 1.0
    // multiplicando por max e obtendo um double entre 0.0 e max
    return ((double)rand() / RAND_MAX) * max;
}   

double calcularMedia(double *media, int qleituras) {
    double soma = 0; //variavel para acumular a soma das leituras
    for (int i=0; i<qleituras; i++)
        soma += *(media +i); //acumula cada leitura na variavel soma

return soma/qleituras; //divide o resultado da soma pela quantidade de leituras e retorna
}

double encontrarMaior(double *max, int qleituras){
    double maior = *max; //assume a leitura 1 como o maior valor
    
    for (int i=1; i<qleituras; i++){
        if(*(max +i) > maior) //se encontrar um valor maior que o atual
            maior = *(max +i); //atualiza o maior 
    }
return  maior; //retorna o maior valor escolhido pelo usuario
}

int posicaoMax (double *posMax, int qleituras){  //funcao adicional para definir a posicao do maior valor
    int pos = 0; //assume que o maior valor está na leitura 1
    for (int i=1; i<qleituras; i++){
        if(*(posMax +i) > *(posMax +pos)) //se o valor da posicao i for maior que o da posicao atual
            pos=i; //atualiza a posicao do maior
    }
return pos; //retorna a posicao do maior valor escolhido pelo usuario
}

double encontrarMenor(double *min, int qleituras){
    double menor = *min; //assume a leitura 1 como o menor valor

    for (int i=1; i<qleituras; i++){
        if(*(min +i) < menor) //se encontrar um valor menor que o atual
            menor = *(min +i); //atualiza o menor
    }
return menor; //retorna o menor valor escolhido pelo usuario
}

int posicaoMin (double *posMin, int qleituras){ //funcao adicional para definir a posicao do menor valor
    int pos = 0; //assume que o menor valor está na leitura 1
    for (int i=1; i<qleituras; i++){
        if (*(posMin +i) < *(posMin +pos)) //se o valor da posicao i for menor que o da posicao atual
            pos=i; //atualiza a posicao do menor
    }
return pos; //retorna a posicao do menor valor escolhido pelo usuario
}

void exibirDesvio(double *desvio, int qleituras) {
    double med = calcularMedia(desvio, qleituras); //calcula e armazena a media das leituras na variavel med
    
    for (int i=0; i<qleituras; i++){
        double d = *(desvio +i) - med; //d armazena a diferença entre a leitura atual e a media
        if (d >= 0)
            printf("Desvio na leitura %d: \033[1;32m%+.2f\033[0m\n", i+1, d); //verde se for acima da media
        else
            printf("Desvio na leitura %d: \033[1;31m%+.2f\033[0m\n", i+1, d); //vermelho se for abaixo da media
    }
}

void exibirFaixa(double *lerFaixa, int qleituras) {
    double minAceitavel, maxAceitavel; 
    
    //limite minimo e maximo da faixa definido pelo usuario
    printf("Digite um valor minimo aceitavel: ");
    scanf(" %lf", &minAceitavel);
    printf("Digite um valor maximo aceitavel: ");
    scanf(" %lf", &maxAceitavel);

    //Nao permite valores negativos ou que o valor minimo seja igual ou superior ao valor maximo
    while (minAceitavel < 0 || maxAceitavel <= minAceitavel) { 
        printf("\033[1;31m!ERROR!\033[0m Valores invalidos, tente novamente.\n");

        printf("Digite um valor minimo aceitavel: ");
        scanf(" %lf", &minAceitavel);
        printf("Digite um valor maximo aceitavel: ");
        scanf(" %lf", &maxAceitavel);
    }

    //lerFaixa armazena o valor que está na posicao i e verifica qual a relação dele com a faixa definida
    for (int i=0; i<qleituras; i++) {
        if (*(lerFaixa + i) < minAceitavel)
            printf("Leitura %d: \033[31mABAIXO DA FAIXA LIMITE!\033[0m\n", i + 1); //inferior a faixa
        else if (*(lerFaixa + i) > maxAceitavel)
            printf("Leitura %d: \033[31mACIMA DA FAIXA LIMITE!\033[0m\n", i + 1); //superior a faixa
        else
            printf("Leitura %d: \033[32mOK\033[0m\n", i + 1); //de acordo com a faixa
    }
}

void exibirBarraGrafica(double media) {
    int asterisco = media/100.0; //divide a media por cem e armazena o resultado no asterisco

    for (int i=1; i<=asterisco; i++) { //representa a quantidade de asteriscos que a barra grafica gerou através da media
        printf ("* ");
   }
    printf("\n");
}

void exibirRelatorioFULL(double *completo, int qleituras) {

    double med = calcularMedia(completo, qleituras); //calcula e armazena a media das leituras na variavel med
    printf("Valor medio das leituras: %.2f\n\n", med); 

    //apresenta o maior e menor valor lido das leituras com suas respectivas posicoes
    printf("Maior valor lido: \033[1;32m%.2f\033[0m (Leitura %d)\n", encontrarMaior(completo, qleituras), posicaoMax(completo, qleituras)+1);
    printf("Menor valor lido: \033[1;31m%.2f\033[0m (Leitura %d)\n\n", encontrarMenor(completo, qleituras), posicaoMin(completo, qleituras)+1);

    exibirDesvio(completo, qleituras);     

    printf("\n");
    exibirFaixa(completo, qleituras);

    printf("\n");
    exibirBarraGrafica(med);
}

void menuIMORTAL() {
    printf("\033[1;32m< MENU >\033[0m\n");

    //exibe as opções disponiveis para o usuario
    printf("\n\033[1;36m<[1] Media>\033[0m\n");    
    printf("\033[1;36m<[2] Max/Min>\033[0m\n");
    printf("\033[1;36m<[3] Desvios>\033[0m\n");
    printf("\033[1;36m<[4] Analise da faixa>\033[0m\n");
    printf("\033[1;36m<[5] Barra grafica>\033[0m\n");
    printf("\033[1;35m<[6] Relatorio completo>\033[0m\n");
    printf("\033[1;33m<[0] Sair>\033[0m\n");
}

int main() {
srand((unsigned int)time(NULL)); //inicializa a semente,obrigatório para sorteio
  
printf("\n\033[1;34m< IMORTAL-1 - SISTEMA DE BORDO >\033[0m\n");

char novaSimulacao = 's'; //variavel que controla o loop do sistema

while (novaSimulacao == 's' || novaSimulacao == 'S'){

    int n = quantleituras(); //quantidade de leituras escolhidas pelo usuario indo para a variavel n
    double *random = malloc(n * sizeof(double)); // random aponta para n espaços na memória, cada um do tipo double

    for (int i = 0; i < n; i++)
        *(random +i) = numAletatorio(2000); //define o valor de max em 2000 e gera um double aleatorio entre 0 a 2000 para cada leitura

    printf("\n\033[1;34mLeitura sorteada: \33[0m\n");
    for (int i = 0; i < n; i++)
        printf("Leitura %d: %.2f\n", i + 1, *(random +i)); //exibe cada leitura sorteada
    
    menuIMORTAL();

    int opcao;
    char continuar = 's'; //controla o loop de operacoes
    
        while (continuar == 's' || continuar == 'S'){            
            printf("\nEscolha uma funcao do \033[1;32mMENU\033[0m: ");
            scanf("%d", &opcao);

            if (opcao ==1){ //Criacao das 7 opções de operacao
                    printf("\n\033[1;36m<OPCAO 1>\033[0m\n");
                    printf("Valor medio das leituras: %.2f\n", calcularMedia(random, n));
                }
                else if (opcao ==2){
                    printf("\n\033[1;36m<OPCAO 2>\033[0m\n");
                    printf("Maior valor lido: \033[1;32m%.2f\033[0m (Leitura %d)\n", encontrarMaior(random, n), posicaoMax(random, n) +1);
                    printf("Menor valor lido: \033[1;31m%.2f\033[0m (Leitura %d)\n", encontrarMenor(random, n), posicaoMin(random, n) +1);
                }
                else if (opcao ==3){
                    printf("\n\033[1;36m<OPCAO 3>\033[0m\n");
                    exibirDesvio(random, n);
                }
                else if (opcao ==4){
                    printf("\n\033[1;36m<OPCAO 4>\033[0m\n");
                    exibirFaixa(random, n);
                }
                else if (opcao ==5){
                    printf("\n\033[1;36m<OPCAO 5>\033[0m\n");
                    exibirBarraGrafica(calcularMedia(random, n));
                }
                else if (opcao ==6){
                    printf("\n\033[1;35m<OPCAO 6>\033[0m\n");
                    exibirRelatorioFULL(random, n);
                }
                else if (opcao ==0){
                    printf("\033[1;33mSaindo...\033[0m\n");
                    break; //encerra o loop se caso escolher sair (opcao 0)
                }
                else { //opcao digitada nao existe no menu
                     printf("\033[1;31mOpcao invalida!\033[0m\n");
                }

            if (opcao !=0) { //se o usuario nao escolher sair, realizar a pergunta
                printf("\nDeseja realizar outra operacao? (\033[1;32mS\033[0m/\033[1;31mN\033[0m): ");
                scanf(" %c", &continuar);
                
                //nao permite valores diferente de S/N ou s/n
                while (continuar != 's' && continuar != 'S' && continuar != 'n' && continuar != 'N'){
                    printf("\033[1;31m!ERROR!\033[0m Digite apenas S ou N\n");
                    printf("\nDeseja realizar outra operacao? (\033[1;32mS\033[0m/\033[1;31mN\033[0m): ");
                    scanf(" %c", &continuar);
                }
            }
        } 

    free(random); //libera a memoria alocada pelo malloc

    printf("\nDeseja iniciar uma nova simulacao? (\033[1;32mS\033[0m/\033[1;31mN\033[0m): ");
    scanf(" %c", &novaSimulacao);

    //nao permite valores diferentes de S/N ou s/n
    while (novaSimulacao != 's' && novaSimulacao != 'S' && novaSimulacao != 'n' && novaSimulacao != 'N') {
        printf("\033[1;31m!ERROR!\033[0m Digite apenas S ou N\n");
        printf("\nDeseja iniciar uma nova simulacao? (\033[1;32mS\033[0m/\033[1;31mN\033[0m): ");
        scanf(" %c", &novaSimulacao);
    }
}

printf("\n\033[1;33mEncerrando sistema...\033[0m\n");
return 0;
}