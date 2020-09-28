
<p align="center">
  <img width="459" height="446" src="https://bit.ly/3kxZ6sj">
</p>

CORE is a software engine that houses the common use-case algorithms used for business management applications. CORE can be used as a processing module of a POS software, an inventory system, and more.

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

CORE is also designed to work in any GUI (mobile, desktop, web) and database.

---

## Getting Started

The repository consists of three main folders and their subfolders:
 - **core**
    - domain - business workflow and components
    - entity - business entities
 - **orchestra**
    - application - presentation layer
    - datamanager - database queries
    - migration   - stack database
 - **utility** - helper classes like logger, fileio, etc.

---

### Pre-requisites

These are the base requirements to build and use CORE.
 - Cmake
 - C++11-standard-compliant compiler

---

### Download

Clone the repository to a local destination using git:

`git clone git@github.com:pointonsoftware/pscore.git`

---

### How to build in Linux

- Run `clean_build.sh`
- Generated/output files are in pscore/build folder

---

### How to build in Windows

- Open the root CMakeLists.txt file with your favorite IDE.
- Hit Build!

---

### Usage

#### Libraries
- Go to your build directory
- The build generates **domain** libraries that contain the CORE use cases. These libraries can be linked to any executable.
#### Executable
- Go to your build directory
- Inside the **bin** folder, run **console_app**.
- This application is used to test the CORE APIs.

---

### Screenshots

- **Unreleased version** asks for the user's name and print it in the console using the logger utility class.

<p align="center">
  <img width="999" height="45" src="https://bit.ly/3j3WzWc">
</p>

- **console_app** v0.0.1 login screen:
<p align="center">
  <img width="571" height="136" src="https://bit.ly/2Ex0SKL">
</p>


---

## Roadmap

The initial CORE v0.0.10 includes the login and view personal information features.

Below are the planned releases in the future:  

 - **v0.1.0** - Full admin login/logout
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