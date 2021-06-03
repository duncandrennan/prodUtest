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

#include "CppUTest/TestHarness.h"
#include "CppUTest/TestDefine.h"

TEST_GROUP(TestDefine)
{
};

TEST(TestDefine, match)
{
    TestDefine define("foo=bar");
    CHECK(define.match("foo"));
}

TEST(TestDefine, mismatch)
{
    TestDefine define("foo=bar");
    CHECK(!define.match("notevenclose"));
    CHECK(!define.match("foo="));
    CHECK(!define.match(""));
}

TEST(TestDefine, notEqual)
{
    TestDefine define1("foo=bar");
    TestDefine define2("foo=bar");
    TestDefine define3("bar=foo");
    TestDefine define4("foo=foo");
    CHECK(define1 != define3);
    CHECK(define1 != define4);
    CHECK(! (define1 != define2));
}

TEST(TestDefine, equality)
{
    TestDefine define1("foo=bar");
    TestDefine define2("foo=bar");
    TestDefine define3("bar=foo");
    TestDefine define4("foo=foo");
    CHECK(define1 == define2);
    CHECK(! (define1 == define3));
    CHECK(! (define1 == define4));
}

TEST(TestDefine, listOfDefines)
{
    TestDefine *listOfDefines = NULL;
    TestDefine first("foo=bar");
    TestDefine secnd("bar=foo");
    listOfDefines = first.add(listOfDefines);
    listOfDefines = secnd.add(listOfDefines);
    TestDefine *current = listOfDefines;
    STRCMP_EQUAL("TestDefine: \"bar\" = \"foo\"", StringFrom(*current).asCharString());
    current = current->getNext();
    STRCMP_EQUAL("TestDefine: \"foo\" = \"bar\"", StringFrom(*current).asCharString());
    POINTERS_EQUAL(NULL, current->getNext());
}

TEST(TestDefine, noInput)
{
    TestDefine define(SimpleString(""));
    STRCMP_EQUAL("TestDefine: \"\" = \"\"", StringFrom(define).asCharString());
}

TEST(TestDefine, equalsValue)
{
    TestDefine define(SimpleString("=value"));
    STRCMP_EQUAL("TestDefine: \"\" = \"\"", StringFrom(define).asCharString());
}

TEST(TestDefine, equalsOnly)
{
    TestDefine define(SimpleString("="));
    STRCMP_EQUAL("TestDefine: \"\" = \"\"", StringFrom(define).asCharString());
}

TEST(TestDefine, keyOnlyWithEquals)
{
    TestDefine define(SimpleString("name="));
    STRCMP_EQUAL("TestDefine: \"name\" = \"\"", StringFrom(define).asCharString());
}

TEST(TestDefine, keyOnly)
{
    TestDefine define(SimpleString("name"));
    STRCMP_EQUAL("TestDefine: \"name\" = \"\"", StringFrom(define).asCharString());
}

TEST(TestDefine, keyValuePair)
{
    TestDefine define(SimpleString("name=value"));
    STRCMP_EQUAL("TestDefine: \"name\" = \"value\"", StringFrom(define).asCharString());
}

TEST(TestDefine, constructors)
{
    TestDefine define1;
    TestDefine define2(SimpleString("name=value"));
    TestDefine define3("name=value");
    CHECK(define1.getNext() == NULL);
    CHECK(define2.getNext() == NULL);
    CHECK(define3.getNext() == NULL);
}
