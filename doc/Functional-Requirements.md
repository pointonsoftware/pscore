# PSCORE - Functional Requirements Document (FRD)

**Document Version:** 1.0  
**Date:** August 24, 2025  
**Project:** PSCORE Business Management Engine  
**Repository:** https://github.com/pointonsoftware/pscore  

---

## 1. EXECUTIVE SUMMARY

### 1.1 Project Overview
PSCORE is a comprehensive business management engine designed to provide core functionality for Point of Sale (POS) systems, inventory management, customer relationship management, and business analytics. The system serves as a reusable, framework-agnostic engine that can be integrated into various business applications.

### 1.2 Business Objectives
- **Primary Goal**: Provide a robust, scalable business management engine for small to medium enterprises
- **Target Industries**: Retail, hospitality, service businesses requiring POS and inventory management
- **Key Value Proposition**: Clean architecture, comprehensive testing, framework independence

---

## 2. SYSTEM OVERVIEW

### 2.1 System Architecture
**Architecture Type:** Clean Architecture (3-Layer)
- **Core Layer**: Business entities, domain logic, validators
- **Application Layer**: UI screens, data access providers  
- **Infrastructure Layer**: Logging, configuration, utilities

### 2.2 Current Version Status
- **Current Version**: v0.4.12
- **Release Status**: Active development with comprehensive unit testing
- **Platform Support**: Linux, Windows (MinGW), cross-platform compatible

---

## 3. FUNCTIONAL REQUIREMENTS

## 3.1 USER AUTHENTICATION & AUTHORIZATION

### 3.1.1 User Login System
**FR-AUTH-001: User Authentication**
- **Description**: System shall authenticate users using User ID and PIN
- **Inputs**: User ID (case-insensitive), PIN (numeric)
- **Processing**: 
  - Validate PIN format and length
  - Retrieve user data from database
  - Verify credentials match
  - Establish user session
- **Outputs**: Authentication success/failure, user session data
- **Business Rules**:
  - PIN must be valid format
  - User ID is case-insensitive
  - Invalid attempts logged for security
  - Empty User ID rejected immediately

**FR-AUTH-002: User Session Management**
- **Description**: System shall maintain user session throughout application usage
- **Inputs**: Authenticated user data
- **Processing**: Track current user, role, and permissions
- **Outputs**: Current user context for business operations
- **Business Rules**:
  - Session persists until explicit logout
  - User role determines accessible features
  - Employee-linked users have extended privileges

## 3.2 EMPLOYEE MANAGEMENT

### 3.2.1 Employee Data Management
**FR-EMP-001: Employee Registration**
- **Description**: System shall register new employees with comprehensive personal information
- **Inputs**: Personal details, contact information, address, personal IDs, employment details
- **Processing**:
  - Validate all required fields
  - Generate unique employee ID
  - Store personal, contact, and employment data
  - Create associated address and personal ID records
- **Outputs**: Employee record, unique employee ID
- **Business Rules**:
  - Employee ID must be unique
  - Required fields: firstname, lastname, birthdate, gender, position, status
  - Status values: ACTIVE, ON-LEAVE, INACTIVE
  - System users flag indicates login capability

**FR-EMP-002: Employee Information Retrieval**
- **Description**: System shall retrieve employee information with related data
- **Inputs**: Employee ID or search criteria
- **Processing**:
  - Query employee table
  - Join with address, contact, and personal ID tables
  - Return complete employee profile
- **Outputs**: Complete employee record with all related information
- **Business Rules**:
  - Return empty record if employee not found
  - Include all related data (address, contacts, personal IDs)

**FR-EMP-003: Employee Information Update**
- **Description**: System shall update existing employee information
- **Inputs**: Employee ID, updated field values
- **Processing**:
  - Validate updated information
  - Update employee record and related tables
  - Log changes for audit trail
