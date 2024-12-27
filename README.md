# 🌐 Banco Simulado en C++

Este proyecto es una simulación de los servicios que ofrece un banco, implementado en C++ con un enfoque en la Programación Orientada a Objetos (POO). Es un programa de consola que permite gestionar clientes, cuentas de ahorro, préstamos de dinero, y otros servicios financieros básicos.

## 🔍 Descripción del Proyecto

El programa simula las siguientes funcionalidades principales:

1. **👨‍💼 Gestión de Clientes**:
   - Buscar, agregar y eliminar clientes.
   - Listar los servicios que cada cliente tiene asociados.

2. **💳 Cuentas de Ahorro**:
   - Registro de cuentas de ahorro, asociadas a tarjetas de débito.
   - Bloqueo y reemplazo de tarjetas de débito.
   - Registro y visualización de ingresos de dinero.
   - Cancelación de cuentas de ahorro (manteniendo un historial).

3. **💰 Préstamos de Dinero**:
   - Solicitud de préstamos.
   - Visualización del cronograma de pagos, incluyendo intereses.
   - Cancelación anticipada de préstamos.
   - Historial de préstamos, incluyendo los pagados.

4. **📊 Reportes**:
   - Reporte actual del saldo de cada cuenta.
   - Reporte de los préstamos realizados.

## 🔧 Características Técnicas

Este proyecto utiliza las siguientes características avanzadas de C++:

1. **💡 Programación Orientada a Objetos (POO)**:
   - Clases y relaciones entre clases: asociación, agregación y composición.
   - Herencia y polimorfismo.
   - Sobrecarga de operadores.

2. **🔢 Estructuras de Datos**:
   - Uso de punteros, arreglos y vectores.
   - Almacenamiento y manipulación eficiente de datos.

3. **⚠️ Gestión de Errores**:
   - Manejo de errores con mensajes claros.
   - Validación de datos de entrada.

4. **📁 Persistencia de Datos** (Opcional):
   - Lectura y escritura de datos en archivos para guardar el progreso.

## 📄 Estructura del Código

### 🔬 Clases Principales

1. `Cliente`: Representa a un cliente del banco. Incluye atributos como DNI, nombre y fecha de nacimiento.
2. `CuentaAhorro`: Hereda de una clase base de cuentas y contiene funcionalidades específicas de las cuentas de ahorro.
3. `Prestamo`: Clase que modela los préstamos de dinero.
4. `Tarjeta`: Clase base para `TarjetaDebito` y `TarjetaCredito`.
5. `Banco`: Clase principal que coordina todas las operaciones y almacena la lista de clientes y servicios.

### 🎯 Relación Entre Clases

- **Asociación**: Los clientes están asociados a múltiples servicios como cuentas y préstamos.
- **Agregación**: Un banco contiene una colección de clientes.
- **Composición**: Una cuenta de ahorro tiene asociada una tarjeta de débito.

### ⚛️ Polimorfismo y Sobrecarga de Operadores

- Polimorfismo: Métodos sobreescritos para diferentes tipos de cuentas y servicios.
- Sobrecarga: Operadores utilizados para comparar, sumar o realizar otras operaciones relevantes.

## 🚀 Ejecución del Programa

1. Abre el proyecto en **CLion**.

2. Asegúrate de que el archivo `CMakeLists.txt` tenga la configuración correcta:

   ```cmake
   cmake_minimum_required(VERSION 3.28)
   project(SIMULADOR_BANCO_C__)

   set(CMAKE_CXX_STANDARD 17)

   add_executable(SIMULADOR_BANCO_C__
           "main.cpp"
           "Prestamo.h"
   )
   ```

3. Presiona el botón **Run** (o usa `Shift + F10`) en CLion para compilar y ejecutar el programa.

4. Navega por el menú para explorar las funcionalidades.

## 🔄 Ejemplo de Uso

A continuación, se muestra un ejemplo detallado de cómo interactuar con el sistema.

### Menú Principal

```plaintext
---Menu---
1. Clientes
2. Cuentas de ahorro
3. Prestamos de dinero
4. Salir
Opcion: 1
```

### 1. Clientes

#### Submenú de Clientes

```plaintext
---Clientes---
1.1 Buscar Cliente
1.2 Agregar Cliente
1.3 Eliminar Cliente
1.4 Regresar
Opcion: 2
```

#### Agregar Cliente

```plaintext
---Agregar cliente---
Ingresar DNI: 76355221
Ingresar Nombre: Juancito
Ingresar Fecha Nacimiento: 23122004

Cliente Registrado
```

#### Buscar Cliente

```plaintext
---Buscar cliente---
Ingresar DNI: 76355221
No hay servicios registrados para este cliente.
```

### 2. Cuentas de Ahorro

#### Submenú de Cuentas de Ahorro

```plaintext
---Cuentas de Ahorro---
1. Crear Cuenta de Ahorro
2. Realizar Depósito
3. Realizar Retiro
4. Consultar Saldo
5. Cancelar cuenta 
6. Regresar
Opción: 1
```

