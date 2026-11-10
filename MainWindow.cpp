#include "MainWindow.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QFrame>
#include <QHeaderView>
#include <QMessageBox>
#include <QDateTime>
#include <QGroupBox>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <algorithm>

#include "ClienteNormal.h"
#include "ClienteFrecuente.h"
#include "ClienteMayorista.h"
#include "ProductoPerecedero.h"
#include "ProductoNoPerecedero.h"
#include "ProductoElectronico.h"
#include "Servicio.h"
#include "Venta.h"
#include "EntradaInventario.h"
#include "Devolucion.h"
#include "ReporteInventario.h"
#include "ReporteVentas.h"
#include "ReporteClientes.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      siguienteClienteId(1),
      siguienteProductoId(1001),
      siguienteMovimientoId(5001),
      stack(nullptr),
      cardProductos(nullptr), cardClientes(nullptr), cardMovimientos(nullptr), cardIngresos(nullptr), cardStockBajo(nullptr),
      clienteIdLabel(nullptr), clienteTipoCombo(nullptr), clienteNombreEdit(nullptr), clienteTelefonoEdit(nullptr), clientesTable(nullptr),
      productoIdLabel(nullptr), productoTipoCombo(nullptr), productoNombreEdit(nullptr), productoPrecioSpin(nullptr), productoStockSpin(nullptr), productosTable(nullptr),
      movimientoIdLabel(nullptr), movimientoTipoCombo(nullptr), movimientoClienteCombo(nullptr), movimientoProductoCombo(nullptr), movimientoCantidadSpin(nullptr), movimientoPagoCombo(nullptr), movimientoEstadoCombo(nullptr), movimientosTable(nullptr),
      reporteText(nullptr), reporteTipoCombo(nullptr)
{
    setWindowTitle("StockPoint Pro - POS e Inventario");
    resize(1180, 720);

    QString qss = R"(
        QWidget { background-color: #F6F8FB; color: #1F2937; font-family: Segoe UI, Arial; font-size: 13px; }
        QFrame#sidebar { background-color: #111827; border: none; }
        QLabel#brand { background-color: transparent; color: white; font-size: 23px; font-weight: 800; padding: 20px 16px 6px 16px; }
        QLabel#brandSub { background-color: transparent; color: #9CA3AF; padding: 0px 16px 18px 16px; }
        QPushButton#nav { background-color: transparent; color: #D1D5DB; border: none; border-radius: 10px; text-align: left; padding: 12px 16px; font-size: 14px; }
        QPushButton#nav:hover { background-color: #1F2937; color: white; }
        QPushButton#nav:pressed { background-color: #2563EB; color: white; }
        QFrame#card { background-color: white; border: 1px solid #E5E7EB; border-radius: 16px; }
        QLabel#title { font-size: 26px; font-weight: 800; color: #111827; }
        QLabel#subtitle { color: #6B7280; }
        QLabel#metricTitle { color: #6B7280; font-size: 13px; }
        QLabel#metricValue { color: #111827; font-size: 28px; font-weight: 800; }
        QLineEdit, QComboBox, QSpinBox, QDoubleSpinBox { background-color: white; border: 1px solid #D1D5DB; border-radius: 10px; padding: 8px; min-height: 25px; }
        QLineEdit:focus, QComboBox:focus, QSpinBox:focus, QDoubleSpinBox:focus { border: 1px solid #2563EB; }
        QPushButton { background-color: #2563EB; color: white; border: none; border-radius: 10px; padding: 10px 14px; font-weight: 600; }
        QPushButton:hover { background-color: #1D4ED8; }
        QPushButton#secondary { background-color: #E5E7EB; color: #111827; }
        QPushButton#secondary:hover { background-color: #D1D5DB; }
        QPushButton#danger { background-color: #EF4444; color: white; }
        QPushButton#danger:hover { background-color: #DC2626; }
        QTableWidget { background-color: white; border: 1px solid #E5E7EB; border-radius: 12px; gridline-color: #F3F4F6; selection-background-color: #DBEAFE; selection-color: #111827; }
        QHeaderView::section { background-color: #F3F4F6; color: #374151; border: none; padding: 8px; font-weight: 700; }
        QTextEdit { background-color: white; border: 1px solid #E5E7EB; border-radius: 12px; padding: 12px; font-family: Consolas, monospace; }
    )";
    setStyleSheet(qss);

    QWidget *central = new QWidget(this);
    QHBoxLayout *root = new QHBoxLayout(central);
    root->setContentsMargins(0, 0, 0, 0);
    root->setSpacing(0);

    QFrame *sidebar = new QFrame(central);
    sidebar->setObjectName("sidebar");
    sidebar->setFixedWidth(230);
    QVBoxLayout *sideLayout = new QVBoxLayout(sidebar);
    sideLayout->setContentsMargins(10, 10, 10, 10);
    sideLayout->setSpacing(8);

    QLabel *brand = new QLabel("StockPoint Pro", sidebar);
    brand->setObjectName("brand");
    QLabel *brandSub = new QLabel(" ", sidebar);
    brandSub->setObjectName("brandSub");
    sideLayout->addWidget(brand);
    sideLayout->addWidget(brandSub);

    QPushButton *dashboardBtn = createSidebarButton("Inicio");
    QPushButton *clientesBtn = createSidebarButton("Clientes");
    QPushButton *productosBtn = createSidebarButton("Productos");
    QPushButton *movimientosBtn = createSidebarButton("Movimientos");
    QPushButton *reportesBtn = createSidebarButton("Reportes");
    QPushButton *salirBtn = createSidebarButton("Salir");
    salirBtn->setObjectName("danger");
    salirBtn->setStyleSheet("text-align: left; padding: 12px 16px; border-radius: 10px; background-color: #EF4444; color: white;");

    sideLayout->addWidget(dashboardBtn);
    sideLayout->addWidget(clientesBtn);
    sideLayout->addWidget(productosBtn);
    sideLayout->addWidget(movimientosBtn);
    sideLayout->addWidget(reportesBtn);
    sideLayout->addStretch();
    sideLayout->addWidget(salirBtn);

    stack = new QStackedWidget(central);
    stack->addWidget(createDashboardPage());
    stack->addWidget(createClientesPage());
    stack->addWidget(createProductosPage());
    stack->addWidget(createMovimientosPage());
    stack->addWidget(createReportesPage());

    root->addWidget(sidebar);
    root->addWidget(stack, 1);
    setCentralWidget(central);

    connect(dashboardBtn, &QPushButton::clicked, this, [this]() { stack->setCurrentIndex(0); refreshAllViews(); });
    connect(clientesBtn, &QPushButton::clicked, this, [this]() { stack->setCurrentIndex(1); refreshAllViews(); });
    connect(productosBtn, &QPushButton::clicked, this, [this]() { stack->setCurrentIndex(2); refreshAllViews(); });
    connect(movimientosBtn, &QPushButton::clicked, this, [this]() { stack->setCurrentIndex(3); refreshAllViews(); });
    connect(reportesBtn, &QPushButton::clicked, this, [this]() { stack->setCurrentIndex(4); refreshAllViews(); generarReporte(); });
    connect(salirBtn, &QPushButton::clicked, this, [this]() { close(); });

    limpiarClienteForm();
    limpiarProductoForm();
    limpiarMovimientoForm();
    refreshAllViews();
}

QPushButton *MainWindow::createSidebarButton(const QString &text)
{
    QPushButton *button = new QPushButton(text);
    button->setObjectName("nav");
    button->setCursor(Qt::PointingHandCursor);
    return button;
}

QLabel *MainWindow::createTitle(const QString &text, const QString &subtitle)
{
    QLabel *label = new QLabel(QString("<span style='font-size:26px; font-weight:800;'>%1</span><br><span style='color:#6B7280;'>%2</span>").arg(text, subtitle));
    label->setTextFormat(Qt::RichText);
    return label;
}

QFrame *MainWindow::createCard()
{
    QFrame *frame = new QFrame;
    frame->setObjectName("card");
    frame->setFrameShape(QFrame::NoFrame);
    return frame;
}

QLabel *MainWindow::createMetricCard(const QString &title, const QString &value)
{
    QLabel *label = new QLabel(QString("<span style='color:#6B7280; font-size:13px;'>%1</span><br><span style='font-size:28px; font-weight:800; color:#111827;'>%2</span>").arg(title, value));
    label->setTextFormat(Qt::RichText);
    label->setMinimumHeight(95);
    label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    label->setContentsMargins(18, 10, 18, 10);
    label->setStyleSheet("background:white; border:1px solid #E5E7EB; border-radius:16px;");
    return label;
}

QTableWidget *MainWindow::createTable(const QStringList &headers)
{
    QTableWidget *table = new QTableWidget;
    table->setColumnCount(headers.size());
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setVisible(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAlternatingRowColors(true);
    return table;
}

QWidget *MainWindow::createDashboardPage()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);
    layout->setContentsMargins(28, 24, 28, 24);
    layout->setSpacing(18);
    layout->addWidget(createTitle("Inicio", "Resumen general del negocio"));

    QGridLayout *grid = new QGridLayout;
    grid->setSpacing(14);
    cardProductos = createMetricCard("Productos", "0");
    cardClientes = createMetricCard("Clientes", "0");
    cardMovimientos = createMetricCard("Movimientos", "0");
    cardIngresos = createMetricCard("Ingresos", "$0.00");
    cardStockBajo = createMetricCard("Stock bajo", "0");
    grid->addWidget(cardProductos, 0, 0);
    grid->addWidget(cardClientes, 0, 1);
    grid->addWidget(cardMovimientos, 0, 2);
    grid->addWidget(cardIngresos, 1, 0);
    grid->addWidget(cardStockBajo, 1, 1);
    layout->addLayout(grid);

    QFrame *info = createCard();
    QVBoxLayout *infoLayout = new QVBoxLayout(info);
    QLabel *infoText = new QLabel("StockPoint Pro permite registrar clientes, productos y movimientos de venta, entrada o devolucion. El inventario se actualiza automaticamente cuando el movimiento se aplica.");
    infoText->setWordWrap(true);
    infoLayout->addWidget(infoText);
    layout->addWidget(info);
    layout->addStretch();
    return page;
}

QWidget *MainWindow::createClientesPage()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);
    layout->setContentsMargins(28, 24, 28, 24);
    layout->setSpacing(16);
    layout->addWidget(createTitle("Clientes", "Alta, modificacion y consulta de clientes"));

    QFrame *formCard = createCard();
    QFormLayout *form = new QFormLayout(formCard);
    form->setContentsMargins(18, 18, 18, 18);
    clienteIdLabel = new QLabel;
    clienteTipoCombo = new QComboBox;
    clienteTipoCombo->addItems({"Cliente normal", "Cliente frecuente", "Cliente mayorista"});
    clienteNombreEdit = new QLineEdit;
    clienteNombreEdit->setPlaceholderText("Nombre del cliente");
    clienteTelefonoEdit = new QLineEdit;
    clienteTelefonoEdit->setPlaceholderText("Telefono");
    form->addRow("ID automatico", clienteIdLabel);
    form->addRow("Tipo", clienteTipoCombo);
    form->addRow("Nombre", clienteNombreEdit);
    form->addRow("Telefono", clienteTelefonoEdit);

    QHBoxLayout *buttons = new QHBoxLayout;
    QPushButton *registrar = new QPushButton("Registrar");
    QPushButton *modificar = new QPushButton("Modificar");
    QPushButton *limpiar = new QPushButton("Limpiar");
    limpiar->setObjectName("secondary");
    buttons->addWidget(registrar);
    buttons->addWidget(modificar);
    buttons->addWidget(limpiar);
    form->addRow(buttons);
    layout->addWidget(formCard);

    clientesTable = createTable({"ID", "Tipo", "Nombre", "Telefono", "Beneficio"});
    layout->addWidget(clientesTable, 1);

    connect(registrar, &QPushButton::clicked, this, [this]() { registrarCliente(); });
    connect(modificar, &QPushButton::clicked, this, [this]() { modificarCliente(); });
    connect(limpiar, &QPushButton::clicked, this, [this]() { limpiarClienteForm(); });
    connect(clientesTable, &QTableWidget::cellClicked, this, [this](int, int) { cargarClienteSeleccionado(); });
    return page;
}

QWidget *MainWindow::createProductosPage()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);
    layout->setContentsMargins(28, 24, 28, 24);
    layout->setSpacing(16);
    layout->addWidget(createTitle("Productos", "Inventario con codigo automatico y control de stock"));

    QFrame *formCard = createCard();
    QFormLayout *form = new QFormLayout(formCard);
    form->setContentsMargins(18, 18, 18, 18);
    productoIdLabel = new QLabel;
    productoTipoCombo = new QComboBox;
    productoTipoCombo->addItems({"Perecedero", "No perecedero", "Electronico", "Servicio"});
    productoNombreEdit = new QLineEdit;
    productoNombreEdit->setPlaceholderText("Nombre del producto o servicio");
    productoPrecioSpin = new QDoubleSpinBox;
    productoPrecioSpin->setRange(0.0, 1000000.0);
    productoPrecioSpin->setDecimals(2);
    productoPrecioSpin->setPrefix("$ ");
    productoStockSpin = new QSpinBox;
    productoStockSpin->setRange(0, 1000000);
    form->addRow("Codigo automatico", productoIdLabel);
    form->addRow("Tipo", productoTipoCombo);
    form->addRow("Nombre", productoNombreEdit);
    form->addRow("Precio", productoPrecioSpin);
    form->addRow("Stock", productoStockSpin);

    QHBoxLayout *buttons = new QHBoxLayout;
    QPushButton *registrar = new QPushButton("Registrar");
    QPushButton *modificar = new QPushButton("Modificar");
    QPushButton *borrar = new QPushButton("Borrar producto");
    QPushButton *limpiar = new QPushButton("Limpiar");
    borrar->setObjectName("danger");
    limpiar->setObjectName("secondary");
    buttons->addWidget(registrar);
    buttons->addWidget(modificar);
    buttons->addWidget(borrar);
    buttons->addWidget(limpiar);
    form->addRow(buttons);
    layout->addWidget(formCard);

    productosTable = createTable({"Codigo", "Tipo", "Nombre", "Precio", "Stock", "Estado"});
    layout->addWidget(productosTable, 1);

    connect(productoTipoCombo, &QComboBox::currentTextChanged, this, [this](const QString &tipo) {
        productoStockSpin->setEnabled(tipo != "Servicio");
        if (tipo == "Servicio") {
            productoStockSpin->setValue(0);
        }
    });
    connect(registrar, &QPushButton::clicked, this, [this]() { registrarProducto(); });
    connect(modificar, &QPushButton::clicked, this, [this]() { modificarProducto(); });
    connect(borrar, &QPushButton::clicked, this, [this]() { borrarProducto(); });
    connect(limpiar, &QPushButton::clicked, this, [this]() { limpiarProductoForm(); });
    connect(productosTable, &QTableWidget::cellClicked, this, [this](int, int) { cargarProductoSeleccionado(); });
    return page;
}

QWidget *MainWindow::createMovimientosPage()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);
    layout->setContentsMargins(28, 24, 28, 24);
    layout->setSpacing(16);
    layout->addWidget(createTitle("Movimientos", "Ventas, entradas de inventario y devoluciones"));

    QFrame *formCard = createCard();
    QFormLayout *form = new QFormLayout(formCard);
    form->setContentsMargins(18, 18, 18, 18);
    movimientoIdLabel = new QLabel;
    movimientoTipoCombo = new QComboBox;
    movimientoTipoCombo->addItems({"Venta", "Entrada inventario", "Devolucion"});
    movimientoClienteCombo = new QComboBox;
    movimientoProductoCombo = new QComboBox;
    movimientoCantidadSpin = new QSpinBox;
    movimientoCantidadSpin->setRange(1, 1000000);
    movimientoPagoCombo = new QComboBox;
    movimientoPagoCombo->addItems({"Efectivo", "Tarjeta", "Transferencia"});
    movimientoEstadoCombo = new QComboBox;
    form->addRow("ID automatico", movimientoIdLabel);
    form->addRow("Tipo", movimientoTipoCombo);
    form->addRow("Cliente", movimientoClienteCombo);
    form->addRow("Producto", movimientoProductoCombo);
    form->addRow("Cantidad", movimientoCantidadSpin);
    form->addRow("Pago", movimientoPagoCombo);
    form->addRow("Estado", movimientoEstadoCombo);

    QHBoxLayout *buttons = new QHBoxLayout;
    QPushButton *registrar = new QPushButton("Registrar movimiento");
    QPushButton *modificar = new QPushButton("Modificar estado");
    QPushButton *limpiar = new QPushButton("Limpiar");
    limpiar->setObjectName("secondary");
    buttons->addWidget(registrar);
    buttons->addWidget(modificar);
    buttons->addWidget(limpiar);
    form->addRow(buttons);
    layout->addWidget(formCard);

    movimientosTable = createTable({"ID", "Tipo", "Cliente", "Producto", "Cantidad", "Estado", "Importe"});
    layout->addWidget(movimientosTable, 1);

    connect(movimientoTipoCombo, &QComboBox::currentTextChanged, this, [this](const QString &) { actualizarEstadosMovimiento(); });
    connect(registrar, &QPushButton::clicked, this, [this]() { registrarMovimiento(); });
    connect(modificar, &QPushButton::clicked, this, [this]() { modificarEstadoMovimiento(); });
    connect(limpiar, &QPushButton::clicked, this, [this]() { limpiarMovimientoForm(); });
    connect(movimientosTable, &QTableWidget::cellClicked, this, [this](int, int) { cargarMovimientoSeleccionado(); });
    return page;
}

