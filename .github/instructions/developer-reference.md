# PSCORE - Developer Reference Guide

## Development Environment Setup

### Required Tools
- **CMake** 3.9.2+ 
- **C++17 Compiler** (gcc-7+ recommended, MinGW for Windows)
- **Qt Creator** (optional but recommended IDE)
- **Git** with GitHub access

### Qt Creator Setup (Optional)
1. Download Qt from https://www.qt.io/download-open-source
2. Install with these components:
   - **Qt 5.15.0**: MinGW 8.1.0 (32/64-bit), Sources, Qt Charts, Qt Data Visualization
   - **Developer Tools**: Qt Creator, CDB Debugger, Debugging Tools, MinGW, CMake, Ninja
3. Import project: File → Open File or Project → Select root `CMakeLists.txt`
4. Configure for Desktop MinGW 64-bit
5. Right-click core project → Run CMake

### Repository Setup
```bash
git clone git@github.com:pointonsoftware/pscore.git
cd pscore
git submodule init && git submodule update
```

## Build System

### Build Commands
```bash
# Linux - Clean build (recommended)
./clean_build.sh

# Windows - Use Qt Creator or:
mkdir build && cd build
cmake -G "Unix Makefiles" -DBUILD_UNITTEST=ON -DBUILD_ALL_COMPONENTS=ON ..
make
```

### Build Configuration Options
- `BUILD_ALL_COMPONENTS=ON` - Build app and data layer
- `BUILD_UNITTEST=ON` - Build unit tests with gcov coverage
- `BUILD_LOG_CLIENT=OFF` - Build socket logger client

### Output Structure
```
build/
├── lib/          # Domain libraries (core business logic)
├── bin/          # console_app executable + config files
└── ...           # Intermediate build files
```

## Architecture Deep Dive

### Data Flow
```
UI Layer (orchestra/application) 
    ↓ (via interfaces)
Business Logic (core/domain controllers)
    ↓ (via data interfaces)  
Data Access (orchestra/datamanager)
    ↓
Database (SQLite via StackDB)
```

### Database Schema (In-Memory StackDB)
Key table structures in `orchestra/migration/storage/table.hpp`:
- **EmployeeTableItem**: employeeID, firstname, lastname, position, status, isSystemUser
- **UserTableItem**: userID, role, PIN, createdAt, employeeID (FK)
- **ProductTableItem**: barcode, sku, name, category, brand, uom, stock, prices
- **SalesTableItem**: ID, datetime, totals, payment info, cashierID, customerID
- **SalesItemTableItem**: saleID, productID, quantities, prices

## Coding Standards & Patterns

### Function Design Principles
```cpp
// BAD - Monolithic function
void read_and_print() {
    int x;
    cin >> x;
    cout << x << "\n";
}

// GOOD - Single responsibility, reusable
int read(istream& is) {
    int x;
    is >> x;
    return x;
}

void print(ostream& os, int x) {
    os << x << "\n";
}
```

### Smart Pointer Guidelines
- **For general use**: Take `T*` or `T&` arguments rather than smart pointers
- **Only use smart pointers** when you need to manage ownership
- **Avoid smart pointers** for function parameters that won't be stored

### Const-ness Patterns
```cpp
int       *      mutable_pointer_to_mutable_int;
int const *      mutable_pointer_to_constant_int;
int       *const constant_pointer_to_mutable_int; 
int const *const constant_pointer_to_constant_int;
```

### Logging Best Practices
- **Always log database operations** with timing info
- **LOG_DEBUG**: Development/verbose logging
- **LOG_INFO**: User action tracking
- **LOG_WARN**: Expected but handled failures
- **LOG_ERROR**: Critical failures that shouldn't happen

Example:
```cpp
LOG_DEBUG("Starting product creation with barcode %s", product.barcode().c_str());
// ... database operation
LOG_INFO("Product %s created successfully", product.name().c_str());
```

## Module Creation Workflow

### 1. Core Module (Business Logic)
```bash
# 1. Create directory structure
core/domain/newmodule/
├── CMakeLists.txt
├── newmodulecontroller.hpp/cpp
└── interface/
    ├── newmoduleiface.hpp      # Controller interface + factory
    ├── newmoduledataif.hpp     # Data access interface
    └── newmoduleviewif.hpp     # UI interface
```

