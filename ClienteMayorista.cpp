#include "ClienteMayorista.h"

ClienteMayorista::ClienteMayorista(int id, const QString &nombre, const QString &telefono, double descuento)
    : Persona(id, nombre, telefono), descuento(descuento)
{
}

ClienteMayorista::~ClienteMayorista() = default;

double ClienteMayorista::getDescuento() const { return descuento; }
void ClienteMayorista::setDescuento(double descuento) { this->descuento = descuento; }

QString ClienteMayorista::getTipo() const { return "Cliente mayorista"; }
double ClienteMayorista::calcularBeneficio() const { return descuento; }

QString ClienteMayorista::mostrarInfo() const
{
    return Persona::mostrarInfo() + QString(" | Descuento: %1%").arg(descuento * 100.0, 0, 'f', 0);
}
