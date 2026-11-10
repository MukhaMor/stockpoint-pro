#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QTextEdit>
#include <QPushButton>
#include <memory>
#include <vector>

#include "Persona.h"
#include "Producto.h"
#include "Movimiento.h"

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private:
    std::vector<std::unique_ptr<Persona>> clientes;
    std::vector<std::unique_ptr<Producto>> productos;
    std::vector<std::unique_ptr<Movimiento>> movimientos;

    int siguienteClienteId;
    int siguienteProductoId;
    int siguienteMovimientoId;

    QStackedWidget *stack;

    QLabel *cardProductos;
    QLabel *cardClientes;
    QLabel *cardMovimientos;
    QLabel *cardIngresos;
    QLabel *cardStockBajo;

    QLabel *clienteIdLabel;
    QComboBox *clienteTipoCombo;
    QLineEdit *clienteNombreEdit;
    QLineEdit *clienteTelefonoEdit;
    QTableWidget *clientesTable;

    QLabel *productoIdLabel;
    QComboBox *productoTipoCombo;
    QLineEdit *productoNombreEdit;
    QDoubleSpinBox *productoPrecioSpin;
    QSpinBox *productoStockSpin;
    QTableWidget *productosTable;

    QLabel *movimientoIdLabel;
    QComboBox *movimientoTipoCombo;
    QComboBox *movimientoClienteCombo;
    QComboBox *movimientoProductoCombo;
    QSpinBox *movimientoCantidadSpin;
    QComboBox *movimientoPagoCombo;
    QComboBox *movimientoEstadoCombo;
    QTableWidget *movimientosTable;

    QTextEdit *reporteText;
    QComboBox *reporteTipoCombo;

    QWidget *createDashboardPage();
    QWidget *createClientesPage();
    QWidget *createProductosPage();
    QWidget *createMovimientosPage();
    QWidget *createReportesPage();

    QPushButton *createSidebarButton(const QString &text);
    QLabel *createTitle(const QString &text, const QString &subtitle);
    QLabel *createMetricCard(const QString &title, const QString &value);
    QFrame *createCard();
    QTableWidget *createTable(const QStringList &headers);

    void registrarCliente();
    void modificarCliente();
    void limpiarClienteForm();
    void cargarClienteSeleccionado();

    void registrarProducto();
    void modificarProducto();
    void borrarProducto();
    void limpiarProductoForm();
    void cargarProductoSeleccionado();

    void registrarMovimiento();
    void modificarEstadoMovimiento();
    void limpiarMovimientoForm();
    void cargarMovimientoSeleccionado();
    void actualizarEstadosMovimiento();

    void generarReporte();
    void descargarReporte();
    void refreshAllViews();
    void refreshDashboard();
    void refreshClientesTable();
    void refreshProductosTable();
    void refreshMovimientosTable();
    void refreshCombos();

    Persona *findClienteById(int id) const;
    Producto *findProductoById(int codigo) const;
    Movimiento *findMovimientoById(int id) const;

    QString calcularEstadoProducto(const QString &tipo, int stock) const;
    void actualizarEstadoProducto(Producto *producto);
    bool estadoActivaMovimiento(const QString &tipo, const QString &estado) const;
    int cantidadDisponibleParaDevolucion(Persona *cliente, Producto *producto, const Movimiento *excluirMovimiento = nullptr) const;
    std::vector<Persona*> rawClientes() const;
    std::vector<Producto*> rawProductos() const;
    std::vector<Movimiento*> rawMovimientos() const;
};

#endif