### 2. Data Provider (Data Access)
```bash
# 2. Create data provider
orchestra/datamanager/
├── newmoduledata.hpp/cpp       # Implements data interface
└── CMakeLists.txt             # Add new files
```

### 3. Screen/View (UI Layer)  
```bash
# 3. Create screen
orchestra/application/screen/
├── newmodulescreen.hpp/cpp     # Implements view interface
└── screendefines.hpp          # Add enum for screen
```

### 4. Integration Points
- Add subdirectory to parent `CMakeLists.txt`
- Add screen enum to `screendefines.hpp`
- Add switch case in `FlowController::show()`
- Create factory function with `CORE_API`

## Testing Framework

### Test Structure
```cpp
class TestNewModule : public testing::Test {
 public:
    TestNewModule() : controller(dataMock, viewMock) {}
    
    std::shared_ptr<NewModuleDataMock> dataMock;
    std::shared_ptr<NewModuleViewMock> viewMock;
    NewModuleController controller;
};

TEST_F(TestNewModule, ShouldCreateEntitySuccessfully) {
    // Arrange
    Entity validEntity("test-data");
    EXPECT_CALL(*dataMock, create(_)).WillOnce(Return());
    
    // Act
    auto result = controller.save(validEntity);
    
    // Assert  
    ASSERT_EQ(NEWMODULEAPISTATUS::SUCCESS, result);
}
```

### Mock Patterns
- **Location**: `core/domain/unittest/mock/{domain}/`
- **Naming**: `{domain}datamock.hpp`, `{domain}viewmock.hpp`
- **Inheritance**: Inherit from domain interfaces, use `MOCK_METHOD`

## Release Process

### Creating Releases
```bash
# 1. Generate changelog
git log --pretty=%s v0.4.x..HEAD

# 2. Create and push tag  
git tag v0.5.0
git push origin v0.5.0

# 3. Create GitHub release with format:
### Upgrade Steps
- [ACTION REQUIRED] Migration steps if needed

### Breaking Changes  
- API changes that break compatibility

### New Features
- Major new functionality

### Bug Fixes
- Issue resolutions

### Improvements  
- Performance/UX enhancements

### Other Changes
- Documentation, dependencies, etc.
```

## File Templates

### Header Guard Format
```cpp
#ifndef CORE_DOMAIN_INVENTORY_INVENTORYCONTROLLER_HPP_
#define CORE_DOMAIN_INVENTORY_INVENTORYCONTROLLER_HPP_
// Format: PATH_FILENAME_HPP_ (all caps, slashes become underscores)
```

### Copyright Notice (Required for all files)
```cpp
/**************************************************************************************************
*                                            PSCORE                                               *
*                               Copyright (C) 2020 Pointon Software                               *
*                                                                                                 *
*           This program is free software: you can redistribute it and/or modify                  *
*           it under the terms of the GNU Affero General Public License as published              *
*           by the Free Software Foundation, either version 3 of the License, or                  *
*           (at your option) any later version.                                                   *
*                                                                                                 *
*           This program is distributed in the hope that it will be useful,                       *
*           but WITHOUT ANY WARRANTY; without even the implied warranty of                        *
*           MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                         *
*           GNU Affero General Public License for more details.                                   *
*                                                                                                 *
*           You should have received a copy of the GNU Affero General Public License              *
*           with this program.  If not, see <https://www.gnu.org/licenses/>.                      *
*                                                                                                 *
*           Ben Ziv <pointonsoftware@gmail.com>                                                   *
*                                                                                                 *
**************************************************************************************************/
```

## Design Patterns Used

- **Factory Pattern**: Module creation with `CORE_API` functions
- **Adapter Pattern**: Extend `std::string` for null handling and utilities
- **Builder Pattern**: JSON string construction, entity builders  
- **Builder Facet**: Complex entity construction (Person → Customer/Employee/User)
- **Template Pattern**: `BaseController` for common controller functionality
- **Dependency Injection**: Controllers receive data/view interfaces

## Troubleshooting

### Console App Issues
- **Qt Creator**: Enable "Run in Terminal" in Build & Run configuration
- **Ubuntu Linux**: Tools → Options → Environment → System, select correct terminal

### Build Issues  
- **Submodules**: Ensure `git submodule update` completed successfully
- **MinGW Path**: Verify MinGW is in system PATH for Windows builds
- **CMake Version**: Ensure CMake 3.9.2+ is available

This developer reference complements the concise Copilot instructions with detailed setup, workflows, and standards.
