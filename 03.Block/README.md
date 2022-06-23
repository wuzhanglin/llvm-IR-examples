# LLVM Block IR

## Build and Run

#### Commands

```
# Format the source code
clang-format -i *.cpp

# Set up C++ standard library and header path
export SDKROOT=$(xcrun --sdk macosx --show-sdk-path)

# Compile
clang++ -w -o HelloBlock `llvm-config --cxxflags --ldflags --system-libs --libs core` HelloBlock.cpp

# Run
./HelloBlock
```

#### Output

```
; ModuleID = 'Hello Module'
source_filename = "Hello Module"

declare void @HelloBlock()
```
