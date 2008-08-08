#include <string>
#include <gloox/jid.h>
#include <cppunit/extensions/HelperMacros.h>

#include <Exception/OptionException.h>
#include <Option/Parser.h>
#include <Option/Option.h>
#include <Option/OptionPort.h>

class OptionTest : public CppUnit::TestFixture
{
    public:
        static CppUnit::Test *suite()
        {
            CppUnit::TestSuite *suite = new CppUnit::TestSuite("Option");

            suite->addTest(new CppUnit::TestCaller<OptionTest>(
                "Correct option parsing",
                &OptionTest::testCorrectParsing));

            suite->addTest(new CppUnit::TestCaller<OptionTest>(
                "Option parsing without an obligatory option",
                &OptionTest::testMissingObligatoryOption));

            suite->addTest(new CppUnit::TestCaller<OptionTest>(
                "Option parsing with an option without the value set",
                &OptionTest::testValueNotSet));

            suite->addTest(new CppUnit::TestCaller<OptionTest>(
                "Option parsing with one option set multiple times",
                &OptionTest::testOptionSetMultipleTimes));

            suite->addTest(new CppUnit::TestCaller<OptionTest>(
                "Option parsing with an unknown long option",
                &OptionTest::testUnknownLongOption));

            suite->addTest(new CppUnit::TestCaller<OptionTest>(
                "Option parsing with an unknown short option",
                &OptionTest::testUnknownShortOption));

            suite->addTest(new CppUnit::TestCaller<OptionTest>(
                "Conflicting short name",
                &OptionTest::testConflictingShortName));

            suite->addTest(new CppUnit::TestCaller<OptionTest>(
                "Conflicting long name",
                &OptionTest::testConflictingLongName));

            suite->addTest(new CppUnit::TestCaller<OptionTest>(
                "JIDs",
                &OptionTest::testJids));

            suite->addTest(new CppUnit::TestCaller<OptionTest>(
                "Type conversion",
                &OptionTest::testConvertType));

            return suite;
        }

        void setUp();
        void tearDown();

        void testCorrectParsing();
        void testMissingObligatoryOption();
        void testValueNotSet();
        void testOptionSetMultipleTimes();
        void testUnknownLongOption();
        void testUnknownShortOption();
        void testConflictingShortName();
        void testConflictingLongName();
        void testJids();
        void testConvertType();

    private:
        void doTestInvalidJid(std::string rawJid);
        void doTestValidJid(std::string rawJid);
        template<typename T> void doTestInvalidConvert(std::string rawValue);
        template<typename T> void doTestValidConvert(std::string rawValue);

        Option::Parser *_parser;
        Option::Option<bool> *_bool;
        Option::Option<bool> *_bool2;
        Option::Option<int> *_int;
        Option::Option<float> *_float;
        Option::Option<char> *_char;
        Option::Option<long> *_long;
        Option::Option<std::string> *_string;
        Option::Option<int> *_default;
        Option::Option<std::string> *_default2;
};
