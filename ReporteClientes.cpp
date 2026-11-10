#include "ReporteClientes.h"

ReporteClientes::ReporteClientes(int id, const QString &titulo)
    : Reporte(id, titulo)
{
}

ReporteClientes::~ReporteClientes() = default;

QString ReporteClientes::getTipo() const { return "Reporte de clientes"; }

QString ReporteClientes::generarResumen(const std::vector<Producto*> &,
                                        const std::vector<Persona*> &clientes,
                                        const std::vector<Movimiento*> &) const
{
    QString texto = titulo + "\n\n";
    for (const Persona *cliente : clientes) {
        if (cliente) {
            texto += cliente->mostrarInfo() + "\n";
        }
    }
    texto += QString("\nClientes registrados: %1").arg(clientes.size());
    return texto;
}
