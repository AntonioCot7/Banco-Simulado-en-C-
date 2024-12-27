#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <map>
#include "Prestamo.h"
#include <cctype>
using namespace std;

map<int, vector<Prestamo>> prestamosPorCliente;

void menu();
bool validarDNI(const string& dni) {
    if (dni.length() != 8) {
        return false; // Verificar que tenga exactamente 8 caracteres
    }
    for (char c : dni) {
        if (!isdigit(c)) {
            return false; // Verificar que todos los caracteres sean dígitos
        }
    }
    return true; // El DNI es válido
}
class Datos_Cliente {
private:
    int dni;
    string nombre;
    int fecha;

public:
    Datos_Cliente(int _dni, string _nombre, int _fecha) {
        dni = _dni;
        nombre = _nombre;
        fecha = _fecha;
    }

    int getDni() const { return dni; }
    string getNombre() const { return nombre; }
    int getFecha() const { return fecha; }
};

class AgregarCliente_BuscarCliente {
private:
    vector<Datos_Cliente*> datos_cliente;
public:
    void agregarCliente(Datos_Cliente *datos) {
        bool cliente_existente = false;
        for (size_t i = 0; i < datos_cliente.size(); ++i) {
            if (datos_cliente[i]->getDni() == datos->getDni()) {
                cliente_existente = true;
                break;
            }
        }
        if (!cliente_existente) {
            datos_cliente.push_back(datos);
        }
    }
    void mostrar_DatosCliente() {
        ofstream listaClientes("../ListaDeClientes.txt", ios::app);

        for (size_t i = 0; i < datos_cliente.size(); ++i) {
            Datos_Cliente *cliente = datos_cliente[i];
            listaClientes << "---CLIENTE " << "(" << cliente->getNombre() << ")---" << endl;
            listaClientes << "DNI: " << cliente->getDni() << endl;
            listaClientes << "Nombre: " << cliente->getNombre() << endl;
            listaClientes << "Fecha de Nacimiento: " << cliente->getFecha() << endl;
            listaClientes << endl;
        }
        listaClientes.close();
    }
    /*
     int buscarClientePorDNI(const string &dni){
        ifstream archivo("../ListaDeClientes.txt");
        string linea;
        int contador=0;
        while(getline(archivo,linea)) {
            // string::npos es lo que retorna find() sino logra encontrar la cadena
            if(linea.find("DNI: " + dni) !=string::npos){
                archivo.close();
                return contador;
            }
            contador++;
        }
        archivo.close();
        return -1;
    }
     */
    int buscarClientePorDNI(const string &dni) {
        for (int i = 0; i < datos_cliente.size(); ++i) {
            if (to_string(datos_cliente[i]->getDni()) == dni) {
                return i; // Retorna la posición del cliente en el vector
            }
        }
        return -1; // Retornar un valor que indique que el cliente no fue encontrado
    }
    void imprimirDatosCliente(int indice) {
        ifstream archivo("../ListaDeClientes.txt");
        string linea;
        int contador=0;
        while(getline(archivo,linea)) {
            if(contador==indice){
                cout<<endl;
                for(int i=0;i<4;i++){
                    cout<<linea<<endl;
                    getline(archivo,linea); // Avazar a la siguiente linea
                }
                cout<<endl;
                break;
            }
            contador++;
        }
        archivo.close();
    }
    void eliminarCliente(int dni) {
        auto it = remove_if(datos_cliente.begin(), datos_cliente.end(), [dni](Datos_Cliente *cliente) {
            return cliente->getDni() == dni;
        });

        // Eliminar los elementos removidos
        if (it != datos_cliente.end()) {
            for (auto itr = it; itr != datos_cliente.end(); ++itr) {
                delete *itr; // Liberar memoria del cliente eliminado
            }
            datos_cliente.erase(it, datos_cliente.end());
            cout << "Cliente eliminado con éxito." << endl;
        } else {
            cout << "Cliente no encontrado." << endl;
        }
    }

};