QWidget *MainWindow::createReportesPage()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);
    layout->setContentsMargins(28, 24, 28, 24);
    layout->setSpacing(16);
    layout->addWidget(createTitle("Reportes", "Resumenes de inventario, ventas y clientes"));

    QFrame *formCard = createCard();
    QHBoxLayout *top = new QHBoxLayout(formCard);
    top->setContentsMargins(18, 18, 18, 18);
    reporteTipoCombo = new QComboBox;
    reporteTipoCombo->addItems({"Inventario", "Ventas", "Clientes"});
    QPushButton *generar = new QPushButton("Generar reporte");
    QPushButton *descargar = new QPushButton("Descargar reporte");
    descargar->setObjectName("secondary");
    top->addWidget(reporteTipoCombo);
    top->addWidget(generar);
    top->addWidget(descargar);
    layout->addWidget(formCard);

    reporteText = new QTextEdit;
    reporteText->setReadOnly(true);
    layout->addWidget(reporteText, 1);

    connect(generar, &QPushButton::clicked, this, [this]() { generarReporte(); });
    connect(descargar, &QPushButton::clicked, this, [this]() { descargarReporte(); });
    return page;
}

void MainWindow::registrarCliente()
{
    const QString nombre = clienteNombreEdit->text().trimmed();
    const QString telefono = clienteTelefonoEdit->text().trimmed();
    if (nombre.isEmpty()) {
        QMessageBox::warning(this, "Validacion", "Ingresa el nombre del cliente.");
        return;
    }
    const int id = siguienteClienteId++;
    const QString tipo = clienteTipoCombo->currentText();
    if (tipo == "Cliente frecuente") {
        clientes.push_back(std::make_unique<ClienteFrecuente>(id, nombre, telefono));
    } else if (tipo == "Cliente mayorista") {
        clientes.push_back(std::make_unique<ClienteMayorista>(id, nombre, telefono));
    } else {
        clientes.push_back(std::make_unique<ClienteNormal>(id, nombre, telefono));
    }
    limpiarClienteForm();
    refreshAllViews();
}

