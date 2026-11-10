#include "ProductoPerecedero.h"

ProductoPerecedero::ProductoPerecedero(int codigo, const QString &nombre, double precio, int stock, const QString &estado)
    : Producto(codigo, nombre, precio, stock, estado)
{
}

ProductoPerecedero::~ProductoPerecedero() = default;

QString ProductoPerecedero::getTipo() const { return "Perecedero"; }
double ProductoPerecedero::calcularPrecioFinal() const { return precio; }

QString ProductoPerecedero::mostrarInfo() const
{
    return Producto::mostrarInfo();
}
