#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include <QString>
#include "Producto.h"

class Movimiento
{
protected:
    int id;
    QString estado;
    Producto *producto;
    int cantidad;
    bool aplicado;

public:
    Movimiento(int id, const QString &estado, Producto *producto, int cantidad);
    virtual ~Movimiento();

    int getId() const;
    QString getEstado() const;
    Producto *getProducto() const;
    int getCantidad() const;
    bool estaAplicado() const;

    void setId(int id);
    void setEstado(const QString &estado);
    void setProducto(Producto *producto);
    void setCantidad(int cantidad);

    virtual QString getTipo() const = 0;
    virtual bool aplicar() = 0;
    virtual void revertir() = 0;
    virtual double calcularImporte() const = 0;
    virtual QString mostrarInfo() const;
};

#endif
