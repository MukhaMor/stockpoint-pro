#ifndef REPORTEVENTAS_H
#define REPORTEVENTAS_H

#include "Reporte.h"

class ReporteVentas : public Reporte
{
public:
    ReporteVentas(int id, const QString &titulo);
    ~ReporteVentas() override;

    QString getTipo() const override;
    QString generarResumen(const std::vector<Producto*> &productos,
                           const std::vector<Persona*> &clientes,
                           const std::vector<Movimiento*> &movimientos) const override;
};

#endif
