// HelloLoop.cpp

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

    // Add a function with argument
    //   int Test(int a)
    std::vector<Type*> parameters(1, builder.getInt32Ty());
    FunctionType* functionType = FunctionType::get(builder.getInt32Ty(), parameters, false);
    Function* function = Function::Create(functionType, GlobalValue::ExternalLinkage, "Test", module);
    Value* a = function->getArg(0);
    a->setName("a");

    // Add some basic blocks to the function
    BasicBlock* entryBlock = BasicBlock::Create(context, "entry", function);
    BasicBlock* forConditionBlock = BasicBlock::Create(context, "for.condition", function);
    BasicBlock* forBodyBlock = BasicBlock::Create(context, "for.body", function);
    BasicBlock* forIncrementBlock = BasicBlock::Create(context, "for.increment", function);
    BasicBlock* forEndBlock = BasicBlock::Create(context, "for.end", function);

    // Fill the "entry" block (1):
    //   int b = 0;
    builder.SetInsertPoint(entryBlock);
    Value* bPtr = builder.CreateAlloca(builder.getInt32Ty(), nullptr, "b.address");
    builder.CreateStore(builder.getInt32(1), bPtr);

    // Fill the "entry" block (2):
    //   for (int i = 0; ...)
    Value* iPtr = builder.CreateAlloca(builder.getInt32Ty(), nullptr, "i.address");
    builder.CreateStore(builder.getInt32(0), iPtr);
    builder.CreateBr(forConditionBlock);

    // Fill the "for.condition" block:
    //   for (... i < a; ...)
    builder.SetInsertPoint(forConditionBlock);
    Value* i0 = builder.CreateLoad(iPtr);
    Value* forConditionCompare = builder.CreateICmpSLT(i0, a, "for.condition.compare.result");
    builder.CreateCondBr(forConditionCompare, forBodyBlock, forEndBlock);

    // Fill the "for.body" block:
    //   b = b + i;
    builder.SetInsertPoint(forBodyBlock);
    Value* b0 = builder.CreateLoad(bPtr);
    Value* i1 = builder.CreateLoad(iPtr);
    Value* addResult = builder.CreateAdd(b0, i1, "add.result");
    builder.CreateStore(addResult, bPtr);
    builder.CreateBr(forIncrementBlock);

    // Fill the "for.increment" block:
    //   for (... i++)
    builder.SetInsertPoint(forIncrementBlock);
    Value* i2 = builder.CreateLoad(iPtr);
    Value* incrementedI = builder.CreateAdd(i2, builder.getInt32(1), "i.incremented");
    builder.CreateStore(incrementedI, iPtr);
    builder.CreateBr(forConditionBlock);

    // Fill the "for.end" block:
    //   return b;
    builder.SetInsertPoint(forEndBlock);
    Value* returnValue = builder.CreateLoad(bPtr, "return.value");
    builder.CreateRet(returnValue);

    // Print the IR
    verifyFunction(*function);
    module->print(outs(), nullptr);

    return 0;
}
