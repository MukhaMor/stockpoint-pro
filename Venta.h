#ifndef VENTA_H
#define VENTA_H

#include "Movimiento.h"
#include "Persona.h"

class Venta : public Movimiento
{
private:
    Persona *cliente;
    QString metodoPago;

public:
    Venta(int id, const QString &estado, Producto *producto, int cantidad, Persona *cliente, const QString &metodoPago);
    ~Venta() override;

    Persona *getCliente() const;
    QString getMetodoPago() const;
    void setCliente(Persona *cliente);
    void setMetodoPago(const QString &metodoPago);

    QString getTipo() const override;
    bool aplicar() override;
    void revertir() override;
    double calcularImporte() const override;
    QString mostrarInfo() const override;
};

#endif
