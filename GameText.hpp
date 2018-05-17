#ifndef GAMETEXT_H_
#define GAMETEXT_H_
#include"BaseObject.hpp"
#include"General_Function.hpp"

class GameText: public BaseObject
{
public:
    void Present( SDL_Renderer *ren ); // present any text
    void ShowNum (TTF_Font *gFont, SDL_Color textColor, SDL_Renderer *gRenderer  ); // only number
    void SetValue(int val) {value_ = val ;} ;
    int GetValue(){return value_ ;} ;
    void IncreaseValue(int x) {   value_+=x;
                                  if (value_<=0) value_ = 0; } ;
private:
    bool loadFromRenderedText(TTF_Font *gFont, std::string textureText, SDL_Color textColor, SDL_Renderer *gRenderer  );
    string ConvertIntToString();
    int value_ = 0;
};
#endif // GAMETEXT_H_
