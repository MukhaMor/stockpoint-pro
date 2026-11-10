cmake_minimum_required(VERSION 3.16)
project(StockPointProGUI VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(StockPointProGUI
    main.cpp
    MainWindow.h MainWindow.cpp
    Persona.h Persona.cpp
    ClienteNormal.h ClienteNormal.cpp
    ClienteFrecuente.h ClienteFrecuente.cpp
    ClienteMayorista.h ClienteMayorista.cpp
    Producto.h Producto.cpp
    ProductoPerecedero.h ProductoPerecedero.cpp
    ProductoNoPerecedero.h ProductoNoPerecedero.cpp
    ProductoElectronico.h ProductoElectronico.cpp
    Servicio.h Servicio.cpp
    Movimiento.h Movimiento.cpp
    Venta.h Venta.cpp
    EntradaInventario.h EntradaInventario.cpp
    Devolucion.h Devolucion.cpp
    Reporte.h Reporte.cpp
    ReporteInventario.h ReporteInventario.cpp
    ReporteVentas.h ReporteVentas.cpp
    ReporteClientes.h ReporteClientes.cpp
)

target_link_libraries(StockPointProGUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
