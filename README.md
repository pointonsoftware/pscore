
<p align="center">
  <img width="459" height="446" src="https://bit.ly/3kxZ6sj">
</p>

CORE is a software engine that houses common algorithms used for business management applications. CORE can be used as the processing module of a POS software, an inventory system, and more.

---

## Technical

These are the tools and technology used in this project:
- Language: C++17
- Compiler: gcc-7
- GUI: Qt Framework
- Database: SQLite
- Build system: CMake
- Profiling: gprof
- Library: C++ Standard Library
- Unit test: gtest
- Static tools: cpplint/cppcheck
- CI: travis-ci
- Platform: Linux, Windows, MinGW

CORE is also designed so the user interface and database can be swapped with another framework/dbms by implementing the domain provided interfaces.

---

## Getting Started

Clone the repository to a local destination using git:

`git clone git@github.com:pointonsoftware/pscore.git`

---

### Pre-requisites

These are the base requirements to build and use CORE.
 - Cmake
 - C++11-standard-compliant compiler

---

### How to build in Linux

- Run `clean_build.sh`
- Generated/output files are in pscore/build folder

---

### How to build in Windows

- Open the root CMakeLists.txt file in your favorite IDE.
- Hit Build!

---

### Usage

- The build generates the **invoker** library that contains the CORE algorithms and can be linked to any executable.
- An application called **console_app** is also available and can be used to test the CORE APIs.

---

## Roadmap

The initial version of CORE (v0.1.0) will contain the login and view personal information features.  

Below are the planned releases in the future:  

 - **v0.1.0** - Admin login/logout
 - **v0.2.0** - User CRUD
 - **v0.3.0** - Basic inventory operations
 - **v0.4.0** - Basic employee management
 - **v0.5.0** - Basic customer management
 - **v0.6.0** - Basic POS
 - **v0.7.0** - Basic sales operations
 - **v1.0.0** - Basic accounting operations
 - **v1.x.x** - Improving the basic operations  
 - **v2.x.x** - Support for external hardwares like barcode scanner and receipt printer

After CORE v1.0.0 is released, it is planned that **console_app** will be upgraded into a more user friendly GUI and build it as another project.

---

## Author
 - Ben Ziv - <pointonsoftware@gmail.com>

---

## Contributing

A developer guide document is currently worked on and will be uploaded soon.  
 
 But even without it, you can already start contributing to the project! Once able to build, you can make your changes and submit a pull request.

---

### Make a Pull Request

Make sure that your master branch is up to date with CORE's master branch:
```
git checkout master
git pull upstream master
```

Create your feature/developement branch and work on your change in this branch:
```
git checkout -b dev/[yourbranchname]
```

Then update your feature branch from your local copy of master, and push it!
```
git pull --rebase origin master
git push -u origin dev/[yourbranchname]
```

Finally, go to GithHub and [make a Pull Request](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request)!  

Travis-CI and GitHub actions will try to build and run several tests on your pull request. We care about quality, so your PR won't be merged until all tests pass.

---

### Merging a Pull Request

A PR can only be merged into master if:
 - It has passed CI.
 - It has been approved by at least one maintainer.
 - It has no requested changes.
 - It is up to date with current master branch.  

The PR author is allowed to merge the PR if all of these conditions are met.



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