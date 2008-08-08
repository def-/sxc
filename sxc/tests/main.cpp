#include <cppunit/ui/text/TestRunner.h>

#include <OptionTest.h>

int main(int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(OptionTest::suite());

    return !runner.run();
}
