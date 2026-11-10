#include "Venta.h"

Venta::Venta(int id, const QString &estado, Producto *producto, int cantidad, Persona *cliente, const QString &metodoPago)
    : Movimiento(id, estado, producto, cantidad), cliente(cliente), metodoPago(metodoPago)
{
}

Venta::~Venta() = default;

Persona *Venta::getCliente() const { return cliente; }
QString Venta::getMetodoPago() const { return metodoPago; }
void Venta::setCliente(Persona *cliente) { this->cliente = cliente; }
void Venta::setMetodoPago(const QString &metodoPago) { this->metodoPago = metodoPago; }

QString Venta::getTipo() const { return "Venta"; }

bool Venta::aplicar()
{
    if (aplicado || estado != "Pagada") {
        return true;
    }
    if (!producto) {
        return false;
    }
    if (!producto->disminuirStock(cantidad)) {
        return false;
    }
    aplicado = true;
    return true;
}

void Venta::revertir()
{
    if (aplicado && producto && producto->requiereStock()) {
        producto->aumentarStock(cantidad);
    }
    aplicado = false;
}

double Venta::calcularImporte() const
{
    if (!producto) {
        return 0.0;
    }
    const double descuento = cliente ? cliente->calcularBeneficio() : 0.0;
    return producto->calcularPrecioFinal() * cantidad * (1.0 - descuento);
}

QString Venta::mostrarInfo() const
{
    const QString nombreCliente = cliente ? cliente->getNombre() : "Sin cliente";
    return Movimiento::mostrarInfo() + QString(" | Cliente: %1 | Metodo: %2").arg(nombreCliente).arg(metodoPago);
}
