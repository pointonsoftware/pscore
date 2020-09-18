
<p align="center">
  <img width="520" height="522" src="https://bit.ly/2ZOUFBj">
  <h2 align="center">PSCORE</h2>
  <p align="center">Business Management Software engine</p>
</p>

---

This project aims to create a software engine that will lessen the time of writing the same algorithms for business management applications such as creating a user, checking the number of inventory items, etc..

---

## Getting Started

You can clone the repository to a local destination using git:

`git clone git@github.com:pointonsoftware/pscore.git`

---

## Technologies

For this repo, we are using:
- Language: C++17
- Compiler: gcc-7
- GUI Framework: Qt
- Database: SQLite
- Build system: CMake
- Profiling: gprof
- Libraries: STL
- Unit test: gtest
- Static tools: cpplint/cppcheck
- CI: travis-ci
- Platform: Linux, Windows, MinGW

The project is designed so the user interface and database can be swapped with another framework/dbms just by implementing the domain provided interfaces.

---

### Build Requirements

These are the base requirements to build and use PSCore.
 - Cmake
 - C++11-standard-compliant compiler

---

### How to build in Linux

- Run `clean_build.sh`
- Generated/output files are in pscore/build folder

---

## License

GNU AFFERO GENERAL PUBLIC LICENSE  
   Version 3, 19 November 2007  

   Copyright (C) 2020 Pointon Software  

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

---

## Author Info
 -  Ben Ziv - <pointonsoftware@gmail.com>
