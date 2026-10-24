# SFUdo — Self-Hosted Real-Time Communication

**A C++17 and Qt 6 desktop application for managing and developing a self-hosted SFU-based real-time communication platform.**

[Official Website](https://www.bashdot.com/sfudo/) · [Qt Documentation](https://doc.qt.io/qt-6/) · [CMake Documentation](https://cmake.org/documentation/) · [Boost.Beast Documentation](https://www.boost.org/doc/libs/release/libs/beast/)

---

## 1. About SFUdo

Live streaming and real-time communication are essential in education, collaboration, and remote interaction. Educational institutes, coaching centers, and training organizations need reliable platforms where teachers can conduct live classes and students can participate remotely.

SFUdo aims to provide a self-hosted foundation for real-time communication, giving organizations greater control over their infrastructure, communication services, and data.

Unlike relying entirely on third-party hosted platforms, a self-hosted solution can be deployed on infrastructure controlled by the organization, provided that the required networking, media transport, security, and server components are configured.

### Project objectives

- Develop a desktop application using C++ and Qt.
- Provide a graphical interface for system, network, and server information.
- Develop networking and signaling components.
- Organize core event handling and SFU connection logic.
- Build a foundation for real-time communication and live-class applications.
- Explore future extensions such as media monitoring, recording, and AI-assisted processing.

> The features available depend on the implementation in the current source code. A desktop management application alone does not guarantee that the media server is deployed or ready for production.

---

## 2. Technology Stack

| Technology | Purpose |
|---|---|
| C++17 | Application logic and core functionality |
| Qt 6 | Desktop graphical user interface |
| Qt Widgets | GUI components and windows |
| CMake | Build configuration and compilation |
| MinGW-w64 | C++ compiler toolchain for Windows |
| Boost.Beast | HTTP and WebSocket networking |
| vcpkg | C++ dependency management |
| Windows APIs | Platform-specific functionality |
| Qt Resource System | Bundled icons, fonts, and other resources |

---

## 3. Project Directory Structure

The following tree reflects the directories shown in the supplied listing. Individual source filenames are included where they were provided earlier; other files may exist in the directories but were not shown in the listing.

```text
v1clean/
│
├── .vscode/                    # Editor and workspace configuration
│
├── build/                      # Generated CMake build files
│   ├── .qt/
│   ├── CMakeFiles/
│   │   ├── 3.29.3/
│   │   ├── SFUdo.dir/
│   │   │   ├── components/
│   │   │   │   └── item/
│   │   │   ├── core/
│   │   │   ├── SSsokcet/
│   │   │   └── window/
│   │   ├── SFUdo_autogen.dir/
│   │   └── pkgRedirects/
│   └── SFUdo_autogen/
│       ├── 3YJK5W5UP7/
│       ├── DT2573FGAL/
│       ├── include/
│       └── XDQFSXMG3O/
│
├── components/                 # Reusable GUI components
│   └── item/                   # Individual item components
│
├── core/                       # Core logic and event processing
│
├── resources/                  # Application resources
│   ├── fonts/                  # Fonts
│   ├── icons/                  # Icons
│   └── styles/                 # Stylesheets
│
├── sfu/                        # SFU-related implementation
│
├── SSsokcet/                   # Signaling/networking implementation
│
├── Test/                       # Testing projects
│   └── cmp/
│       ├── build/              # Generated test build files
│       └── ...
│
├── window/                     # Main application windows
│
├── CMakeLists.txt              # Main CMake configuration
├── main.cpp                    # Application entry point
├── build.bat                   # Build script, if included
├── run.bat                     # Run script, if included
└── README.md                   # Project documentation
```

### Important directories

**`components/`** — Contains reusable UI components such as headers, system information widgets, server information, room lists, and profile components.

**`core/`** — Contains core application functionality, including event processing and SFU connection logic.

**`resources/`** — Stores application resources, such as fonts, icons, and styles.

**`sfu/`** — Reserved for or containing SFU-related implementation. Its precise responsibilities depend on the source files inside it.

**`SSsokcet/`** — Contains signaling and networking-related implementation. The directory name is preserved from the supplied project.

**`window/`** — Contains the application windows, such as the login and onboarding windows.

**`Test/cmp/`** — Contains a separate test or comparison project and its generated build files.

**`build/`** — Contains generated CMake files and Qt-generated code. It should generally not be committed to GitHub.

---

## 4. Prerequisites

Install the following tools before building SFUdo.

### 4.1 Git

Download: https://git-scm.com/downloads/win

Verify:

```bat
git --version
```

### 4.2 CMake

Download: https://cmake.org/download/

Verify:

```bat
cmake --version
```

The supplied build directory indicates CMake version `3.29.3` was used previously. A compatible installed CMake version is required.

### 4.3 Qt 6

Download: https://www.qt.io/download-qt-installer-oss

Install the matching Qt version and MinGW kit used by your project.

The original build configuration uses:

```text
C:\Qt\6.11.0\mingw_64
```

Ensure that the Qt Widgets module and matching MinGW compiler are installed.

### 4.4 MinGW-w64

Use the MinGW toolchain compatible with your Qt installation.

Verify that the compiler and build utility are accessible:

```bat
g++ --version
mingw32-make --version
```

If the commands are not found, open the Qt MinGW environment or add the correct compiler directory to PATH.

### 4.5 vcpkg

Official repository: https://github.com/microsoft/vcpkg

Clone and bootstrap vcpkg:

```bat
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat
```

The existing configuration references this location:

```text
D:\Bashdot\projects\dot3\server\v1\header\vcpkg
```

If your vcpkg installation is elsewhere, update the path in the build commands.

### 4.6 Boost.Beast

Install the required Boost.Beast package using a vcpkg triplet compatible with your compiler.

Example:

```bat
vcpkg install boost-beast:x64-mingw-dynamic
```

If that triplet is unavailable in your environment, use a supported triplet and update the CMake configuration to match it.

---

## 5. Get the Source Code

If the repository is hosted on GitHub, clone it using the repository URL:

```bat
git clone https://github.com/YOUR_USERNAME/SFUdo.git
cd SFUdo
```

Replace the example URL with the actual repository URL.

If the repository is private, authenticate using your GitHub account or an authorized access token.

Alternatively, download the source ZIP, extract it, and open Command Prompt in the directory containing `CMakeLists.txt`.

For your current local copy, the directory is:

```text
D:\Bashdot\projects\dot3\server\main\v1\v1clean
```

Open Command Prompt there:

```bat
cd /d D:\Bashdot\projects\dot3\server\main\v1\v1clean
```

---

## 6. Configure CMake

The main `CMakeLists.txt` should be in the project root.

Your build configuration needs to:

1. Select C++17.
2. Locate Qt 6 Widgets.
3. Locate the required Boost headers.
4. List the existing application source files.
5. Link the required Windows system libraries.
6. Enable Qt automatic code generation and resource processing.

A cleaned-up starting point based on your previously supplied source list is:

```cmake
cmake_minimum_required(VERSION 3.16)

project(SFUdo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Boost CONFIG REQUIRED)

qt_add_executable(SFUdo
    main.cpp

    window/loginwindow.cpp
    window/onboard.cpp

    components/header.cpp
    components/onNetwrok.cpp
    components/onServer.cpp
    components/onSystem.cpp
    components/OnRoomList.cpp
    components/RamUsageWidget.cpp
    components/item/roomitem.cpp
    components/TopProfile.cpp

    core/eventqueue.cpp
    core/sfuconnections.cpp

    SSsokcet/signaling.cpp

    resources/resources.qrc
)

target_link_libraries(SFUdo
    PRIVATE
        Qt6::Widgets
        Boost::headers
        dwmapi
        ws2_32
)
```

**Before using this example:** verify that every listed source file exists. Your actual tree listing shows directories but not their contents. If your current CMake configuration already builds successfully, preserve any additional source files or dependencies it requires, including files under `sfu/`.

Boost's exported CMake target may be `Boost::headers` or another target, depending on the package configuration. Use the target actually provided by your installed Boost package.

---

## 7. Build SFUdo

### Step 1: Open the project directory

```bat
cd /d D:\Bashdot\projects\dot3\server\main\v1\v1clean
```

### Step 2: Configure the project

```bat
cmake -B build ^
-G "MinGW Makefiles" ^
-DCMAKE_TOOLCHAIN_FILE=D:/Bashdot/projects/dot3/server/v1/header/vcpkg/scripts/buildsystems/vcpkg.cmake ^
-DCMAKE_PREFIX_PATH=C:/Qt/6.11.0/mingw_64 ^
-DVCPKG_TARGET_TRIPLET=x64-mingw-dynamic
```

Update the Qt and vcpkg paths if your installations differ.

### Step 3: Compile the source code

```bat
cmake --build build
```

If configuration and compilation succeed, CMake should generate the SFUdo executable in the build output directory, typically:

```text
build/SFUdo.exe
```

### Step 4: Run the application

```bat
build\SFUdo.exe
```

If Qt DLLs are missing, run the application from an environment containing the matching Qt runtime libraries.

---

## 8. Build Script

Create `build.bat` in the project root:

```bat
@echo off
setlocal

set "QT_DIR=C:\Qt\6.11.0\mingw_64"
set "VCPKG_DIR=D:\Bashdot\projects\dot3\server\v1\header\vcpkg"

set "PATH=%QT_DIR%\bin;%PATH%"

if not exist "%VCPKG_DIR%\scripts\buildsystems\vcpkg.cmake" (
    echo ERROR: vcpkg toolchain not found.
    echo Check VCPKG_DIR in build.bat.
    pause
    exit /b 1
)

echo Configuring SFUdo...

cmake -B build ^
-G "MinGW Makefiles" ^
-DCMAKE_TOOLCHAIN_FILE="%VCPKG_DIR%/scripts/buildsystems/vcpkg.cmake" ^
-DCMAKE_PREFIX_PATH="%QT_DIR%" ^
-DVCPKG_TARGET_TRIPLET=x64-mingw-dynamic

if errorlevel 1 (
    echo Configuration failed.
    pause
    exit /b 1
)

echo Building SFUdo...

cmake --build build

if errorlevel 1 (
    echo Build failed.
    pause
    exit /b 1
)

echo Build completed successfully.
pause
```

Run the script:

```bat
build.bat
```

Make sure the compiler, Qt installation, and vcpkg triplet are compatible.

---

## 9. Run Script

Create `run.bat`:

```bat
@echo off
setlocal

set "QT_DIR=C:\Qt\6.11.0\mingw_64"
set "PATH=%QT_DIR%\bin;%PATH%"

if not exist "build\SFUdo.exe" (
    echo SFUdo.exe not found.
    echo Run build.bat first.
    pause
    exit /b 1
)

echo Launching SFUdo...

start "" "%CD%\build\SFUdo.exe"
```

Run:

```bat
run.bat
```

---

## 10. Troubleshooting

### Qt6 not found

Check the `CMAKE_PREFIX_PATH` and ensure that the Qt Widgets module is installed.

### Boost.Beast not found

Verify that Boost.Beast is installed and that the configured vcpkg toolchain and triplet match your compiler.

### MinGW compiler not found

Check that the matching MinGW `bin` directory is available in PATH.

### Source file not found

Check the file names in `CMakeLists.txt` against the actual source directory. Remember that the tree provided so far lists directory names, not all source files.

### Missing Qt DLLs

Run from the correct Qt environment or deploy the runtime dependencies with the matching `windeployqt` executable.

### Configuration errors after changing toolchains

Delete the generated `build/` directory and configure the project again using the intended compiler, Qt installation, and vcpkg triplet.

---

## 11. GitHub Repository Hygiene

The `build/` directory contains generated CMake files and Qt-generated code. These generally should not be committed.

A starter `.gitignore` is:

```gitignore
# CMake build output
/build/
/Test/cmp/build/

# Qt-generated files
*_autogen/
CMakeFiles/
CMakeCache.txt
cmake_install.cmake
Makefile

# IDE configuration (optional)
.vscode/

# Compiled binaries and objects
*.exe
*.dll
*.o
*.obj
*.a
*.lib

# Local environment and secrets
.env
.env.*
!.env.example
```

Keep `CMakeLists.txt`, source files, headers, `resources.qrc`, and the actual resources required to build the application under version control.

If your `.vscode/` directory contains shared project configuration needed by contributors, you can choose to commit it rather than ignore it.

Never commit API tokens, passwords, private keys, or other secrets.

---

## 12. Security and Deployment

Before making SFUdo accessible over a public network:

- Configure authentication and authorization.
- Use secure signaling connections where applicable.
- Configure the required media and signaling ports.
- Restrict firewall access to necessary services.
- Protect credentials and private configuration.
- Test connectivity and concurrency before production use.

A public IP address by itself is not sufficient to make an SFU operational. Media routing, signaling, transport configuration, and the required server components must be implemented and configured.

---

## 13. Future Scope

Potential future improvements include:

- Enhanced SFU connection and room management.
- Improved monitoring of CPU, memory, and network utilization.
- Support for additional real-time media workflows.
- Session recording and playback.
- AI-assisted media analysis.
- Deployment automation and improved scalability.

These are potential improvements, not claims that every feature is currently implemented.

---

## 14. Learn More

- **SFUdo official website:** https://www.bashdot.com/sfudo/
- Qt 6: https://doc.qt.io/qt-6/
- CMake: https://cmake.org/documentation/
- Boost.Beast: https://www.boost.org/doc/libs/release/libs/beast/
- vcpkg: https://learn.microsoft.com/en-us/vcpkg/
- GitHub: https://docs.github.com/

---

## 15. License

Add the actual license for this repository here. Do not claim that the project is open-source or grant reuse rights until the license has been selected.

---

**SFUdo — Building a foundation for self-hosted real-time communication.**

For more information, visit the [official SFUdo website](https://www.bashdot.com/sfudo/).
