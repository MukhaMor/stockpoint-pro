#ifndef REPORTEINVENTARIO_H
#define REPORTEINVENTARIO_H

#include "Reporte.h"

class ReporteInventario : public Reporte
{
public:
    ReporteInventario(int id, const QString &titulo);
    ~ReporteInventario() override;

    QString getTipo() const override;
    QString generarResumen(const std::vector<Producto*> &productos,
                           const std::vector<Persona*> &clientes,
                           const std::vector<Movimiento*> &movimientos) const override;
};

#endif
