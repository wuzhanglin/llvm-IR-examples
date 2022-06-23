# LLVM if-else IR

## Build and Run

#### Commands

```
# Format the source code
clang-format -i *.cpp

# Set up C++ standard library and header path
export SDKROOT=$(xcrun --sdk macosx --show-sdk-path)

# Compile
clang++ -w -o HelloIfElse `llvm-config --cxxflags --ldflags --system-libs --libs core` HelloIfElse.cpp

# Run
./HelloIfElse
```

#### Output

```

```

## Inspect With Clang

#### Code in C

See Test.c

#### Generate IR

```
clang -emit-llvm -c -S Test.c
```

#### IR

See Test.ll
