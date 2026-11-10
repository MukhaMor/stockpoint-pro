#include "Devolucion.h"

Devolucion::Devolucion(int id, const QString &estado, Producto *producto, int cantidad, Persona *cliente)
    : Movimiento(id, estado, producto, cantidad), cliente(cliente)
{
}

Devolucion::~Devolucion() = default;

Persona *Devolucion::getCliente() const { return cliente; }
void Devolucion::setCliente(Persona *cliente) { this->cliente = cliente; }

QString Devolucion::getTipo() const { return "Devolucion"; }

bool Devolucion::aplicar()
{
    if (aplicado || estado != "Aplicada") {
        return true;
    }
    if (!producto) {
        return false;
    }
    producto->aumentarStock(cantidad);
    aplicado = true;
    return true;
}

void Devolucion::revertir()
{
    if (aplicado && producto && producto->requiereStock()) {
        producto->disminuirStock(cantidad);
    }
    aplicado = false;
}

double Devolucion::calcularImporte() const
{
    if (!producto) {
        return 0.0;
    }
    const double descuento = cliente ? cliente->calcularBeneficio() : 0.0;
    return producto->calcularPrecioFinal() * cantidad * (1.0 - descuento) * -1.0;
}

QString Devolucion::mostrarInfo() const
{
    const QString nombreCliente = cliente ? cliente->getNombre() : "Sin cliente";
    return Movimiento::mostrarInfo() + QString(" | Cliente: %1").arg(nombreCliente);
}
