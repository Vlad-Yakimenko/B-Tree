#include <iostream>
#include <string>

using namespace std;

class BTreeNode
{
public:
    BTreeNode(int Key = 0, string Word = "Hello!")
    {
        this -> Key = Key;
        this -> Word = Word;
        Min = 0;
        Max = 0;
        for(int i = 0; i < 3; i++)
            Array[i] = NULL;
    }
    int Key;
    string Word;
    int Min;
    int Max;
    BTreeNode **Array = new BTreeNode *[3];
};

int Checkout(const BTreeNode *Temp)
{
    for(int i = 0; i < 3; ++i)
    {
        if(Temp -> Array[i] == NULL)
            return i;
    }
}

int RightNumber(const BTreeNode *Temp, const int Number)
{
    for(int i = 0; i < 3; i++)
    {
        if((Temp -> Array[i]) -> Key > Number)
            return i;
    }
}

int CheckIt(const BTreeNode *Temp, const int Number)
{
    for(int i = 0; i < 3; i++)
    {
        if((Temp -> Array[i]) -> Max >= Number && (Temp -> Array[i]) -> Min <= Number)
            return i;
    }
}

int CheckForSearch(const BTreeNode *Temp, const int Number)
{
    for(int i = 0; i < 3; i++)
    {
        if((Temp -> Array[i]) == NULL)
            continue;
        if((Temp -> Array[i]) -> Key == Number)
            return 0;
        if((Temp -> Array[i]) -> Min <= Number && (Temp -> Array[i]) -> Max >= Number)
            return 1;
    }
}

int IndexForSearch(const BTreeNode *Temp, const int Number)
{
    for(int i = 0; i < 3; i++)
    {
        if((Temp -> Array[i]) == NULL)
            continue;
        if((Temp -> Array[i]) -> Key == Number)
            return i;
    }
}

int SearchForNextStep(const BTreeNode *Temp, const int Number)
{
    for(int i = 0; i < 3; i++)
    {
        if((Temp -> Array[i]) == NULL)
            continue;
        if((Temp -> Array[i]) -> Min <= Number && (Temp -> Array[i]) -> Max >= Number)
            return i;
    }
}

int WhatToDo(const BTreeNode *Temp, const int Number)
{
    for(int i = 0; i < 3; i++)
    {
        if(Temp -> Array[i] == NULL)
            return 1;
        if((Temp -> Array[i]) -> Min <= Number && (Temp -> Array[i]) -> Max >= Number)
            return 2;
    }
    if(Temp -> Min > Number && (Temp -> Array[0]) -> Min != NULL)
        return 3;
    if(Temp -> Max < Number && (Temp -> Array[2]) -> Max != NULL)
        return 4;
    if((Temp -> Array[0]) -> Key != NULL)
        return 5;
}

void ExtremeValues(BTreeNode *Temp, const string Word)
{
    Temp -> Array[0] = new BTreeNode(Temp -> Min, Word);
    Temp -> Array[2] = new BTreeNode(Temp -> Max, Temp -> Word);
}

