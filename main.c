#include <stdio.h>
#include <string.h>

typedef struct _Chave Chave;
    struct _Chave{
        char nis[14];
        char posicao[12];
};

    int compara(const void *e1, const void *e2)
{
    return strncmp(((Chave*)e1)->nis,((Chave*)e2)->nis, 14);
}

int main()
{
    FILE *f;
    Chave *e;
    long posicao, qtd;

    f = fopen("indice.txt","r");
    fseek(f,0,SEEK_END); /*no arq que o ponteiro aponta a partir do final avança 0 bytes*/
    posicao = ftell(f);
    qtd = posicao/sizeof(Chave);
    e = (Chave*) malloc(posicao);
    rewind(f); /*volta a cabeça de leitura para o inicio*/

    if(fread(e,sizeof(Chave),qtd,f) == qtd)
    {
        printf("Lido = OK\n");
    }

    fclose(f);

    qsort(e,qtd,sizeof(Chave),compara);
    printf("Ordenado = OK\n");

    f = fopen("indiceOrdenado.txt","w");
    fwrite(e,sizeof(Chave),qtd,f);

    fclose(f);

    printf("Escrito = OK\n");
    free(e);

    return 0;
}
