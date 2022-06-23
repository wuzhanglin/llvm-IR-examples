# LLVM Return Statement IR

## Build and Run

#### Commands

```
# Format the source code
clang-format -i *.cpp

# Set up C++ standard library and header path
export SDKROOT=$(xcrun --sdk macosx --show-sdk-path)

# Compile
clang++ -w -o HelloReturn `llvm-config --cxxflags --ldflags --system-libs --libs core` HelloReturn.cpp

# Run
./HelloReturn
```

#### Output

```
; ModuleID = 'HelloModule'
source_filename = "HelloModule"

@helloGlobalVariable = common global i32, align 4

define i32 @HelloFunction() {
entry:
  ret i32 0
}
```
