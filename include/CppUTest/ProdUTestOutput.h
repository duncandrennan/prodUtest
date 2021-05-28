#ifndef D_ProdUTestOutput_h
#define D_ProdUTestOutput_h

#include "TestOutput.h"

class ProdUTestOutput: public ConsoleTestOutput
{
public:
    ProdUTestOutput(void);
    virtual ~ProdUTestOutput(void);

    virtual void printCurrentTestEnded(const TestResult& res) _override;
    virtual void printFailure(const TestFailure& failure) _override;

protected:
    virtual void printEclipseErrorInFileOnLine(SimpleString file, int lineNumber);
    virtual void printFileAndLineForFailure(const TestFailure& failure) _override;
};

#endif
