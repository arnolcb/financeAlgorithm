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
    int tiempo;
    int tipoTiempo;
    string moneda;

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

        periodos.push_back(0);
        pagos.push_back(0);
        intereses.push_back(0);
        amortizaciones.push_back(0);
        saldos.push_back(prestamo);

        for (int i = 1; i <= tiempo; i++)
        {
            periodos.push_back(i);
            
            interes = calcularInteres(prestamo, tasa, i);
            amortizacion = calcularAmortizacion(pago, interes);
            saldo = prestamo - amortizacion;

            prestamo = saldo;
            if (i == tiempo)
            {
                saldo = 0;
            }

            pagos.push_back(pago);
            intereses.push_back(interes);
            amortizaciones.push_back(amortizacion);
            saldos.push_back(saldo);
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

int main()
{
    double prestamo;
    double tasa;
    int tipoTasa;
    int tiempo;
    int tipoTiempo;
    string moneda;

    // Ingreso de datos
    cout << "\t Algoritmo"
         << "\n";
    cout << "Ingresa prestamo: ";
    cin >> prestamo;
    cout << "Ingresa tasa: ";
    cin >> tasa;
    cout << "Ingresa tipo de tasa"
         << "\n";
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

    double pago = 0;
    double interes = 0;
    double amortizacion = 0;
    double saldo = 0;

    tabladepagos tablaUser = tabladepagos(prestamo, pago, interes, amortizacion, saldo, tasa, tiempo, tipoTiempo, tipoTasa, moneda);

    tablaUser.asignar();
    tablaUser.mostrarTabla();

    return 0;
}