void MainWindow::modificarCliente()
{
    const int id = clienteIdLabel->property("id").toInt();
    Persona *cliente = findClienteById(id);
    if (!cliente) {
        QMessageBox::warning(this, "Seleccion", "Selecciona un cliente de la tabla.");
        return;
    }
    if (clienteNombreEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validacion", "El nombre no puede estar vacio.");
        return;
    }

    const QString nuevoTipo = clienteTipoCombo->currentText();
    const QString nuevoNombre = clienteNombreEdit->text().trimmed();
    const QString nuevoTelefono = clienteTelefonoEdit->text().trimmed();

    if (cliente->getTipo() == nuevoTipo) {
        cliente->setNombre(nuevoNombre);
        cliente->setTelefono(nuevoTelefono);
    } else {
        Persona *clienteAnterior = cliente;
        std::unique_ptr<Persona> clienteNuevo;

        if (nuevoTipo == "Cliente frecuente") {
            clienteNuevo = std::make_unique<ClienteFrecuente>(id, nuevoNombre, nuevoTelefono);
        } else if (nuevoTipo == "Cliente mayorista") {
            clienteNuevo = std::make_unique<ClienteMayorista>(id, nuevoNombre, nuevoTelefono);
        } else {
            clienteNuevo = std::make_unique<ClienteNormal>(id, nuevoNombre, nuevoTelefono);
        }

        Persona *clienteNuevoPtr = clienteNuevo.get();
        for (auto &movimiento : movimientos) {
            if (Venta *venta = dynamic_cast<Venta*>(movimiento.get())) {
                if (venta->getCliente() == clienteAnterior) {
                    venta->setCliente(clienteNuevoPtr);
                }
            } else if (Devolucion *devolucion = dynamic_cast<Devolucion*>(movimiento.get())) {
                if (devolucion->getCliente() == clienteAnterior) {
                    devolucion->setCliente(clienteNuevoPtr);
                }
            }
        }

        for (auto &item : clientes) {
            if (item.get() == clienteAnterior) {
                item = std::move(clienteNuevo);
                break;
            }
        }
    }

    clienteIdLabel->setProperty("id", id);
    refreshAllViews();
}

