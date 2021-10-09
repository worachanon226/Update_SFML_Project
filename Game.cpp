#include "Game.h"

Background background;

Game::Game(RenderWindow* window, View& view){
	this->window = window;
	this->view = view;
	this->window->setFramerateLimit(60);
	this->IsPause = 0;

#pragma region UI
	this->pause_buttontex.loadFromFile("Texture/Box/Pause.png");
	this->pause_button.setTexture(pause_buttontex);
	this->pause_button.setOrigin(Vector2f(pause_buttontex.getSize().x / 2, pause_buttontex.getSize().y / 2));
	this->pause_button.setScale(1.f, 1.f);

	this->playerNameBackTex.loadFromFile("Texture/Box/Button.png");
	this->playerNameBack.setTexture(playerNameBackTex);
	this->playerNameBack.setOrigin(playerNameBackTex.getSize().x / 2.0f, playerNameBackTex.getSize().y / 2.0f);
	this->playerNameBack.setScale(2.2f, 1.5f);
#pragma endregion

#pragma region Init Texture
	//Init textures
	this->playerTexture.loadFromFile("Texture/Character/Red_slime.png");
	this->bulletTexture.loadFromFile("Texture/Bullet/Single_Bullet.png");
	this->enemyTexture.loadFromFile("Texture/Enemy/Enemy_Random.png");
	this->CureBoxTexture.loadFromFile("Texture/Box/Cure_Box.png");
	this->BulletBoxTexture.loadFromFile("Texture/Box/Bullet_Box.png");
	this->ScoreBoxTexture.loadFromFile("Texture/Box/Score_Box.png");

	this->hpBarBackTex.loadFromFile("Texture/Box/HPBarBack.png");
	this->hpBarTex.loadFromFile("Texture/Box/HPBar.png");

	this->hpBarBackEnemyTex.loadFromFile("Texture/Box/HPBarBack.png");
	this->hpBarEnemyTex.loadFromFile("Texture/Box/HPBar.png");

	this->font_Pixeboy.loadFromFile("Font/Pixeboy-z8XGD.ttf");
#pragma endregion

#pragma region Init Score
	//Init Score
	this->Score = 0;
	this->scorebackTex.loadFromFile("Texture/Box/score_back.png");
	this->scoreback.setTexture(scorebackTex);
	this->scoreback.setOrigin(scorebackTex.getSize().x / 2.0f, scorebackTex.getSize().y / 2.0f);
	this->scoreback.setScale(0.4f, 0.4f);
#pragma endregion

#pragma region Character
	//Init player
	this->players.push_back(Player(&playerTexture, &bulletTexture, Vector2u(4, 4), 0.2f, Vector2f(250.0f, 275.0f), 10, 10, 1, 1, 25));

	//Init Enemy
	this->MaxTimeSpawnEnemy = 4.5f;
	this->NowTimeSpawnEnemy = 0;
#pragma endregion

#pragma region HPBar
	//Init HP_Bar
	this->hpBarBack.setSize(Vector2f(256.f, 64.f));
	this->hpBarBack.setOrigin(128.0f, 32.0f);
	this->hpBarBack.setScale(0.125f, 0.125f);
	this->hpBarBack.setTexture(&hpBarBackTex);

	this->hpBar.setTexture(&hpBarTex);
	this->hpBar.setFillColor(Color::Green);
	this->hpBar.setOrigin(hpBarBack.getOrigin());
	this->hpBar.setScale(0.125f, 0.125f);

	this->hpBarBackEnemy.setSize(Vector2f(256.f, 64.f));
	this->hpBarBackEnemy.setOrigin(128.0f, 32.0f);
	this->hpBarBackEnemy.setScale(0.125f, 0.125f);
	this->hpBarBackEnemy.setTexture(&hpBarBackTex);

	this->hpBarEnemy.setTexture(&hpBarTex);
	this->hpBarEnemy.setFillColor(Color::Red);
	this->hpBarEnemy.setOrigin(hpBarBack.getOrigin());
	this->hpBarEnemy.setScale(0.125f, 0.125f);
#pragma endregion

#pragma region Init Font
	//Init Font
	score_text.setString("Score: " + to_string(Score));
	score_text.setFont(font_Pixeboy);
	score_text.setFillColor(Color::Black);
	score_text.setCharacterSize(1000);
	score_text.setScale(0.03f, 0.03f);

	playerNameText.setFont(font_Pixeboy);
	playerNameText.setFillColor(Color::Black);
	playerNameText.setCharacterSize(1000);
	playerNameText.setScale(0.03f, 0.03f);
#pragma endregion

#pragma region InitBox
	//Init Box
	this->showing = 0;
	this->UsingBulletBox = 0;
	this->StopUseBullet = 0;
	this->StopUseScore = 0;
	this->UsingTimeBox = 0;

	this->UsingTimeMaxBox = 2.0f;
	this->BulletBoxShowing = 0;
	this->CureBoxShowing = 0;
	this->ScoreBoxShowing = 0;

	this->DelaytimeSpawn = 0.0f;
	this->DelaytimeSpawnMax = 5.0f;
	this->DelaytimeDel = 0.0f;
	this->DelaytimeDelMax = 5.0f;

	this->CureBox.setTexture(&CureBoxTexture);
	this->CureBox.setSize(Vector2f(256.0f, 256.0f));
	this->CureBox.setOrigin(128.0f, 128.0f);
	this->CureBox.setScale(0.1f,0.1f);

	this->BulletBox.setTexture(&BulletBoxTexture);
	this->BulletBox.setSize(this->CureBox.getSize());
	this->BulletBox.setOrigin(this->CureBox.getOrigin());
	this->BulletBox.setScale(this->CureBox.getScale());

	this->ScoreBox.setTexture(&ScoreBoxTexture);
	this->ScoreBox.setSize(this->CureBox.getSize());
	this->ScoreBox.setOrigin(this->CureBox.getOrigin());
	this->ScoreBox.setScale(this->CureBox.getScale());
#pragma endregion

#pragma region	InitMouse
	this->mouseCursorTex.loadFromFile("Texture/Mouse/Cursor.png");
	this->mouseCursor.setTexture(mouseCursorTex);
	this->mouseCursor.setOrigin(Vector2f(mouseCursorTex.getSize().x / 2, mouseCursorTex.getSize().y / 2));
	this->mouseCursor.setScale(1.00f, 1.00f);
	this->mouseCursor.setColor(Color::White);
#pragma endregion

//GameOver
	this->gameoverTex.loadFromFile("Texture/Wallpaper/GameOver.png");
	this->gameover.setTexture(gameoverTex);
	this->gameover.setOrigin(gameoverTex.getSize().x / 2, gameoverTex.getSize().y / 2);

	this->home_buttontex.loadFromFile("Texture/Box/Home.png");
	this->home_button.setTexture(home_buttontex);
	this->home_button.setOrigin(Vector2f(home_buttontex.getSize().x / 2, home_buttontex.getSize().y / 2));
	this->home_button.setScale(0.35f, 0.35f);
}

