#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "intDList.hpp"
#include <iostream>
#include <string>
using namespace std;

TEST_CASE ("Test cases for intDList")
{
    IntDLList myList;
    
   
    SECTION("output all elemrnts of list")
    {
        myList.insertInOrder(9);
        myList.insertInOrder(8);
        myList.insertInOrder(0);
        myList.insertInOrder(3);
        string output = myList.addToString();
        string output_should_be = "0389";
        REQUIRE_THAT(output, Catch::Equals(output_should_be));
        
        myList.insertInOrder(4);
        output = myList.addToString();
        output_should_be = "03489";
        REQUIRE_THAT(output, Catch::Equals(output_should_be));
        
        myList.deleteFromHead();
        output = myList.addToString();
        output_should_be = "3489";
        REQUIRE_THAT(output, Catch::Equals(output_should_be));
        
        myList.deleteNode(8);
        output = myList.addToString();
        output_should_be = "349";
        REQUIRE_THAT(output, Catch::Equals(output_should_be));

        myList.deleteFromTail();
        output = myList.addToString();
        output_should_be = "34";
        REQUIRE_THAT(output, Catch::Equals(output_should_be));
    }
    
}

    

