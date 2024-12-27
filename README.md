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

1. Compila el código utilizando un compilador de C++ compatible con C++11 o superior:

   ```bash
   g++ -o BancoSimulado main.cpp Cliente.cpp CuentaAhorro.cpp Prestamo.cpp Banco.cpp -std=c++11
   ```

2. Ejecuta el programa desde la terminal:

   ```bash
   ./BancoSimulado
   ```

3. Navega por el menú para explorar las funcionalidades.

## 🔄 Ejemplo de Uso

### 🔢 Menú Principal

```
1. Clientes
2. Cuentas de ahorro
3. Préstamos de dinero
4. Salir
Opción: 1
```

### 🔎 Buscar Cliente

```
1.1 Buscar cliente
Ingresar DNI: 34981234
====
Servicios
Cuenta de ahorro: 0011-938485 Monto S/: 3500.00 Activa
Tarjeta débito asociada: 3456-1234-2345-1234 Venc: 12/27
Prestamos:
Fecha        Monto   Nro Cuota   Interes  Estado
12/02/2023   5000.00 12          20%      Activo
```

## 🎓 Aprendizajes

Este proyecto demuestra el conocimiento en:

- Diseño e implementación de sistemas basados en POO.
- Uso de conceptos avanzados de C++ como herencia, polimorfismo y manejo de memoria.
- Implementación de simulaciones reales en un entorno de consola.

## 📄 **Licencia**

Este proyecto está bajo la licencia MIT. Puedes usarlo, modificarlo y compartirlo libremente.
