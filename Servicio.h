#ifndef SERVICIO_H
#define SERVICIO_H

#include "Producto.h"

class Servicio : public Producto
{
public:
    Servicio(int codigo, const QString &nombre, double precio, int stock, const QString &estado);
    ~Servicio() override;

    QString getTipo() const override;
    bool requiereStock() const override;
    double calcularPrecioFinal() const override;
    QString mostrarInfo() const override;
};

#endif
