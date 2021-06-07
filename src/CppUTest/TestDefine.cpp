/*
 * Copyright (c) 2021, Duncan Drennan, Michael Feathers, James Grenning and Bas Vodde
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
 * THIS SOFTWARE IS PROVIDED BY THE EARLIER MENTIONED AUTHORS ``AS IS'' AND ANY
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

#include "CppUTest/CppUTestConfig.h"
#include "CppUTest/TestDefine.h"

TestDefine::TestDefine() : name_(""), value_(""), next_(NULL)
{
}

TestDefine::TestDefine(const SimpleString& testDefine) : name_(""), value_(""), next_(NULL)
{
    keyValue(testDefine);
}

TestDefine::TestDefine(const char* testDefine) : name_(""), value_(""), next_(NULL)
{
    keyValue(SimpleString(testDefine));
}

TestDefine* TestDefine::add(TestDefine* testDefine)
{
    next_ = testDefine;
    return this;
}

TestDefine* TestDefine::getNext() const
{
    return next_;
}

const SimpleString& TestDefine::getValue() const
{
    return value_;
}

bool TestDefine::match(const SimpleString& name) const
{
    return (name_ == name);
}

bool TestDefine::operator==(const TestDefine& testDefine) const
{
    return ((name_ == testDefine.name_) && 
            (value_ == testDefine.value_));
}

bool TestDefine::operator!=(const TestDefine& testDefine) const
{
    return ((name_ != testDefine.name_) ||
            (value_ != testDefine.value_));
}

SimpleString TestDefine::asString() const
{
    return StringFromFormat("TestDefine: \"%s\" = \"%s\"", name_.asCharString(), value_.asCharString());
}

void TestDefine::keyValue(const SimpleString& keyValue)
{
    size_t equalsAt = keyValue.find('=');
    size_t length = keyValue.size();

    if ((length == 0) || (equalsAt == 0)) {
        name_ = "";
        value_ = "";
    } else if ((equalsAt == SimpleString::npos) || (equalsAt == (length - 1))) {
        name_ = keyValue.subString(0, equalsAt);
        value_ = "";
    } else {
        name_ = keyValue.subString(0, equalsAt);
        value_ = keyValue.subString(equalsAt + 1);
    }
}

SimpleString StringFrom(const TestDefine& parameter)
{
    return parameter.asString();
}

