#ifndef ENTRADAINVENTARIO_H
#define ENTRADAINVENTARIO_H

#include "Movimiento.h"

class EntradaInventario : public Movimiento
{
public:
    EntradaInventario(int id, const QString &estado, Producto *producto, int cantidad);
    ~EntradaInventario() override;

    QString getTipo() const override;
    bool aplicar() override;
    void revertir() override;
    double calcularImporte() const override;
    QString mostrarInfo() const override;
};

#endif
