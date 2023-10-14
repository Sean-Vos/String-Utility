#pragma once
#include <string>
#include <vector>

//Defines the location of a substring within a larger string
struct SubString
{
    unsigned int Start = 0;
    unsigned int End = 0;
};

//Defines the characters used to define a region where the string will not be split
struct GroupingExspression
{
    char StartingChar = NULL;
    char EndingChar = NULL;
    bool KeepGroupChars = false;

    bool operator== (GroupingExspression);
};

class StringUtility 
{
private:
    std::string* SourceString;
    std::vector<char> SeperationChars;
    std::vector<GroupingExspression> GroupingExspressions;
    std::vector<bool> GroupStates;
    std::vector<SubString> SubStrings;
    std::vector<char> CharacatersToIgnore;
public:
    StringUtility(std::string* InputString);
    void AddSeperator(char NewSeperator);
    void RemoveSeperator(char Seperator);
    void AddGroupingExpression(GroupingExspression NewGroup);
    void RemoveGroupingExpression(GroupingExspression Group);
    void SeperateString();
    unsigned int SeperatedSize();
    void AddIgnoreCharacater(char NewChar);
    void RemoveIgnoreCharacaters(char Remove);

    std::string operator [] (unsigned int Index);
};

bool GroupingExspression::operator== (GroupingExspression CompareTo)
{
    if ((this->EndingChar == CompareTo.EndingChar) && (this->StartingChar == CompareTo.StartingChar))
    {
        return true;
    }
    else
    {
        return false;
    }
}

StringUtility::StringUtility(std::string* InputString)
{
    SourceString = InputString;
    return;
}

void StringUtility::AddSeperator(char NewSeperator)
{
    for (unsigned int i = 0; i < SeperationChars.size(); i++)
    {
        if (SeperationChars.at(i) == NewSeperator)
        {
            return;
        }
    }

    SeperationChars.push_back(NewSeperator);
    return;
}

void StringUtility::RemoveSeperator(char Seperator)
{
    for (unsigned int i = 0; i < SeperationChars.size(); i++)
    {
        if (SeperationChars.at(i) == Seperator)
        {
            SeperationChars.erase(SeperationChars.begin() + i);
            break;
        }
    }
    return;
}

void StringUtility::AddGroupingExpression(GroupingExspression NewGroup)
{
    for (unsigned int i = 0; i < GroupingExspressions.size(); i++)
    {
        if (NewGroup == GroupingExspressions.at(i))
        {
            return;
        }
    }

    GroupingExspressions.push_back(NewGroup);
    GroupStates.push_back(false);
    return;
}

void StringUtility::RemoveGroupingExpression(GroupingExspression Grouping)
{
    for (unsigned int i = 0; i < GroupingExspressions.size(); i++)
    {
        if (Grouping == GroupingExspressions.at(i))
        {
            GroupingExspressions.erase(GroupingExspressions.begin() + i);
            return;
        }
    }
    return;
}

void StringUtility::SeperateString()
{
    SubString CurrentSubString;
    unsigned int CurrentGroupIndex = -1;
    const unsigned int MAX = -1;

    for (unsigned int i = 0; i < SourceString->size(); i++)
    {
        bool InsideGroup = false;

        for (unsigned int a = 0; a < GroupingExspressions.size(); a++)
        {
            if ((SourceString->at(i) == GroupingExspressions.at(a).StartingChar) && (GroupStates.at(a) == false))
            {

                if (CurrentGroupIndex == MAX)
                {
                    GroupStates.at(a) = true;
                    CurrentSubString.End = i;
                    SubStrings.push_back(CurrentSubString);
                    CurrentSubString.Start = i + 1;
                    CurrentSubString.End = 0;
                    CurrentGroupIndex = a;
                }
            }
            else if (SourceString->at(i) == GroupingExspressions.at(a).EndingChar)
            {
                if (CurrentGroupIndex == a)
                {
                    GroupStates.at(a) = false;
                    CurrentSubString.End = i;
                    SubStrings.push_back(CurrentSubString);
                    CurrentSubString.Start = i + 1;
                    CurrentSubString.End = 0;
                    CurrentGroupIndex = MAX;
                }
            }
        }

        for (unsigned int a = 0; a < GroupStates.size(); a++)
        {
            if (GroupStates.at(a) == true)
            {
                InsideGroup = true;
                break;
            }
        }

        if (InsideGroup == true)
        {
            continue;
        }

        for (unsigned int a = 0; a < SeperationChars.size(); a++)
        {
            if (SourceString->at(i) == SeperationChars.at(a))
            {
                CurrentSubString.End = i;
                SubStrings.push_back(CurrentSubString);
                CurrentSubString.Start = i + 1;
                CurrentSubString.End = 0;
            }
        }
    }

    CurrentSubString.End = SourceString->size();
    SubStrings.push_back(CurrentSubString);

    //remove empty SubStrings
    for (unsigned int i = 0; i < SubStrings.size(); i++)
    {
        unsigned int Start = SubStrings.at(i).Start;
        unsigned int End = SubStrings.at(i).End;
        if ((End - Start) == 0)
        {
            SubStrings.erase(SubStrings.begin() + i);
            i--;
        }
    }

    return;
}

unsigned int StringUtility::SeperatedSize()
{
    return SubStrings.size();
}

std::string StringUtility::operator[] (unsigned int Index)
{
    std::string StringFromRange;
    unsigned int Size = SubStrings.at(Index).End - SubStrings.at(Index).Start;

    for (unsigned int i = 0; i < Size; i++)
    {
        bool IgnoreThisChar = false;
        for (unsigned int a = 0; a < CharacatersToIgnore.size(); a++)
        {
            if (CharacatersToIgnore.at(a) == SourceString->at(SubStrings.at(Index).Start + i))
            {
                IgnoreThisChar = true;
                break;
            }
        }

        if (IgnoreThisChar)
        {
            continue;
        }

        StringFromRange += SourceString->at(SubStrings.at(Index).Start + i);
    }

    return StringFromRange;
}

void StringUtility::AddIgnoreCharacater(char NewChar)
{
    for (unsigned int i = 0; i < CharacatersToIgnore.size(); i++)
    {
        if (CharacatersToIgnore.at(i) == NewChar)
        {
            return;
        }
    }

    CharacatersToIgnore.push_back(NewChar);
    return;
}

void StringUtility::RemoveIgnoreCharacaters(char Remove)
{
    for (unsigned int i = 0; i < CharacatersToIgnore.size(); i++)
    {
        if (CharacatersToIgnore.at(i) == Remove)
        {
            CharacatersToIgnore.erase(CharacatersToIgnore.begin() + i);
            return;
        }
    }

    return;
}