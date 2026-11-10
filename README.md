# StockPoint Pro

A desktop point-of-sale and inventory management application built with C++17 and Qt Widgets.

## Features

- Manage regular, frequent, and wholesale customers.
- Manage perishable, non-perishable, and electronic products, plus services.
- Record sales, inventory entries, and returns.
- Update inventory when stock movements are recorded.
- Review inventory, sales, and customer reports.

## Requirements

- CMake 3.16 or newer.
- A C++17 compiler.
- Qt 5 or Qt 6 with the Widgets module.

## Build

Open `CMakeLists.txt` in Qt Creator, select a Desktop kit with Qt Widgets, then configure, build, and run the project.

Or use CMake from a shell where Qt is discoverable:

```bash
cmake -S . -B build
cmake --build build
```

If CMake cannot find Qt, set `CMAKE_PREFIX_PATH` to the Qt installation for your compiler and platform.

## Data storage

The application currently keeps records in memory. Data entered during a session is cleared when the application closes.


