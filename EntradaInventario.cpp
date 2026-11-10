#include "EntradaInventario.h"

EntradaInventario::EntradaInventario(int id, const QString &estado, Producto *producto, int cantidad)
    : Movimiento(id, estado, producto, cantidad)
{
}

EntradaInventario::~EntradaInventario() = default;

QString EntradaInventario::getTipo() const { return "Entrada inventario"; }

bool EntradaInventario::aplicar()
{
    if (aplicado || estado != "Registrada") {
        return true;
    }
    if (!producto) {
        return false;
    }
    producto->aumentarStock(cantidad);
    aplicado = true;
    return true;
}

void EntradaInventario::revertir()
{
    if (aplicado && producto && producto->requiereStock()) {
        producto->disminuirStock(cantidad);
    }
    aplicado = false;
}

double EntradaInventario::calcularImporte() const
{
    return 0.0;
}

QString EntradaInventario::mostrarInfo() const
{
    return Movimiento::mostrarInfo() + " | Movimiento para aumentar existencias";
}
