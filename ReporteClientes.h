#ifndef REPORTECLIENTES_H
#define REPORTECLIENTES_H

#include "Reporte.h"

class ReporteClientes : public Reporte
{
public:
    ReporteClientes(int id, const QString &titulo);
    ~ReporteClientes() override;

    QString getTipo() const override;
    QString generarResumen(const std::vector<Producto*> &productos,
                           const std::vector<Persona*> &clientes,
                           const std::vector<Movimiento*> &movimientos) const override;
};

#endif
