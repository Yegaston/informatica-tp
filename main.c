#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CantidadDeDiasEnMes 31
#define CantidadDeMeses 12
#define LocalidadStringCharacters 26
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

} traslados;

void carga(struct Traslados traslados[CantidadDeMeses][CantidadDeDiasEnMes]);

bool validateYear(int year);

int main()
{
    bool menuFull = false;
    struct Traslados traslado[CantidadDeMeses][CantidadDeDiasEnMes];

    carga(traslado);

    return 0;
}

void carga(struct Traslados traslado[CantidadDeMeses][CantidadDeDiasEnMes])
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
                traslado[dia][mes].accion = accion;
                traslado[dia][mes].anoDelTraslado = anal;
                traslado[dia][mes].cantidadDeAdultos = adultos;
                traslado[dia][mes].cantidadDeMenores = menores;
                traslado[dia][mes].ciudadDelDestino[LocalidadStringCharacters] = localidad;
                traslado[dia][mes].diaDelTraslado = dia;
                traslado[dia][mes].mesDelTraslado = mes;
                traslado[dia][mes].numeroDeColectivo = colectivo;
                printf("%i %i %i %i %s %i %i %i \n", dia, mes, anal, colectivo, localidad, accion, adultos, menores);
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
