// HelloIfElse.cpp

#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

#include <vector>

using namespace llvm;

int main(int argc, char* argv[])
{
    LLVMContext context;
    IRBuilder<> builder(context);

    // Create a module
    Module* module = new Module("Test.c", context);

    // Add a function
    std::vector<Type*> parameters(1, builder.getInt32Ty());
    FunctionType* functionType = FunctionType::get(builder.getInt32Ty(), parameters, false);
    Function* function = Function::Create(functionType, GlobalValue::ExternalLinkage, "Test", module);

    // Add an argument to the function
    Value* arg = function->getArg(0);
    arg->setName("a");

    // Add some basic blocks to the function
    BasicBlock* entryBlock = BasicBlock::Create(context, "entry", function);
    BasicBlock* thenBlock = BasicBlock::Create(context, "if.then", function);
    BasicBlock* elseBlock = BasicBlock::Create(context, "if.else", function);
    BasicBlock* returnBlock = BasicBlock::Create(context, "if.end", function);

    // Fill the "entry" block (1):
    //   int b;
    builder.SetInsertPoint(entryBlock);
    Value* bPtr = builder.CreateAlloca(builder.getInt32Ty(), nullptr, "b.address");

    // Fill the "entry" block (2):
    //   if (a > 33)
    ConstantInt* value33 = builder.getInt32(33);
    Value* condition = builder.CreateICmpSGT(arg, value33, "compare.result");
    builder.CreateCondBr(condition, thenBlock, elseBlock);

    // Fill the "if.then" block:
    //   b = 66;
    builder.SetInsertPoint(thenBlock);
    ConstantInt* value66 = builder.getInt32(66);
    builder.CreateStore(value66, bPtr);
    builder.CreateBr(returnBlock);

    // Fill the "if.else" block:
    //   b = 77;
    builder.SetInsertPoint(elseBlock);
    ConstantInt* value77 = builder.getInt32(77);
    builder.CreateStore(value77, bPtr);
    builder.CreateBr(returnBlock);

    // Fill the "if.end" block:
    //   return b;
    builder.SetInsertPoint(returnBlock);
    Value* returnValue = builder.CreateLoad(bPtr, "return.value");
    builder.CreateRet(returnValue);

    // Print the IR
    verifyFunction(*function);
    module->print(outs(), nullptr);

    return 0;
}
