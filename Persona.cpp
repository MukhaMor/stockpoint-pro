#include "Persona.h"

Persona::Persona(int id, const QString &nombre, const QString &telefono)
    : id(id), nombre(nombre), telefono(telefono)
{
}

Persona::~Persona() = default;

int Persona::getId() const { return id; }
QString Persona::getNombre() const { return nombre; }
QString Persona::getTelefono() const { return telefono; }

void Persona::setId(int id) { this->id = id; }
void Persona::setNombre(const QString &nombre) { this->nombre = nombre; }
void Persona::setTelefono(const QString &telefono) { this->telefono = telefono; }

QString Persona::mostrarInfo() const
{
    return QString("ID: %1 | Tipo: %2 | Nombre: %3 | Telefono: %4")
        .arg(id)
        .arg(getTipo())
        .arg(nombre)
        .arg(telefono);
}
