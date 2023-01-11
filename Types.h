#pragma once
class Types
{
public:

    struct GridBox
    {
        int xIndex;
        int yIndex;
        bool ocupied;
        int Index;

        GridBox()
            	{

            	}

        GridBox(int x, int y, bool ocupied, int index)
        {
            xIndex = x;
            yIndex = y;
            //remove ambiguity
            this->ocupied = ocupied;
            Index = index;
        }

        //implemented operator overload
        friend bool operator == (const GridBox &obj1, const GridBox &obj2)
        {
           	return obj1.yIndex == obj2.yIndex && obj1.xIndex == obj2.xIndex && obj1.ocupied == obj2.ocupied && obj1.Index == obj2.Index;
        }

    };

    enum CharacterClass
    {
        Paladin = 1,
        Warrior = 2,
        Cleric = 3,
        Archer = 4
    };

};

