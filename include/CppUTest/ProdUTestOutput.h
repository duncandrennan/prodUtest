#ifndef D_ProdUTestOutput_h
#define D_ProdUTestOutput_h

#include "TestOutput.h"
#include "PlatformSpecificFunctions.h"

class ProdUTestOutput: public ConsoleTestOutput
{
public:
    ProdUTestOutput(void);
    virtual ~ProdUTestOutput(void);

    virtual void printTestsStarted();
    virtual void printTestsEnded(const TestResult& result);
    virtual void printCurrentTestStarted(const UtestShell& test);
    virtual void printCurrentTestEnded(const TestResult& res);

    virtual void printFailure(const TestFailure& failure);

protected:
    PlatformSpecificFile file_;
    int errorCode_;
    bool finalTest_;

    virtual void printFileAndLineForFailure(const TestFailure& failure);

    virtual void openFileForWrite(const SimpleString& fileName);
    virtual void writeToFile(const SimpleString& buffer);
    virtual void closeFile();
};

#endif
