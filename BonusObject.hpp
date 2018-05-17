#ifndef BONUS_OBJECT_H_
#define BONUS_OBJECT_H_
#include"BaseObject.hpp"
const int MAX_COUNT = 100 ; // until count_  reach this value then bonus object disappear (being deleted) .

class BonusObject : public BaseObject
{
public:
    BonusObject();
    //~BonusObject();
    void SetIsShown(bool x ) { is_shown_ = x; };
    void HandleCount() ;  //  every time this function is called, count_++ and is_shown_ is true until count_ reach max value.
    bool GetIsShown() { return is_shown_ ;} ;
    void SetType (int type) ;
    int GetType () {return type_ ;} ;
private:
    bool is_shown_ = 1;
    int count_ = 0;
    int type_ = 1;
    int BONUS_HEIGHT = 72 ;
    int BONUS_WIDTH = 48 ;
};

#endif // BONUS_OBJECT_H_