- **Outputs**: Update confirmation, validation errors if any
- **Business Rules**:
  - Maintain data integrity across related tables
  - Validate all field constraints
  - Preserve audit trail

**FR-EMP-004: System User Creation**
- **Description**: System shall create system user accounts for employees
- **Inputs**: Employee record, PIN, role information
- **Processing**:
  - Generate unique user ID from employee name
  - Create user record with role and PIN
  - Link to employee record
- **Outputs**: User account details, generated user ID
- **Business Rules**:
  - User ID must be unique across system
  - PIN stored securely
  - Role determines system access level
  - Only system-enabled employees can have user accounts

### 3.2.2 Employee Listing and Search
**FR-EMP-005: Employee Listing**
- **Description**: System shall provide paginated listing of all employees
- **Inputs**: Optional search/filter criteria
- **Processing**: Query employee database with optional filters
- **Outputs**: List of employees with key information
- **Business Rules**:
  - Display active employees by default
  - Support filtering by status, department, etc.

## 3.3 CUSTOMER MANAGEMENT

### 3.3.1 Customer Data Operations
**FR-CUST-001: Customer Registration**
- **Description**: System shall register new customers with personal information
- **Inputs**: Customer personal details (firstname, lastname, birthdate, gender)
- **Processing**:
  - Validate customer information
  - Generate unique customer ID
  - Store customer record
- **Outputs**: Customer record, unique customer ID
- **Business Rules**:
  - Customer ID must be unique
  - Required fields: firstname, lastname
  - Optional fields: middlename, birthdate, gender

**FR-CUST-002: Customer Information Management**
- **Description**: System shall support CRUD operations for customer data
- **Inputs**: Customer data for create/update, customer ID for read/delete
- **Processing**:
  - Validate input data
  - Perform requested operation
  - Update database accordingly
- **Outputs**: Operation result, updated customer data
- **Business Rules**:
  - Maintain referential integrity
  - Validate all field constraints
  - Prevent deletion of customers with transaction history

## 3.4 INVENTORY MANAGEMENT

### 3.4.1 Product Management
**FR-INV-001: Product Registration**
- **Description**: System shall register products with comprehensive details
- **Inputs**: Product information (barcode, SKU, name, description, category, brand, UOM, pricing, supplier)
- **Processing**:
  - Validate product information
  - Check barcode uniqueness
  - Store product record
  - Update inventory cache
- **Outputs**: Product record, validation results
- **Business Rules**:
  - Barcode must be unique (primary identifier)
  - Required fields: barcode, name, category, UOM, pricing
  - Selling price ≥ original price
  - Stock must be positive integer
  - Status values: High, Active, Reorder, Low Stock

**FR-INV-002: Product Retrieval and Listing**
- **Description**: System shall retrieve product information and provide product listings
- **Inputs**: Barcode for specific product, optional filters for listing
- **Processing**:
  - Query product database
  - Apply filters if specified
  - Return product data with caching
- **Outputs**: Product records, "product not found" if applicable
- **Business Rules**:
  - Use barcode as primary lookup key
  - Cache frequently accessed products
  - Support filtering by category, status, supplier

**FR-INV-003: Product Information Updates**
- **Description**: System shall update existing product information
- **Inputs**: Product barcode, updated field values
- **Processing**:
  - Validate updates against business rules
  - Update product record
  - Refresh cache
  - Log changes
- **Outputs**: Update confirmation, validation errors
- **Business Rules**:
  - Barcode cannot be changed (primary key)
  - Maintain price validation rules
  - Update inventory cache immediately

**FR-INV-004: Product Removal**
- **Description**: System shall remove products from inventory
- **Inputs**: Product barcode
- **Processing**:
  - Verify product exists
  - Check for transaction dependencies
  - Remove from database and cache
- **Outputs**: Removal confirmation
- **Business Rules**:
  - Cannot remove products with transaction history
  - Update all related caches
  - Log removal for audit trail

