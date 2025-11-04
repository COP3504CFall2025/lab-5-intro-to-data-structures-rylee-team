#ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
	LinkedList test = LinkedList<int>();
	test.addHead(5);
	test.addHead(3);
	test.addTail(8);
	
	LinkedList test2 = test;

	LinkedList test3 = LinkedList<int>();
	test3.addHead(49);
	test3 = test;

	test.printForward();
	std::cout << std::endl;
	test2.printForward();
	std::cout << std::endl;
	test3.printForward();

    return 0;
}


#endif