string obtenerMesYAnioTarjeta() {
    // Obtener el tiempo actual
    time_t now = time(0);
    tm *ltm = localtime(&now);
    // Obtener el mes y el año
    int mes = 1 + ltm->tm_mon;
    int anio = 1900 + ltm->tm_year;
    anio = (anio % 100)+5; // Las 2 ultimas cifras
    string _mes;
    if (mes<10){
        _mes= "0"+to_string(mes);
    }
    string resultado = _mes + "/" + to_string(anio);
    return resultado;
}

string TarjetaDeDebito() {
    string cadena;
    srand(time(0));
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cadena += to_string(rand() % 10);
        }
        if (i < 3) {cadena += "-";}
    }
    return cadena;
}

string NumeroDeCuenta(){
    string cadena = "";
    for (int i = 0; i < 4; ++i) {
        cadena += to_string(rand() % 10);
    }
    cadena += "-";
    for (int i = 0; i < 6; ++i) {
        cadena += to_string(rand() % 10);
    }
    return cadena;
}

class CuentaAhorro {
private:
    string NumCuenta;
    string MesYAnio;
    string TarjetaDebito;
    int dni_cliente;
    double saldo;
    string activa;
public:
    CuentaAhorro(int dni) : dni_cliente(dni), saldo(0.0),  activa("Activa") {}

    void setNumeroDeCuenta(){NumCuenta=NumeroDeCuenta();}
    string getNumeroDeCuenta() const {return NumCuenta;} // Marcar como const

    void setTarjetaDebito(){TarjetaDebito=TarjetaDeDebito();}
    string getTarjetaDebito() const {return TarjetaDebito;} // Marcar como const

    void setMesYAnio(){MesYAnio=obtenerMesYAnioTarjeta();}
    string getMesYAnio() const {return MesYAnio;} // Marcar como const

    void depositar(double monto) {
        if(activa=="Activa" and monto > 0) {
            saldo += monto;
        } else {
            cout << "\nOperación inválida." << endl;
        }
    }

    void retirar(double monto) {
        if(activa=="Activa" and monto <= saldo and monto > 0) {
            saldo -= monto;
        } else {
            cout << "\nOperación inválida." << endl;
        }
    }

    double consultarSaldo() const { // Marcar como const
        if(activa=="Activa") {
            return saldo;
        } else {
            return 0.0;
        }
    }
    void cancelarCuenta() {
        activa = "Cancelada"; // Cambia el estado de la cuenta a "Cancelada"
        TarjetaDebito = "Invalidada"; // Invalida la tarjeta de débito
    }
    string esEstado() const { return activa; } // Marcar como const
    void desactivarCuenta() { activa = "Inactivo"; }
    int getDniCliente() const { return dni_cliente; } // Marcar como const
};


AgregarCliente_BuscarCliente agregarClienteObjeto; // Mantener una instancia única de AgregarCliente
map<int, vector<CuentaAhorro>> cuentasPorCliente; // Vector para almacenar cuentas de ahorro
void eliminarCuentasYPréstamos(int dni) {
    // Eliminar cuentas de ahorro
    auto itCuentas = cuentasPorCliente.find(dni);
    if (itCuentas != cuentasPorCliente.end()) {
        cuentasPorCliente.erase(itCuentas);
        cout << "Cuentas de ahorro eliminadas con éxito." << endl;
    }

    // Eliminar préstamos
    auto itPrestamos = prestamosPorCliente.find(dni);
    if (itPrestamos != prestamosPorCliente.end()) {
        prestamosPorCliente.erase(itPrestamos);
        cout << "Préstamos eliminados con éxito." << endl;
    }
}
// Declaración de funciones
int Clientes(int &opcion);
void gestionarClientes(int opcion);
void cancelarCuentaDeAhorro();

// Implementación de funciones

