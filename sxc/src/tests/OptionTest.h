#include <string>
#include <cppunit/extensions/HelperMacros.h>

#include "../Exception/OptionException.h"
#include "../Option/Parser.h"
#include "../Option/Option.h"
#include "../Option/OptionPort.h"

class OptionTest : public CppUnit::TestFixture
{
    public:
        static CppUnit::Test *suite()
        {
            CppUnit::TestSuite *suite = new CppUnit::TestSuite("Option");

            suite->addTest(new CppUnit::TestCaller<OptionTest>(
                "Correct option parsing",
                &OptionTest::testCorrectOptionParsing));

            suite->addTest(new CppUnit::TestCaller<OptionTest>(
                "Option parsing with an unknown long option",
                &OptionTest::testOptionParsingUnknownLongOption));

            suite->addTest(new CppUnit::TestCaller<OptionTest>(
                "Option parsing with an unknown short option",
                &OptionTest::testOptionParsingUnknownShortOption));

            suite->addTest(new CppUnit::TestCaller<OptionTest>(
                "Conflicting short name",
                &OptionTest::testConflictingShortName));

            suite->addTest(new CppUnit::TestCaller<OptionTest>(
                "Conflicting long name",
                &OptionTest::testConflictingLongName));

            return suite;
        }

        void setUp()
        {
            _parser = new Option::Parser;

            _bool   = new Option::Option<bool>(
                _parser, 'a', "bool", "abc", "description");

            _bool2   = new Option::Option<bool>(
                _parser, 'g', "bool2", "abc", "description", true);

            _int    = new Option::Option<int>(
                _parser, 'b', "int", "def", "description", 42);

            _float  = new Option::Option<float>(
                _parser, 'c', "float", "ghi", "description");

            _char   = new Option::Option<char>(
                _parser, 'd', "char", "jkl", "description", 'x');

            _long   = new Option::Option<long>(
                _parser, 'e', "long", "foobar", "description");

            _string = new Option::Option<std::string>(
                _parser, 'f', "string", "var", "description", "default");

            _default = new Option::Option<int>(
                _parser, ' ', "", "foo", "description");

            _default2 = new Option::Option<std::string>(
                _parser, ' ', "", "foob", "description");
        }

        void tearDown()
        {
            delete _parser;

            delete _bool;
            delete _bool2;
            delete _int;
            delete _float;
            delete _char;
            delete _long;
            delete _string;
            delete _default;
            delete _default2;
        }

        void testCorrectOptionParsing()
        {
            const char *argv[] = {
                "sxc-test", "-a", "--float", "1.2345", "--char", "c", "-e",
                "123456789", "123", "bar", NULL};

            try {
                _parser->parse(const_cast<char **>(argv));
            } catch (Exception::OptionException &e) {
                CPPUNIT_FAIL(e.getDescription());
            }

            CPPUNIT_ASSERT(_bool->getValue());
            CPPUNIT_ASSERT(_bool2->getValue());
            CPPUNIT_ASSERT_EQUAL(42, _int->getValue());
            CPPUNIT_ASSERT_DOUBLES_EQUAL(1.2345, _float->getValue(), 0.00001);
            CPPUNIT_ASSERT_EQUAL('c', _char->getValue());
            CPPUNIT_ASSERT_EQUAL(123456789L, _long->getValue());
            CPPUNIT_ASSERT_EQUAL(std::string("default"), _string->getValue());
            CPPUNIT_ASSERT_EQUAL(123, _default->getValue());
            CPPUNIT_ASSERT_EQUAL(std::string("bar"), _default2->getValue());
        }

        void testOptionParsingUnknownLongOption()
        {
            const char *argv[] = {
                "sxc-test", "-a", "--float", "1.2345", "--zomfg", "--char", "c",
                "-e", "123456789", "123", "bar", NULL};

            try {
                _parser->parse(const_cast<char **>(argv));
            } catch (Exception::OptionException &e) {
                if (Exception::OptionUnknown == e.getType())
                    return;
            }
            CPPUNIT_FAIL("Unknown Option added");
        }

        void testOptionParsingUnknownShortOption()
        {
            const char *argv[] = {
                "sxc-test", "-a", "--float", "1.2345", "-z", "--char", "c",
                "-e", "123456789", "123", "bar", NULL};

            try {
                _parser->parse(const_cast<char **>(argv));
            } catch (Exception::OptionException &e) {
                if (Exception::OptionUnknown == e.getType())
                    return;
            }
            CPPUNIT_FAIL("Unknown Option added");
        }

        void testConflictingShortName()
        {
            try {
                Option::Option<int> _conflicting(
                    _parser, 'd', "conflicting", "barfoo", "descr");
            } catch (Exception::OptionException &e) {
                if (Exception::OptionsConflicting == e.getType())
                    return;
            }
            CPPUNIT_FAIL("Conflicting Option added");
        }

        void testConflictingLongName()
        {
            try {
                Option::Option<char> _conflicting(
                    _parser, 'z', "long", "bar", "descr", 'y');
            } catch (Exception::OptionException &e) {
                if (Exception::OptionsConflicting == e.getType())
                    return;
            }
            CPPUNIT_FAIL("Conflicting Option added");
        }

    private:
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
