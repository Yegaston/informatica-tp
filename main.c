#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define CantidadDeDiasEnMes 31
#define CantidadDeMeses 12
#define LocalidadStringCharacters 26
#define PrecioDeViajeMayores 500
#define PrecioDeViajeMenores 300

struct Traslados
{
    int diaDelTraslado;
    int mesDelTraslado;
    int anoDelTraslado;
    int numeroDeColectivo;
    char ciudadDelDestino[LocalidadStringCharacters];
    int accion;
    int cantidadDeAdultos;
    int cantidadDeMenores;

} traslado[CantidadDeMeses][CantidadDeDiasEnMes];

void inicialidorDeRegistro();

void carga();

bool validateYear(int year);

bool validateMonth(int mes);

void CostosXMes();

char Mayor();

void cleanBuffer();

int main()
{
    bool menuFull = false;
    // struct Traslados ;
    inicialidorDeRegistro();

    carga();

    // CostosXMes();

    Mayor();
    return 0;
}

void inicialidorDeRegistro()
{
    for (int i = 0; i < CantidadDeMeses; i++)
    {
        for (int j = 0; j < CantidadDeDiasEnMes; j++)
        {
            traslado[i][j].accion = 0;
            traslado[i][j].anoDelTraslado = 0;
            traslado[i][j].cantidadDeAdultos = 0;
            traslado[i][j].cantidadDeMenores = 0;
            strcpy(traslado[i][j].ciudadDelDestino, "");
            traslado[i][j].diaDelTraslado = 0;
            traslado[i][j].mesDelTraslado = 0;
            traslado[i][j].numeroDeColectivo = 0;
        }
    }
}
void carga()
{
    int ano, dia, mes, anal, colectivo, accion, adultos, menores;
    char localidad[LocalidadStringCharacters];
    // Input year want charge data.

    printf("Ingrese el año sobre el que desea realizar la carga. \n");
    scanf("%i", &ano);

    if (validateYear(ano))
    {
        printf("Access confirm\n");

        FILE *fp;

        fp = fopen("reservas.txt", "r"); // read mode

        // Capturing err
        if (fp == NULL)
        {
            perror("Error while opening the file.\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Comenzado la carga.\n");
        }

        while (!feof(fp))
        {

            fscanf(fp, "%i %i %i %i %s %i %i %i", &dia, &mes, &anal, &colectivo, localidad, &accion, &adultos, &menores);

            if (anal == ano)
            {
                traslado[mes][dia].accion = accion;
                traslado[mes][dia].anoDelTraslado = anal;
                traslado[mes][dia].cantidadDeAdultos = adultos;
                traslado[mes][dia].cantidadDeMenores = menores;
                strcpy(traslado[mes][dia].ciudadDelDestino, localidad);
                traslado[mes][dia].diaDelTraslado = dia;
                traslado[mes][dia].mesDelTraslado = mes;
                traslado[mes][dia].numeroDeColectivo = colectivo;
                if (traslado[mes][dia].diaDelTraslado != 0)
                {
                    printf("%i %i %i %i %s %i %i %i \n", traslado[mes][dia].diaDelTraslado, traslado[mes][dia].mesDelTraslado, traslado[mes][dia].anoDelTraslado, traslado[mes][dia].numeroDeColectivo, traslado[mes][dia].ciudadDelDestino, traslado[mes][dia].accion, traslado[mes][dia].cantidadDeAdultos, traslado[mes][dia].cantidadDeMenores);
                }
            }
        }

        fclose(fp);
    }
    else
    {
        printf("Access denied\n");
    }
}

bool validateYear(int year)
{
    if (year < 2020 && year > 2016)
    {
        return true;
    }
    else
    {
        return true;
    }
}

void CostosXMes()
{
    int mes, ano;
    float cantApagar = 0;
    char mesesArray[12][10], nombreDelArchivo[50], anoString[6];

    // Array con los nombres de cada mes. ¡Abra alguna manera mas eficiente de hacer esta mierda?

    strcpy(mesesArray[0], "Enero");
    strcpy(mesesArray[1], "Febrero");
    strcpy(mesesArray[2], "Marzo");
    strcpy(mesesArray[3], "Abril");
    strcpy(mesesArray[4], "Mayo");
    strcpy(mesesArray[5], "Junio");
    strcpy(mesesArray[6], "Julio");
    strcpy(mesesArray[7], "Agosto");
    strcpy(mesesArray[8], "Septiembre");
    strcpy(mesesArray[9], "Octubre");
    strcpy(mesesArray[10], "Noviembre");
    strcpy(mesesArray[11], "Diciembre");

    printf("Ingrese un mes.\n");
    scanf("%i", &mes);
    while (validateMonth(mes) != true)
    {
        printf("Mes invalido\n");
        printf("Ingrese nuevamente un mes.\n");
        scanf("%i", &mes);
    }

    for (int i = 0; i < CantidadDeMeses; i++)
    {
        for (int j = 0; j < CantidadDeDiasEnMes; j++)
        {
            if (traslado[i][j].mesDelTraslado == mes && traslado[i][j].diaDelTraslado != 0)
            {
                printf("Depurando mesDelTraslado: %i\n", traslado[i][j].mesDelTraslado);
                printf("Depurando diaDelTraslado: %i\n", traslado[i][j].diaDelTraslado);

                cantApagar += (traslado[i][j].cantidadDeAdultos * PrecioDeViajeMayores) + (traslado[i][j].cantidadDeMenores * PrecioDeViajeMenores);
                ano = traslado[i][j].anoDelTraslado;
            }
        }
    }
    printf("Cantidad a pagar %f\n", cantApagar);

    FILE *fp;
    cleanBuffer();
    fseek(stdin, 0, SEEK_END);
    strcpy(nombreDelArchivo, "");
    strcat(nombreDelArchivo, "ventas_");
    strcat(nombreDelArchivo, mesesArray[mes - 1]);
    strcat(nombreDelArchivo, "_");
    sprintf(anoString, "%d", ano);
    strcat(nombreDelArchivo, anoString);
    strcat(nombreDelArchivo, ".txt");

    fp = fopen(nombreDelArchivo, "w");
    fprintf(fp, "La cantidad a pagar del mes %s es: %f$\n", mesesArray[mes - 1], cantApagar);
}

char Mayor()
{
    int traffics[12], aux, mes;
    char res[100];
    printf("Ingrese el mes que deseas analizar.\n");
    scanf("%i", &mes);
    while (validateMonth(mes) == false)
    {
        printf("Mes invalid, ingrese nuevamente \n");
    }

    for (int i = 0; i < 12; i++)
        traffics[i] = 0;

    for (int i = 0; i < CantidadDeMeses; i++)
    {
        for (int j = 0; j < CantidadDeDiasEnMes; j++)
        {
            if (traslado[i][j].mesDelTraslado == mes && traslado[i][j].diaDelTraslado != 0)
            {
                traffics[traslado[i][j].numeroDeColectivo] += traslado[i][j].cantidadDeAdultos + traslado[i][j].cantidadDeMenores;
            }
        }
    }

    for (int i = 0; i < 12; i++)
        printf("Traffic %i: %i\n", i, traffics[i]);

    {
        /* code */
    }
    
}

bool validateMonth(int mes)
{
    if (mes >= 1 && mes <= 12)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void cleanBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}