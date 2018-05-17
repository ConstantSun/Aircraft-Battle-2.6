#include"BonusObject.hpp"

BonusObject::BonusObject()
{
    rect_.w = BONUS_WIDTH ;
    rect_.h = BONUS_HEIGHT;
}
void BonusObject::SetType (int type)
{
    type_ = type;
    switch(type_)
    {
    case 1 :
        // bonus1.png
        BONUS_HEIGHT = 72 ;
        BONUS_WIDTH = 48 ;
    break;
    case 2 :
        //BonusStarLife.png
        BONUS_WIDTH= 474/4 ;
        BONUS_HEIGHT = 551/4 ;
    break;
    }
    rect_.w = BONUS_WIDTH ;
    rect_.h = BONUS_HEIGHT;
} ;

void BonusObject::HandleCount()
{
    count_++;
    if (count_ >= MAX_COUNT ) {
        is_shown_ = 0;
    }
} ;
