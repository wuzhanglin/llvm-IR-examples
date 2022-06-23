# LLVM if-else-phi IR

## Build and Run

#### Commands

```
# Format the source code
clang-format -i *.cpp

# Set up C++ standard library and header path
export SDKROOT=$(xcrun --sdk macosx --show-sdk-path)

# Compile
clang++ -w -o HelloIfElsePhi `llvm-config --cxxflags --ldflags --system-libs --libs core` HelloIfElsePhi.cpp

# Run
./HelloIfElsePhi
```

#### Output

```
; ModuleID = 'Test.c'
source_filename = "Test.c"

define i32 @Test(i32 %a) {
entry:
  %b.address = alloca i32, align 4
  %compare.result = icmp sgt i32 %a, 33
  br i1 %compare.result, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  br label %if.end

if.else:                                          ; preds = %entry
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %0 = phi i32 [ 66, %if.then ], [ 77, %if.else ]
  store i32 %0, i32* %b.address, align 4
  %return.value = load i32, i32* %b.address, align 4
  ret i32 %return.value
}
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
