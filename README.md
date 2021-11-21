[![Actions Status](https://github.com/danielplawrence/MazeGeneration/workflows/MacOS/badge.svg)](https://github.com/danielplawrence/MazeGeneration/actions)
[![Actions Status](https://github.com/danielplawrence/MazeGeneration/workflows/Windows/badge.svg)](https://github.com/danielplawrence/MazeGeneration/actions)
[![Actions Status](https://github.com/danielplawrence/MazeGeneration/workflows/Ubuntu/badge.svg)](https://github.com/danielplawrence/MazeGeneration/actions)
[![Actions Status](https://github.com/danielplawrence/MazeGeneration/workflows/Style/badge.svg)](https://github.com/danielplawrence/MazeGeneration/actions)
[![Actions Status](https://github.com/danielplawrence/MazeGeneration/workflows/Install/badge.svg)](https://github.com/danielplawrence/MazeGeneration/actions)
[![codecov](https://codecov.io/gh/danielplawrence/MazeGeneration/branch/master/graph/badge.svg)](https://codecov.io/gh/danielplawrence/MazeGeneration)

<p align="center">
  <img src="https://repository-images.githubusercontent.com/254842585/4dfa7580-7ffb-11ea-99d0-46b8fe2f4170" height="175" width="auto" />
</p>

# MazeGenerator

This project implements classes for generating and visualizing mazes and their solutions.
Based on: https://pragprog.com/titles/jbmaze/mazes-for-programmers/

### Build and run the standalone target

Use the following command to build and run the executable target.

```bash
cmake -S standalone -B build/standalone
cmake --build build/standalone
./build/standalone/MazeGenerator --help
```

### Build and run test suite

Use the following commands from the project's root directory to run the test suite.

```bash
cmake -S test -B build/test
cmake --build build/test
CTEST_OUTPUT_ON_FAILURE=1 cmake --build build/test --target test

# or simply call the executable: 
./build/test/MazeGeneratorTests
```

To collect code coverage information, run CMake with the `-DENABLE_TEST_COVERAGE=1` option.

### Run clang-format

Use the following commands from the project's root directory to check and fix C++ and CMake source style.
This requires _clang-format_, _cmake-format_ and _pyyaml_ to be installed on the current system.

```bash
cmake -S test -B build/test

# view changes
cmake --build build/test --target format

# apply changes
cmake --build build/test --target fix-format
```

See [Format.cmake](https://github.com/TheLartians/Format.cmake) for details.

### Build the documentation

The documentation is automatically built and [published](https://thelartians.github.io/ModernCppStarter) whenever a [GitHub Release](https://help.github.com/en/github/administering-a-repository/managing-releases-in-a-repository) is created.
To manually build documentation, call the following command.

```bash
cmake -S documentation -B build/doc
cmake --build build/doc --target GenerateDocs
# view the docs
open build/doc/doxygen/html/index.html
```

To build the documentation locally, you will need Doxygen, jinja2 and Pygments on installed your system.

### Build everything at once

The project also includes an `all` directory that allows building all targets at the same time.
This is useful during development, as it exposes all subprojects to your IDE and avoids redundant builds of the library.

```bash
cmake -S all -B build
cmake --build build

# run tests
./build/test/MazeGeneratorTests
# format code
cmake --build build --target fix-format
# run standalone
./build/standalone/MazeGenerator --help
# build docs
cmake --build build --target GenerateDocs
```
## Related projects and alternatives

- [**ModernCppStarter & PVS-Studio Static Code Analyzer**](https://github.com/viva64/pvs-studio-cmake-examples/tree/master/modern-cpp-starter): Official instructions on how to use the ModernCppStarter with the PVS-Studio Static Code Analyzer.
- [**lefticus/cpp_starter_project**](https://github.com/lefticus/cpp_starter_project/): A popular C++ starter project, created in 2017.
- [**filipdutescu/modern-cpp-template**](https://github.com/filipdutescu/modern-cpp-template): A recent starter using a more traditional approach for CMake structure and dependency management.
- [**vector-of-bool/pitchfork**](https://github.com/vector-of-bool/pitchfork/): Pitchfork is a Set of C++ Project Conventions.