Game::~Game()
{
}
void Game::CombatUpdate()
{

}

void Game::InitUI()
{
}

void Game::UpdateUI(int i,int j)
{
	//Enemy
	if (j == 0) {
		this->hp = enemies[i].getHp();

		this->Maxhp = enemies[i].getMaxhp(); this->hp = enemies[i].getHp();

		this->hpBarBackEnemy.setPosition(enemies[i].getPosition().x, enemies[i].getPosition().y - (enemies[i].getLocalBounds().height * enemies[i].getScale()));

		this->hpBarEnemy.setPosition(this->hpBarBackEnemy.getPosition());
		this->hpBarEnemy.setSize(Vector2f((hp * 256.0f) / Maxhp, this->hpBarBackEnemy.getSize().y));

	}

	//Player && UI
	if (j == 1) {

		this->PlayerPosition = players[i].getPosition();

		this->Maxhp = players[i].gethpMax(); this->hp = players[i].gethp();

		this->hpBarBack.setPosition(players[i].getPosition().x, players[i].getPosition().y - 30.0f);
		
		this->hpBar.setPosition(this->hpBarBack.getPosition());
		if (hp <= 0) hp = 0;
		this->hpBar.setSize(Vector2f((hp * 256.0f) / Maxhp, this->hpBarBack.getSize().y));

		this->gameover.setPosition(PlayerPosition);
		this->home_button.setPosition(PlayerPosition.x, PlayerPosition.y + 120.0f);

		this->pause_button.setPosition(players[i].getPosition().x + 400 , players[i].getPosition().y - 218.0f);

		scoreback.setPosition(players[i].getPosition().x, players[i].getPosition().y - 215.0f);

		score_text.setOrigin(score_text.getLocalBounds().width / 2, score_text.getLocalBounds().height / 2);
		score_text.setPosition(scoreback.getPosition().x, scoreback.getPosition().y - 15.0f);

		this->playerNameText.setString("Name: " + playerName);
		this->playerNameBack.setPosition(players[i].getPosition().x, players[i].getPosition().y + 215.0f);
		this->playerNameText.setOrigin(playerNameText.getLocalBounds().width / 2, playerNameText.getLocalBounds().height / 2);
		this->playerNameText.setPosition(playerNameBack.getPosition().x, playerNameBack.getPosition().y - 14.0f);

		
	}
}

