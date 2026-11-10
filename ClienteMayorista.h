#ifndef CLIENTEMAYORISTA_H
#define CLIENTEMAYORISTA_H

#include "Persona.h"

class ClienteMayorista : public Persona
{
private:
    double descuento;

public:
    ClienteMayorista(int id, const QString &nombre, const QString &telefono, double descuento = 0.10);
    ~ClienteMayorista() override;

    double getDescuento() const;
    void setDescuento(double descuento);

    QString getTipo() const override;
    double calcularBeneficio() const override;
    QString mostrarInfo() const override;
};

#endif
