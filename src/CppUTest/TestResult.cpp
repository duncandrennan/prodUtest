/*
 * Copyright (c) 2007, Michael Feathers, James Grenning and Bas Vodde
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE EARLIER MENTIONED AUTHORS ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "CppUTest/TestHarness.h"
#include "CppUTest/TestResult.h"
#include "CppUTest/TestFailure.h"
#include "CppUTest/TestOutput.h"
#include "CppUTest/PlatformSpecificFunctions.h"

TestResult::TestResult(TestOutput& p) :
    output_(p), testCount_(0), runCount_(0), checkCount_(0), failureCount_(0), filteredOutCount_(0), ignoredCount_(0), totalExecutionTime_(0), timeStarted_(0), currentTestTimeStarted_(0),
            currentTestTotalExecutionTime_(0), currentGroupTimeStarted_(0), currentGroupTotalExecutionTime_(0), result_(""), expected_(""), expected_max_(""), info_("")
{
}

TestResult::~TestResult()
{
}

void TestResult::currentGroupStarted(UtestShell* test)
{
    output_.printCurrentGroupStarted(*test);
    currentGroupTimeStarted_ = (size_t) GetPlatformSpecificTimeInMillis();
}

void TestResult::currentGroupEnded(UtestShell* /*test*/)
{
    currentGroupTotalExecutionTime_ = (size_t) GetPlatformSpecificTimeInMillis() - currentGroupTimeStarted_;
    output_.printCurrentGroupEnded(*this);
}

void TestResult::currentTestStarted(UtestShell* test)
{
    output_.printCurrentTestStarted(*test);
    currentTestTimeStarted_ = (size_t) GetPlatformSpecificTimeInMillis();
}

void TestResult::print(const char* text)
{
    output_.print(text);
}

void TestResult::printVeryVerbose(const char* text)
{
    output_.printVeryVerbose(text);
}

void TestResult::currentTestEnded(UtestShell* test)
{
    currentTestTotalExecutionTime_ = (size_t) GetPlatformSpecificTimeInMillis() - currentTestTimeStarted_;
    currentTestPassed_ = !test->hasFailed();
    output_.printCurrentTestEnded(*this);
    result_ = "";
    expected_ = "";
    expected_max_ = "";
    info_ = "";
}

void TestResult::addFailure(const TestFailure& failure)
{
    output_.printFailure(failure);
    failureCount_++;
}

void TestResult::addExpected(const SimpleString& expected, const SimpleString& expected_max)
{
    expected_ = expected;
    expected_max_ = expected_max;
}

void TestResult::addResult(const SimpleString& result)
{
    result_ += result;
}

void TestResult::addInfo(const SimpleString& info)
{
    info_ += info;
}

void TestResult::countTest()
{
    testCount_++;
}

void TestResult::countRun()
{
    runCount_++;
}

void TestResult::countCheck()
{
    checkCount_++;
}

void TestResult::countFilteredOut()
{
    filteredOutCount_++;
}

void TestResult::countIgnored()
{
    ignoredCount_++;
}

void TestResult::testsStarted()
{
    timeStarted_ = (size_t) GetPlatformSpecificTimeInMillis();
    output_.printTestsStarted();
}

void TestResult::testsEnded()
{
    size_t timeEnded = (size_t) GetPlatformSpecificTimeInMillis();
    totalExecutionTime_ = timeEnded - timeStarted_;
    output_.printTestsEnded(*this);
}

const char * TestResult::getExpected() const
{
    return expected_.asCharString();
}

const char * TestResult::getExpectedMax() const
{
    return expected_max_.asCharString();
}

const char * TestResult::getResult() const
{
    return result_.asCharString();
}

const char * TestResult::getInfo() const
{
    return info_.asCharString();
}

size_t TestResult::getTotalExecutionTime() const
{
    return totalExecutionTime_;
}

void TestResult::setTotalExecutionTime(size_t exTime)
{
    totalExecutionTime_ = exTime;
}

size_t TestResult::getCurrentTestTotalExecutionTime() const
{
    return currentTestTotalExecutionTime_;
}

size_t TestResult::getCurrentGroupTotalExecutionTime() const
{
    return currentGroupTotalExecutionTime_;
}

bool TestResult::getCurrentTestPassed() const
{
    return currentTestPassed_;
}