void Game::ButtonUI(RenderWindow& window)
{
	// get the current mouse position in the window
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

	// convert it to world coordinates
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

	this->mouseCursor.setPosition(worldPos.x, worldPos.y);

	if (isAlive == 1) {
		if (pause_button.getGlobalBounds().contains(worldPos.x, worldPos.y))
		{
			this->pause_button.setScale(0.36f, 0.36f);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) IsPause = 1;

		}
		else {
			this->pause_button.setScale(0.35f, 0.35f);
		}
	}
	if (isAlive == 0) {
		if (home_button.getGlobalBounds().contains(worldPos.x, worldPos.y))
		{
			this->home_button.setScale(0.36f, 0.36f);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) IsHome = 1;

		}
		else {
			this->home_button.setScale(0.35f, 0.35f);
		}
	}
}

void Game::Update(float deltatime)
{
	//cout << view.getSize().x << " " << view.getSize().y << endl;

	if (isAlive == 1) {
		NowTimeSpawnEnemy += deltatime;
		MaxTimeSpawnEnemy -= deltatime * 0.05f;
		if (MaxTimeSpawnEnemy < 0.3f) MaxTimeSpawnEnemy = 0.3f;
		if (NowTimeSpawnEnemy >= MaxTimeSpawnEnemy) {

			int randtype = rand() % 2 + 1;
			int redd = rand() % 155 + 100;
			int greenn = rand() % 155 + 100;
			int bluee = rand() % 155 + 100;
			if (randtype == 1) this->enemies.push_back(Enemy(&enemyTexture, Vector2f(-200.0f, 335.0f), Vector2f(0.0f, 0.0f), 1, 0.175f, Vector2u(4, 1), 0.2f, 1, 1, 1, Color(redd, greenn, bluee)));
			if (randtype == 2) this->enemies.push_back(Enemy(&enemyTexture, Vector2f(655.0f, 360.0f), Vector2f(0.0f, 0.0f), 2, 0.175f, Vector2u(4, 1), 0.2f, 1, 1, 1, Color(redd, greenn, bluee)));
			NowTimeSpawnEnemy -= MaxTimeSpawnEnemy;
		}

		if (UsingBulletBox == 1) {
			DelaytimeDel = 0.0f;
			DelaytimeSpawn = 0.0f;

			UsingTimeBox += deltatime;
			if (UsingTimeBox >= UsingTimeMaxBox) {
				StopUseBullet = 1;
				UsingBulletBox = 0;
				UsingTimeBox -= UsingTimeMaxBox;
			}
		}

		if (UsingScoreBox == 1) {
			DelaytimeDel = 0.0f;
			DelaytimeSpawn = 0.0f;

			UsingTimeBox += deltatime;
			if (UsingTimeBox >= UsingTimeMaxBox) {
				StopUseScore = 1;
				UsingScoreBox = 0;
				UsingTimeBox -= UsingTimeMaxBox;
			}
		}

		if (!showing) {
			DelaytimeDel = 0.0f;
			DelaytimeSpawn += deltatime;
			if (DelaytimeSpawn >= DelaytimeSpawnMax) {

				this->Boxtype = rand() % 3 + 1; int randx = rand() % 584 - 53; int randy = rand() % 555 - 4;

				if (Boxtype == 1) {
					this->CureBox.setPosition(randx, randy);
					this->CureBoxShowing = 1;
					this->BulletBoxShowing = 0;
					this->ScoreBoxShowing = 0;
				}
				if (Boxtype == 2) {
					this->BulletBox.setPosition(randx, randy);
					this->CureBoxShowing = 0;
					this->BulletBoxShowing = 1;
					this->ScoreBoxShowing = 0;
				}
				if (Boxtype == 3) {
					this->ScoreBox.setPosition(randx, randy);
					this->CureBoxShowing = 0;
					this->BulletBoxShowing = 0;
					this->ScoreBoxShowing = 1;
				}
				showing = 1;
				DelaytimeSpawn -= DelaytimeSpawnMax;
			}
		}

		if (showing) {
			DelaytimeSpawn = 0.0f;
			DelaytimeDel += deltatime;
			if (DelaytimeDel >= DelaytimeDelMax) {
				showing = 0;
				CureBoxShowing = 0;
				BulletBoxShowing = 0;
				ScoreBoxShowing = 0;
				DelaytimeDel -= DelaytimeDelMax;
			}
		}

		//All Character
		for (size_t i = 0; i < this->players.size(); i++) {

			if (players[i].gethp() <= 0) {
				isAlive = 0;
			}

			//Player Update
			this->players[i].Update(this->window->getSize(), deltatime);
			if (StopUseBullet == 1) {
				cout << "Stop Bullet!\n";
				StopUseBullet = 0;
				this->players.push_back(Player(&playerTexture, &bulletTexture, Vector2u(4, 4), 0.2f, players[i].getPosition(), players[i].gethp(), 10, 1, 1, players[i].getShootTimerMax() * 2.5f));
				this->players.erase(this->players.begin() + i);
			}

			if (StopUseScore == 1) {
				StopUseScore = 0;
				cout << "Stop Score!\n";
				this->players.push_back(Player(&playerTexture, &bulletTexture, Vector2u(4, 4), 0.2f, players[i].getPosition(), players[i].gethp(), 10, 1, 1, players[i].getShootTimerMax()));
				this->players.erase(this->players.begin() + i);
			}

			//Check Cure Box
			if (this->players[i].getGlobalBounds().intersects(CureBox.getGlobalBounds()) && showing == 1 && CureBoxShowing == 1 && BulletBoxShowing == 0 && ScoreBoxShowing == 0) {
				cout << "Cure!" << endl;
				this->players.push_back(Player(&playerTexture, &bulletTexture, Vector2u(4, 4), 0.2f, players[i].getPosition(), players[i].gethpMax(), 10, 1, 1, players[i].getShootTimerMax()));
				this->players.erase(this->players.begin() + i);
				showing = 0;
				CureBoxShowing = 0;
				BulletBoxShowing = 0;
				ScoreBoxShowing = 0;
				break;
			}

			//Check Bullet Box
			if (this->players[i].getGlobalBounds().intersects(BulletBox.getGlobalBounds()) && showing == 1 && CureBoxShowing == 0 && BulletBoxShowing == 1 && ScoreBoxShowing == 0) {
				cout << "Bullet!!" << endl;
				this->players.push_back(Player(&playerTexture, &bulletTexture, Vector2u(4, 4), 0.2f, players[i].getPosition(), players[i].gethp(), 10, 1, 1, players[i].getShootTimerMax() / 2.5f));
				this->players.erase(this->players.begin() + i);
				showing = 0;
				UsingTimeBox = 0.0f;
				UsingBulletBox = 1;
				UsingScoreBox = 0;
				CureBoxShowing = 0;
				BulletBoxShowing = 0;
				ScoreBoxShowing = 0;
				break;
			}

			//Check Score Box
			if (this->players[i].getGlobalBounds().intersects(ScoreBox.getGlobalBounds()) && showing == 1 && CureBoxShowing == 0 && BulletBoxShowing == 0 && ScoreBoxShowing == 1) {
				cout << "Score!!!" << endl;
				this->players.push_back(Player(&playerTexture, &bulletTexture, Vector2u(4, 4), 0.2f, players[i].getPosition(), players[i].gethp(), 10, 2, 1, players[i].getShootTimerMax()));
				this->players.erase(this->players.begin() + i);
				showing = 0;
				UsingTimeBox = 0.0f;
				UsingScoreBox = 1;
				UsingBulletBox = 0;
				CureBoxShowing = 0;
				BulletBoxShowing = 0;
				ScoreBoxShowing = 0;
				break;
			}

			//Enemy Update
			for (int j = 0; j < this->enemies.size(); j++) {
				this->enemies[j].Update(players[i].getPosition(), deltatime);

				//Update Score
				if (enemies[j].getHp() <= 0) {
					Score += players[i].getScoremul() * enemies[j].getMaxhp();
					score_text.setString("Score: " + to_string(Score));
					this->Score = Score;

					this->enemies.erase(this->enemies.begin() + j);
					break;
				}

				if (players[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds())) {
					this->players.push_back(Player(&playerTexture, &bulletTexture, Vector2u(4, 4), 0.2f, players[i].getPosition(), players[i].gethp() - enemies[j].getDamage(), 10, 0, 1, players[i].getShootTimerMax()));
					this->players.erase(this->players.begin() + i);
					this->enemies.erase(this->enemies.begin() + j);
					break;
				}

				for (int l = 0; l < j; l++) {
					if (enemies[j].getGlobalBounds().intersects(enemies[l].getGlobalBounds()) && j != l) {

						this->enemies.push_back(Enemy(&enemyTexture, (enemies[j].getPosition() + enemies[l].getPosition()) / 2.0f,
							Vector2f(0.0f, 0.0f), 0, (enemies[j].getScale() + enemies[l].getScale()) * 0.75
							, Vector2u(4, 1), 0.2f, enemies[j].getHp() + enemies[l].getHp()
							, enemies[j].getMaxhp() + enemies[l].getMaxhp(), enemies[j].getDamage() + enemies[l].getDamage(),
							Color((enemies[l].getcolor().r + enemies[j].getcolor().r) / 2, (enemies[l].getcolor().g + enemies[j].getcolor().g) / 2, (enemies[l].getcolor().b + enemies[j].getcolor().b) / 2)));

						this->enemies.erase(this->enemies.begin() + j);
						this->enemies.erase(this->enemies.begin() + l);
						break;
					}
				}
			}

			//Bullets Update	
			for (size_t k = 0; k < this->players[i].getBullets().size(); k++)
			{
				this->players[i].getBullets()[k].Update();
				Vector2f BulletPos = this->players[i].getBullets()[k].getPosition();

				if (BulletPos.x > 600.0f || BulletPos.x < -150.0f || BulletPos.y < -30.0f || BulletPos.y > 560.0f) {
					this->players[i].getBullets().erase(this->players[i].getBullets().begin() + k);
					break;
				}

				for (size_t j = 0; j < this->enemies.size(); j++) {
					if (players[i].getBullets()[k].getGlobalBounds().intersects(enemies[j].getGlobalBounds())) {

						this->enemies.push_back(Enemy(&enemyTexture, enemies[j].getPosition(),
							Vector2f(0.0f, 0.0f), 0, enemies[j].getScale()
							, Vector2u(4, 1), 0.2f, enemies[j].getHp() - 1
							, enemies[j].getMaxhp(), enemies[j].getDamage(),
							enemies[j].getcolor()));

						this->enemies.erase(this->enemies.begin() + j);
						this->players[i].getBullets().erase(this->players[i].getBullets().begin() + k);
						break;
					}
				}
			}
		}
	}
}