int Clientes(int &opcion) {
    do {
        cout << "---Clientes---" << endl;
        cout << "1.1 Buscar Cliente" << endl;
        cout << "1.2 Agregar Cliente" << endl;
        cout << "1.3 Eliminar Cliente" << endl;
        cout << "1.4 Regresar" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        cout << endl;
    } while (opcion < 1 or opcion > 4);
    return opcion;
}

void gestionarClientes(int opcion) {
    switch (opcion) {
        case 1: {
            // Buscar cliente
            int dni_buscar;
            cout << "---Buscar cliente---" << endl;
            cout << "Ingresar DNI: ";
            cin >> dni_buscar;

            // Mostrar cuentas de ahorro
            bool encontrado = false;
            if (cuentasPorCliente.find(dni_buscar) != cuentasPorCliente.end()) {
                encontrado = true;
                cout << "====" << endl << "Servicios" << endl;
                for (const auto& cuenta : cuentasPorCliente[dni_buscar]) {
                    cout << "Cuenta de ahorro: " << cuenta.getNumeroDeCuenta() << " Monto S/: " << fixed << setprecision(2) << cuenta.consultarSaldo() << " " << cuenta.esEstado() << endl;
                    cout << "Tarjeta débito asociada: " << cuenta.getTarjetaDebito() << " Venc: " << cuenta.getMesYAnio() << endl;
                }
            }

            // Mostrar préstamos
            if (prestamosPorCliente.find(dni_buscar) != prestamosPorCliente.end()) {
                if (!encontrado) {
                    cout << "====" << endl << "Servicios" << endl;
                    encontrado = true;
                }
                cout << "Préstamos:" << endl;
                for (const auto& prestamo : prestamosPorCliente[dni_buscar]) {
                    cout << "Fecha: " << prestamo.getFecha() << " Monto S/: " << prestamo.getMonto() << " Nro Cuota S/: " << prestamo.getCuota() << " Interés: " << prestamo.getInteres() << " Estado: " << prestamo.getEstado() << endl;
                }
            } else if (!encontrado) {
                cout << "No hay servicios registrados para este cliente." << endl;
            }
            break;
        }
        case 2: { // Opción para agregar un nuevo cliente
            string dni_agregar;
            string nombre;
            long int f_nacimiento;
            cout << "---Agregar cliente---" << endl;
            cout << "Ingresar DNI: ";
            cin >> dni_agregar;
            // Validar el DNI ingresado
            if (!validarDNI(dni_agregar)) {
                cout << "El DNI ingresado no es válido. Asegúrese de que tenga 8 dígitos y solo contenga números." << endl;
                break; // Salir del caso si el DNI no es válido
            }
            long int dni_numerico = stol(dni_agregar); // Convertir DNI a número
            cin.ignore();
            cout << "Ingresar Nombre: ";
            getline(cin, nombre);
            cout << "Ingresar Fecha Nacimiento: ";
            cin >> f_nacimiento;

            Datos_Cliente *cliente = new Datos_Cliente(dni_numerico, nombre, f_nacimiento);
            agregarClienteObjeto.agregarCliente(cliente);
            agregarClienteObjeto.mostrar_DatosCliente();
            cout << endl << "Cliente Registrado" << endl;
            cout << endl;
            menu(); // Volver al menú principal después de agregar un cliente
            break;
        }
        case 3:{ // Cambia este caso para manejar la eliminación de clientes
            int dni_eliminar;
            cout << "---Eliminar cliente---" << endl;
            cout << "Ingresar DNI del cliente a eliminar: ";
            cin >> dni_eliminar;
            agregarClienteObjeto.eliminarCliente(dni_eliminar);
            eliminarCuentasYPréstamos(dni_eliminar); // Asegúrate de que esta función esté definida correctamente
            cout << "Cliente y sus datos relacionados eliminados con éxito." << endl;
            break;
        }

        case 4:
            menu();
            break;
    }
}