void Add(int KeyForInput, string Word, BTreeNode **Root)
{
    BTreeNode *Temp = *Root;
    if(*Root == NULL)
    {
        Temp = new BTreeNode(KeyForInput, Word);
        *Root = Temp;
    }
    if(Temp -> Key != 0)
    {
        if(Temp -> Key < KeyForInput)
        {
            string Template;
            Temp -> Max = KeyForInput;
            Temp -> Min = Temp -> Key;
            Temp -> Key = NULL;
            Template = Temp -> Word;
            Temp -> Word = Word;
            Word = Template;
            ExtremeValues(Temp, Word);
        }
        else if(Temp -> Key > KeyForInput)
        {
            Temp -> Min = KeyForInput;
            Temp -> Max = Temp -> Key;
            Temp -> Key = NULL;
            ExtremeValues(Temp, Word);
        }
    }
    else if(Temp -> Key == NULL)
    {
        if(Temp -> Min < KeyForInput && Temp -> Max > KeyForInput)
        {
            while(true)
            {
                int Wut = WhatToDo(Temp, KeyForInput);
                if(Wut == 0 || Wut == 1)
                {
                    int Index = Checkout(Temp);
                    Temp -> Array[Index] = new BTreeNode(KeyForInput, Word);
                    break;
                }
                else if(Wut == 2)
                {
                    int Index = CheckIt(Temp, KeyForInput);
                    Temp = Temp -> Array[Index];
                }
                else if(Wut == 5)
                {
                    int Index = RightNumber(Temp, KeyForInput);
                    Temp = Temp -> Array[Index];
                    Temp -> Min = KeyForInput;
                    Temp -> Max = Temp -> Key;
                    Temp -> Key = NULL;
                    ExtremeValues(Temp, Word);
                    break;
                }
            }
        }
        if(Temp -> Min > KeyForInput)
        {
            while(true)
            {
                int Wut = WhatToDo(Temp, KeyForInput);
                if(Wut == 0 || Wut == 1)
                {
                    int Index = Checkout(Temp);
                    Temp -> Min = KeyForInput;
                    Temp -> Array[Index] = Temp -> Array[0];
                    Temp -> Array[0] = new BTreeNode(KeyForInput, Word);
                    break;
                }
                else if(Wut == 3)
                {
                    while((Temp -> Array[0]) -> Key == NULL)
                    {
                        Temp -> Min = KeyForInput;
                        Temp = Temp -> Array[0];
                    }
                }
                else if(Wut == 5)
                {
                    Temp -> Min = KeyForInput;
                    Temp = Temp -> Array[0];
                    Temp -> Min = KeyForInput;
                    Temp -> Max = Temp -> Key;
                    Temp -> Key = NULL;
                    ExtremeValues(Temp, Word);
                    break;
                }
            }
        }
        else if(Temp -> Max < KeyForInput)
        {
            while(true)
            {
                int Wut = WhatToDo(Temp, KeyForInput);
                if(Wut == 1)
                {
                    int Index = Checkout(Temp);
                    Temp -> Max = KeyForInput;
                    Temp -> Array[Index] = Temp -> Array[2];
                    Temp -> Array[2] = new BTreeNode(KeyForInput, Word);
                    break;
                }
                else if(Wut == 4)
                {
                    while((Temp -> Array[2]) -> Key == NULL)
                    {
                        Temp -> Max = KeyForInput;
                        Temp = Temp -> Array[2];
                    }
                }
                else
                {
                    string Template;
                    Temp -> Max = KeyForInput;
                    Temp = Temp -> Array[2];
                    Temp -> Min = Temp -> Key;
                    Temp -> Max = KeyForInput;
                    Temp -> Key = NULL;
                    Template = Temp -> Word;
                    Temp -> Word = Word;
                    Word = Template;
                    ExtremeValues(Temp, Word);
                    break;
                }
            }
        }
    }
}

BTreeNode *Search(const int KeyForOutput, BTreeNode *Root)
{
    BTreeNode *Temp = Root;
    if(KeyForOutput > Temp -> Max || KeyForOutput < Temp -> Min)
        cout << "Wrong Index" << endl;
    else
    {
        while(true)
        {
            int WhereToGo = CheckForSearch(Temp, KeyForOutput);
            if(WhereToGo == 0)
            {
                int Index = IndexForSearch(Temp, KeyForOutput);
                Temp = Temp -> Array[Index];
                return Temp;
            }
            else if(WhereToGo == 1)
            {
                int Index = SearchForNextStep(Temp, KeyForOutput);
                Temp = Temp -> Array[Index];
            }
        }
        /*
        Temp = Temp -> Array[2];
        Temp = Temp -> Array[2];
        Temp = Temp -> Array[2];
        cout << (Temp -> Array[2]) -> Word << endl;
        */
    }
}

void Searching(const int KeyForSearch, BTreeNode *Root)
{
    BTreeNode *Temp = Search(KeyForSearch, Root);
    cout << Temp -> Word << endl;
}

void Deleting(const int KeyForDelete, BTreeNode *Root)
{
    BTreeNode *Temp = Search(KeyForDelete, Root);
    delete Temp;
}

int main()
{
    BTreeNode *Root = nullptr;
    Add(15, "Vladik", &Root);
    Add(25, "Tatiana", &Root);
    Add(18, "!!!", &Root);
    Add(19, "00000", &Root);
    Add(20, "LOLLOL", &Root);
    Add(16, "WWW", &Root);
    Add(17, "PPPPP", &Root);
    Add(21, "+-+-+-", &Root);
    Add(22, "&&??", &Root);
    Add(23, "@", &Root);
    Add(14, "qwerty", &Root);
    Add(26, "###", &Root);
    Add(27, "Maxim", &Root);
    Add(28, "Samoilenko", &Root);
    Add(29, "Ivanov", &Root);
    Add(30, "Karnaux", &Root);
    Add(31, "Karnaux  1", &Root);
    Searching(31, Root);
    return 0;
}

//if((Temp -> Array[0]) -> Key != NULL && (Temp -> Array[2]) -> Key != NULL & Temp -> Array[i] == NULL)
