#include "Game.h"
#include "PauseMenu.h"
#include "Mainmenu.h"
#include "ScoreBoard.h"
#include <time.h>
static float VIEW_HEIGHT = 512.0f;

int main()
{
    //Variable
    RenderWindow window(VideoMode(1920,1080), "Slime Advanture",Style::Fullscreen | Style::Close);
    View view(Vector2f(0.0f, 0.0f), Vector2f(1920,1080));

    bool Focus = true, PauseGame = true, MenuGame = true, playMainSound = false, playGameSound = false;
    float deltatime = 0.0f;
    
    SoundBuffer mainBuffer, gameBuffer;
    //mainBuffer.loadFromFile("Sound/Mainmenu.wav");
    //gameBuffer.loadFromFile("Sound/PlayGame.wav");

    Sound mainSound, gameSound;
    //mainSound.setBuffer(mainBuffer);
    //mainSound.setVolume(10);
    //gameSound.setBuffer(gameBuffer);
    //gameSound.setVolume(10);

    Clock clock;
    Game game(&window,view);
    ScoreBoard scoreboard;
    PauseMenu pausemenu(&window, view);
    Mainmenu mainmenu(&window, view);


    game.ResizeView(window, view, VIEW_HEIGHT);
    Vector2f PlayerPosBeforePause;
    srand(time(NULL));

    Image icon;
    icon.loadFromFile("Texture/Icon/Icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    while (window.isOpen()) {
        deltatime = clock.restart().asSeconds();
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
            ///if (event.type == Event::GainedFocus) Focus = true;
            //if (event.type == Event::LostFocus) Focus = false;
        }

        //if (Focus == true) {

            if (MenuGame == true && PauseGame == true) {
                if (!playMainSound) { mainSound.play(); mainSound.setLoop(true); playMainSound = true; }
                #pragma region Other
                window.setMouseCursorVisible(true);
                game.ResetGame();       game.resetPause();
                pausemenu.resetPlay();  pausemenu.resetHome();
                scoreboard.settoMenu(); game.resetHome();

                window.clear();
                mainmenu.Update(window, event, deltatime);

                #pragma endregion
                if (mainmenu.getPlay() == 1) {
                    game.getPlayerName(mainmenu.getName());
                    MenuGame = false;
                    PauseGame = false;
                }
                else if (mainmenu.getScore() == 1) {
                    scoreboard.Update(window, event);
                    scoreboard.Draw(window);
                    if (scoreboard.istoMenu() == 1) mainmenu.setScore();
                }
                else mainmenu.Draw(window);
            }

            if (PauseGame == false && MenuGame == false) {
                mainSound.pause(); playMainSound = false;
                if (!playGameSound) { gameSound.play(); gameSound.setLoop(true); playGameSound = true; }
                if (game.getHp() <= 0) { gameSound.stop(); playGameSound = false; }
                #pragma region Other
                window.clear();
                mainmenu.resetPlay(); pausemenu.resetPlay(); game.Update(deltatime); game.Draw(window);
                #pragma endregion
                if (game.getPause() == 1) {
                    PlayerPosBeforePause = game.getPlayerPosition();
                    pausemenu.getScore(game.getScore());
                    pausemenu.getPlayerName(game.getName());
                    cout << game.getScore() << " " << mainmenu.getName() << endl;
                    PauseGame = true;
                    MenuGame = false;
                }
                if (game.getHome() == 1) {
                    MenuGame = true;  PauseGame = true;
                }
            }
            if (PauseGame == true && MenuGame == false) {
                gameSound.stop(); playGameSound = false;
                #pragma region Other
                window.setMouseCursorVisible(true);
                window.clear();
                game.resetPause();
                pausemenu.Update(window, PlayerPosBeforePause);
                pausemenu.Draw(window);
                #pragma endregion
                if (pausemenu.getPlay() == 1) {
                    MenuGame = false;  PauseGame = false;
                }
                if (pausemenu.getHome() == 1) {
                    MenuGame = true;  PauseGame = true;
                }
            }
        //}
    }
    return 0;
}