void gestionarCuentasDeAhorro() {
    int opcion = 0;
    do {
        cout << "---Cuentas de Ahorro---\n";
        cout << "1. Crear Cuenta de Ahorro\n";
        cout << "2. Realizar Depósito\n";
        cout << "3. Realizar Retiro\n";
        cout << "4. Consultar Saldo\n";
        cout << "5. Cancelar cuenta \n";
        cout << "6. Regresar\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cout << "\n---Crear Cuenta de Ahorro---" << endl;
                int dni_cliente;
                cout << "Ingresar DNI del Cliente: ";
                cin >> dni_cliente;

                CuentaAhorro nuevaCuenta(dni_cliente);
                nuevaCuenta.setNumeroDeCuenta();
                nuevaCuenta.setTarjetaDebito();
                nuevaCuenta.setMesYAnio();
                cuentasPorCliente[dni_cliente].push_back(nuevaCuenta);
                cout << "\nCuenta de ahorro creada exitosamente." << endl;
                cout << "Su numero de cuenta es "<<nuevaCuenta.getNumeroDeCuenta()<<endl;
                cout << "Ahora su nueva targeta es "<<nuevaCuenta.getTarjetaDebito()<<endl;
                cout << "Y la targeta tiene un fecha de vencimiento el "<<nuevaCuenta.getMesYAnio()<<endl;
                cout << "\nPresiona Enter para continuar...\n";cin.get();
                cin.get();
                gestionarCuentasDeAhorro();
                break;
            }
            case 2: {
                cout << "\n---Realizar Depósito---" << endl;
                int dni_cliente;
                cout << "Ingresar DNI del Cliente: ";
                cin >> dni_cliente;

                if (cuentasPorCliente.find(dni_cliente) == cuentasPorCliente.end()) {
                    cout << "No se encontraron cuentas para el DNI proporcionado." << endl;
                    gestionarCuentasDeAhorro();
                    break;
                }
                string NumCuenta;
                string Tarjeta;
                // Mostrar todas las cuentas del cliente
                cout << "Tarjetas encontradas:" << endl;
                for (int i = 0; i < cuentasPorCliente[dni_cliente].size(); ++i) {
                    NumCuenta=cuentasPorCliente[dni_cliente][i].getNumeroDeCuenta();
                    Tarjeta=cuentasPorCliente[dni_cliente][i].getTarjetaDebito();
                    cout << i + 1 << ". Saldo de la tarjeta " << Tarjeta << " de la cuenta "<<NumCuenta<<" : "<< cuentasPorCliente[dni_cliente][i].consultarSaldo() << endl;
                }

                int indiceCuenta;
                do {
                    cout << "Seleccione la tarjeta con la que desea realizar el depósito: ";
                    cin >> indiceCuenta;
                    if (indiceCuenta < 1 or indiceCuenta > cuentasPorCliente[dni_cliente].size()) {
                        cout << "Selección inválida; intente de nuevo." << endl;
                    }
                } while (indiceCuenta < 1 or indiceCuenta > cuentasPorCliente[dni_cliente].size());

                // Ajuste para índice basado en 0
                indiceCuenta -= 1;

                double monto;
                cout << "\nIngrese el monto a depositar: ";
                cin >> monto;
                cuentasPorCliente[dni_cliente][indiceCuenta].depositar(monto);
                cout << "Se deposito correctamente S/" << monto << endl;
                cout << "Presiona Enter para continuar...\n";cin.get();
                cin.get();
                gestionarCuentasDeAhorro();
                break;
            }
            case 3: {
                cout << "\n---Realizar Retiro---" << endl;
                int dni_cliente;
                cout << "Ingresar DNI del Cliente: ";
                cin >> dni_cliente;

                if (cuentasPorCliente.find(dni_cliente) == cuentasPorCliente.end()) {
                    cout << "No se encontraron cuentas para el DNI proporcionado." << endl;
                    gestionarCuentasDeAhorro();
                    break;
                }
                string NumCuenta;
                string Tarjeta;
                // Mostrar todas las cuentas del cliente
                cout << "Tarjetas encontradas:" << endl;
                for (int i = 0; i < cuentasPorCliente[dni_cliente].size(); ++i) {
                    NumCuenta=cuentasPorCliente[dni_cliente][i].getNumeroDeCuenta();
                    Tarjeta=cuentasPorCliente[dni_cliente][i].getTarjetaDebito();
                    cout << i + 1 << ". Saldo de la tarjeta " << Tarjeta << " de la cuenta "<<NumCuenta<<" : "<< cuentasPorCliente[dni_cliente][i].consultarSaldo() << endl;
                }

                int indiceCuenta;
                do {
                    cout << "Seleccione la tarjeta de la que desea realizar el retiro: ";
                    cin >> indiceCuenta;
                    if (indiceCuenta < 1 or indiceCuenta > cuentasPorCliente[dni_cliente].size()) {
                        cout << "Selección inválida; intente de nuevo" << endl;
                    }
                } while (indiceCuenta < 1 or indiceCuenta > cuentasPorCliente[dni_cliente].size());

                // Ajuste para índice basado en 0
                indiceCuenta -= 1;

                double monto;
                cout << "\nIngrese el monto a retirar: ";
                cin >> monto;
                cuentasPorCliente[dni_cliente][indiceCuenta].retirar(monto);
                cout << "Se retiro correctamente S/" << monto << endl;
                cout << "Presiona Enter para continuar...\n";cin.get();
                cin.get();
                gestionarCuentasDeAhorro();
                break;
            }
            case 4: {
                cout << "\n---Consultar Saldo---" << endl;
                int dni_cliente;
                cout << "Ingresar DNI del Cliente: ";
                cin >> dni_cliente;

                if (cuentasPorCliente.find(dni_cliente) == cuentasPorCliente.end()) {
                    cout << "No se encontraron cuentas para el DNI proporcionado." << endl;
                    gestionarCuentasDeAhorro();
                    break;
                }
                string NumCuenta;
                string Tarjeta;
                // Mostrar todas las cuentas del cliente
                cout << "Tarjetas encontradas:" << endl;
                for (int i = 0; i < cuentasPorCliente[dni_cliente].size(); ++i) {
                    NumCuenta=cuentasPorCliente[dni_cliente][i].getNumeroDeCuenta();
                    Tarjeta=cuentasPorCliente[dni_cliente][i].getTarjetaDebito();
                    cout << i + 1 << ". Saldo de la tarjeta " << Tarjeta << " de la cuenta "<<NumCuenta<<" : "<< cuentasPorCliente[dni_cliente][i].consultarSaldo() << endl;
                }
                cout << "Presiona Enter para continuar...\n";cin.get();
                cin.get();
                gestionarCuentasDeAhorro();
                break;
            }
            case 5:
                cancelarCuentaDeAhorro();
                break;
            case 6:
                cout<<endl;
                menu();
            default:
                cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 5);
}