void MainWindow::limpiarClienteForm()
{
    clienteIdLabel->setText(QString::number(siguienteClienteId));
    clienteIdLabel->setProperty("id", 0);
    clienteTipoCombo->setCurrentIndex(0);
    clienteNombreEdit->clear();
    clienteTelefonoEdit->clear();
}

void MainWindow::cargarClienteSeleccionado()
{
    const int row = clientesTable->currentRow();
    if (row < 0) return;
    const int id = clientesTable->item(row, 0)->text().toInt();
    Persona *cliente = findClienteById(id);
    if (!cliente) return;
    clienteIdLabel->setText(QString::number(cliente->getId()));
    clienteIdLabel->setProperty("id", cliente->getId());
    clienteTipoCombo->setCurrentText(cliente->getTipo());
    clienteNombreEdit->setText(cliente->getNombre());
    clienteTelefonoEdit->setText(cliente->getTelefono());
}

void MainWindow::registrarProducto()
{
    const QString nombre = productoNombreEdit->text().trimmed();
    if (nombre.isEmpty()) {
        QMessageBox::warning(this, "Validacion", "Ingresa el nombre del producto.");
        return;
    }
    const int codigo = siguienteProductoId++;
    const QString tipo = productoTipoCombo->currentText();
    const double precio = productoPrecioSpin->value();
    const int stock = (tipo == "Servicio") ? 0 : productoStockSpin->value();
    const QString estado = calcularEstadoProducto(tipo, stock);

    if (tipo == "Perecedero") {
        productos.push_back(std::make_unique<ProductoPerecedero>(codigo, nombre, precio, stock, estado));
    } else if (tipo == "Electronico") {
        productos.push_back(std::make_unique<ProductoElectronico>(codigo, nombre, precio, stock, estado));
    } else if (tipo == "Servicio") {
        productos.push_back(std::make_unique<Servicio>(codigo, nombre, precio, 0, estado));
    } else {
        productos.push_back(std::make_unique<ProductoNoPerecedero>(codigo, nombre, precio, stock, estado));
    }
    limpiarProductoForm();
    refreshAllViews();
}

