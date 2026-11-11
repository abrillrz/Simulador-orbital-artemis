/* Casos de prueba: valores calculados A MANO vs. resultado del programa. */
#include <stdio.h>
#include <math.h>
#include "orbita.h"

static int fallos = 0;

static void comprobar(const char *nombre, double obtenido, double esperado, double tol_rel) {
    double err = fabs(obtenido - esperado) / fabs(esperado);
    int ok = err < tol_rel;
    printf("  [%s] %-28s obtenido=%.4f esperado=%.4f (err rel=%.2e)\n",
           ok ? "OK" : "FALLA", nombre, obtenido, esperado, err);
    if (!ok) fallos++;
}

static void caso(const char *titulo, double h, double m,
                 double v_man, double T_man, double Fg_man, double ac_man) {
    DatosOrbita o;
    o.altitud = h;
    o.masa = m;
    printf("%s\n", titulo);
    if (!calcular_orbita(&o)) { printf("  [FALLA] datos invalidos\n"); fallos++; return; }
    comprobar("velocidad orbital [m/s]", o.velocidad, v_man, 1e-4);
    comprobar("periodo [s]", o.periodo_s, T_man, 1e-4);
    comprobar("periodo [min]", o.periodo_min, T_man / 60.0, 1e-4);
    comprobar("fuerza gravitatoria [N]", o.fuerza_grav, Fg_man, 1e-4);
    comprobar("aceleracion centripeta", o.aceleracion_centr, ac_man, 1e-4);
    if (!o.fuerzas_coinciden) { printf("  [FALLA] Fg != Fc\n"); fallos++; }
    else printf("  [OK]   Fg == Fc\n");
}

int main(void) {
    /* Caso 1: consigna (h = 192 km, m = 33000 kg) */
    caso("Caso 1: h = 192 km, m = 33000 kg", 192000.0, 33000.0,
         7792.95, 5291.52, 305362.1, 9.25340);

    /* Caso 2: h = 400 km, m = 33000 kg */
    caso("Caso 2: h = 400 km, m = 33000 kg", 400000.0, 33000.0,
         7672.32, 5545.06, 286889.3, 8.69361);

    printf("\nResultado: %s (%d fallos)\n", fallos == 0 ? "TODO OK" : "HAY FALLOS", fallos);
    return fallos != 0;
}