void cancelarCuentaDeAhorro() {
    int dni_cliente;
    string numCuenta;
    cout << "Ingresar DNI del Cliente: ";
    cin >> dni_cliente;
    cout << "Ingresar número de cuenta a cancelar: ";
    cin >> numCuenta;

    auto itCuentasCliente = cuentasPorCliente.find(dni_cliente);
    if (itCuentasCliente == cuentasPorCliente.end()) {
        cout << "No se encontraron cuentas para el DNI proporcionado." << endl;
        return;
    }

    bool cuentaEncontrada = false;
    for (auto& cuenta : itCuentasCliente->second) {
        if (cuenta.getNumeroDeCuenta() == numCuenta && cuenta.esEstado() != "Cancelada") {
            cuenta.cancelarCuenta();
            cout << "Cuenta y tarjeta asociada canceladas correctamente." << endl;
            cuentaEncontrada = true;
            break;
        }
    }

    if (!cuentaEncontrada) {
        cout << "No se encontró la cuenta o ya está cancelada." << endl;
    }
}


void crearPrestamo(int dni) {
    string fecha;
    float monto;
    int plazo, interes;

    cout << "Crear nuevo préstamo para el cliente con DNI: " << dni << endl;
    cout << "Introduce la fecha del préstamo (dd/mm/aaaa): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el '\n' anterior
    getline(cin, fecha); // Usa getline para manejar mejor la entrada de texto

    cout << "Introduce el monto del préstamo: ";
    while (!(cin >> monto)) { // Verifica la entrada
        cout << "Entrada inválida. Por favor, introduce un número: ";
        cin.clear(); // Limpia el estado de cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta la entrada hasta el próximo '\n'
    }

    cout << "Introduce el plazo del préstamo (en meses): ";
    cin >> plazo; // Asumiendo que el usuario introduce valores válidos, pero deberías verificar esto también

    cout << "Introduce el interés del préstamo (porcentaje anual): ";
    cin >> interes; // Igual que con 'plazo', considera verificar la entrada

    Prestamo nuevoPrestamo(fecha, monto, plazo, interes);
    nuevoPrestamo.calcularCuotaMensualInteres(monto, plazo, interes);

    prestamosPorCliente[dni].push_back(nuevoPrestamo);

    cout << "Préstamo creado exitosamente para el cliente con DNI: " << dni << endl;
}