### 3.4.2 Inventory Organization
**FR-INV-005: Category Management**
- **Description**: System shall manage product categories
- **Inputs**: Category name for create/delete operations
- **Processing**:
  - Validate category information
  - Ensure category uniqueness
  - Update product categorization
- **Outputs**: Category list, operation results
- **Business Rules**:
  - Category names must be unique
  - Cannot delete categories with associated products
  - Predefined categories: Grocery, Medicine, Beverage

**FR-INV-006: Unit of Measurement (UOM) Management**
- **Description**: System shall manage units of measurement for products
- **Inputs**: UOM details (name, abbreviation)
- **Processing**:
  - Validate UOM information
  - Store UOM record
  - Make available for product assignment
- **Outputs**: UOM list, operation confirmations
- **Business Rules**:
  - UOM names and abbreviations must be unique
  - Cannot delete UOMs used by existing products
  - Standard UOMs: pieces, liters, kilograms, etc.

## 3.5 POINT OF SALE (POS) SYSTEM

### 3.5.1 Sales Transaction Processing
**FR-POS-001: Sale Computation**
- **Description**: System shall compute sales totals with tax and discount calculations
- **Inputs**: Subtotal amount, discount type (None, SCPWD, Coupon)
- **Processing**:
  - Apply tax calculations (12% VAT)
  - Calculate applicable discounts
    - SCPWD (Senior Citizen/PWD): 20% discount, no tax
    - Coupon: 10% discount with tax
  - Compute final amount due
- **Outputs**: Computation breakdown (taxable amount, tax, discount, total)
- **Business Rules**:
  - VAT = 12% (configurable)
  - SCPWD discount = 20% (tax-exempt)
  - Coupon discount = 10% (taxable)
  - Tax is pre-included in item prices

**FR-POS-002: Sales Transaction Recording**
- **Description**: System shall record complete sales transactions
- **Inputs**: Sale items, customer information, payment details, cashier information
- **Processing**:
  - Generate unique transaction ID
  - Record sale header with totals and metadata
  - Record individual sale items with quantities and prices
  - Update inventory levels
  - Apply payment processing
- **Outputs**: Transaction record, receipt data, inventory updates
- **Business Rules**:
  - Transaction ID must be unique
  - All sale items must exist in inventory
  - Payment amount must be ≥ total due
  - Record cashier for accountability
  - Optional customer linking for loyalty programs

## 3.6 ACCOUNTING & REPORTING

### 3.6.1 Sales Analytics
**FR-ACC-001: Sales Period Reporting**
- **Description**: System shall generate sales reports for specified periods
- **Inputs**: Date range (start date, end date) or predefined periods (today, yesterday, this week, this month, this year)
- **Processing**:
  - Validate date range
  - Query sales within specified period
  - Aggregate totals and statistics
  - Format for presentation
- **Outputs**: Sales report with transaction details and totals
- **Business Rules**:
  - Start date must be ≤ end date
  - Support predefined period shortcuts
  - Include transaction count, total sales, average transaction value
  - Filter by date/time accurately

**FR-ACC-002: Category Sales Analysis**
- **Description**: System shall analyze sales performance by product category
- **Inputs**: Optional date range filter
- **Processing**:
  - Aggregate sales by product category
  - Calculate totals and percentages
  - Generate comparative analysis
- **Outputs**: Category-wise sales breakdown with graphical data
- **Business Rules**:
  - Show all categories with sales activity
  - Calculate percentage of total sales
  - Support trend analysis over time periods

**FR-ACC-003: Sales Transaction Details**
- **Description**: System shall provide detailed transaction information
- **Inputs**: Transaction ID
- **Processing**:
  - Retrieve sale header information
  - Get all sale items for transaction
  - Format complete transaction details
- **Outputs**: Complete transaction details including items, quantities, prices, totals
- **Business Rules**:
  - Show complete audit trail
  - Include cashier and customer information
  - Display payment method and change given

