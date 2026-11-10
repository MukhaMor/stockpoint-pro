#include "ReporteInventario.h"

ReporteInventario::ReporteInventario(int id, const QString &titulo)
    : Reporte(id, titulo)
{
}

ReporteInventario::~ReporteInventario() = default;

QString ReporteInventario::getTipo() const { return "Reporte de inventario"; }

QString ReporteInventario::generarResumen(const std::vector<Producto*> &productos,
                                          const std::vector<Persona*> &,
                                          const std::vector<Movimiento*> &) const
{
    int totalStock = 0;
    int bajoStock = 0;
    double valorInventario = 0.0;
    QString texto = titulo + "\n\n";
    for (const Producto *producto : productos) {
        if (!producto) {
            continue;
        }
        totalStock += producto->getStock();
        if (producto->requiereStock() && producto->getStock() <= 5) {
            bajoStock++;
        }
        valorInventario += producto->getPrecio() * producto->getStock();
        texto += producto->mostrarInfo() + "\n";
    }
    texto += QString("\nTotal de productos: %1\nUnidades en inventario: %2\nProductos con bajo stock: %3\nValor estimado: $%4")
        .arg(productos.size())
        .arg(totalStock)
        .arg(bajoStock)
        .arg(valorInventario, 0, 'f', 2);
    return texto;
}
