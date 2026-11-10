#ifndef DEVOLUCION_H
#define DEVOLUCION_H

#include "Movimiento.h"
#include "Persona.h"

class Devolucion : public Movimiento
{
private:
    Persona *cliente;

public:
    Devolucion(int id, const QString &estado, Producto *producto, int cantidad, Persona *cliente);
    ~Devolucion() override;

    Persona *getCliente() const;
    void setCliente(Persona *cliente);

    QString getTipo() const override;
    bool aplicar() override;
    void revertir() override;
    double calcularImporte() const override;
    QString mostrarInfo() const override;
};

#endif
