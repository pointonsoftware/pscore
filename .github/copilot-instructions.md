# PSCORE - AI Coding Agent Instructions

## Architecture Overview
PSCORE is a **3-layer business management engine** following Clean Architecture principles:
- **`core/`** - Pure business logic (entities, domain controllers, validators)  
- **`orchestra/`** - Application layer (UI, data access)
- **`utility/`** - Infrastructure services (logging, config, file I/O)

**Key Principle**: Business logic never depends on infrastructure. Dependencies flow inward via interfaces.

## Important References
**Developer Reference Guide**: For comprehensive setup instructions, detailed workflows, troubleshooting, and advanced development topics, consult `.github/instructions/developer-reference.md`. **Load this document when developers need:**
- Detailed environment setup and troubleshooting
- Complete build system configuration
- Advanced CMake usage and cross-platform builds
- Code quality tools integration (cppcheck, cpplint, gcov)
- Git workflow best practices
- Performance profiling guidance
- Production deployment procedures

## Development Setup
**Prerequisites**: CMake, C++17 compiler (MinGW for Windows), Qt Creator (optional)
**Build**: `./clean_build.sh` (Linux) or import root `CMakeLists.txt` in Qt Creator
**Submodules**: `git submodule init && git submodule update`
**Output**: `build/lib/` (domain libraries), `build/bin/` (console_app + configs)

## Domain-Driven Design Pattern
Each business domain follows this structure:
```
core/domain/{domain}/
├── {domain}controller.hpp/cpp     # Business logic orchestrator
├── interface/
│   ├── {domain}iface.hpp         # Controller interface + factory
│   ├── {domain}dataif.hpp        # Data access interface  
│   └── {domain}viewif.hpp        # UI presentation interface
```

**Example**: `inventory/`, `customermgmt/`, `employeemgmt/`, `userlogin/`, `accounting/`

## Essential Patterns

### 1. Factory Pattern (Module Creation)
Every domain exposes a factory function with `CORE_API`:
```cpp
// In interface/{domain}iface.hpp
CORE_API InventoryControllerPtr createInventoryModule(
    const InventoryDataPtr& data, const InventoryViewPtr& view);

// Implementation returns unique_ptr
return std::make_unique<InventoryController>(data, view);
```

### 2. BaseController Template
Controllers inherit from `BaseController<DataInterface, ViewInterface, EntityType>`:
```cpp
class InventoryController : public InventoryControlInterface,
                           public BaseController<InventoryDataInterface,
                                                InventoryViewInterface,
                                                entity::Product>
```
Provides caching via `mCachedList` and dependency injection via `mDataProvider`/`mView`.

### 3. Status Enums + Validation
All operations return domain-specific status enums:
```cpp
enum class INVENTORYAPISTATUS { SUCCESS, FAILED, UNINITIALIZED, NOT_FOUND };

// Operations accept validation result maps
INVENTORYAPISTATUS save(const entity::Product& product,
                       std::map<std::string, std::string>* validationResult);
```

### 4. Entity Field Constants
Entities define validation field constants:
```cpp
// In entity/product.hpp
constexpr char FIELD_BCODE[] = "Product.Barcode";
constexpr char FIELD_PNAME[] = "Product.Name";
```

### 5. Structured Logging
Use `LOG_DEBUG`, `LOG_INFO`, `LOG_WARN`, `LOG_ERROR` macros:
```cpp
#include <logger/loghelper.hpp>
LOG_DEBUG("Creating product with code %s", product.barcode().c_str());
```
**Logging Guidelines**
- `LOG_DEBUG` - Verbose logging for development
- `LOG_INFO` - Useful information about user actions
- `LOG_WARN` - Expected failures that are handled by system  
- `LOG_ERROR` - Critical conditions that should not fail
- Log all database operations with timing information

## Coding Standards

