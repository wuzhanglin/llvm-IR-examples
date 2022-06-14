// HelloReturn.cpp

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

using namespace llvm;

int main(int argc, char* argv[])
{
    LLVMContext context;
    IRBuilder<> builder(context);

    // Create a module
    Module* module = new Module("HelloModule", context);

    // Add a global variable
    module->getOrInsertGlobal("helloGlobalVariable", builder.getInt32Ty());
    GlobalVariable* globalVariable = module->getNamedGlobal("helloGlobalVariable");
    globalVariable->setLinkage(GlobalValue::CommonLinkage);
    globalVariable->setAlignment(MaybeAlign(4));

    // Add a function
    FunctionType* functionType = FunctionType::get(builder.getInt32Ty(), false);
    Function* function = Function::Create(functionType, GlobalValue::ExternalLinkage, "HelloFunction", module);

    // Create a block
    BasicBlock* block = BasicBlock::Create(context, "entry", function);
    builder.SetInsertPoint(block);

    // Add a return
    ConstantInt* zero = builder.getInt32(0);
    builder.CreateRet(zero);

    // Print the IR
    verifyFunction(*function);
    module->print(outs(), nullptr);

    return 0;
}
