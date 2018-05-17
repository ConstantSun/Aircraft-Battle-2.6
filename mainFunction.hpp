#ifndef MAINFUNCTION_H_
#define MAINFUNCTION_H_

#include"General_Function.hpp"
#include"LTexture.hpp"

#include"MainObject.hpp"
#include"BulletObject.hpp"

#include"ThreatObject.hpp"
#include"EnemyBullet.hpp"
#include"EnemyDeath.hpp"

#include"BonusObject.hpp"

#include"BossObject.hpp"
#include"BossDeath.hpp"
#include"BossBullet.hpp"

#include"GameText.hpp"

bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		g_Window = SDL_CreateWindow(" Aircraft Battle vs0.1 ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		g_renderer = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED );

		if (g_renderer!= NULL)
		{
			SDL_SetRenderDrawColor(g_renderer, 255 , 255, 255, 255);

			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				cout<<"SDL_image could not initialize! SDL_image Error: "<< IMG_GetError()<<endl;
				return 0;
			}

			if ( Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096) == -1 ){
                cout<< " Mix_OpenAudio didn't work !! " <<endl;
                return 0;
			}

            g_deploy_missile = Mix_LoadMUS("gameShooting/m_deploy_missile.mp3");
            g_main_injured = Mix_LoadWAV("gameShooting/m_main_injured.wav");

            g_end_music = Mix_LoadWAV("gameShooting/gameover.mp3");
            g_enemy_death = Mix_LoadWAV("gameShooting/m_enemydeath.wav");
            //g_bk_music = Mix_LoadWAV("gameShooting/Bang Bang_BigBang_-5911316.mp3");
            g_bk_music = Mix_LoadWAV("gameShooting/PlayForReal.mp3");
            g_through_gate = Mix_LoadWAV("gameShooting/throughTheGatesAsphalt8AirborneOST.mp3");
            g_get_item = Mix_LoadWAV("gameShooting/m_get_item.mp3");
            g_success_get_item = Mix_LoadWAV("gameShooting/success_elegant.mp3");


            if ( g_deploy_missile == NULL || g_enemy_death == NULL || g_main_injured == NULL ||
                 g_bk_music == NULL || g_get_item == NULL || g_success_get_item == NULL || g_through_gate == NULL ) {
                if ( g_deploy_missile == NULL  ) cout << " g deploy missile = null " << endl;
                if ( g_enemy_death == NULL  ) cout << " g enemy death = null " << endl;
                if ( g_bk_music == NULL ) cout << " g bk music = null " <<endl;
                if ( g_get_item == NULL ) cout << " g get item = null " <<endl;
                if ( g_main_injured == NULL ) cout << " g main injured = null " <<endl;
                if ( g_through_gate == NULL ) cout << " g through gate = null " <<endl;
                cout << Mix_GetError() << endl;
                return 0;
            }

            // Init TTF and load TTF (gFont)

            if( TTF_Init() == -1 )
            {
                printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }

            gFont = TTF_OpenFont( "gameShooting/JosefinSans-SemiBold.ttf", 28 ); // 28 = point size.
            if( gFont == NULL )
            {
                printf( "Failed to load JosefinSans font (TTF)! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }

			return 1;
		}
		else
			return 0;
	}
	else
        return 0;
}


void InitIntroAndEnd(LTexture &intro, LTexture &pressS, LTexture &gModulatedTexture)
{
    intro.loadFromFile("gameShooting/intro.png");
	pressS.loadFromFile("gameShooting/pressStoPlay.png") ;

	gModulatedTexture.loadFromFile( "gameShooting/gg1.png" ) ;
    gModulatedTexture.setColor(0xFF,0,0);

    intro.setColor(255,255,255);
    pressS.setColor(255,255,255);
}

void ShowThreatsList(vector<ThreatObject*> ThreatsList)
{
    for(int i=0;i<ThreatsList.size();i++)
    {
        if (ThreatsList[i]->GetIsMove())
        {
            ThreatsList[i]->ShowAnimation(g_renderer);
        }
    }
}
;

void InitializeMainObject(MainObject &mainObj)
{
    mainObj.LoadDeathImg("gameShooting/mainDeath.png", g_renderer);
	mainObj.LoadImg("gameShooting/aircraftSpriteSheet.png", g_renderer);
	mainObj.LoadInjuredImg("gameShooting/main_injured.png",g_renderer);
	mainObj.ShowAnimation(g_renderer);
} ;

