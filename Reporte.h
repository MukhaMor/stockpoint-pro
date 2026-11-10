#ifndef REPORTE_H
#define REPORTE_H

#include <QString>
#include <vector>
#include "Producto.h"
#include "Persona.h"
#include "Movimiento.h"

class Reporte
{
protected:
    int id;
    QString titulo;

public:
    Reporte(int id, const QString &titulo);
    virtual ~Reporte();

    int getId() const;
    QString getTitulo() const;
    void setId(int id);
    void setTitulo(const QString &titulo);

    virtual QString getTipo() const = 0;
    virtual QString generarResumen(const std::vector<Producto*> &productos,
                                   const std::vector<Persona*> &clientes,
                                   const std::vector<Movimiento*> &movimientos) const = 0;
};

#endif
