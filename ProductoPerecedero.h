#ifndef PRODUCTOPERECEDERO_H
#define PRODUCTOPERECEDERO_H

#include "Producto.h"

class ProductoPerecedero : public Producto
{
public:
    ProductoPerecedero(int codigo, const QString &nombre, double precio, int stock, const QString &estado);
    ~ProductoPerecedero() override;

    QString getTipo() const override;
    double calcularPrecioFinal() const override;
    QString mostrarInfo() const override;
};

#endif
