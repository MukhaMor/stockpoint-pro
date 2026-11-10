# StockPoint Pro

StockPoint Pro is a desktop point-of-sale and inventory app written in C++17 with Qt Widgets.

It handles three customer types (regular, frequent, and wholesale), several product types, and services. The app can record sales, stock entries, and returns, update inventory after stock movements, and show reports for inventory, sales, and customers.

The app currently keeps its records in memory. Closing it clears the data.

## Build

Open `CMakeLists.txt` in Qt Creator and select a Desktop kit with Qt Widgets (Qt 5 or Qt 6). Configure the project, then build and run it.

The project uses CMake 3.16 and C++17.
