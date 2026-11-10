#ifndef CLIENTENORMAL_H
#define CLIENTENORMAL_H

#include "Persona.h"

class ClienteNormal : public Persona
{
public:
    ClienteNormal(int id, const QString &nombre, const QString &telefono);
    ~ClienteNormal() override;

    QString getTipo() const override;
    double calcularBeneficio() const override;
    QString mostrarInfo() const override;
};

#endif