void MainWindow::modificarProducto()
{
    const int codigo = productoIdLabel->property("codigo").toInt();
    Producto *producto = findProductoById(codigo);
    if (!producto) {
        QMessageBox::warning(this, "Seleccion", "Selecciona un producto de la tabla.");
        return;
    }
    if (productoNombreEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validacion", "El nombre no puede estar vacio.");
        return;
    }

    const QString nuevoTipo = productoTipoCombo->currentText();
    const QString nuevoNombre = productoNombreEdit->text().trimmed();
    const double nuevoPrecio = productoPrecioSpin->value();
    const int nuevoStock = (nuevoTipo == "Servicio") ? 0 : productoStockSpin->value();
    const QString nuevoEstado = calcularEstadoProducto(nuevoTipo, nuevoStock);

    if (producto->getTipo() == nuevoTipo) {
        producto->setNombre(nuevoNombre);
        producto->setPrecio(nuevoPrecio);
        producto->setStock(nuevoStock);
        producto->setEstado(nuevoEstado);
    } else {
        Producto *productoAnterior = producto;
        std::unique_ptr<Producto> productoNuevo;

        if (nuevoTipo == "Perecedero") {
            productoNuevo = std::make_unique<ProductoPerecedero>(codigo, nuevoNombre, nuevoPrecio, nuevoStock, nuevoEstado);
        } else if (nuevoTipo == "Electronico") {
            productoNuevo = std::make_unique<ProductoElectronico>(codigo, nuevoNombre, nuevoPrecio, nuevoStock, nuevoEstado);
        } else if (nuevoTipo == "Servicio") {
            productoNuevo = std::make_unique<Servicio>(codigo, nuevoNombre, nuevoPrecio, 0, nuevoEstado);
        } else {
            productoNuevo = std::make_unique<ProductoNoPerecedero>(codigo, nuevoNombre, nuevoPrecio, nuevoStock, nuevoEstado);
        }

        Producto *productoNuevoPtr = productoNuevo.get();
        for (auto &movimiento : movimientos) {
            if (movimiento->getProducto() == productoAnterior) {
                movimiento->setProducto(productoNuevoPtr);
            }
        }

        for (auto &item : productos) {
            if (item.get() == productoAnterior) {
                item = std::move(productoNuevo);
                break;
            }
        }
    }

    productoStockSpin->setEnabled(nuevoTipo != "Servicio");
    productoIdLabel->setProperty("codigo", codigo);
    refreshAllViews();
}

void MainWindow::borrarProducto()
{
    const int codigo = productoIdLabel->property("codigo").toInt();
    Producto *producto = findProductoById(codigo);
    if (!producto) {
        QMessageBox::warning(this, "Seleccion", "Selecciona un producto de la tabla.");
        return;
    }

    for (const auto &movimiento : movimientos) {
        if (movimiento->getProducto() == producto) {
            QMessageBox::warning(this, "No se puede borrar",
                                 "Este producto ya tiene movimientos registrados. Para conservar el historial de ventas e inventario, no se puede borrar.");
            return;
        }
    }

    const int respuesta = QMessageBox::question(this, "Confirmar borrado",
                                                QString("Deseas borrar el producto '%1'?").arg(producto->getNombre()),
                                                QMessageBox::Yes | QMessageBox::No);
    if (respuesta != QMessageBox::Yes) {
        return;
    }

    productos.erase(std::remove_if(productos.begin(), productos.end(), [codigo](const std::unique_ptr<Producto> &item) {
        return item->getCodigo() == codigo;
    }), productos.end());

    limpiarProductoForm();
    refreshAllViews();
}

void MainWindow::limpiarProductoForm()
{
    productoIdLabel->setText(QString::number(siguienteProductoId));
    productoIdLabel->setProperty("codigo", 0);
    productoTipoCombo->setCurrentIndex(0);
    productoNombreEdit->clear();
    productoPrecioSpin->setValue(0.0);
    productoStockSpin->setValue(0);
    productoStockSpin->setEnabled(true);
}

void MainWindow::cargarProductoSeleccionado()
{
    const int row = productosTable->currentRow();
    if (row < 0) return;
    const int codigo = productosTable->item(row, 0)->text().toInt();
    Producto *producto = findProductoById(codigo);
    if (!producto) return;
    productoIdLabel->setText(QString::number(producto->getCodigo()));
    productoIdLabel->setProperty("codigo", producto->getCodigo());
    productoTipoCombo->setCurrentText(producto->getTipo());
    productoNombreEdit->setText(producto->getNombre());
    productoPrecioSpin->setValue(producto->getPrecio());
    productoStockSpin->setValue(producto->getStock());
    productoStockSpin->setEnabled(producto->requiereStock());
}