void InitializeBossAndBossDeathList( vector<BossObject*> &BossList, vector <BossDeath*> &BossDeathList)
{
    for(int i=0;i< MAX_NUMBER_OF_BOSS ;i++)
    {
        BossList.push_back(new BossObject(g_renderer));
        BossList[BossList.size()-1]->LoadImg("gameShooting/boss.png",g_renderer);
        BossDeathList.push_back(new BossDeath);
        BossDeathList[BossDeathList.size()-1]->LoadImg("gameShooting/bossdeath.png",g_renderer);
    }
} ;

void MakeABossDeath(vector<BossDeath*> BossDeathList,BossObject *&boss)
{
    for (int i=0;i<BossDeathList.size();i++)
    {
        if ( !BossDeathList[i]->GetIsShown() )
        {
            //cout << "Boss Death made!" << endl;
            BossDeathList[i]->SetIsShown(true);
            BossDeathList[i]->SetRect(boss->GetRect().x + -30 , boss->GetRect().y + -35 );
            BossDeathList[i]->ShowAnimation(g_renderer);
            break;
        }
    }
}

void CreateAndInitAndPutThreatInList(vector<ThreatObject*> &ThreatsList)
{
    ThreatsList.push_back(new ThreatObject);
    ThreatsList[ThreatsList.size()-1]->LoadImg("gameShooting/enemySpriteSheet.png",g_renderer);
    ThreatsList[ThreatsList.size()-1]->ShowAnimation(g_renderer);
    ThreatsList[ThreatsList.size()-1]->GenerateBullet(g_renderer);
} ;

void CreateAndInitAndPutEnemyDeathInList( vector<EnemyDeath*> &EnemyDeathList,ThreatObject* threat )
{
    EnemyDeathList.push_back(new EnemyDeath);
    EnemyDeathList[EnemyDeathList.size()-1]->LoadImg("gameShooting/enemydeath.png",g_renderer);
    EnemyDeathList[EnemyDeathList.size()-1]->SetRect( threat->GetRect().x , threat->GetRect().y );
    EnemyDeathList[EnemyDeathList.size()-1]->ShowAnimation(g_renderer);
}

void MakeABoss(vector<BossObject*> &BossList,GameText &Score)
{
    for (int i=0;i<BossList.size();i++)
    {
        if ( !BossList[i]->GetIsMove() )
            if (Score.GetValue()>= SCORE_WHICH_BOSS_SHOWN && rand()%50 == 1 ) {
                BossList[i]->Fresh();
                break;
            }
    }
};

void ShowBossList(const vector<BossObject*> &BossList)
{
    for (int i=0;i<BossList.size();i++)
        if (BossList[i]->GetIsMove())
            BossList[i]->ShowAnimation(g_renderer);
}

