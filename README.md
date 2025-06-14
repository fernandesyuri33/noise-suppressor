# Noise Suppressor

This project is a basic JUCE audio application.

## Dependencies
- C++17 compiler
- CMake 3.15+
- JUCE library (version 7.0+). On Debian/Ubuntu you can install it with:
  ```bash
  sudo apt-get install juce-modules-source juce-tools
  ```

## Building
```bash
mkdir build
cd build
cmake ..
cmake --build .
```
On Windows and macOS, ensure JUCE is installed and available via `find_package`. The generated executable will be placed in the build directory.
