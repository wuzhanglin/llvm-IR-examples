# LLVM Module IR

## Build and Run

#### Commands

```
# Format the source code
clang-format -i *.cpp

# Set up C++ standard library and header path
export SDKROOT=$(xcrun --sdk macosx --show-sdk-path)

# Compile
clang++ -o HelloModule `llvm-config --cxxflags --ldflags --system-libs --libs core` HelloModule.cpp

# Compile with all warnings suppressed
clang++ -w -o HelloModule `llvm-config --cxxflags --ldflags --system-libs --libs core` HelloModule.cpp

# Run
./HelloModule
```

#### Output

```
; ModuleID = 'HelloModule'
source_filename = "HelloModule"
```