void ManageBossListWithMainOjectAndBossDeathList(vector<BossObject*> &BossList, MainObject &MyAirPlane,
                                                  vector <BossDeath*> &BossDeathList, GameText &Score )
{
    for (int i=0;i< BossList.size() ;i++)
    {
        if (BossList[i]->GetIsMove())
        {
            vector <BulletObject*> main_bullet_list;
            main_bullet_list = MyAirPlane.GetBulletList();

            if (rand()%10 == 1)  BossList[i]->HandleMove(SCREEN_WIDTH , SCREEN_HEIGHT );
            if (rand()%5 == 1) BossList[i]->GenerateBullet(g_renderer);

            if (SDL_General::Do_two_objects_overlap(BossList[i]->GetRect(),MyAirPlane.GetRect())) {
                MyAirPlane.DecreaseLives();
                Mix_PlayChannel(-1,g_enemy_death,0);
            }
            BossList[i]->ControlBulletAndKillMainObject(SCREEN_WIDTH , SCREEN_HEIGHT,
                                                           g_renderer , MyAirPlane, g_main_injured, Score);

            // Tim xem co enemy nao chet ko ?
            for (int j=0; j < main_bullet_list.size() ; j++ ) {
                // Neu co vien dan  nao ban trung dich thi: xoa dich, xoa dan cua minh, show vu no cua dich
                if ( SDL_General::Do_two_objects_overlap( main_bullet_list[j]->GetRect() , BossList[i]->GetRect() ) )
                {
                    BossList[i]->DecreaseLives();
                    if (BossList[i]->GetLives()<= 0) {
                        // update score :
                        Score.IncreaseValue(KILL_BOSS_SCORE) ;
                        MyAirPlane.IncreaseLives(LIVES_PLUS_FOR_KILL_BOSS);
                        // phat am thanh enemy no:
                        Mix_PlayChannel(-1,g_enemy_death,0);
                        // tao ra 1 enemy death = vu no.
                        MakeABossDeath(BossDeathList,BossList[i]);
                        BossList[i]->SetIsMove(false);
                    }
                    delete main_bullet_list[j];
                    main_bullet_list.erase(main_bullet_list.begin()+j);
                    MyAirPlane.SetBulletList(main_bullet_list);
                }
            }
        }
    }
}
void ManageThreatsListWithMainOjectAndEnemyDeathList(vector<ThreatObject*> &ThreatsList,
                                                    MainObject &MyAirPlane, vector <EnemyDeath*> &EnemyDeathList,
                                                    GameText &Score)
{
    for (int i=0;i< ThreatsList.size() ;i++)
    {
        if (ThreatsList[i]->GetIsMove())
        {
            vector <BulletObject*> main_bullet_list;
            main_bullet_list = MyAirPlane.GetBulletList();

            //ThreatsList[i]->ShowAnimation(g_renderer);
            if (rand()%3 == 1)  ThreatsList[i]->HandleMove(SCREEN_WIDTH , SCREEN_HEIGHT );
            if (rand()%15 == 1) ThreatsList[i]->GenerateBullet(g_renderer);

            if (SDL_General::Do_two_objects_overlap(ThreatsList[i]->GetRect(),MyAirPlane.GetRect())) {
                MyAirPlane.DecreaseLives();
                Mix_PlayChannel(-1,g_enemy_death,0);

                CreateAndInitAndPutEnemyDeathInList(EnemyDeathList,ThreatsList[i]);
                delete ThreatsList[i];
                ThreatsList.erase(ThreatsList.begin()+i);
                break;

            }
            ThreatsList[i]->ControlBulletAndKillMainObject(SCREEN_WIDTH , SCREEN_HEIGHT,
                                                           g_renderer , MyAirPlane, g_main_injured, Score);

            // Tim xem co enemy nao chet ko ?
            for (int j=0; j < main_bullet_list.size() ; j++ ) { // xet tat ca cac vien dan cua nhan vat chinh
                // Neu co vien dan  nao ban trung dich thi: xoa dich, xoa dan cua minh, show vu no cua dich
                if ( SDL_General::Do_main_bullet_overlap_enemy( main_bullet_list[j]->GetRect() , ThreatsList[i]->GetRect() ) )
                {
                    // phat am thanh enemy no:
                    Mix_PlayChannel(-1,g_enemy_death,0);

                    // update score :
                    Score.IncreaseValue(KILL_ENEMY_SCORE) ;

                    // tao ra 1 enemy death = vu no.
                    CreateAndInitAndPutEnemyDeathInList(EnemyDeathList,ThreatsList[i]);

                    delete ThreatsList[i];
                    ThreatsList.erase(ThreatsList.begin()+i);

                    delete main_bullet_list[j];
                    main_bullet_list.erase(main_bullet_list.begin()+j);

                    MyAirPlane.SetBulletList(main_bullet_list);
                }
            }
        }
        else {
            delete ThreatsList[i];
            ThreatsList.erase(ThreatsList.begin()+i);
            cout << " Threats number #" << i << " is deleted !" <<endl;
            cout << " ThreatsList.size() = " << ThreatsList.size() <<endl<<endl ;
        }
    }
}