### Design Principles
**Always consider YAGNI + SOLID + KISS + DRY principles when designing or adding new code**
- **YAGNI** (You Aren't Gonna Need It) - Don't implement features until they're actually needed
- **SOLID** - Single Responsibility, Open/Closed, Liskov Substitution, Interface Segregation, Dependency Inversion
- **KISS** (Keep It Simple, Stupid) - Favor simple solutions over complex ones
- **DRY** (Don't Repeat Yourself) - Eliminate code duplication through abstraction

**Must follow Clean Architecture principles:**
- Business logic (`core/`) never depends on infrastructure or UI
- Dependencies flow inward toward business rules
- Use interfaces to decouple layers and enable testing
- Keep domain entities independent of external frameworks

### Functions & Design
- Keep functions **short and single-purpose** - each should perform one operation
- Use meaningful, related function names
- Declare small, time-critical functions as `inline`
- Take `T*` or `T&` arguments rather than smart pointers for general use
- Functions must maintain program invariants even when exceptions occur

### Namespacing
Give appropriate namespace to all code in your module (e.g., `domain::inventory`)

## Testing Architecture

### Unit Test Structure
Tests in `core/domain/unittest/` with comprehensive mocking:
```cpp
// Test class pattern
class TestInventory : public testing::Test {
 public:
    TestInventory() : inventoryController(dpMock, viewMock) {}
    
    std::shared_ptr<InventoryDataMock> dpMock;
    std::shared_ptr<InventoryViewMock> viewMock;
    InventoryController inventoryController;
};

// Mock pattern using Google Mock
MOCK_METHOD(std::vector<entity::Product>, getProducts, (), (override));
```

### Test Naming Convention
- Test files: `test_{domain}.cpp`
- Mock files: `mock/{domain}/{domain}datamock.hpp`, `mock/{domain}/{domain}viewmock.hpp`
- Test classes: `Test{Domain}`

## Build System

### Development Workflow
```bash
# Clean build (recommended for development)
./clean_build.sh

# Build output structure:
build/
├── lib/          # Generated domain libraries
├── bin/          # Executable + configs
└── ...
```

### CMake Configuration
- Root `CMakeLists.txt` enables: `BUILD_UNITTEST=ON`, `BUILD_ALL_COMPONENTS=ON`
- Each component has its own `CMakeLists.txt`
- Test builds include code coverage flags (`-fprofile-arcs -ftest-coverage`)

## Data Layer Integration
Data providers in `orchestra/datamanager/` implement domain interfaces:
```cpp
// Pattern: {domain}data.hpp/cpp
class InventoryDataProvider : public domain::inventory::InventoryDataInterface {
    // Implements SQLite operations
};
```

## Header Guard Convention
```cpp
#ifndef CORE_DOMAIN_INVENTORY_INVENTORYCONTROLLER_HPP_
#define CORE_DOMAIN_INVENTORY_INVENTORYCONTROLLER_HPP_
// Pattern: PATH_FILENAME_HPP_ (all caps, slashes become underscores)
```

## Critical Files
- `core/domain/common/basecontroller.hpp` - Base controller template
- `core/domain/unittest/CMakeLists.txt` - Test build configuration  
- `orchestra/datamanager/` - Data access implementations
- `utility/logger/loghelper.hpp` - Logging macros

## When Adding New Features
1. **New Entity**: Add to `core/entity/` + corresponding validator in `core/validator/`
2. **New Domain**: Follow existing domain structure pattern
3. **New Business Rule**: Add to appropriate controller, never in data layer
4. **Tests Required**: Controller tests with mocks, entity tests for validation

## Adding New Core Modules (Step-by-Step)
1. **API Creation**: Create module folder in `core/domain/`, add `CMakeLists.txt`
2. **Interfaces**: Create controller, data, view interfaces in `interface/` folder
3. **Controller**: Inherit from controller interface, implement pure virtual functions
4. **Screen**: Add new screen in `orchestra/application/screen/` (inherit from `ScreenInterface`)
5. **Data Provider**: Create in `orchestra/datamanager/`, inherit from data interface
6. **Integration**: Add to parent `CMakeLists.txt` files and flow controller

## Adding New Screens
1. Create `.hpp/.cpp` in `orchestra/application/screen/` with copyright notice
2. Add files to `orchestra/application/CMakeLists.txt`  
3. Include `<screeniface.hpp>`, inherit from `screen::ScreenInterface`
4. Add enum to `screendefines.hpp`, add switch-case in `FlowController::show()`

Focus on maintaining **separation of concerns** and **dependency inversion** - business logic should never know about databases, UI frameworks, or external services directly.
