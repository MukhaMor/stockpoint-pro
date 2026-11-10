#include "Movimiento.h"

Movimiento::Movimiento(int id, const QString &estado, Producto *producto, int cantidad)
    : id(id), estado(estado), producto(producto), cantidad(cantidad), aplicado(false)
{
}

Movimiento::~Movimiento() = default;

int Movimiento::getId() const { return id; }
QString Movimiento::getEstado() const { return estado; }
Producto *Movimiento::getProducto() const { return producto; }
int Movimiento::getCantidad() const { return cantidad; }
bool Movimiento::estaAplicado() const { return aplicado; }

void Movimiento::setId(int id) { this->id = id; }
void Movimiento::setEstado(const QString &estado) { this->estado = estado; }
void Movimiento::setProducto(Producto *producto) { this->producto = producto; }
void Movimiento::setCantidad(int cantidad) { this->cantidad = cantidad; }

QString Movimiento::mostrarInfo() const
{
    const QString nombreProducto = producto ? producto->getNombre() : "Sin producto";
    return QString("ID: %1 | Tipo: %2 | Producto: %3 | Cantidad: %4 | Estado: %5 | Importe: $%6")
        .arg(id)
        .arg(getTipo())
        .arg(nombreProducto)
        .arg(cantidad)
        .arg(estado)
        .arg(calcularImporte(), 0, 'f', 2);
}
