#include "ReporteVentas.h"

ReporteVentas::ReporteVentas(int id, const QString &titulo)
    : Reporte(id, titulo)
{
}

ReporteVentas::~ReporteVentas() = default;

QString ReporteVentas::getTipo() const { return "Reporte de ventas"; }

QString ReporteVentas::generarResumen(const std::vector<Producto*> &,
                                      const std::vector<Persona*> &,
                                      const std::vector<Movimiento*> &movimientos) const
{
    int ventas = 0;
    double ingresos = 0.0;
    QString texto = titulo + "\n\n";
    for (const Movimiento *movimiento : movimientos) {
        if (!movimiento) {
            continue;
        }
        texto += movimiento->mostrarInfo() + "\n";
        if (movimiento->getTipo() == "Venta" && movimiento->getEstado() == "Pagada") {
            ventas++;
            ingresos += movimiento->calcularImporte();
        }
    }
    texto += QString("\nVentas pagadas: %1\nIngresos totales: $%2\nMovimientos registrados: %3")
        .arg(ventas)
        .arg(ingresos, 0, 'f', 2)
        .arg(movimientos.size());
    return texto;
}
