#include <stdio.h>
#include <stdlib.h>

// Gera lista com os códigos em hexadecimal que representam cada número de 0 a 9 exibidos em um display de 7 segmentos
char *tabelaSeteSegmentos[] = {"7e\n", "30\n", "6d\n", "79\n", "33\n", "5b\n", "5f\n", "70\n", "7f\n", "7b\n"};

int main() {
    
    // Gera um arquivo para cada display
    FILE *arq_unidades = fopen("unidades.txt", "w"); 
    FILE *arq_dezenas = fopen("dezenas.txt", "w");
    FILE *arq_centenas = fopen("centenas.txt", "w");
    FILE *arq_sinal = fopen("sinal.txt", "w");

    if (arq_unidades == NULL || arq_dezenas == NULL || arq_centenas == NULL || arq_sinal == NULL) {
        printf("Houve um erro ao tentar gerar os arquivos.\n");
        system("pause");
        exit(1);
    }

    int unidades;
    int dezenas;
    int centenas;
    
    /*
    Separa os valores unsigned int de 0 a 255 em três partes: unidade, dezena e centena, 
    convertendo esses valores para hexadecimal utilizando a lista "tabelaSeteSegmentos" 
    e armazenando-os nos respectivos arquivos designados para cada display.
    */ 
    for (int i = 0; i < 256; i++) {
        unidades = i%10; // Armazena o número da unidade referente ao loop atual
        dezenas = (i%100)/10; // Armazena o número da dezena referente ao loop atual
        centenas = i/100; // Armazena o número da centena referente ao loop atual
        fputs(tabelaSeteSegmentos[unidades], arq_unidades);
        fputs(tabelaSeteSegmentos[dezenas], arq_dezenas);
        fputs(tabelaSeteSegmentos[centenas], arq_centenas);
        fputs(tabelaSeteSegmentos[0], arq_sinal); // Preenche 256 posições de arq_sinal com 0;
    }

    /*
    Separa os primeiros 128 valores signed int em três partes e realiza a mesma ação descrita no primeiro loop for
    */
    for (int i = 0; i < 128; i++) {
        unidades = i%10;
        dezenas = (i%100)/10;
        centenas = i/100;
        fputs(tabelaSeteSegmentos[unidades], arq_unidades);
        fputs(tabelaSeteSegmentos[dezenas], arq_dezenas);
        fputs(tabelaSeteSegmentos[centenas], arq_centenas);
        fputs(tabelaSeteSegmentos[0], arq_sinal); // Preenche mais 128 posições de arq_sinal com 0;
    }

    /*
    Separa os próximos 128 valores signed int em três partes e realiza a mesma ação descrita no primeiro loop for
    */
    for (int i = 128; i >= 1; i--) {
        unidades = i%10;
        dezenas = (i%100)/10;
        centenas = i/100;
        fputs(tabelaSeteSegmentos[unidades], arq_unidades);
        fputs(tabelaSeteSegmentos[dezenas], arq_dezenas);
        fputs(tabelaSeteSegmentos[centenas], arq_centenas);
        fputs("01\n", arq_sinal); // Preenche as últimas 128 posições de arq_sinal com sinal "-";
    }

    printf("Arquivos gerados com sucesso!");
    fclose(arq_unidades);
    fclose(arq_dezenas);
    fclose(arq_centenas);
    fclose(arq_sinal);

    return 0;
}