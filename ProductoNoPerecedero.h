#ifndef PRODUCTONOPERECEDERO_H
#define PRODUCTONOPERECEDERO_H

#include "Producto.h"

class ProductoNoPerecedero : public Producto
{
public:
    ProductoNoPerecedero(int codigo, const QString &nombre, double precio, int stock, const QString &estado);
    ~ProductoNoPerecedero() override;

    QString getTipo() const override;
    double calcularPrecioFinal() const override;
    QString mostrarInfo() const override;
};

#endif
