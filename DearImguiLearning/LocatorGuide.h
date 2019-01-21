/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		LOCATOR PATTERN OBJECT -- IMPLEMENTATION GUIDE
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/

// 1.	Create an almost-identical '_i' interface class for the class that you would
//		like to exist as a Singleton & Globally-accessible class. This '_i' class
//		contains pure virtual functions and is the one that is received and used
//		everywhere in the rest of the code.
//
//		EXTRA NOTE #1: 'Class : public Class_i' (<-- Order of inheritance)

// 2.	Create 'provide()' and 'get()' functions for your class in 'locator.hpp',
//		as well as make sure to 'new' the interface pointer out in main and call
//		its 'provide()' function out in main as well.
//
//		IMPORTANT: Also make sure you delete the interface pointer at the bottom
//		of main (in this program it's done in the 'CleanUpLocatorPointers()' function).

// 3.	Use 'Locator::' to access the Locator's pointer variable member and set
//		it to 'nullptr' at the TOP OF THIS FILE.

//		FOR EXAMPLE FILES, SEE: 'serializer.hpp', 'serializer_i.hpp'