void Game::DrawUI()
{
	
}


void Game::Draw(RenderWindow &window)
{	
	this->window->clear();
	background.Draw_map(*this->window);
	
	if (showing == 1 && Boxtype == 1) window.draw(CureBox);
	if (showing == 1 && Boxtype == 2) window.draw(BulletBox);
	if (showing == 1 && Boxtype == 3) window.draw(ScoreBox);

	//Enemy == 0
	for (size_t i = 0; i < this->enemies.size(); i++) {
		this->enemies[i].Draw(*this->window);
		UpdateUI(i, 0);

		this->window->draw(this->hpBarEnemy);
		this->window->draw(this->hpBarBackEnemy);
	}

	//Player == 1
	for (size_t i = 0; i < this->players.size(); i++) {

		view.setCenter(players[i].getPosition());
		this->players[i].Draw(*this->window);
		this->window->setView(view);

		UpdateUI(i, 1);

		this->window->draw(this->hpBar);
		this->window->draw(this->hpBarBack);
		this->window->draw(this->pause_button);
		this->window->draw(this->scoreback);
		this->window->draw(this->score_text);
		this->window->draw(this->playerNameBack);

		this->window->draw(this->playerNameText);

		if (isAlive == 1) this->window->draw(this->mouseCursor);
	}
	
	if (isAlive == 0) {
		this->window->draw(gameover);
		this->window->draw(home_button);
		window.setMouseCursorVisible(true);
	}

	else window.setMouseCursorVisible(false);

	if (isAlive == 0 && ch == 1) ScoreBoard().WriteFile(playerName, Score), ch = 0; 
	ButtonUI(window);
	this->window->display();
}

void Game::ResetGame()
{
	for (int i = 0; i < players.size(); i++)  players[i].getBullets().clear();
	players.clear(); enemies.clear();

	this->players.push_back(Player(&playerTexture, &bulletTexture, Vector2u(4, 4), 0.2f, 
		Vector2f(250.0f, 275.0f), 10, 10, 1, 1, 25));

	this->isAlive = 1;
	this->ch = 1;

	this->Score = 0;
	this->score_text.setString("Score: " + to_string(Score));
	this->showing = 0;
	this->Boxtype = 0;

	this->UsingBulletBox = 0;
	this->UsingScoreBox = 0;

	this->BulletBoxShowing = 0;
	this->CureBoxShowing = 0;
	this->ScoreBoxShowing = 0;

	this->UsingTimeBox = 0;
	this->DelaytimeSpawn = 0;
	this->DelaytimeDel = 0;

	this->MaxTimeSpawnEnemy = 4.5f;
}