void ManageBossDeathListAndMakeBonus( vector<BossDeath*> &BossDeathList , vector<BonusObject*> &BonusObjectList )
{
    for (int i=0; i<BossDeathList.size();i++ )
    {
        if (BossDeathList[i]->GetIsShown())
        {
            //BossDeathList[i]->ShowAnimation(g_renderer);
            BossDeathList[i]->HandleAnimation();
        }
        if (BossDeathList[i]->ShowEnough())
        {
            BonusObjectList.push_back(new BonusObject);
            BonusObjectList[BonusObjectList.size()-1]->SetType(2);
            BonusObjectList[BonusObjectList.size()-1]->LoadImg("gameShooting/BonusStarLife.png",g_renderer);
            BonusObjectList[BonusObjectList.size()-1]->SetRect(BossDeathList[i]->GetRect().x + BOSS_OBJECT_WIDTH/2 ,
                                                                BossDeathList[i]->GetRect().y + BOSS_OBJECT_HEIGHT/2);
            //BonusObjectList[BonusObjectList.size()-1]->Show(g_renderer);
        }
    }
}
void ManageEnemyDeathListAndMakeBonus(vector<EnemyDeath*> &EnemyDeathList,vector<BonusObject*> &BonusObjectList) {
    for ( int i=0 ;i < EnemyDeathList.size() ;i++ )
    {
        if ( EnemyDeathList[i]->GetIsShown() ){
            EnemyDeathList[i]->HandleAnimation();
            //EnemyDeathList[i]->ShowAnimation(g_renderer);
        } else {
            // Appear bonus :
            if (rand()% 3 == 0)
            {
                // Add sound effect when getting an item !
                Mix_PlayChannel(-1,g_get_item,0);

                BonusObjectList.push_back(new BonusObject);
                BonusObjectList[BonusObjectList.size()-1]->SetType(1);
                BonusObjectList[BonusObjectList.size()-1]->LoadImg("gameShooting/bonus1.png",g_renderer);
                BonusObjectList[BonusObjectList.size()-1]->SetRect(EnemyDeathList[i]->GetRect().x + THREAT_OBJECT_WIDTH/2 ,
                                                                    EnemyDeathList[i]->GetRect().y + THREAT_OBJECT_HEIGHT/2);
                BonusObjectList[BonusObjectList.size()-1]->Show(g_renderer);
            }

            delete EnemyDeathList[i] ;
            EnemyDeathList.erase ( EnemyDeathList.begin() + i );
            //i--;
        }
    }
}

void ManageBonusObjectList( vector<BonusObject*> &BonusObjectList, MainObject &MyAirPlane, GameText &Score) {
    for (int i=0;i<BonusObjectList.size();i++)
    {
        if( BonusObjectList[i]->GetIsShown() ){
            // if MyAirPlane gets bonus object then it disappears ( being deleted ).
            if ( SDL_General::Do_two_objects_overlap(BonusObjectList[i]->GetRect(), MyAirPlane.GetRect()) )
            {
                //update score
                switch (BonusObjectList[i]->GetType())
                {
                    case 1:
                        Score.IncreaseValue(GET_BONUS_SCORE);
                    break;
                    case 2:
                        Score.IncreaseValue(GET_BONUS_STAR_SCORE);
                        MyAirPlane.IncreaseLives(LIVES_PLUS_FOR_GET_STAR);
                    break;
                }
                Mix_PlayChannel(-1,g_success_get_item,0);
                delete BonusObjectList[i];
                BonusObjectList.erase(BonusObjectList.begin()+i);
            }
            else
            {
                BonusObjectList[i]->HandleCount();
                //BonusObjectList[i]->Show(g_renderer);
            }

        } else {
            delete BonusObjectList[i];
            BonusObjectList.erase(BonusObjectList.begin()+i);
        }
    }
}
void ShowBossListThreatsListBonusListBossDeathThreatsDeath( vector<BossObject*> BossList,vector<ThreatObject*> ThreatsList,
                                                           vector<BonusObject*> BonusObjectList,vector<BossDeath*> BossDeathList,
                                                           vector<EnemyDeath*> EnemyDeathList)
{
    ShowBossList(BossList);
    ShowThreatsList(ThreatsList);
    for (int i=0;i<BonusObjectList.size();i++)
    {
        if( BonusObjectList[i]->GetIsShown() ){
                BonusObjectList[i]->Show(g_renderer);
        }
    }
    for (int i=0;i<BossDeathList.size();i++)
    {
        if(BossDeathList[i]->GetIsShown()) {
            BossDeathList[i]->ShowAnimation(g_renderer);
        }
    }
        for (int i=0;i<EnemyDeathList.size();i++)
    {
        if(EnemyDeathList[i]->GetIsShown()) {
            EnemyDeathList[i]->ShowAnimation(g_renderer);
        }
    }

}
;



#endif // MAINFUNCTION_H_
