// HelloModule.cpp

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

using namespace llvm;

int main(int argc, char* argv[])
{
    LLVMContext context;
    Module* module = new Module("HelloModule", context);

    module->print(outs(), nullptr);

    return 0;
}
