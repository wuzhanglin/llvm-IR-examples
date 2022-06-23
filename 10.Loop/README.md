# LLVM Loop IR

## Build and Run

#### Commands

```
# Format the source code
clang-format -i *.cpp

# Set up C++ standard library and header path
export SDKROOT=$(xcrun --sdk macosx --show-sdk-path)

# Compile
clang++ -w -o HelloLoop `llvm-config --cxxflags --ldflags --system-libs --libs core` HelloLoop.cpp

# Run
./HelloLoop
```

#### Output

```
; ModuleID = 'Test.c'
source_filename = "Test.c"

define i32 @Test(i32 %a) {
entry:
  %b.address = alloca i32, align 4
  store i32 1, i32* %b.address, align 4
  %i.address = alloca i32, align 4
  store i32 0, i32* %i.address, align 4
  br label %for.condition

for.condition:                                    ; preds = %for.increment, %entry
  %0 = load i32, i32* %i.address, align 4
  %for.condition.compare.result = icmp slt i32 %0, %a
  br i1 %for.condition.compare.result, label %for.body, label %for.end

for.body:                                         ; preds = %for.condition
  %1 = load i32, i32* %b.address, align 4
  %2 = load i32, i32* %i.address, align 4
  %add.result = add i32 %1, %2
  store i32 %add.result, i32* %b.address, align 4
  br label %for.increment

for.increment:                                    ; preds = %for.body
  %3 = load i32, i32* %i.address, align 4
  %i.incremented = add i32 %3, 1
  store i32 %i.incremented, i32* %i.address, align 4
  br label %for.condition

for.end:                                          ; preds = %for.condition
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
