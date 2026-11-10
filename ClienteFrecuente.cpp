#include "ClienteFrecuente.h"

ClienteFrecuente::ClienteFrecuente(int id, const QString &nombre, const QString &telefono, int puntos)
    : Persona(id, nombre, telefono), puntos(puntos)
{
}

ClienteFrecuente::~ClienteFrecuente() = default;

int ClienteFrecuente::getPuntos() const { return puntos; }
void ClienteFrecuente::setPuntos(int puntos) { this->puntos = puntos; }
void ClienteFrecuente::agregarPuntos(int puntos) { this->puntos += puntos; }

QString ClienteFrecuente::getTipo() const { return "Cliente frecuente"; }
double ClienteFrecuente::calcularBeneficio() const { return 0.05; }

QString ClienteFrecuente::mostrarInfo() const
{
    return Persona::mostrarInfo() + QString(" | Puntos: %1 | Descuento: 5%").arg(puntos);
}