### 3.6.2 Dashboard Analytics
**FR-ACC-004: Sales Dashboard**
- **Description**: System shall provide real-time sales dashboard
- **Inputs**: Current date/time context
- **Processing**:
  - Aggregate key performance indicators
  - Generate trend charts and graphs
  - Calculate comparative metrics
- **Outputs**: Dashboard with KPIs, charts, and summary statistics
- **Business Rules**:
  - Update in real-time with new transactions
  - Show daily, weekly, monthly trends
  - Highlight performance indicators

## 3.7 USER INTERFACE REQUIREMENTS

### 3.7.1 Console Application Interface
**FR-UI-001: Main Navigation**
- **Description**: Console application shall provide structured menu navigation
- **Inputs**: User menu selections via keyboard input
- **Processing**:
  - Display available options based on user role
  - Handle navigation flow between screens
  - Maintain user session context
- **Outputs**: Screen transitions, option menus, system responses
- **Business Rules**:
  - Role-based menu options
  - Consistent navigation patterns
  - Clear exit and logout options

**FR-UI-002: Data Entry Screens**
- **Description**: System shall provide structured data entry interfaces
- **Inputs**: User-typed data for various business entities
- **Processing**:
  - Guide user through required fields
  - Validate input in real-time where possible
  - Handle input errors gracefully
  - Support cancel operations
- **Outputs**: Formatted input prompts, validation messages, success confirmations
- **Business Rules**:
  - Clear field labels and requirements
  - Input validation with helpful error messages
  - Allow users to cancel operations
  - Confirm destructive operations

**FR-UI-003: Data Display and Listing**
- **Description**: System shall display business data in organized, readable formats
- **Inputs**: Data records from business operations
- **Processing**:
  - Format data in tabular layouts
  - Support pagination for large datasets
  - Provide detail views for individual records
- **Outputs**: Formatted tables, detail screens, navigation options
- **Business Rules**:
  - Consistent data formatting
  - Clear column headers and data alignment
  - Support for empty states
  - Intuitive detail navigation

---

## 4. NON-FUNCTIONAL REQUIREMENTS

### 4.1 Performance Requirements
- **Response Time**: Database operations complete within 500ms
- **Concurrent Users**: Support minimum 10 concurrent users
- **Data Volume**: Handle databases up to 1GB size efficiently
- **Memory Usage**: Operate within 256MB RAM allocation

### 4.2 Security Requirements
- **Authentication**: PIN-based user authentication
- **Authorization**: Role-based access control
- **Data Privacy**: Secure storage of customer and employee PII
- **Audit Logging**: Complete audit trail for all data modifications

### 4.3 Reliability Requirements
- **Data Integrity**: Maintain ACID compliance for all transactions
- **Error Handling**: Graceful degradation with meaningful error messages
- **Recovery**: Support data backup and restoration procedures
- **Uptime**: 99.9% availability during business hours

### 4.4 Usability Requirements
- **Learning Curve**: New users productive within 2 hours of training
- **Navigation**: Consistent UI patterns across all modules
- **Error Prevention**: Input validation prevents common data entry errors
- **Help System**: Context-sensitive help available throughout application

### 4.5 Compatibility Requirements
- **Operating Systems**: Windows (MinGW), Linux (gcc-7+)
- **Database**: SQLite embedded database
- **Integration**: Framework-agnostic design for easy integration
- **Standards**: C++17 compliance, CMake build system

---

## 5. SYSTEM INTERFACES

### 5.1 User Interfaces
- **Primary Interface**: Console-based application with text menus
- **Future Interface**: Designed for integration with Qt, web, or mobile interfaces
- **Navigation**: Keyboard-driven menu system with shortcuts

### 5.2 Data Interfaces
- **Database**: SQLite embedded database with in-memory StackDB for development/testing
- **File System**: Configuration files, log files, backup files
- **Import/Export**: Designed for future CSV/JSON data exchange capabilities

