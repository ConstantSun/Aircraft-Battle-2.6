#ifndef MAINOBJECT_H_
#define MAINOBJECT_H_
#include"BaseObject.hpp"
#include"BulletObject.hpp"
#include<vector>

const int WIDTH_MAIN_OBJECT = 124;
const int HEIGHT_MAIN_OBJECT = 106;
const int LIVES = 10 ;
const int MAX_INJURED_TIMES = LIVES;

class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();
	void HandleInputAction(SDL_Event events, SDL_Renderer* ren, Mix_Music* m_bullet);
	void HandleMove();
    void SetBulletList(std::vector<BulletObject*> _bullet_list_){
        p_bullet_list_ = _bullet_list_ ;
    }

	void ControlBullet(SDL_Renderer* g_renderer);
    bool LoadInjuredImg(string path, SDL_Renderer *ren);
	void ShowAnimation(SDL_Renderer* ren);
    void ShowInjured(SDL_Renderer* ren) ;

    bool GetIsShownInjured(){ return is_shown_injured_ ; } ;
    void SetIsShownInjured(bool x) { is_shown_injured_ = x;  };
    void IncreaseLives(int val) { lives_+=val; }
    void DecreaseLives() { lives_--; } ;
    int GetLives() {return lives_<=0 ? 0 : lives_ ; } ;

	std::vector <BulletObject*> GetBulletList() {  return p_bullet_list_; } ;
	void LoadDeathImg(string path, SDL_Renderer *ren);
	void ShowDeath(SDL_Renderer* ren, bool & is_quit);
	bool ShowDeathEnough() {return (frame_death >=7 ) ; } ;

private:
	std::vector <BulletObject*> p_bullet_list_;
	int x_val_;
	int y_val_;
	SDL_Rect rectTexture[7];
	SDL_Texture* injured_ = NULL ;
	SDL_Texture* death_ = NULL;

	SDL_Rect rect_injured[4];
	SDL_Rect rect_death[7];

	int lives_ = LIVES ;
	int count_injured_times_ = 0;
	bool is_shown_injured_ = 0;
	int frame = 0 ;
	int frame_death = 0;
};

#endif  // MAINOBJECT_H_