void visualizarPrestamos(int dni) {
    // Verificar si el cliente tiene préstamos asociados
    auto it = prestamosPorCliente.find(dni);
    if (it == prestamosPorCliente.end() || it->second.empty()) {
        cout << "No hay préstamos registrados para el cliente con DNI: " << dni << endl;
        return;
    }

    // Si hay préstamos, mostrar sus detalles
    cout << "Préstamos para el cliente con DNI: " << dni << endl;
    for (const auto& prestamo : it->second) {
        cout << "----------------------------------------" << endl;
        cout << "Fecha del préstamo: " << prestamo.getFecha() << endl;
        cout << "Monto del préstamo: " << fixed << setprecision(2) << prestamo.getMonto() << endl;
        cout << "Plazo (meses): " << prestamo.getPlazo() << endl;
        cout << "Interés (% anual): " << prestamo.getInteres() << endl;
        cout << "Estado del préstamo: " << prestamo.getEstado() << endl;
        cout << "Cuota mensual: " << fixed << setprecision(2) << prestamo.getCuota() << endl;
        cout << "Deuda restante: " << fixed << setprecision(2) << prestamo.getDeuda() << endl;
        cout << "----------------------------------------" << endl;
    }
}

void realizarPagoPrestamo(int dni) {
    // Primero, verificar si el cliente tiene préstamos
    auto itPrestamos = prestamosPorCliente.find(dni);
    if (itPrestamos == prestamosPorCliente.end() || itPrestamos->second.empty()) {
        cout << "No se encontraron préstamos para el cliente con DNI: " << dni << endl;
        return;
    }

    // Verificar si el cliente tiene cuentas de ahorro
    auto itCuentas = cuentasPorCliente.find(dni);
    if (itCuentas == cuentasPorCliente.end() || itCuentas->second.empty()) {
        cout << "No se encontraron cuentas de ahorro para el cliente con DNI: " << dni << endl;
        return;
    }

    // Mostrar todos los préstamos del cliente y pedirle que elija uno para pagar
    cout << "Préstamos del cliente con DNI: " << dni << endl;
    int index = 1;
    for (const auto& prestamo : itPrestamos->second) {
        cout << index << ". Monto: " << prestamo.getMonto()
             << ", Plazo: " << prestamo.getPlazo() << " meses"
             << ", Cuota: " << prestamo.getCuota()
             << ", Deuda restante: " << prestamo.getDeuda()
             << ", Estado: " << prestamo.getEstado() << endl;
        ++index;
    }

    cout << "Seleccione el préstamo a pagar (1-" << itPrestamos->second.size() << "): ";
    int eleccionPrestamo;
    cin >> eleccionPrestamo;
    if (eleccionPrestamo < 1 || eleccionPrestamo > itPrestamos->second.size()) {
        cout << "Selección inválida." << endl;
        return;
    }

    auto& prestamoSeleccionado = itPrestamos->second[eleccionPrestamo - 1];
    if (prestamoSeleccionado.getEstado() == "Finalizado") {
        cout << "Este préstamo ya está completamente pagado." << endl;
        return;
    }

    // Mostrar todas las cuentas de ahorro del cliente y pedirle que elija una para el pago
    cout << "Cuentas de ahorro del cliente con DNI: " << dni << endl;
    index = 1;
    for (const auto& cuenta : itCuentas->second) {
        cout << index << ". Número de cuenta: " << cuenta.getNumeroDeCuenta()
             << ", Saldo disponible: " << cuenta.consultarSaldo() << endl;
        ++index;
    }

    cout << "Seleccione la cuenta de ahorro para realizar el pago (1-" << itCuentas->second.size() << "): ";
    int eleccionCuenta;
    cin >> eleccionCuenta;
    if (eleccionCuenta < 1 || eleccionCuenta > itCuentas->second.size()) {
        cout << "Selección inválida." << endl;
        return;
    }

    auto& cuentaSeleccionada = itCuentas->second[eleccionCuenta - 1];
    if (cuentaSeleccionada.consultarSaldo() < prestamoSeleccionado.getCuota()) {
        cout << "Saldo insuficiente en la cuenta seleccionada para cubrir el pago del préstamo." << endl;
        return;
    }

    // Realizar el pago
    cuentaSeleccionada.retirar(prestamoSeleccionado.getCuota());
    prestamoSeleccionado.estadoPrestamoActivoInactivo();
    prestamoSeleccionado.fechaDePagoMensualSiguiente();

    cout << "Pago realizado exitosamente desde la cuenta de ahorro. Detalles actualizados del préstamo:" << endl;
    cout << "Deuda restante: " << prestamoSeleccionado.getDeuda() << ", Estado: " << prestamoSeleccionado.getEstado() << endl;
}
void visualizarCronogramaDePagos(int dni) {
    auto it = prestamosPorCliente.find(dni);
    if (it == prestamosPorCliente.end() || it->second.empty()) {
        cout << "No hay préstamos registrados para el cliente con DNI: " << dni << endl;
        return;
    }

    cout << "Cronograma de pagos para el cliente con DNI: " << dni << endl;
    for (const auto& prestamo : it->second) {
        cout << "----------------------------------------" << endl;
        cout << "Fecha del préstamo: " << prestamo.getFecha() << endl;
        cout << "Monto del préstamo: " << fixed << setprecision(2) << prestamo.getMonto() << endl;
        cout << "Plazo (meses): " << prestamo.getPlazo() << endl;
        cout << "Interés (% anual): " << prestamo.getInteres() << endl;
        cout << "Estado del préstamo: " << prestamo.getEstado() << endl;
        cout << "Cuota mensual: " << fixed << setprecision(2) << prestamo.getCuota() << endl;
        cout << "Cronograma de pagos:" << endl;
        prestamo.mostrarCronogramaPagos();
        cout << "----------------------------------------" << endl;
    }
}
void cancelarPrestamoCompleto(int dni) {
    auto itPrestamos = prestamosPorCliente.find(dni);
    if (itPrestamos == prestamosPorCliente.end() || itPrestamos->second.empty()) {
        cout << "No se encontraron préstamos para el cliente con DNI: " << dni << endl;
        return;
    }

    cout << "Préstamos para el cliente con DNI: " << dni << endl;
    int index = 1;
    for (const auto& prestamo : itPrestamos->second) {
        cout << index << ". Monto: " << prestamo.getMonto()
             << ", Plazo: " << prestamo.getPlazo() << " meses"
             << ", Cuota: " << prestamo.getCuota()
             << ", Deuda restante: " << prestamo.getDeuda()
             << ", Estado: " << prestamo.getEstado() << endl;
        ++index;
    }

    cout << "Seleccione el préstamo a cancelar (1-" << itPrestamos->second.size() << "): ";
    int eleccionPrestamo;
    cin >> eleccionPrestamo;
    if (eleccionPrestamo < 1 || eleccionPrestamo > itPrestamos->second.size()) {
        cout << "Selección inválida." << endl;
        return;
    }

    auto& prestamoSeleccionado = itPrestamos->second[eleccionPrestamo - 1];

    // Verificar si el cliente tiene cuentas de ahorro
    auto itCuentas = cuentasPorCliente.find(dni);
    if (itCuentas == cuentasPorCliente.end() || itCuentas->second.empty()) {
        cout << "No se encontraron cuentas de ahorro para el cliente con DNI: " << dni << endl;
        return;
    }

    // Pedir al usuario que seleccione la cuenta de ahorro para cancelar el préstamo
    cout << "Seleccione la cuenta de ahorro para cancelar el préstamo:" << endl;
    index = 1;
    for (const auto& cuenta : itCuentas->second) {
        cout << index << ". Número de cuenta: " << cuenta.getNumeroDeCuenta()
             << ", Saldo disponible: " << cuenta.consultarSaldo() << endl;
        ++index;
    }

    int eleccionCuenta;
    cout << "Seleccione la cuenta (1-" << itCuentas->second.size() << "): ";
    cin >> eleccionCuenta;
    if (eleccionCuenta < 1 || eleccionCuenta > itCuentas->second.size()) {
        cout << "Selección inválida." << endl;
        return;
    }

    auto& cuentaSeleccionada = itCuentas->second[eleccionCuenta - 1];

    if (cuentaSeleccionada.consultarSaldo() < prestamoSeleccionado.getDeuda()) {
        cout << "Saldo insuficiente en la cuenta seleccionada para cubrir el préstamo." << endl;
        return;
    }

    // Cancelar el préstamo y deducir el saldo
    cuentaSeleccionada.retirar(prestamoSeleccionado.getDeuda());
    prestamoSeleccionado.cancelarPrestamo();

    cout << "El préstamo ha sido cancelado con éxito. Saldo actualizado de la cuenta: " << cuentaSeleccionada.consultarSaldo() << endl;
}



