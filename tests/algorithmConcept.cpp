#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>

using namespace std;

void igualartiempos(int tiempo, int tipoTiempo, double tasa, int tipoTasa)
{

    if (tipoTiempo == 1)
    {
        if (tipoTasa == 2)
        {
            // Tasa mensual a anual
            tasa = pow((1 + tasa), 12) - 1;
        }
        else if (tipoTasa == 3)
        {
            // Tasa diaria a anual
            tasa = pow((1 + tasa), 365) - 1;
        }
    }

    else if (tipoTiempo == 2)
    {
        if (tipoTasa == 1)
        {
            // Tasa anual a mensual
            tasa = pow((1 + tasa), 1 / 12) - 1;
        }
        else if (tipoTasa == 3)
        {
            // Tasa diaria a mensual
            tasa = pow((1 + tasa), 30) - 1;
        }
    }

    else if (tipoTiempo == 3)
    {
        if (tipoTasa == 1)
        {
            // Tasa anual a diaria
            tasa = pow((1 + tasa), 1 / 365) - 1;
        }
        else if (tipoTasa == 2)
        {
            // Tasa mensual a diaria
            tasa = pow((1 + tasa), 1 / 30) - 1;
        }
    }
}

// Funcion principal
double pago(double saldo, double tasa, int tiempo)
{
    double pago;
    pago = (saldo * tasa) / (1 - pow((1 + tasa), -tiempo));

    return pago;
}

double interes(double capital, double tasa, int tiempo)
{
    double interes;
    interes = ((capital * (1 + tasa)) - capital);

    return interes;
}

double amortizacion(double pago, double interes)
{
    double amortizacion;
    amortizacion = pago - interes;

    return amortizacion;
}

int main()
{
    // Declaracion de variables
    double prestamo;
    double tasa;
    int tipoTasa;
    int tiempo; //-> periodos
    int tipoTiempo;
    string moneda;

    // Ingreso de datos
    cout << "\t Algoritmo"
         << "\n";
    cout << "Ingresa prestamo: ";
    cin >> prestamo;
    // cout << "Ingresa numero de cuotas:"; cin >> numCuotas;
    cout << "Ingresa tasa: ";
    cin >> tasa;
    cout << "Ingresa tipo de tasa"
         << "\n";
    // cout << "1.Tasa Nominal" << "2. Tasa Efectiva"; cin >> tipoTasa;
    cout << "1. Anual"
         << "\n"
         << "2. Mensual"
         << "\n"
         << "3. Diaria"
         << "\n";
    cin >> tipoTasa;
    cout << "Ingresa tiempo: ";
    cin >> tiempo;
    cout << "Ingresa tipo de tiempo"
         << "\n";
    cout << "1. A" << char(164) << "os"
         << "\n"
         << "2. Meses"
         << "\n"
         << "3. Dias"
         << "\n";
    cin >> tipoTiempo;
    cout << "Ingresa tipo de moneda: ";
    cin >> moneda;

    // Igualar tiempos
    igualartiempos(tiempo, tipoTiempo, tasa, tipoTasa);

    // Calcular pagos
    double pagoUser = pago(prestamo, tasa, tiempo);
    cout << "El pago es: " << pagoUser << " " << moneda << "\n";

    // Calcular intereses
    double interesUser = interes(prestamo, tasa, tiempo);
    cout << "El interes es: " << interesUser << " " << moneda << "\n";

    // Calcular amortizacion
    double amortizacionUser = amortizacion(pagoUser, interesUser);
    cout << "La amortizacion es: " << amortizacionUser << " " << moneda << "\n";

    return 0;
}