#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <QString>

class Producto
{
protected:
    int codigo;
    QString nombre;
    double precio;
    int stock;
    QString estado;

public:
    Producto(int codigo, const QString &nombre, double precio, int stock, const QString &estado);
    virtual ~Producto();

    int getCodigo() const;
    QString getNombre() const;
    double getPrecio() const;
    int getStock() const;
    QString getEstado() const;

    void setCodigo(int codigo);
    void setNombre(const QString &nombre);
    void setPrecio(double precio);
    void setStock(int stock);
    void setEstado(const QString &estado);

    bool disminuirStock(int cantidad);
    void aumentarStock(int cantidad);

    virtual QString getTipo() const = 0;
    virtual bool requiereStock() const;
    virtual double calcularPrecioFinal() const = 0;
    virtual QString mostrarInfo() const;
};

#endif
