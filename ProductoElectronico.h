#ifndef PRODUCTOELECTRONICO_H
#define PRODUCTOELECTRONICO_H

#include "Producto.h"

class ProductoElectronico : public Producto
{
public:
    ProductoElectronico(int codigo, const QString &nombre, double precio, int stock, const QString &estado);
    ~ProductoElectronico() override;

    QString getTipo() const override;
    double calcularPrecioFinal() const override;
    QString mostrarInfo() const override;
};

#endif
