#include "StringUtility.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    std::string TestStrings[] = 
    {
        "This string should be  seperated    by        words",
        "[This is] using {groups}",
        "This is a test to check[interactions]{ between [groups] and }seperators",
        "Th#is\n te#st\n is\n t#o\n te#s#t\n i#gn#or#e\n ch#ar#s\n",
        "This is to test \"same char\" grouping chars"
    };

    std::string ResultStrings1[] = 
    {
        "This",
        "string",
        "should",
        "be",
        "seperated",
        "by",
        "words"
    };

    std::string ResultStrings2[] =
    {
        "This is",
        "using",
        "groups"
    };

    std::string ResultStrings3[] =
    {
        "This",
        "is",
        "a",
        "test",
        "to",
        "check",
        "interactions",
        " between [groups] and ",
        "seperators"
    };

    std::string ResultStrings4[] =
    {
        "This",
        "test",
        "is",
        "to",
        "test",
        "ignore",
        "chars"
    };

    std::string ResultStrings5[] =
    {
        "This",
        "is",
        "to",
        "test",
        "same char",
        "grouping",
        "chars"
    };

    StringUtility TestUtility1(&TestStrings[0]);
    TestUtility1.AddSeperator(' ');

    TestUtility1.SeperateString();

    if (TestUtility1.SeperatedSize() != 7)
    {
        std::cout << "Seperator Test falied: invalid number of sub strings" << std::endl;
        return 2;
    }

    for (unsigned int i = 0; i < TestUtility1.SeperatedSize(); i++)
    {
        std::string CurrentRead = TestUtility1[i];
        if (CurrentRead != ResultStrings1[i])
        {
            std::cout << "Seperator test falied" << std::endl;
            return 1;
        }
    }

    std::cout << "Seperator test passed" << std::endl;

    StringUtility TestUtility2(&TestStrings[1]);
    TestUtility2.AddSeperator(' ');
    GroupingExspression NewGroupExpression;
    NewGroupExpression.StartingChar = '{';
    NewGroupExpression.EndingChar = '}';
    TestUtility2.AddGroupingExpression(NewGroupExpression);
    NewGroupExpression.StartingChar = '[';
    NewGroupExpression.EndingChar = ']';
    TestUtility2.AddGroupingExpression(NewGroupExpression);

    TestUtility2.SeperateString();

    if (TestUtility2.SeperatedSize() != 3)
    {
        std::cout << "Grouping test falied: invalid number of sub strings" << std::endl;
        return 3;
    }

    for (unsigned int i = 0; i < TestUtility2.SeperatedSize(); i++)
    {
        std::string CurrentRead = TestUtility2[i];
        if (CurrentRead != ResultStrings2[i])
        {
            std::cout << "Grouping Test falied" << std::endl;
            return 4;
        }
    }

    std::cout << "Grouping test passed" << std::endl;

    StringUtility TestUtility3(&TestStrings[2]);
    TestUtility3.AddSeperator(' ');
    NewGroupExpression.StartingChar = '{';
    NewGroupExpression.EndingChar = '}';
    TestUtility3.AddGroupingExpression(NewGroupExpression);
    NewGroupExpression.StartingChar = '[';
    NewGroupExpression.EndingChar = ']';
    TestUtility3.AddGroupingExpression(NewGroupExpression);

    TestUtility3.SeperateString();

    if (TestUtility3.SeperatedSize() != 9)
    {
        std::cout << "Interaction Test falied: invalid number of sub strings" << std::endl;
        return 5;
    }

    for (unsigned int i = 0; i < TestUtility3.SeperatedSize(); i++)
    {
        std::string CurrentRead = TestUtility3[i];
        if (CurrentRead != ResultStrings3[i])
        {
            std::cout << "Interaction Test falied" << std::endl;
            return 6;
        }
    }

    std::cout << "Interaction test passed" << std::endl;

    StringUtility TestUtility4(&TestStrings[3]);
    TestUtility4.AddSeperator(' ');
    TestUtility4.AddIgnoreCharacater('#');
    TestUtility4.AddIgnoreCharacater('\n');

    TestUtility4.SeperateString();

    if (TestUtility4.SeperatedSize() != 7)
    {
        std::cout << "Ignore char test falied: invalid number of sub strings" << std::endl;
        return 7;
    }

    for (unsigned int i = 0; i < TestUtility4.SeperatedSize(); i++)
    {
        std::string CurrentRead = TestUtility4[i];
        if (CurrentRead != ResultStrings4[i])
        {
            std::cout << "Ignore char test falied" << std::endl;
            return 7;
        }
    }

    std::cout << "Ingore char test passed" << std::endl;

    StringUtility TestUtility5(&TestStrings[4]);
    TestUtility5.AddSeperator(' ');
    NewGroupExpression.StartingChar = '\"';
    NewGroupExpression.EndingChar = '\"';
    TestUtility5.AddGroupingExpression(NewGroupExpression);
    TestUtility5.SeperateString();

    if (TestUtility5.SeperatedSize() != 7)
    {
        std::cout << "Same char grouping test failed: invalid number fo sub strings" << std::endl;
        //return 8;
    }

    for (unsigned int i = 0; i < TestUtility5.SeperatedSize(); i++)
    {
        std::string CurrentRead = TestUtility5[i];
        if (CurrentRead != ResultStrings5[i])
        {
            std::cout << "Same char grouping test failed" << std::endl;
            return 9;
        }
    }

    std::cout << "Same char grouping test passed" << std::endl;
    return 0;
}