#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>

using namespace std;

vector<double> pagos;
vector<double> intereses;
vector<double> amortizaciones;
vector<double> saldos;
vector<double> tasas;
// vector<int> tiempos;
//  vector<int> tipoTiempos;
//  vector<int> tipoTasas;
vector<int> periodos;

double totalPagos;
double totalIntereses;
double totalAmortizaciones;

class tabladepagos
{
public:
    double prestamo;
    double pago;
    double interes;
    double amortizacion;
    double saldo;
    double tasa;
    int tipoTasa;
    int tiempo; //-> periodos
    int tipoTiempo;
    // int periodo;
    string moneda;
    // vector<string> monedas;

    tabladepagos(double _prestamo, double _pago, double _interes, double _amortizacion, double _saldo, double _tasa, int _tiempo, int _tipoTiempo, int _tipoTasa, string _moneda)
    {
        prestamo = _prestamo;
        pago = _pago;
        interes = _interes;
        amortizacion = _amortizacion;
        saldo = _saldo;
        tasa = _tasa;
        tiempo = _tiempo;
        tipoTiempo = _tipoTiempo;
        tipoTasa = _tipoTasa;
        moneda = _moneda;
    }

    double calcularPago(double saldo, double tasa, int tiempo)
    {
        double pago;
        pago = (saldo * tasa) / (1 - pow((1 + tasa), -tiempo));

        return pago;
    }

    double calcularInteres(double capital, double tasa, int tiempo)
    {
        double intr;
        intr = ((capital * (1 + tasa)) - capital);

        return intr;
    }

    double calcularAmortizacion(double pago, double interes)
    {
        double amortizacion;
        amortizacion = pago - interes;

        return amortizacion;
    }

    void asignar()
    {
        pago = calcularPago(prestamo, tasa, tiempo);
        // Periodo[0]: i == 0, pago = 0, interes = 0, amortizacion = 0, saldo = prestamo
        periodos.push_back(0);
        pagos.push_back(0);
        intereses.push_back(0);
        amortizaciones.push_back(0);
        saldos.push_back(prestamo);

        for (int i = 1; i <= tiempo; i++)
        {
            // hacer pushback a periodos
            periodos.push_back(i);
            
            /*if (i == 0)
            {
                pago = 0;
                interes = 0;
                amortizacion = 0;
                saldo = pago;
            }
            else if( i > 0 )
            {*/

            /* Debug
            cout << " " << endl;
            cout << "Antes de las funciones" << endl;
            cout << "iteracion " << i << endl;
            cout << "prestamo: " << prestamo << endl;
            cout << "pago: " << pago << endl;
            cout << "interes: " << interes << endl;
            cout << "tasa: " << tasa << endl;
            cout << "amortizacion: " << amortizacion << endl;
            cout << "saldo: " << saldo << endl;
            cout << "tiempo: " << tiempo << endl;
            */

            interes = calcularInteres(prestamo, tasa, i);
            amortizacion = calcularAmortizacion(pago, interes);
            saldo = prestamo - amortizacion;

            // actualizamos prestamos
            prestamo = saldo;
            if (i == tiempo)
            {
                saldo = 0;
            }

            /* Debug
            cout << "Despues de las funciones" << endl;
            cout << "pago: " << pago << endl;
            cout << "interes: " << interes << endl;
            cout << "tasa: " << tasa << endl;
            cout << "amortizacion: " << amortizacion << endl;
            cout << "saldo: " << saldo << endl;
            cout << "-------------" << endl;*/

            //}

            // pushback
            pagos.push_back(pago);
            intereses.push_back(interes);
            amortizaciones.push_back(amortizacion);
            saldos.push_back(saldo);

            // cout << "Periodo: " << periodos[i]<< "\n";
            // cout << "Pago: " << pagos[i] << "\n";
            // cout << "Interes: " << intereses[i] << "\n";
            // cout << "Amortizacion: " << amortizaciones[i] << "\n";
            // cout << "Saldo: " << saldos[i] << "\n";
        }
    }

    void mostrarTabla()
    {
        cout << "" << endl;
        cout << "\tTabla de pagos" << endl;
        cout << "" << endl;
        cout << "Periodo"
             << "\t"
             << "Pago"
             << "\t"
             << "Interes"
             << "\t"
             << "Amortizacion"
             << "\t"
             << "Saldo"
             << "\n";
        for (int i = 0; i < periodos.size(); i++)
        {
            cout << periodos[i] << "\t" << pagos[i] << "\t" << intereses[i] << "\t" << amortizaciones[i] << "\t" << saldos[i] << "\n";
            // calcular los totales
            totalPagos += pagos[i];
            totalIntereses += intereses[i];
            totalAmortizaciones += amortizaciones[i];
        }

        // Mostrar totales
        cout << "\n";
        cout << "Total"
             << "\t" << totalPagos << "\t" << totalIntereses << "\t" << totalAmortizaciones << "\t" << "---" << "\n";
    }
};

/*
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
*/

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

    /*
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
    */

    double pago = 0;
    double interes = 0;
    double amortizacion = 0;
    double saldo = 0;
    // Crear tabladepagos TablaUser
    tabladepagos tablaUser = tabladepagos(prestamo, pago, interes, amortizacion, saldo, tasa, tiempo, tipoTiempo, tipoTasa, moneda);

    // Asignar valores a la tabla
    tablaUser.asignar();

    // Mostrar tabla
    tablaUser.mostrarTabla();

    return 0;
}