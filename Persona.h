#ifndef PERSONA_H
#define PERSONA_H

#include <QString>

class Persona
{
protected:
    int id;
    QString nombre;
    QString telefono;

public:
    Persona(int id, const QString &nombre, const QString &telefono);
    virtual ~Persona();

    int getId() const;
    QString getNombre() const;
    QString getTelefono() const;

    void setId(int id);
    void setNombre(const QString &nombre);
    void setTelefono(const QString &telefono);

    virtual QString getTipo() const = 0;
    virtual double calcularBeneficio() const = 0;
    virtual QString mostrarInfo() const;
};

#endif
