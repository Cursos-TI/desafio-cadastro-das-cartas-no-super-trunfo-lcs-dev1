#include <stdio.h>
#include <string.h>

void lerStringSeguramente(char *dest, int tamanho, const char *mensagem)
{
    while (1)
    {
        printf("%s", mensagem);
        if (fgets(dest, tamanho, stdin))
        {
            if (strchr(dest, '\n') == NULL)
            {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF)
                    ;
                printf("Texto muito longo! Máximo de %d caracteres.\n", tamanho - 1);
            }
            else
            {
                dest[strcspn(dest, "\n")] = 0;
                break;
            }
        }
    }
}

int lerInteiroSeguramente(const char *mensagem)
{
    int valor;
    while (1)
    {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1)
        {
            while (getchar() != '\n')
                ;
            return valor;
        }
        else
        {
            printf("Entrada inválida! Digite um número inteiro.\n");
            while (getchar() != '\n')
                ;
        }
    }
}

float lerFloatSeguramente(const char *mensagem)
{
    float valor;
    while (1)
    {
        printf("%s", mensagem);
        if (scanf("%f", &valor) == 1)
        {
            while (getchar() != '\n')
                ;
            return valor;
        }
        else
        {
            printf("Entrada inválida! Digite um número decimal.\n");
            while (getchar() != '\n')
                ;
        }
    }
}


typedef struct
{
    char codigo[9];
    char nome[50];
    unsigned long int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidadePopulacional;
    float pibPerCapita;
    float superPoder;
} Carta;

// ====================== NÍVEL NOVATO ======================
void cadastrarCarta(Carta *carta, int numero)
{
    printf("\nCadastro da Carta %d\n", numero);
    lerStringSeguramente(carta->codigo, sizeof(carta->codigo), "Código da cidade: ");
    lerStringSeguramente(carta->nome, sizeof(carta->nome), "Nome da cidade: ");
    carta->populacao = (unsigned long int)lerInteiroSeguramente("População: ");
    carta->area = lerFloatSeguramente("Área (km²): ");
    carta->pib = lerFloatSeguramente("PIB (em bilhões): ");
    carta->pontosTuristicos = lerInteiroSeguramente("Número de pontos turísticos: ");
}

// ====================== NÍVEL AVENTUREIRO ======================
void calcularAtributosDerivados(Carta *carta)
{
    carta->densidadePopulacional = carta->populacao / carta->area;
    carta->pibPerCapita = carta->pib / carta->populacao;
}

// ====================== NÍVEL MESTRE ======================
void calcularSuperPoder(Carta *carta)
{
    carta->superPoder = carta->populacao + carta->area + carta->pib + carta->pontosTuristicos +
                        carta->pibPerCapita + (1 / carta->densidadePopulacional);
}

void exibirCarta(const Carta *carta, int numero)
{
    printf("\n--- Carta %d ---\n", numero);
    printf("Código: %s\n", carta->codigo);
    printf("Nome: %s\n", carta->nome);
    printf("População: %lu\n", carta->populacao);
    printf("Área: %.2f km²\n", carta->area);
    printf("PIB: %.2f bilhões\n", carta->pib);
    printf("Pontos Turísticos: %d\n", carta->pontosTuristicos);
    printf("Densidade Populacional: %.2f hab/km²\n", carta->densidadePopulacional);
    printf("PIB per Capita: %.6f\n", carta->pibPerCapita);
    printf("Super Poder: %.6f\n", carta->superPoder);
}

// ====================== NÍVEL MESTRE ======================
void compararAtributo(double a, double b, const char *nome, int menorVence)
{
    printf("%s: ", nome);
    if ((menorVence && a < b) || (!menorVence && a > b))
        printf("Carta 1 venceu\n");
    else if ((menorVence && a > b) || (!menorVence && a < b))
        printf("Carta 2 venceu\n");
    else
        printf("Empate\n");
}

void compararCartas(const Carta *c1, const Carta *c2)
{
    printf("\n--- Comparações ---\n");

    compararAtributo((double)c1->populacao, (double)c2->populacao, "População", 0);
    compararAtributo((double)c1->area, (double)c2->area, "Área", 0);
    compararAtributo((double)c1->pib, (double)c2->pib, "PIB", 0);
    compararAtributo((double)c1->pontosTuristicos, (double)c2->pontosTuristicos, "Pontos Turísticos", 0);
    compararAtributo((double)c1->densidadePopulacional, (double)c2->densidadePopulacional, "Densidade Populacional (menor vence)", 1);
    compararAtributo((double)c1->pibPerCapita, (double)c2->pibPerCapita, "PIB per Capita", 0);
    compararAtributo((double)c1->superPoder, (double)c2->superPoder, "Super Poder", 0);
}

int main()
{
    Carta carta1, carta2;

    // ====================== NÍVEL NOVATO ======================
    cadastrarCarta(&carta1, 1);
    cadastrarCarta(&carta2, 2);

    // ====================== NÍVEL AVENTUREIRO ======================
    calcularAtributosDerivados(&carta1);
    calcularAtributosDerivados(&carta2);

    // ====================== NÍVEL MESTRE ======================
    calcularSuperPoder(&carta1);
    calcularSuperPoder(&carta2);

    exibirCarta(&carta1, 1);
    exibirCarta(&carta2, 2);

    // ====================== NÍVEL MESTRE ======================
    compararCartas(&carta1, &carta2);

    return 0;
}
