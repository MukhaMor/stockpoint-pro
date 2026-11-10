#ifndef CLIENTEFRECUENTE_H
#define CLIENTEFRECUENTE_H

#include "Persona.h"

class ClienteFrecuente : public Persona
{
private:
    int puntos;

public:
    ClienteFrecuente(int id, const QString &nombre, const QString &telefono, int puntos = 0);
    ~ClienteFrecuente() override;

    int getPuntos() const;
    void setPuntos(int puntos);
    void agregarPuntos(int puntos);

    QString getTipo() const override;
    double calcularBeneficio() const override;
    QString mostrarInfo() const override;
};

#endif
