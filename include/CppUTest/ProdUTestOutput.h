#ifndef D_ProdUTestOutput_h
#define D_ProdUTestOutput_h

#include "TestOutput.h"
#include "PlatformSpecificFunctions.h"

class ProdUTestOutput: public ConsoleTestOutput
{
public:
    ProdUTestOutput(void);
    virtual ~ProdUTestOutput(void);

    virtual void printTestsStarted()_override;
    virtual void printTestsEnded(const TestResult& result)_override;
    virtual void printCurrentTestStarted(const UtestShell& test)_override;
    virtual void printCurrentTestEnded(const TestResult& res) _override;

    virtual void printFailure(const TestFailure& failure) _override;

protected:
    PlatformSpecificFile file_;
    int errorCode_;
    bool finalTest_;

    virtual void printEclipseErrorInFileOnLine(SimpleString file, int lineNumber);
    virtual void printFileAndLineForFailure(const TestFailure& failure) _override;

    virtual void openFileForWrite(const SimpleString& fileName);
    virtual void writeToFile(const SimpleString& buffer);
    virtual void closeFile();
};

#endif
