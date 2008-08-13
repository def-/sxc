#include <string>
#include <gloox/jid.h>
#include <cppunit/extensions/HelperMacros.h>

#include <Exception/OptionException.h>
#include <Option/Parser.h>
#include <Option/Option.h>
#include <Option/OptionPort.h>

class OptionTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(OptionTest);
        CPPUNIT_TEST(testCorrectParsing);
        CPPUNIT_TEST(testMissingObligatoryOption);
        CPPUNIT_TEST(testValueNotSet);
        CPPUNIT_TEST(testOptionSetMultipleTimes);
        CPPUNIT_TEST(testUnknownLongOption);
        CPPUNIT_TEST(testUnknownShortOption);
        CPPUNIT_TEST(testConflictingShortName);
        CPPUNIT_TEST(testConflictingLongName);
        CPPUNIT_TEST(testJids);
        CPPUNIT_TEST(testConvertType);
    CPPUNIT_TEST_SUITE_END();

    public:
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