void MainWindow::registrarMovimiento()
{
    if (productos.empty()) {
        QMessageBox::warning(this, "Validacion", "Registra al menos un producto.");
        return;
    }
    const QString tipo = movimientoTipoCombo->currentText();
    Persona *cliente = nullptr;
    if (tipo != "Entrada inventario") {
        if (clientes.empty()) {
            QMessageBox::warning(this, "Validacion", "Registra al menos un cliente.");
            return;
        }
        cliente = findClienteById(movimientoClienteCombo->currentData().toInt());
    }
    Producto *producto = findProductoById(movimientoProductoCombo->currentData().toInt());
    if (!producto) {
        QMessageBox::warning(this, "Validacion", "Selecciona un producto valido.");
        return;
    }
    const int cantidad = movimientoCantidadSpin->value();
    const QString estado = movimientoEstadoCombo->currentText();

    if (tipo == "Devolucion") {
        const int disponibleParaDevolver = cantidadDisponibleParaDevolucion(cliente, producto);
        if (disponibleParaDevolver <= 0) {
            QMessageBox::warning(this, "Devolucion no permitida",
                                 "No se puede registrar la devolucion porque este cliente no tiene una compra pagada de ese producto.");
            return;
        }
        if (cantidad > disponibleParaDevolver) {
            QMessageBox::warning(this, "Devolucion no permitida",
                                 QString("La cantidad a devolver supera la compra disponible. Cantidad disponible para devolver: %1.").arg(disponibleParaDevolver));
            return;
        }
    }

    const int id = siguienteMovimientoId++;

    std::unique_ptr<Movimiento> nuevo;
    if (tipo == "Venta") {
        nuevo = std::make_unique<Venta>(id, estado, producto, cantidad, cliente, movimientoPagoCombo->currentText());
    } else if (tipo == "Devolucion") {
        nuevo = std::make_unique<Devolucion>(id, estado, producto, cantidad, cliente);
    } else {
        nuevo = std::make_unique<EntradaInventario>(id, estado, producto, cantidad);
    }

    if (estadoActivaMovimiento(tipo, estado) && !nuevo->aplicar()) {
        QMessageBox::warning(this, "Stock insuficiente", "No hay stock suficiente para aplicar el movimiento.");
        siguienteMovimientoId--;
        return;
    }
    actualizarEstadoProducto(producto);
    movimientos.push_back(std::move(nuevo));
    limpiarMovimientoForm();
    refreshAllViews();
}

void MainWindow::modificarEstadoMovimiento()
{
    const int id = movimientoIdLabel->property("id").toInt();
    Movimiento *movimiento = findMovimientoById(id);
    if (!movimiento) {
        QMessageBox::warning(this, "Seleccion", "Selecciona un movimiento de la tabla.");
        return;
    }
    const QString tipo = movimiento->getTipo();
    const QString nuevoEstado = movimientoEstadoCombo->currentText();
    const bool debeAplicar = estadoActivaMovimiento(tipo, nuevoEstado);

    if (tipo == "Devolucion" && debeAplicar) {
        Devolucion *devolucion = dynamic_cast<Devolucion*>(movimiento);
        if (!devolucion || !devolucion->getCliente()) {
            QMessageBox::warning(this, "Devolucion no permitida", "La devolucion no tiene cliente valido.");
            return;
        }
        const int disponibleParaDevolver = cantidadDisponibleParaDevolucion(devolucion->getCliente(), devolucion->getProducto(), movimiento);
        if (disponibleParaDevolver <= 0) {
            QMessageBox::warning(this, "Devolucion no permitida",
                                 "No se puede aplicar la devolucion porque este cliente no tiene una compra pagada de ese producto.");
            return;
        }
        if (devolucion->getCantidad() > disponibleParaDevolver) {
            QMessageBox::warning(this, "Devolucion no permitida",
                                 QString("La cantidad a devolver supera la compra disponible. Cantidad disponible para devolver: %1.").arg(disponibleParaDevolver));
            return;
        }
    }

    if (!debeAplicar) {
        movimiento->revertir();
        movimiento->setEstado(nuevoEstado);
    } else {
        movimiento->setEstado(nuevoEstado);
        if (!movimiento->aplicar()) {
            QMessageBox::warning(this, "Stock insuficiente", "No se puede aplicar el movimiento por stock insuficiente.");
            movimiento->setEstado("Pendiente");
        }
    }
    actualizarEstadoProducto(movimiento->getProducto());
    refreshAllViews();
}

void MainWindow::limpiarMovimientoForm()
{
    movimientoIdLabel->setText(QString::number(siguienteMovimientoId));
    movimientoIdLabel->setProperty("id", 0);
    movimientoTipoCombo->setCurrentIndex(0);
    movimientoCantidadSpin->setValue(1);
    movimientoPagoCombo->setCurrentIndex(0);
    actualizarEstadosMovimiento();
    refreshCombos();
}

void MainWindow::cargarMovimientoSeleccionado()
{
    const int row = movimientosTable->currentRow();
    if (row < 0) return;
    const int id = movimientosTable->item(row, 0)->text().toInt();
    Movimiento *movimiento = findMovimientoById(id);
    if (!movimiento) return;
    movimientoIdLabel->setText(QString::number(movimiento->getId()));
    movimientoIdLabel->setProperty("id", movimiento->getId());
    movimientoTipoCombo->setCurrentText(movimiento->getTipo());
    actualizarEstadosMovimiento();
    movimientoProductoCombo->setCurrentText(QString("%1 - %2").arg(movimiento->getProducto()->getCodigo()).arg(movimiento->getProducto()->getNombre()));
    movimientoCantidadSpin->setValue(movimiento->getCantidad());
    movimientoEstadoCombo->setCurrentText(movimiento->getEstado());
}

