#include "Game.h"

Background background;

Game::Game(RenderWindow* window, View& view) {
	this->window = window;
	this->view = view;
	this->window->setFramerateLimit(60);
	this->IsPause = 0;

	this->skill_1TimeNow = 11.f;
	this->skill_2TimeNow = 16.f;
	this->skill_3TimeNow = 61.f;

	this->usingSkill_1 = false;
	this->usingSkill_2 = false;
	this->usingSkill_3 = false;

	this->pressSkill_1 = false;
	this->pressSkill_2 = false;
	this->pressSkill_3 = false;

	this->isBlackchole = false;

#pragma region UI
	this->pause_buttontex.loadFromFile("Texture/Box/Pause.png");
	this->pause_button.setTexture(pause_buttontex);
	this->pause_button.setOrigin(Vector2f(pause_buttontex.getSize().x / 2, pause_buttontex.getSize().y / 2));
	this->pause_button.setScale(1.f, 1.f);

	this->playerNameBackTex.loadFromFile("Texture/Box/Button.png");
	this->playerNameBack.setTexture(playerNameBackTex);
	this->playerNameBack.setOrigin(playerNameBackTex.getSize().x / 2.0f, playerNameBackTex.getSize().y / 2.0f);
	this->playerNameBack.setScale(2.2f, 1.5f);

	this->skillBoxTex.loadFromFile("Texture/Box/Skill_Box.png");

	this->skillBox1.setTexture(skillBoxTex);
	this->skillBox1.setOrigin(skillBoxTex.getSize().x / 2.f, skillBoxTex.getSize().y / 2.f);
	this->skillBox1.setScale(0.35f, 0.35f);

	this->skillBox2.setTexture(skillBoxTex);
	this->skillBox2.setOrigin(skillBoxTex.getSize().x / 2.f, skillBoxTex.getSize().y / 2.f);
	this->skillBox2.setScale(0.35f, 0.35f);

	this->skillBox3.setTexture(skillBoxTex);
	this->skillBox3.setOrigin(skillBoxTex.getSize().x / 2.f, skillBoxTex.getSize().y / 2.f);
	this->skillBox3.setScale(0.35f, 0.35f);

	this->skill_1Tex.loadFromFile("Texture/Box/Skill_1.png");
	this->skill_1.setTexture(skill_1Tex);
	this->skill_1.setOrigin(skill_1Tex.getSize().x / 2.f, skill_1Tex.getSize().y / 2.f);
	this->skill_1.setScale(0.35f, 0.35f);

	this->skill_2Tex.loadFromFile("Texture/Box/Skill_2.png");
	this->skill_2.setTexture(skill_2Tex);
	this->skill_2.setOrigin(skill_2Tex.getSize().x / 2.f, skill_2Tex.getSize().y / 2.f);
	this->skill_2.setScale(0.35f, 0.35f);

	this->skill_3Tex.loadFromFile("Texture/Box/Skill_3.png");
	this->skill_3.setTexture(skill_3Tex);
	this->skill_3.setOrigin(skill_3Tex.getSize().x / 2.f, skill_3Tex.getSize().y / 2.f);
	this->skill_3.setScale(0.35f, 0.35f);

	this->blackhole.setTexture(skill_3Tex);
	this->blackhole.setOrigin(skill_3Tex.getSize().x / 2.f, skill_3Tex.getSize().y / 2.f);

	this->cd_skill_1_Text.setFont(font_Pixeboy);
	this->cd_skill_1_Text.setFillColor(Color::Black);
	this->cd_skill_1_Text.setCharacterSize(1000);
	this->cd_skill_1_Text.setScale(0.035f, 0.035f);

	this->skill_q.setString("Q");
	this->skill_q.setFont(font_Pixeboy);
	this->skill_q.setFillColor(Color::Black);
	this->skill_q.setCharacterSize(1000);
	this->skill_q.setScale(0.035f, 0.035f);

	this->cd_skill_2_Text.setFont(font_Pixeboy);
	this->cd_skill_2_Text.setFillColor(Color::Black);
	this->cd_skill_2_Text.setCharacterSize(1000);
	this->cd_skill_2_Text.setScale(0.035f, 0.035f);

	this->skill_e.setString("E");
	this->skill_e.setFont(font_Pixeboy);
	this->skill_e.setFillColor(Color::Black);
	this->skill_e.setCharacterSize(1000);
	this->skill_e.setScale(0.035f, 0.035f);

	this->cd_skill_3_Text.setFont(font_Pixeboy);
	this->cd_skill_3_Text.setFillColor(Color::Black);
	this->cd_skill_3_Text.setCharacterSize(1000);
	this->cd_skill_3_Text.setScale(0.035f, 0.035f);

	this->skill_r.setString("R");
	this->skill_r.setFont(font_Pixeboy);
	this->skill_r.setFillColor(Color::Black);
	this->skill_r.setCharacterSize(1000);
	this->skill_r.setScale(0.035f, 0.035f);

	this->localTime.setFont(font_Pixeboy);
	this->localTime.setFillColor(Color::Black);
	this->localTime.setCharacterSize(1000);
	this->localTime.setScale(0.025f, 0.025f);

	this->Lock1_Text.setFont(font_Pixeboy);
	this->Lock1_Text.setFillColor(Color::Black);
	this->Lock1_Text.setCharacterSize(1000);
	this->Lock1_Text.setScale(0.015f, 0.015f);

	this->Lock2_Text.setFont(font_Pixeboy);
	this->Lock2_Text.setFillColor(Color::Black);
	this->Lock2_Text.setCharacterSize(1000);
	this->Lock2_Text.setScale(0.015f, 0.015f);

	this->Lock3_Text.setFont(font_Pixeboy);
	this->Lock3_Text.setFillColor(Color::Black);
	this->Lock3_Text.setCharacterSize(1000);
	this->Lock3_Text.setScale(0.015f, 0.015f);

	//Lock
	this->Lock_Tex.loadFromFile("Texture/Box/Lock.png");
	this->Lock1.setTexture(Lock_Tex);
	this->Lock1.setOrigin(Lock_Tex.getSize().x / 2.f, Lock_Tex.getSize().y / 2.f);
	this->Lock1.setScale(0.25f, 0.25f);

	this->Lock2.setTexture(Lock_Tex);
	this->Lock2.setOrigin(Lock_Tex.getSize().x / 2.f, Lock_Tex.getSize().y / 2.f);
	this->Lock2.setScale(0.25f, 0.25f);

	this->Lock3.setTexture(Lock_Tex);
	this->Lock3.setOrigin(Lock_Tex.getSize().x / 2.f, Lock_Tex.getSize().y / 2.f);
	this->Lock3.setScale(0.25f, 0.25f);

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
	this->CureBox.setScale(0.1f, 0.1f);

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

void Game::UpdateUI(int i, int j)
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

		this->pause_button.setPosition(players[i].getPosition().x + 400, players[i].getPosition().y - 218.0f);

		scoreback.setPosition(players[i].getPosition().x, players[i].getPosition().y - 215.0f);

		score_text.setOrigin(score_text.getLocalBounds().width / 2, score_text.getLocalBounds().height / 2);
		score_text.setPosition(scoreback.getPosition().x, scoreback.getPosition().y - 15.0f);

		this->playerNameText.setString("Name: " + playerName);
		this->playerNameBack.setPosition(players[i].getPosition().x, players[i].getPosition().y + 215.0f);
		this->playerNameText.setOrigin(playerNameText.getLocalBounds().width / 2, playerNameText.getLocalBounds().height / 2);
		this->playerNameText.setPosition(playerNameBack.getPosition().x, playerNameBack.getPosition().y - 14.0f);

		this->skillBox1.setPosition(players[i].getPosition().x - 400.0f, players[i].getPosition().y + 215.0f);
		this->skill_1.setPosition(skillBox1.getPosition());

		this->skillBox2.setPosition(players[i].getPosition().x - 325.0f, players[i].getPosition().y + 215.0f);
		this->skill_2.setPosition(skillBox2.getPosition());

		this->skillBox3.setPosition(players[i].getPosition().x - 250.0f, players[i].getPosition().y + 215.0f);
		this->skill_3.setPosition(skillBox3.getPosition());

		this->cd_skill_1_Text.setString(to_string(int(skill_1TimeNow)));
		this->cd_skill_1_Text.setOrigin(cd_skill_1_Text.getLocalBounds().width / 2.f, cd_skill_1_Text.getLocalBounds().height / 2.f);
		this->cd_skill_1_Text.setPosition(players[i].getPosition().x - 400.0f, players[i].getPosition().y + 200.0f);

		this->skill_q.setOrigin(skill_q.getLocalBounds().width / 2.f, skill_q.getLocalBounds().height / 2.f);
		this->skill_q.setPosition(players[i].getPosition().x - 400.0f, players[i].getPosition().y + 150.0f);

		this->cd_skill_2_Text.setString(to_string(int(skill_2TimeNow)));
		this->cd_skill_2_Text.setOrigin(cd_skill_2_Text.getLocalBounds().width / 2.f, cd_skill_2_Text.getLocalBounds().height / 2.f);
		this->cd_skill_2_Text.setPosition(players[i].getPosition().x - 325.0f, players[i].getPosition().y + 200.0f);

		this->skill_e.setOrigin(skill_q.getLocalBounds().width / 2.f, skill_q.getLocalBounds().height / 2.f);
		this->skill_e.setPosition(players[i].getPosition().x - 325.0f, players[i].getPosition().y + 150.0f);

		this->cd_skill_3_Text.setString(to_string(int(skill_3TimeNow)));
		this->cd_skill_3_Text.setOrigin(cd_skill_3_Text.getLocalBounds().width / 2.f, cd_skill_3_Text.getLocalBounds().height / 2.f);
		this->cd_skill_3_Text.setPosition(players[i].getPosition().x - 250.0f, players[i].getPosition().y + 200.0f);

		this->skill_r.setOrigin(skill_q.getLocalBounds().width / 2.f, skill_q.getLocalBounds().height / 2.f);
		this->skill_r.setPosition(players[i].getPosition().x - 250.0f, players[i].getPosition().y + 150.0f);

		this->Lock1.setPosition(players[i].getPosition().x - 400.0f, players[i].getPosition().y + 215.0f);
		this->Lock2.setPosition(players[i].getPosition().x - 325.0f, players[i].getPosition().y + 215.0f);
		this->Lock3.setPosition(players[i].getPosition().x - 250.0f, players[i].getPosition().y + 215.0f);

		Lock1_Text.setString("5");
		Lock1_Text.setOrigin(Lock1_Text.getLocalBounds().width / 2.f, Lock1_Text.getLocalBounds().height / 2.f);
		Lock1_Text.setPosition(players[i].getPosition().x - 400.0f, players[i].getPosition().y + 215.0f);

		Lock2_Text.setString("20");
		Lock2_Text.setOrigin(Lock2_Text.getLocalBounds().width / 2.f, Lock2_Text.getLocalBounds().height / 2.f);
		Lock2_Text.setPosition(players[i].getPosition().x - 325.0f, players[i].getPosition().y + 215.0f);

		Lock3_Text.setString("50");
		Lock3_Text.setOrigin(Lock3_Text.getLocalBounds().width / 2.f, Lock3_Text.getLocalBounds().height / 2.f);
		Lock3_Text.setPosition(players[i].getPosition().x - 250.0f, players[i].getPosition().y + 215.0f);

		time_t rawtime;
		struct tm* timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		this->localTime.setString(asctime(timeinfo));
		this->localTime.setOrigin(localTime.getLocalBounds().width / 2.f, localTime.getLocalBounds().height / 2.f);
		this->localTime.setPosition(players[i].getPosition().x + 325.0f, players[i].getPosition().y + 230.0f);
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

		if (Score < 5) this->skill_1.setColor(Color(255, 255, 255, 50));
		else this->skill_1.setColor(Color(255, 255, 255, 225));

		if (Score < 20) this->skill_2.setColor(Color(255, 255, 255, 50));
		else this->skill_2.setColor(Color(255, 255, 255, 225));

		if (Score < 50) this->skill_3.setColor(Color(255, 255, 255, 50));
		else this->skill_3.setColor(Color(255, 255, 255, 225));

		if (Keyboard::isKeyPressed(Keyboard::Q) && !pressSkill_1 && Score >= 5) pressSkill_1 = true;
		if (pressSkill_1) {
			this->skill_1.setColor(Color(255, 255, 255, 50));
			skill_1TimeNow -= deltatime;

			if (skill_1TimeNow <= 5) usingSkill_1 = false;
			else usingSkill_1 = true;

			if (skill_1TimeNow <= 0) {
				skill_1TimeNow = 16.f;
				this->skill_1.setColor(Color(255, 255, 255, 225));
				pressSkill_1 = false;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::E) && !pressSkill_2 && Score >= 20) pressSkill_2 = true;
		if (pressSkill_2) {
			this->skill_2.setColor(Color(255, 255, 255, 50));
			skill_2TimeNow -= deltatime;

			if (skill_2TimeNow <= 13) usingSkill_2 = false;
			else usingSkill_2 = true;

			if (skill_2TimeNow <= 0) {
				skill_2TimeNow = 16.f;
				this->skill_2.setColor(Color(255, 255, 255, 225));
				pressSkill_2 = false;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::R) && !pressSkill_3 && Score >= 50) pressSkill_3 = true;
		if (pressSkill_3) {
			this->skill_3.setColor(Color(255, 255, 255, 50));
			skill_3TimeNow -= deltatime;

			if (skill_3TimeNow <= 60.9) usingSkill_3 = false;
			else usingSkill_3 = true;

			if (skill_3TimeNow <= 0) {
				skill_3TimeNow = 61.f;
				this->skill_3.setColor(Color(255, 255, 255, 225));
				pressSkill_3 = false;
			}
		}

		if (!usingSkill_2) NowTimeSpawnEnemy += deltatime;
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

		if (usingSkill_3) enemies.clear();

		//All Character
		Vector2f position_Player;
		for (size_t i = 0; i < this->players.size(); i++) {

			position_Player = players[i].getPosition();

			if (players[i].gethp() <= 0) isAlive = 0;
			if (usingSkill_1) players[i].SetColorOpa();
			else players[i].SetColor();

			if (usingSkill_3) {
				enemies.clear();
				this->players.push_back(Player(&playerTexture, &bulletTexture, Vector2u(4, 4), 0.2f, players[i].getPosition(), 10, 10, 1, 1, players[i].getShootTimerMax()));
				blackhole.setPosition(players[i].getPosition());
				this->players.erase(this->players.begin() + i);
				isBlackchole = true;
				usingSkill_3 = false;
			}

			if (isBlackchole) {
				blackhole.rotate(500.f * deltatime);
				blackhole.setScale(blackhole.getScale().x - (deltatime * 10.f), blackhole.getScale().y - (deltatime * 10.f));
				cout << blackhole.getScale().x - (deltatime * 10.f) << endl;
				if (blackhole.getScale().x - (deltatime * 10.f) <= -8) {
					isBlackchole = false;
					blackhole.setScale(1, 1);
				}
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

				if (!usingSkill_2) this->enemies[j].Update(players[i].getPosition(), deltatime);

				//Update Score
				if (enemies[j].getHp() <= 0) {
					Score += players[i].getScoremul() * enemies[j].getMaxhp();
					score_text.setString("Score: " + to_string(Score));
					this->Score = Score;

					this->enemies.erase(this->enemies.begin() + j);
					break;
				}

				if (players[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds()) && !usingSkill_1) {
					players[i].SetHp(enemies[j].getHp());
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

		if (!showing) {
			DelaytimeDel = 0.0f;
			DelaytimeSpawn += deltatime;
			if (DelaytimeSpawn >= DelaytimeSpawnMax) {

				this->Boxtype = rand() % 3 + 1;
				int quadrant_rand, randx, randy;
				if (position_Player.x < 240 && position_Player.y < 272.5f) quadrant_rand = rand() % 3 + 2;
				if (position_Player.x > 240 && position_Player.y < 272.5f) quadrant_rand = (rand() % 3 == 0) ? 1 : rand() % 2 + 3;
				if (position_Player.x > 240 && position_Player.y > 272.5f) quadrant_rand = (rand() % 3 == 0) ? 4 : rand() % 2 + 1;
				if (position_Player.x < 240 && position_Player.y > 272.5f) quadrant_rand = rand() % 3 + 1;

				randx = rand() % 290; randy = rand() % 272;
				if (quadrant_rand == 1) randx -= 50, randy;
				if (quadrant_rand == 2) randx += 240, randy;
				if (quadrant_rand == 3) randx += 240, randy += 272.5;
				if (quadrant_rand == 4) randx -= 50, randy += 272.5;

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
	}
}

void Game::DrawUI()
{

}


void Game::Draw(RenderWindow& window)
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

		this->window->draw(this->skillBox1);
		this->window->draw(this->skillBox2);
		this->window->draw(this->skillBox3);

		this->window->draw(this->skill_1);
		this->window->draw(this->skill_2);
		this->window->draw(this->skill_3);

		this->window->draw(this->skill_q);
		this->window->draw(this->skill_e);
		this->window->draw(this->skill_r);

		if (Score < 5) this->window->draw(this->Lock1);
		if (Score < 20) this->window->draw(this->Lock2);
		if (Score < 50) this->window->draw(this->Lock3);

		if (Score < 5) this->window->draw(this->Lock1_Text);
		if (Score < 20) this->window->draw(this->Lock2_Text);
		if (Score < 50) this->window->draw(this->Lock3_Text);

		//this->window->draw(localTime);

		if (isBlackchole) this->window->draw(this->blackhole);

		if (pressSkill_1) this->window->draw(this->cd_skill_1_Text);
		if (pressSkill_2) this->window->draw(this->cd_skill_2_Text);
		if (pressSkill_3) this->window->draw(this->cd_skill_3_Text);
	}

	if (isAlive == 0) {
		this->window->draw(gameover);
		this->window->draw(home_button);
	}

	if (isAlive == 0 && ch == 1) ScoreBoard().WriteFile(playerName, Score), ch = 0;
	ButtonUI(window);
	this->window->draw(this->mouseCursor);
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

	this->skill_1TimeNow = 11.f;
	this->skill_2TimeNow = 16.f;
	this->skill_3TimeNow = 61.f;

	this->usingSkill_1 = false;
	this->usingSkill_2 = false;
	this->usingSkill_3 = false;

	this->pressSkill_1 = false;
	this->pressSkill_2 = false;
	this->pressSkill_3 = false;

	this->skill_1.setColor(Color(255, 255, 255, 225));
	this->skill_2.setColor(Color(255, 255, 255, 225));
	this->skill_3.setColor(Color(255, 255, 255, 225));

	this->isBlackchole = false;
}
