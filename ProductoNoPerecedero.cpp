#include "ProductoNoPerecedero.h"

ProductoNoPerecedero::ProductoNoPerecedero(int codigo, const QString &nombre, double precio, int stock, const QString &estado)
    : Producto(codigo, nombre, precio, stock, estado)
{
}

ProductoNoPerecedero::~ProductoNoPerecedero() = default;

QString ProductoNoPerecedero::getTipo() const { return "No perecedero"; }
double ProductoNoPerecedero::calcularPrecioFinal() const { return precio; }

QString ProductoNoPerecedero::mostrarInfo() const
{
    return Producto::mostrarInfo();
}
