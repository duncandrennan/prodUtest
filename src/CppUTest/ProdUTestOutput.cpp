#include "CppUTest/TestHarness.h"
#include "CppUTest/ProdUTestOutput.h"

#include <time.h>

ProdUTestOutput::ProdUTestOutput() :
     file_(NULL), errorCode_(0), finalTest_(false)
{
    verbose(level_verbose);
}

ProdUTestOutput::~ProdUTestOutput()
{
}

void ProdUTestOutput::printTestsStarted()
{
    // TODO: open a directory
    // TODO: specify log filename or suffix from command line

    time_t tm = time(NULL);
    char dateTime[80];
    struct tm *tmp = gmtime(&tm);
    strftime(dateTime, 80, "%Y%m%d_%H%M%S", tmp);
    
    SimpleString fileName = StringFromFormat("logs/%s_log.json", dateTime);

    print("Logging to:");
    print(fileName.asCharString());
    print("\n");

    openFileForWrite(fileName);
    writeToFile("{");
    writeToFile(StringFromFormat("\"ts\":\"%lu\",", (unsigned long)tm));
    strftime(dateTime, 80, "%Y-%m-%dT%H:%M:%SZ", tmp);
    writeToFile(StringFromFormat("\"date\":\"%s\",", dateTime));
    writeToFile("\"tests\":[");
}

void ProdUTestOutput::printTestsEnded(const TestResult& result)
{
    TestOutput::printTestsEnded(result);

    writeToFile("],");
    writeToFile(StringFromFormat("\"error\":%d,", errorCode_));
    writeToFile(StringFromFormat("\"duration\":%lu,", result.getTotalExecutionTime()));
    writeToFile(StringFrom("\"pass\":") + StringFrom(result.getFailureCount() == 0));
    writeToFile("}");
    closeFile();
}

void ProdUTestOutput::printCurrentTestStarted(const UtestShell& test)
{
    print(test.getFormattedName().asCharString());

    writeToFile("{");
    writeToFile(StringFromFormat("\"group\":\"%s\",", test.getGroup().asCharString()));
    writeToFile(StringFromFormat("\"name\":\"%s\",", test.getName().asCharString()));
    writeToFile(StringFrom("\"will_run\":") + StringFrom(test.willRun()) + StringFrom(","));

    if (test.getNext() == NULL)
    {
        finalTest_ = true;
    }
}

void ProdUTestOutput::printCurrentTestEnded(const TestResult& res)
{
    print(";");
    if (res.getCurrentTestPassed()) {
        print("PASS;0;");
    } else {
        print("FAIL;");
        print((long)errorCode_); 
        print(";");
    }
    print(res.getResult());
    print(";");
    print(res.getExpected());
    print(";");
    print(res.getExpectedMax());
    print(";");
    print(res.getCurrentTestTotalExecutionTime());
    print(" ms\n");

    writeToFile(StringFromFormat("\"result\":\"%s\",", res.getResult()));
    writeToFile(StringFromFormat("\"expected\":\"%s\",", res.getExpected()));
    writeToFile(StringFromFormat("\"expected_max\":\"%s\",", res.getExpectedMax()));
    writeToFile(StringFromFormat("\"info\":\"%s\",", res.getInfo()));
    writeToFile(StringFromFormat("\"duration\":%lu,", res.getCurrentTestTotalExecutionTime()));
    writeToFile(StringFrom("\"pass\":") + StringFrom(res.getCurrentTestPassed()));
    writeToFile("}");

    if (!finalTest_ && res.getCurrentTestPassed()) {
        writeToFile(",");
    }
}

void ProdUTestOutput::printFailure(const TestFailure& failure)
{
    if (errorCode_ == 0) {
        errorCode_ = failure.getErrorCode();
    }
}

void ProdUTestOutput::printFileAndLineForFailure(const TestFailure& failure)
{
    printErrorInFileOnLineFormattedForWorkingEnvironment(failure.getFileName(), failure.getFailureLineNumber());
}

void ProdUTestOutput::openFileForWrite(const SimpleString& fileName)
{
    file_ = PlatformSpecificFOpen(fileName.asCharString(), "w");
}

void ProdUTestOutput::writeToFile(const SimpleString& buffer)
{
    PlatformSpecificFPuts(buffer.asCharString(), file_);
}

void ProdUTestOutput::closeFile()
{
    PlatformSpecificFClose(file_);
}