#### Crear Cuenta de Ahorro

```plaintext
---Crear Cuenta de Ahorro---
Ingresar DNI del Cliente: 76355221

Cuenta de ahorro creada exitosamente.
Su numero de cuenta es 1740-948824
Ahora su nueva targeta es 4916-1566-2162-0361
Y la targeta tiene un fecha de vencimiento el /29

Presiona Enter para continuar...
```

#### Realizar Depósito

```plaintext
---Realizar Depósito---
Ingresar DNI del Cliente: 76355221
Tarjetas encontradas:
1. Saldo de la tarjeta 4916-1566-2162-0361 de la cuenta 1740-948824 : 0
2. Saldo de la tarjeta 3424-0531-8096-1776 de la cuenta 3873-913863 : 0
Seleccione la tarjeta con la que desea realizar el depósito: 1

Ingrese el monto a depositar: 75000
Se deposito correctamente S/75000
Presiona Enter para continuar...
```

#### Consultar Saldo

```plaintext
---Consultar Saldo---
Ingresar DNI del Cliente: 76355221
Tarjetas encontradas:
1. Saldo de la tarjeta 4916-1566-2162-0361 de la cuenta 1740-948824 : 75000
2. Saldo de la tarjeta 3424-0531-8096-1776 de la cuenta 3873-913863 : 13600
Presiona Enter para continuar...
```

#### Realizar Retiro

```plaintext
---Realizar Retiro---
Ingresar DNI del Cliente: 76355221
Tarjetas encontradas:
1. Saldo de la tarjeta 4916-1566-2162-0361 de la cuenta 1740-948824 : 75000
2. Saldo de la tarjeta 3424-0531-8096-1776 de la cuenta 3873-913863 : 13600
Seleccione la tarjeta de la que desea realizar el retiro: 1

Ingrese el monto a retirar: 500
Se retiro correctamente S/500
Presiona Enter para continuar...
```

### 3. Préstamos de Dinero

#### Crear Préstamo

```plaintext
Ingrese DNI del cliente para gestionar préstamos: 76355221
1. Crear nuevo préstamo
2. Visualizar préstamos existentes
3. Realizar pago de préstamo
4. Visualizar cronograma de pagos
5. Cancelar prestamo completo
6. Regresar
Seleccione una opción: 1
Crear nuevo préstamo para el cliente con DNI: 76355221
Introduce la fecha del préstamo (dd/mm/aaaa): 27/12/2024
Introduce el monto del préstamo: 20000
Introduce el plazo del préstamo (en meses): 2
Introduce el interés del préstamo (porcentaje anual): 2
Préstamo creado exitosamente para el cliente con DNI: 76355221
```

#### Visualizar Préstamos Existentes

```plaintext
Préstamos para el cliente con DNI: 76355221
----------------------------------------
Fecha del préstamo: 27/12/2024
Monto del préstamo: 20000.00
Plazo (meses): 2
Interés (% anual): 2%
Estado del préstamo: 
Cuota mensual: 10200.00
Deuda restante: 20400.00
----------------------------------------
```

#### Realizar Pago de Préstamo

```plaintext
Préstamos del cliente con DNI: 76355221
1. Monto: 20000.00, Plazo: 2 meses, Cuota: 10200.00, Deuda restante: 20400.00, Estado: 
Seleccione el préstamo a pagar (1-2): 1
Cuentas de ahorro del cliente con DNI: 76355221
1. Número de cuenta: 1740-948824, Saldo disponible: 74500.00
Seleccione la cuenta de ahorro para realizar el pago (1-2): 1
Pago realizado exitosamente desde la cuenta de ahorro. Detalles actualizados del préstamo:
Deuda restante: 10200.00, Estado: Activo
```

#### Visualizar Cronograma de Pagos

```plaintext
Cronograma de pagos para el cliente con DNI: 76355221
----------------------------------------
Fecha del préstamo: 27/12/2024
Monto del préstamo: 12000.00
Plazo (meses): 5
Interés (% anual): 2%
Estado del préstamo: 
Cuota mensual: 2448.00
Cronograma de pagos para el préstamo:
Pago 1: 2448.00 (Estado: Pendiente)
Pago 2: 2448.00 (Estado: Pendiente)
Pago 3: 2448.00 (Estado: Pendiente)
Pago 4: 2448.00 (Estado: Pendiente)
Pago 5: 2448.00 (Estado: Pendiente)
----------------------------------------
```

### 4. Salir

```plaintext
---Menu---
1. Clientes
2. Cuentas de ahorro
3. Prestamos de dinero
4. Salir
Opcion: 4
Saliendo del sistema...
```

## 🎓 Aprendizajes

Este proyecto demuestra el conocimiento en:

- Diseño e implementación de sistemas basados en POO.
- Uso de conceptos avanzados de C++ como herencia, polimorfismo y manejo de memoria.
- Implementación de simulaciones reales en un entorno de consola.

## 📄 **Licencia**

Este proyecto está bajo la licencia MIT. Puedes usarlo, modificarlo y compartirlo libremente.