void gestionarPrestamos() {
    int opcion, dni;
    cout << "Ingrese DNI del cliente para gestionar préstamos: ";
    cin >> dni;

    do {
        cout << "1. Crear nuevo préstamo" << endl;
        cout << "2. Visualizar préstamos existentes" << endl;
        cout << "3. Realizar pago de préstamo" << endl;
        cout << "4. Visualizar cronograma de pagos" << endl;
        cout << "5. Cancelar prestamo completo" << endl;
        cout << "6. Regresar" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                crearPrestamo(dni);
                break;
            case 2:
                visualizarPrestamos(dni);
                break;
            case 3:
                realizarPagoPrestamo(dni);
                break;
            case 4:
                visualizarCronogramaDePagos(dni);
                break;
            case 5:
                cancelarPrestamoCompleto(dni);
                break;
            case 6:
                return; // Regresar al menú principal
            default:
                cout << "Opción no válida, por favor intente de nuevo." << endl;
        }
    } while (opcion != 4);
}


void menu() {
    int opcion = 0; // Inicializamos opcion aquí
    do {
        cout << "---Menu---" << endl;
        cout << "1. Clientes" << endl;
        cout << "2. Cuentas de ahorro" << endl;
        cout << "3. Prestamos de dinero" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        cout << endl;
        switch (opcion) {
            case 1:
                Clientes(opcion);
                gestionarClientes(opcion);
                break;
            case 2:
                gestionarCuentasDeAhorro();
                break;
            case 3:
                gestionarPrestamos();
                break;
            case 4:
                exit(0);
            default:
                cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
        }
    } while (opcion != 4);
}

int main() {
    menu();
    return 0;
}
