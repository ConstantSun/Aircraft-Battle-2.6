#include"mainFunction.hpp"
#include<thread>
#include<chrono>
int main(int argc, char* argv[])
{
    srand (time(NULL));
    bool is_quit = false;
    if (!init())
    {
	cout << "can't initialize SDL !!! " << endl;
	return 0 ;
    }
    rect_background.x = rect_background.y = 0; rect_background.w = SCREEN_WIDTH;  rect_background.h = SCREEN_HEIGHT;
	SDL_General::LoadBackGround(g_renderer) ;
    static SDL_Rect rectPress { rectPress.x = 65 ,  rectPress.y = 327 ,   rectPress.w = 458 , rectPress.h = 88  }  ;
    static LTexture gModulatedTexture(g_renderer,rect_background), intro(g_renderer,rect_background), pressS(g_renderer, rectPress) ;
    InitIntroAndEnd(intro,pressS,gModulatedTexture);

    // Introduce game : Game's name, rules.
    int iii = 0;
    Mix_PlayChannel( -1,g_through_gate , 100 );
    while(!is_quit)
    {
            while (SDL_PollEvent(&g_even)!=0) {
                if (g_even.key.keysym.sym == SDLK_s) {
                    is_quit = true;
                }
            };
            if (is_quit) break;
            iii++;
            SDL_RenderClear(g_renderer) ; intro.setAlpha(iii); intro.render();  SDL_RenderPresent( g_renderer );
            pressS.setAlpha(iii); pressS.render(); SDL_RenderPresent( g_renderer );
            SDL_Delay(45);
            if(iii==255) break;
    };
    iii = 0;
     while(!is_quit)
    {
            while (SDL_PollEvent(&g_even)!=0) {
                if (g_even.key.keysym.sym == SDLK_s) {
                    is_quit = true;
                    break;
                }
            }
            if (is_quit) break;
            //ManagePressS(intro,pressS,iii,g_renderer);
            if (iii>=255) iii = -1;
            intro.render();   SDL_RenderPresent( g_renderer );
            pressS.setAlpha(++iii);    pressS.render();    SDL_RenderPresent( g_renderer );
            SDL_Delay(25);
    };
    // Initialize objects in game :
	MainObject  MyAirPlane;
    vector<EnemyDeath*> EnemyDeathList ;
    vector<BonusObject*> BonusObjectList ;
    vector<ThreatObject*> ThreatsList ;
    vector<BossObject*> BossList ;
    vector<BossDeath*> BossDeathList ;
    GameText PlayerLives,Score;
    SDL_General::LoadBackGround(g_renderer);

    InitializeBossAndBossDeathList(BossList,BossDeathList);
	InitializeMainObject(MyAirPlane) ;
	PlayerLives.SetValue(LIVES);
	PlayerLives.SetRect(SCREEN_WIDTH-40,0);
    is_quit = false;
    Mix_HaltChannel(-1);
    // play back ground music
    Mix_PlayChannel( -1,g_bk_music , 100 );
	while (!is_quit)
    {
		while (SDL_PollEvent(&g_even)) {
			if (g_even.type == SDL_QUIT) {
				is_quit = true;
				break;
			}
			MyAirPlane.HandleInputAction(g_even, g_renderer, g_deploy_missile);
        }
        SDL_RenderClear(g_renderer) ;
        SDL_General::ShowBackGround(g_renderer);
        MyAirPlane.ShowAnimation(g_renderer);
        ShowBossListThreatsListBonusListBossDeathThreatsDeath(BossList,ThreatsList,
                                                              BonusObjectList,BossDeathList,EnemyDeathList);
        PlayerLives.ShowNum(gFont,textColor,g_renderer);
        Score.ShowNum(gFont,textColor,g_renderer) ;

        if (MyAirPlane.GetLives()<=0)
        {
            MyAirPlane.ShowDeath(g_renderer,is_quit);
            if (is_quit) break;
        } else
        if ( MyAirPlane.GetIsShownInjured() )
            MyAirPlane.ShowInjured(g_renderer);

        MyAirPlane.HandleMove();
        MyAirPlane.ControlBullet(g_renderer);
        //ShowBossList(BossList);
        PlayerLives.SetValue(MyAirPlane.GetLives());
         // Handle bonus object appear or disappear
        ManageBonusObjectList(BonusObjectList,MyAirPlane,Score);
        if ( rand()%50 == 1 ) CreateAndInitAndPutThreatInList(ThreatsList);
        MakeABoss(BossList,Score);
        // Handle main object vs threats list
        ManageThreatsListWithMainOjectAndEnemyDeathList(ThreatsList,MyAirPlane,EnemyDeathList,Score );
        ManageBossListWithMainOjectAndBossDeathList(BossList,MyAirPlane,BossDeathList,Score );
        // Handle EnemyDeathList : if there is an enemydeath which appeared enough then erasing it.
        ManageEnemyDeathListAndMakeBonus(EnemyDeathList,BonusObjectList);
        ManageBossDeathListAndMakeBonus(BossDeathList,BonusObjectList);
        if (MyAirPlane.GetLives()<=0)
           SDL_Delay(155);
        else  SDL_Delay(45);
	}
	// End Game Information : Showing Game Over 3 times and shut down Game, turn to  window Console.
    Mix_HaltChannel(-1);
    Mix_PlayChannel(-1, g_end_music ,0);
    int i=0,times=0;
    is_quit = false ;
    gModulatedTexture.setColor(255,0,0);
    while(times!=3)
    {
            while (SDL_PollEvent(&g_even)!=0) {
                if (g_even.type == SDL_QUIT) is_quit = true;
            };
            if (is_quit) break;
            i=(i+1)%256;
            SDL_General::ShowBackGround(g_renderer); Score.ShowNum(gFont,textColor,g_renderer) ;
//            ShowBossListThreatsListBonusListBossDeathThreatsDeath(BossList,ThreatsList, BonusObjectList,BossDeathList,EnemyDeathList) ;
            gModulatedTexture.setAlpha(i);   gModulatedTexture.render();    SDL_RenderPresent( g_renderer );
            SDL_Delay(35);
            if(i==255)times++;
    };
	SDL_General::CleanUp();
	SDL_Quit();
	return 0;
}