void MainWindow::actualizarEstadosMovimiento()
{
    if (!movimientoEstadoCombo || !movimientoTipoCombo) return;
    const QString tipo = movimientoTipoCombo->currentText();
    movimientoEstadoCombo->clear();
    if (tipo == "Venta") {
        movimientoEstadoCombo->addItems({"Pagada", "Pendiente", "Cancelada"});
        movimientoClienteCombo->setEnabled(true);
        movimientoPagoCombo->setEnabled(true);
    } else if (tipo == "Devolucion") {
        movimientoEstadoCombo->addItems({"Aplicada", "Pendiente", "Cancelada"});
        movimientoClienteCombo->setEnabled(true);
        movimientoPagoCombo->setEnabled(false);
    } else {
        movimientoEstadoCombo->addItems({"Registrada", "Pendiente", "Cancelada"});
        movimientoClienteCombo->setEnabled(false);
        movimientoPagoCombo->setEnabled(false);
    }
}

void MainWindow::generarReporte()
{
    if (!reporteText || !reporteTipoCombo) return;
    const QString tipo = reporteTipoCombo->currentText();
    QString texto;
    if (tipo == "Ventas") {
        ReporteVentas reporte(2, "Reporte de ventas");
        texto = reporte.generarResumen(rawProductos(), rawClientes(), rawMovimientos());
    } else if (tipo == "Clientes") {
        ReporteClientes reporte(3, "Reporte de clientes");
        texto = reporte.generarResumen(rawProductos(), rawClientes(), rawMovimientos());
    } else {
        ReporteInventario reporte(1, "Reporte de inventario");
        texto = reporte.generarResumen(rawProductos(), rawClientes(), rawMovimientos());
    }
    reporteText->setPlainText(texto);
}

void MainWindow::descargarReporte()
{
    if (!reporteText || !reporteTipoCombo) return;
    if (reporteText->toPlainText().trimmed().isEmpty()) {
        generarReporte();
    }

    QString nombreBase = reporteTipoCombo->currentText().toLower();
    nombreBase.replace(" ", "_");
    const QString ruta = QFileDialog::getSaveFileName(
        this,
        "Descargar reporte",
        QDir::homePath() + "/reporte_" + nombreBase + ".txt",
        "Archivo de texto (*.txt);;Todos los archivos (*.*)"
    );

    if (ruta.isEmpty()) {
        return;
    }

    QFile archivo(ruta);
    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo guardar el reporte.");
        return;
    }

    archivo.write(reporteText->toPlainText().toUtf8());
    archivo.close();
    QMessageBox::information(this, "Reporte descargado", "El reporte se guardo correctamente.");
}

void MainWindow::refreshAllViews()
{
    refreshDashboard();
    refreshClientesTable();
    refreshProductosTable();
    refreshMovimientosTable();
    refreshCombos();
}

void MainWindow::refreshDashboard()
{
    int stockBajo = 0;
    double ingresos = 0.0;
    for (const auto &producto : productos) {
        if (producto->requiereStock() && producto->getStock() <= 5) {
            stockBajo++;
        }
    }
    for (const auto &movimiento : movimientos) {
        if (movimiento->getTipo() == "Venta" && movimiento->getEstado() == "Pagada") {
            ingresos += movimiento->calcularImporte();
        }
    }
    if (cardProductos) cardProductos->setText(QString("<span style='color:#6B7280; font-size:13px;'>Productos</span><br><span style='font-size:28px; font-weight:800;'>%1</span>").arg(productos.size()));
    if (cardClientes) cardClientes->setText(QString("<span style='color:#6B7280; font-size:13px;'>Clientes</span><br><span style='font-size:28px; font-weight:800;'>%1</span>").arg(clientes.size()));
    if (cardMovimientos) cardMovimientos->setText(QString("<span style='color:#6B7280; font-size:13px;'>Movimientos</span><br><span style='font-size:28px; font-weight:800;'>%1</span>").arg(movimientos.size()));
    if (cardIngresos) cardIngresos->setText(QString("<span style='color:#6B7280; font-size:13px;'>Ingresos</span><br><span style='font-size:28px; font-weight:800;'>$%1</span>").arg(ingresos, 0, 'f', 2));
    if (cardStockBajo) cardStockBajo->setText(QString("<span style='color:#6B7280; font-size:13px;'>Stock bajo</span><br><span style='font-size:28px; font-weight:800;'>%1</span>").arg(stockBajo));
}

void MainWindow::refreshClientesTable()
{
    if (!clientesTable) return;
    clientesTable->setRowCount(static_cast<int>(clientes.size()));
    for (int i = 0; i < static_cast<int>(clientes.size()); ++i) {
        Persona *cliente = clientes[i].get();
        clientesTable->setItem(i, 0, new QTableWidgetItem(QString::number(cliente->getId())));
        clientesTable->setItem(i, 1, new QTableWidgetItem(cliente->getTipo()));
        clientesTable->setItem(i, 2, new QTableWidgetItem(cliente->getNombre()));
        clientesTable->setItem(i, 3, new QTableWidgetItem(cliente->getTelefono()));
        clientesTable->setItem(i, 4, new QTableWidgetItem(QString("%1%").arg(cliente->calcularBeneficio() * 100.0, 0, 'f', 0)));
    }
}

void MainWindow::refreshProductosTable()
{
    if (!productosTable) return;
    productosTable->setRowCount(static_cast<int>(productos.size()));
    for (int i = 0; i < static_cast<int>(productos.size()); ++i) {
        Producto *producto = productos[i].get();
        productosTable->setItem(i, 0, new QTableWidgetItem(QString::number(producto->getCodigo())));
        productosTable->setItem(i, 1, new QTableWidgetItem(producto->getTipo()));
        productosTable->setItem(i, 2, new QTableWidgetItem(producto->getNombre()));
        productosTable->setItem(i, 3, new QTableWidgetItem(QString("$%1").arg(producto->getPrecio(), 0, 'f', 2)));
        productosTable->setItem(i, 4, new QTableWidgetItem(producto->requiereStock() ? QString::number(producto->getStock()) : "N/A"));
        productosTable->setItem(i, 5, new QTableWidgetItem(producto->getEstado()));
    }
}

