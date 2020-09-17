# PSCore

Business management software engine

---

### Technologies

For this repo, we are using:
- Language: C++17
- Compiler: gcc-7
- Framework: Qt
- Database: SQLite
- Build system: CMake
- Profiling: gprof
- Libraries: STL
- Code coverage: gtest/gcov
- Static tools: cpplint/cppcheck
- CI: travis-ci

The project is designed so that the user interface and database can be swapped with another framework/dbms by implementing the domain provided interfaces.

---

### Getting Started

Ubuntu linux environment is recommended, Core is still untested on other development environments whilst we focus on a Linux build.

You can clone the repository to a local destination using git:

`git clone git@github.com:pointonsoftware/pscore.git`

---

### How to build

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
