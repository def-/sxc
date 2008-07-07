#include <string>
#include <cppunit/extensions/HelperMacros.h>

#include "../Option/Parser.h"
#include "../Option/Option.h"
#include "../Option/OptionPort.h"

class OptionTest : public CppUnit::TestFixture
{
    public:
        static CppUnit::Test *suite()
        {
            CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("Option test");
            suiteOfTests->addTest(new CppUnit::TestCaller<OptionTest>("Test short options", &OptionTest::testShortOptions));
            suiteOfTests->addTest(new CppUnit::TestCaller<OptionTest>("Test short options", &OptionTest::testLongOptions));
            return suiteOfTests;
        }

        void setUp()
        {
            _parser = new Option::Parser;
            _short1 = new Option::Option<std::string>(_parser, 'a', "abc", "var", "description");
        }

        void tearDown()
        {
            delete _parser;
            delete _short1;
        }

        void testShortOptions()
        {
            CPPUNIT_ASSERT(2 == 2);
        }

        void testLongOptions()
        {
            CPPUNIT_ASSERT(3 == 2);
        }

    private:
        Option::Parser *_parser;
        Option::Option<std::string> *_short1;
};