void MainWindow::refreshMovimientosTable()
{
    if (!movimientosTable) return;
    movimientosTable->setRowCount(static_cast<int>(movimientos.size()));
    for (int i = 0; i < static_cast<int>(movimientos.size()); ++i) {
        Movimiento *movimiento = movimientos[i].get();
        QString cliente = "-";
        if (Venta *venta = dynamic_cast<Venta*>(movimiento)) {
            cliente = venta->getCliente() ? venta->getCliente()->getNombre() : "-";
        } else if (Devolucion *devolucion = dynamic_cast<Devolucion*>(movimiento)) {
            cliente = devolucion->getCliente() ? devolucion->getCliente()->getNombre() : "-";
        }
        movimientosTable->setItem(i, 0, new QTableWidgetItem(QString::number(movimiento->getId())));
        movimientosTable->setItem(i, 1, new QTableWidgetItem(movimiento->getTipo()));
        movimientosTable->setItem(i, 2, new QTableWidgetItem(cliente));
        movimientosTable->setItem(i, 3, new QTableWidgetItem(movimiento->getProducto() ? movimiento->getProducto()->getNombre() : "-"));
        movimientosTable->setItem(i, 4, new QTableWidgetItem(QString::number(movimiento->getCantidad())));
        movimientosTable->setItem(i, 5, new QTableWidgetItem(movimiento->getEstado()));
        movimientosTable->setItem(i, 6, new QTableWidgetItem(QString("$%1").arg(movimiento->calcularImporte(), 0, 'f', 2)));
    }
}

void MainWindow::refreshCombos()
{
    if (movimientoClienteCombo) {
        const int current = movimientoClienteCombo->currentData().toInt();
        movimientoClienteCombo->clear();
        for (const auto &cliente : clientes) {
            movimientoClienteCombo->addItem(QString("%1 - %2").arg(cliente->getId()).arg(cliente->getNombre()), cliente->getId());
        }
        const int idx = movimientoClienteCombo->findData(current);
        if (idx >= 0) movimientoClienteCombo->setCurrentIndex(idx);
    }
    if (movimientoProductoCombo) {
        const int current = movimientoProductoCombo->currentData().toInt();
        movimientoProductoCombo->clear();
        for (const auto &producto : productos) {
            movimientoProductoCombo->addItem(QString("%1 - %2").arg(producto->getCodigo()).arg(producto->getNombre()), producto->getCodigo());
        }
        const int idx = movimientoProductoCombo->findData(current);
        if (idx >= 0) movimientoProductoCombo->setCurrentIndex(idx);
    }
}

Persona *MainWindow::findClienteById(int id) const
{
    for (const auto &cliente : clientes) {
        if (cliente->getId() == id) {
            return cliente.get();
        }
    }
    return nullptr;
}

Producto *MainWindow::findProductoById(int codigo) const
{
    for (const auto &producto : productos) {
        if (producto->getCodigo() == codigo) {
            return producto.get();
        }
    }
    return nullptr;
}

Movimiento *MainWindow::findMovimientoById(int id) const
{
    for (const auto &movimiento : movimientos) {
        if (movimiento->getId() == id) {
            return movimiento.get();
        }
    }
    return nullptr;
}


QString MainWindow::calcularEstadoProducto(const QString &tipo, int stock) const
{
    if (tipo == "Servicio") {
        return "Activo";
    }
    if (stock <= 0) {
        return "Agotado";
    }
    if (stock <= 5) {
        return "Bajo stock";
    }
    return "Disponible";
}

void MainWindow::actualizarEstadoProducto(Producto *producto)
{
    if (!producto) {
        return;
    }
    producto->setEstado(calcularEstadoProducto(producto->getTipo(), producto->getStock()));
}

bool MainWindow::estadoActivaMovimiento(const QString &tipo, const QString &estado) const
{
    return (tipo == "Venta" && estado == "Pagada") ||
           (tipo == "Entrada inventario" && estado == "Registrada") ||
           (tipo == "Devolucion" && estado == "Aplicada");
}

int MainWindow::cantidadDisponibleParaDevolucion(Persona *cliente, Producto *producto, const Movimiento *excluirMovimiento) const
{
    if (!cliente || !producto) {
        return 0;
    }

    int cantidadComprada = 0;
    int cantidadDevuelta = 0;

    for (const auto &item : movimientos) {
        const Movimiento *movimiento = item.get();
        if (!movimiento || movimiento == excluirMovimiento || movimiento->getProducto() != producto) {
            continue;
        }

        if (const Venta *venta = dynamic_cast<const Venta*>(movimiento)) {
            if (venta->getCliente() == cliente && venta->getEstado() == "Pagada") {
                cantidadComprada += venta->getCantidad();
            }
        } else if (const Devolucion *devolucion = dynamic_cast<const Devolucion*>(movimiento)) {
            if (devolucion->getCliente() == cliente && devolucion->getEstado() == "Aplicada") {
                cantidadDevuelta += devolucion->getCantidad();
            }
        }
    }

    const int disponible = cantidadComprada - cantidadDevuelta;
    return disponible > 0 ? disponible : 0;
}

std::vector<Persona*> MainWindow::rawClientes() const
{
    std::vector<Persona*> data;
    for (const auto &cliente : clientes) {
        data.push_back(cliente.get());
    }
    return data;
}

std::vector<Producto*> MainWindow::rawProductos() const
{
    std::vector<Producto*> data;
    for (const auto &producto : productos) {
        data.push_back(producto.get());
    }
    return data;
}

std::vector<Movimiento*> MainWindow::rawMovimientos() const
{
    std::vector<Movimiento*> data;
    for (const auto &movimiento : movimientos) {
        data.push_back(movimiento.get());
    }
    return data;
}
