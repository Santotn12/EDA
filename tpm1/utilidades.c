#include "utilidades.h"
#include <ctype.h>
#include <string.h>

void str_normalize(char* str)
{
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void str_normalize_copy(const char* src, char* dst)
{
    for (int i = 0; src[i]; i++) {
        dst[i] = tolower((unsigned char)src[i]);
    }
    dst[strlen(src)] = '\0';
}

int compararElectores(Elector e1, Elector e2)
{
    char n1[MAX_STR], n2[MAX_STR];
    char d1[MAX_STR], d2[MAX_STR];

    str_normalize_copy(e1.nombreApellido, n1);
    str_normalize_copy(e2.nombreApellido, n2);
    str_normalize_copy(e1.domicilio, d1);
    str_normalize_copy(e2.domicilio, d2);

    if (e1.circuito != e2.circuito) return 0;
    if (e1.dni != e2.dni) return 0;
    if (strcmp(n1, n2) != 0) return 0;
    if (strcmp(d1, d2) != 0) return 0;
    if (e1.codigoPostal != e2.codigoPostal) return 0;
    if (e1.mesa != e2.mesa) return 0;

    return 1; // Son id茅nticos
}

int procesarArchivoOperaciones(const char* nombreArchivo,
                               LSOBB* lsobb, LSOBB_F* lsobb_f,
                               ABB* abb, ABB_F* abb_f,
                               SistemaCostos* costos)
{
    FILE* fp = fopen(nombreArchivo, "r");
    if (!fp) {
        printf("Error: No se pudo abrir el archivo %s\n", nombreArchivo);
        return 0;
    }

    int operacion;
    while (fscanf(fp, "%d", &operacion) == 1) {
        if (operacion == 1) {
            // ALTA
            Elector elector;
            fscanf(fp, "%d", &elector.circuito);
            fscanf(fp, "%d", &elector.dni);
            fscanf(fp, " %50[^\n]", elector.nombreApellido);
            fscanf(fp, " %50[^\n]", elector.domicilio);
            fscanf(fp, "%d", &elector.codigoPostal);
            fscanf(fp, "%d", &elector.mesa);

            str_normalize(elector.nombreApellido);
            str_normalize(elector.domicilio);

            altaLSOBB(lsobb, elector, &costos->lsobb);
            altaLSOBB_F(lsobb_f, elector, &costos->lsobb_f);
            altaABB(abb, elector, &costos->abb);
            altaABB_F(abb_f, elector, &costos->abb_f);

        } else if (operacion == 2) {
            // BAJA
            Elector elector;
            fscanf(fp, "%d", &elector.circuito);
            fscanf(fp, "%d", &elector.dni);
            fscanf(fp, " %50[^\n]", elector.nombreApellido);
            fscanf(fp, " %50[^\n]", elector.domicilio);
            fscanf(fp, "%d", &elector.codigoPostal);
            fscanf(fp, "%d", &elector.mesa);

            str_normalize(elector.nombreApellido);
            str_normalize(elector.domicilio);

            bajaLSOBB(lsobb, elector, &costos->lsobb);
            bajaLSOBB_F(lsobb_f, elector, &costos->lsobb_f);
            bajaABB(abb, elector, &costos->abb);
            bajaABB_F(abb_f, elector, &costos->abb_f);

        } else if (operacion == 3) {
            // EVOCACI脫N (CONSULTA)
            int circuito, dni;
            fscanf(fp, "%d", &circuito);
            fscanf(fp, "%d", &dni);

            buscarLSOBB(lsobb, circuito, dni, NULL, &costos->lsobb);
            buscarElectorLSOBB_F(lsobb_f, circuito, dni, &costos->lsobb_f);
            buscarABB(*abb, circuito, dni, &costos->abb);
            buscarABB_F(*abb_f, circuito, dni, &costos->abb_f);
        }
    }

    fclose(fp);
    return 1;
}
