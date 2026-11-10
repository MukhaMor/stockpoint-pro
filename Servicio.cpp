#include "Servicio.h"

Servicio::Servicio(int codigo, const QString &nombre, double precio, int stock, const QString &estado)
    : Producto(codigo, nombre, precio, stock, estado)
{
}

Servicio::~Servicio() = default;

QString Servicio::getTipo() const { return "Servicio"; }
bool Servicio::requiereStock() const { return false; }
double Servicio::calcularPrecioFinal() const { return precio; }

QString Servicio::mostrarInfo() const
{
    return QString("Codigo: %1 | Tipo: Servicio | Nombre: %2 | Precio: $%3 | Estado: %4 | Sin control de stock")
        .arg(codigo)
        .arg(nombre)
        .arg(precio, 0, 'f', 2)
        .arg(estado);
}
