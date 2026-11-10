#include "ProductoElectronico.h"

ProductoElectronico::ProductoElectronico(int codigo, const QString &nombre, double precio, int stock, const QString &estado)
    : Producto(codigo, nombre, precio, stock, estado)
{
}

ProductoElectronico::~ProductoElectronico() = default;

QString ProductoElectronico::getTipo() const { return "Electronico"; }
double ProductoElectronico::calcularPrecioFinal() const { return precio; }

QString ProductoElectronico::mostrarInfo() const
{
    return Producto::mostrarInfo();
}
