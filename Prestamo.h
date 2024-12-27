#ifndef SIMULADOR_BANCO_C___PRESTAMO_H
#define SIMULADOR_BANCO_C___PRESTAMO_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

class Prestamo{
    string p_fecha,p_estado;
    int p_plazo,p_diaRespaldo,p_interes;
    float p_cuota,p_monto,p_deuda;
public:
    Prestamo(){};
    Prestamo(string fecha,float monto,int plazo,int interes){
        p_fecha=fecha, p_monto=monto, p_plazo=plazo, p_interes=interes;
        p_diaRespaldo = stoi(p_fecha.substr(0, 2));
        p_deuda=p_monto*(1+p_interes/100.0);
    }
    ~Prestamo(){};

    void calcularCuotaMensualInteres(int monto,int plazo,float interes){
        float cuotaMensual,interesMensual=interes/100.0;
        cuotaMensual=monto*(interesMensual+1)/plazo;
        p_cuota=cuotaMensual;
    }
    void estadoPrestamoActivoInactivo() {
        // Primero, reduce la deuda por el monto de la cuota.
        p_deuda -= p_cuota;

        // Luego, verifica si la deuda restante es mayor que 0 para determinar el estado.
        if (p_deuda > 0) {
            p_estado = "Activo";
        } else {
            p_estado = "Finalizado";
            p_deuda = 0; // Asegura que la deuda no quede en un valor negativo.
        }
    }

    void fechaDePagoMensualSiguiente(){
        string fecha;

        int dia = stoi(p_fecha.substr(0, 2));
        int mes = stoi(p_fecha.substr(3, 2));
        int anio = stoi(p_fecha.substr(6, 4));

        dia=p_diaRespaldo;

        if (anio % 4 == 0) { // Año bisiesto
            if (mes == 1) { // Modificar valor de día cuando es Enero para ajustarlo al siguiente mes de Febrero
                if (dia > 28) {
                    dia = 29;
                }
            }
        }
        else {
            if (mes == 1) { //Lo mismo de arriba pero cuando es un año común no bisiesto
                if (dia > 27) {
                    dia = 28;
                }
            }
        }
        // Aumentar el mes y ajustar el día si es necesario
        mes++;
        if (mes > 12) { // Si el mes es diciembre, incrementar el año y establecer el mes en enero
            mes = 1;
            anio++;
        }

        // Ajustar el día si es necesario
        if (dia > 30 && (mes == 4 || mes == 6 || mes == 9 || mes == 11)) {
            dia = 30;
        }


        if(mes<10 && dia<10)
            fecha="0"+to_string(dia)+"/0"+to_string(mes)+"/"+to_string(anio);
        else if(mes<10)
            fecha=to_string(dia)+"/0"+to_string(mes)+"/"+to_string(anio);
        else if(dia<10)
            fecha="0"+to_string(dia)+"/"+to_string(mes)+"/"+to_string(anio);
        else
            fecha=to_string(dia)+"/"+to_string(mes)+"/"+to_string(anio);
        p_fecha=fecha;
    }
    void cancelarPrestamo() {
        p_estado = "Cancelado";
        p_deuda = 0.0;
        // Aquí puedes agregar más lógica si es necesario, como registrar la fecha de cancelación.
    }
    void mostrarCronogramaPagos() const {
        cout << "Cronograma de pagos para el préstamo:" << endl;
        for (int i = 1; i <= p_plazo; ++i) {
            cout << "Pago " << i << ": " << p_cuota << " (Estado: Pendiente)" << endl;
            // Nota: este ejemplo asume que todos los pagos están pendientes y usa un valor constante para la cuota.
            // Deberás ajustar esta lógica según cómo manejes los pagos y sus estados en tu aplicación.
        }
    }

    float getCuota(){return p_cuota;}
    string getEstado(){return p_estado;}
    float getDeuda(){return p_deuda;}
    string getFecha() const { return p_fecha; }
    float getMonto() const { return p_monto; }
    int getPlazo() const { return p_plazo; }
    string getInteres() const { return to_string(p_interes) + "%"; }
    string getEstado() const { return p_estado; }
    float getCuota() const { return p_cuota; }
    float getDeuda() const { return p_deuda; }



};

#endif //SIMULADOR_BANCO_C___PRESTAMO_H
