#include "ClienteNormal.h"

ClienteNormal::ClienteNormal(int id, const QString &nombre, const QString &telefono)
    : Persona(id, nombre, telefono)
{
}

ClienteNormal::~ClienteNormal() = default;

QString ClienteNormal::getTipo() const { return "Cliente normal"; }
double ClienteNormal::calcularBeneficio() const { return 0.0; }

QString ClienteNormal::mostrarInfo() const
{
    return Persona::mostrarInfo() + " | Beneficio: sin descuento";
}
