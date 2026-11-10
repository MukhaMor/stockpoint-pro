#include "Reporte.h"

Reporte::Reporte(int id, const QString &titulo)
    : id(id), titulo(titulo)
{
}

Reporte::~Reporte() = default;

int Reporte::getId() const { return id; }
QString Reporte::getTitulo() const { return titulo; }
void Reporte::setId(int id) { this->id = id; }
void Reporte::setTitulo(const QString &titulo) { this->titulo = titulo; }
