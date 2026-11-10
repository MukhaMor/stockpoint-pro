#include "Producto.h"

Producto::Producto(int codigo, const QString &nombre, double precio, int stock, const QString &estado)
    : codigo(codigo), nombre(nombre), precio(precio), stock(stock), estado(estado)
{
}

Producto::~Producto() = default;

int Producto::getCodigo() const { return codigo; }
QString Producto::getNombre() const { return nombre; }
double Producto::getPrecio() const { return precio; }
int Producto::getStock() const { return stock; }
QString Producto::getEstado() const { return estado; }

void Producto::setCodigo(int codigo) { this->codigo = codigo; }
void Producto::setNombre(const QString &nombre) { this->nombre = nombre; }
void Producto::setPrecio(double precio) { this->precio = precio; }
void Producto::setStock(int stock) { this->stock = stock; }
void Producto::setEstado(const QString &estado) { this->estado = estado; }

bool Producto::disminuirStock(int cantidad)
{
    if (!requiereStock()) {
        return true;
    }
    if (cantidad <= 0 || stock < cantidad) {
        return false;
    }
    stock -= cantidad;
    if (stock == 0) {
        estado = "Agotado";
    } else if (stock <= 5) {
        estado = "Bajo stock";
    }
    return true;
}

void Producto::aumentarStock(int cantidad)
{
    if (!requiereStock() || cantidad <= 0) {
        return;
    }
    stock += cantidad;
    if (stock > 5 && estado != "Inactivo") {
        estado = "Disponible";
    }
}

bool Producto::requiereStock() const { return true; }

QString Producto::mostrarInfo() const
{
    return QString("Codigo: %1 | Tipo: %2 | Nombre: %3 | Precio: $%4 | Stock: %5 | Estado: %6")
        .arg(codigo)
        .arg(getTipo())
        .arg(nombre)
        .arg(precio, 0, 'f', 2)
        .arg(stock)
        .arg(estado);
}
