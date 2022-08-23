# LLVM Function Arguments IR

## Build and Run

#### Commands

```bash
# Format the source code
clang-format -i *.cpp

# Set up C++ standard library and header path
export SDKROOT=$(xcrun --sdk macosx --show-sdk-path)

# Compile
clang++ -w -o HelloFunctionArguments `llvm-config --cxxflags --ldflags --system-libs --libs core` HelloFunctionArguments.cpp

# Run
./HelloFunctionArguments
```

#### Output

```cpp
; ModuleID = 'HelloModule'
source_filename = "HelloModule"

@helloGlobalVariable = common global i32, align 4

define i32 @HelloFunction(i32 %a, i32 %b) {
entry:
  ret i32 0
}
```
