# LLVM Arithmetic Statement IR

## Build and Run

#### Commands

```
# Format the source code
clang-format -i *.cpp

# Set up C++ standard library and header path
export SDKROOT=$(xcrun --sdk macosx --show-sdk-path)

# Compile
clang++ -w -o HelloArithmeticStatement `llvm-config --cxxflags --ldflags --system-libs --libs core` HelloArithmeticStatement.cpp

# Run
./HelloArithmeticStatement
```

#### Output

```
; ModuleID = 'HelloModule'
source_filename = "HelloModule"

@helloGlobalVariable = common global i32, align 4

define i32 @HelloFunction(i32 %a, i32 %b) {
entry:
  %multiplyResult = mul i32 %a, 3
  ret i32 %multiplyResult
}
```