### 5.3 External System Interfaces
- **Future Integration Points**:
  - Barcode scanner hardware
  - Receipt printer hardware  
  - Payment processing systems
  - External accounting software

---

## 6. BUSINESS RULES & CONSTRAINTS

### 6.1 Data Validation Rules
- **Employee Management**:
  - Employee IDs must be unique across system
  - Required fields: firstname, lastname, birthdate, position, status
  - Status must be one of: ACTIVE, ON-LEAVE, INACTIVE
  - System users require valid PIN for login

- **Customer Management**:
  - Customer IDs must be unique
  - Minimum required: firstname, lastname
  - Prevent deletion of customers with transaction history

- **Inventory Management**:
  - Product barcodes must be unique (primary identifier)
  - Selling price must be ≥ original price
  - Stock quantities must be positive integers
  - Categories and UOMs must be unique

- **Sales Processing**:
  - Transaction IDs must be unique
  - Sale items must exist in current inventory
  - Payment amount must be ≥ total amount due
  - Discount types: None, SCPWD (20%, tax-exempt), Coupon (10%, taxable)

### 6.2 Business Process Rules
- **User Authentication**:
  - PIN-based authentication for system access
  - User roles determine feature accessibility
  - Session management throughout application use

- **Inventory Control**:
  - Real-time inventory updates with sales transactions
  - Product status tracking (High, Active, Reorder, Low Stock)
  - Supplier information maintained for reordering

- **Financial Processing**:
  - VAT calculations at 12% rate
  - SCPWD discounts for senior citizens and PWDs
  - Complete audit trail for all financial transactions

---

## 7. ASSUMPTIONS AND DEPENDENCIES

### 7.1 Technical Assumptions
- **Development Environment**: CMake build system with C++17 compiler
- **Database**: SQLite provides sufficient performance for target business size
- **Platform**: Console interface sufficient for initial deployment
- **Integration**: Clean architecture supports future GUI framework integration

### 7.2 Business Assumptions
- **Target Market**: Small to medium retail businesses
- **User Base**: 5-20 concurrent users typical deployment
- **Transaction Volume**: Up to 1000 transactions per day
- **Data Retention**: Historical data retained indefinitely for analytics

### 7.3 Dependencies
- **External Libraries**: Google Test for unit testing, SQLite for data storage
- **Build Tools**: CMake, gcc/MinGW compiler toolchain
- **Development Tools**: Qt Creator recommended but not required
- **Version Control**: Git with GitHub for source code management

---

## 8. FUTURE ENHANCEMENTS

### 8.1 Planned Features (Roadmap)
- **v0.5.0**: Complete sales operations with transaction processing
- **v0.6.0**: Full Point of Sale interface with barcode scanning
- **v1.0.0**: Complete accounting module with financial reporting
- **v1.x.x**: Performance optimization and feature enhancement
- **v2.x.x**: Hardware integration (barcode scanners, receipt printers)

### 8.2 Potential Integrations
- **GUI Frameworks**: Qt, web-based interfaces, mobile applications
- **Hardware**: Barcode scanners, receipt printers, cash drawers
- **External Systems**: Accounting software, e-commerce platforms
- **Payment Processing**: Credit card terminals, digital wallets

---

## 9. ACCEPTANCE CRITERIA

### 9.1 Functional Acceptance
- All specified business domains (Auth, Employee, Customer, Inventory, POS, Accounting) operational
- Complete CRUD operations for all major business entities
- Data validation and error handling working as specified
- User interface navigation functional and intuitive

### 9.2 Technical Acceptance  
- Unit test coverage ≥ 80% for all business logic
- Clean architecture principles maintained throughout
- Performance requirements met under specified load conditions
- Security requirements implemented and tested

### 9.3 User Acceptance
- Business users can complete typical workflows without technical assistance
- Error messages are clear and actionable
- Data entry processes are efficient and user-friendly
- Reporting provides useful business insights

---
