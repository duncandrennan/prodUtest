#include "CppUTest/TestHarness.h"
#include "CppUTest/ProdUTestOutput.h"

ProdUTestOutput::ProdUTestOutput()
{
    verbose();
}

ProdUTestOutput::~ProdUTestOutput()
{
}

void ProdUTestOutput::printCurrentTestEnded(const TestResult& res)
{
    if (res.getCurrentTestPassed())
    {
        print(";PASS;");
    }

    print(res.getCurrentTestTotalExecutionTime());
    print(" ms\n");
}

void ProdUTestOutput::printFailure(const TestFailure& failure)
{
    print(";FAIL;");
    print(failure.getErrorCode());
    print(";");
    printFileAndLineForFailure(failure);
}

void ProdUTestOutput::printFileAndLineForFailure(const TestFailure& failure)
{
    printErrorInFileOnLineFormattedForWorkingEnvironment(failure.getFileName(), failure.getFailureLineNumber());
}

void ProdUTestOutput::printEclipseErrorInFileOnLine(SimpleString file, int lineNumber)
{
    print(file.asCharString());
    print(":");
    print(lineNumber);
    print(";");
}
