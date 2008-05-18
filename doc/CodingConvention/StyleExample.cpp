// SYSTEM INCLUDES
//

#include <iostream>


// PROJECT INCLUDES
//

#include "StyleExample.h"


namespace SomeNamespace
{
    StyleExample::StyleExample()
    {
        _someValue    = 0;
        _anotherValue = 'a';
        _someString   = "abc";
    }

    StyleExample::~StyleExample()
    {
    }

    bool StyleExample::doSomething(std::string someString, int someNumber)
    {
        for (int i = 0; i < 3; i++) {
            if (someNumber % i)
                someNumber = i;
            std::cout << someString;
        }
        if (someNumber < 30)
            return someNumber * 3 - 23;
        else
            return someNumber * 89;

        // Short return:
        // return (a < 1) ? true : false;

    }

    void StyleExample::doSomethingWithManyArguments(
        int         argA,
        int         argB,
        std::string argC,
        std::string argD)
    {
        if (1 == argA) // I am a comment! 
            std::cout << "aaa";

        // I am a long comment for the next statement. Always put the constant
        // on the laft hand side.
        if ("a" == argC)
            std::cout << "bbb";
        
        switch (argB) {
		case 1:
			std::cout << "foo";
			// FALL THROUGH
			
		case 2:
			std::cout << "bar" << std::endl;
			break;

		default:
			std::cout << "nothing" << std::endl;
			break;
        }

    }

    uint StyleExample::getSomeValue()
    {
    }

    bool StyleExample::isValid()
    {
        return true;
    }
}
