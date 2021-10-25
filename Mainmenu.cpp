#include "Mainmenu.h"
#include <iostream>
using namespace std;

Mainmenu::Mainmenu(RenderWindow* window, View& view)
{
	this->window = window;
	this->view = view;
	this->view.setCenter(640.0f, 360.0f);

	this->IsPlay = IsPlay;

	this->delayMax = 0.15f;
	this->delaynow = delayMax;

	//Init Font
	this->font_Pixeboy.loadFromFile("Font/Pixeboy-z8XGD.ttf");

#pragma region UI

	//Wallpaper
	this->wallpaperTex.loadFromFile("Texture/Wallpaper/Mainmenu.png");
	this->wallpaper.setTexture(wallpaperTex);
	this->wallpaper.setOrigin(Vector2f(wallpaperTex.getSize().x / 2, wallpaperTex.getSize().y / 2));
	this->wallpaper.setScale(1.f, 1.f);
	this->wallpaper.setPosition(640.0f, 360.0f);

	#pragma region Button

	//Mainmenu_Play
	this->Mainmenu_PlayTex.loadFromFile("Texture/Box/Mainmenu_Play.png");
	this->Mainmenu_Play.setTexture(Mainmenu_PlayTex);
	this->Mainmenu_Play.setOrigin(Vector2f(Mainmenu_PlayTex.getSize().x / 2, Mainmenu_PlayTex.getSize().y / 2));
	this->Mainmenu_Play.setPosition(640.0f, 300.0f);

	//Mainmenu_Score
	this->Mainmenu_LeaderTex.loadFromFile("Texture/Box/Mainmenu_Leader.png");
	this->Mainmenu_Leader.setTexture(Mainmenu_LeaderTex);
	this->Mainmenu_Leader.setOrigin(Vector2f(Mainmenu_LeaderTex.getSize().x / 2, Mainmenu_LeaderTex.getSize().y / 2));
	this->Mainmenu_Leader.setPosition(640.0f, 500.0f);

	//Mainmenu_Quit
	this->Mainmenu_QuitTex.loadFromFile("Texture/Box/Mainmenu_Quit.png");
	this->Mainmenu_Quit.setTexture(Mainmenu_QuitTex);
	this->Mainmenu_Quit.setOrigin(Vector2f(Mainmenu_QuitTex.getSize().x / 2, Mainmenu_QuitTex.getSize().y / 2));
	this->Mainmenu_Quit.setPosition(640.0f, 700.0f);
	#pragma endregion
	//Input Name
	this->InputNameTex.loadFromFile("Texture/Box/NameInput.png");
	this->InputName.setTexture(InputNameTex);
	this->InputName.setOrigin(Vector2f(InputNameTex.getSize().x / 2, InputNameTex.getSize().y / 2));
	this->InputName.setPosition(640.0f, 360.0f);

	//Play Button
	this->play_buttontex.loadFromFile("Texture/Box/Play.png");
	this->play_button.setTexture(play_buttontex);
	this->play_button.setOrigin(Vector2f(play_buttontex.getSize().x / 2, play_buttontex.getSize().y / 2));
	this->play_button.setPosition(InputName.getPosition().x, InputName.getPosition().y + 360.0f);

	//PlayerName
	this->PlayerName.setString("");
	this->PlayerName.setFont(font_Pixeboy);
	this->PlayerName.setFillColor(Color::Black);
	this->PlayerName.setCharacterSize(1000);
	this->PlayerName.setScale(0.14f, 0.14f);
	this->PlayerName.setPosition(InputName.getPosition().x, InputName.getPosition().y + 70.0f);

	//Close Name Button
	this->CloseInputNameButtonTex.loadFromFile("Texture/Box/Close_Button.png");
	this->CloseInputNameButton.setTexture(CloseInputNameButtonTex);
	this->CloseInputNameButton.setOrigin(Vector2f(CloseInputNameButtonTex.getSize().x / 2, CloseInputNameButtonTex.getSize().y / 2));
	this->CloseInputNameButton.setPosition(InputName.getPosition().x + 550.0f, InputName.getPosition().y - 270.0f);

#pragma region Text
	//Play
	this->Play_text.setString("Play");
	this->Play_text.setFont(font_Pixeboy);
	this->Play_text.setFillColor(Color::White);
	this->Play_text.setCharacterSize(1000);
	this->Play_text.setOrigin(Play_text.getLocalBounds().width / 2.0f, Play_text.getLocalBounds().height / 2.0f);
	this->Play_text.setPosition(Mainmenu_Play.getPosition().x + 30.0f, Mainmenu_Play.getPosition().y - 25.0f);

	//Leader
	this->Leader_text.setString("Score");
	this->Leader_text.setFont(font_Pixeboy);
	this->Leader_text.setFillColor(Color::White);
	this->Leader_text.setCharacterSize(1000);
	this->Leader_text.setOrigin(Leader_text.getLocalBounds().width / 2.0f, Leader_text.getLocalBounds().height / 2.0f);
	this->Leader_text.setPosition(Mainmenu_Leader.getPosition().x + 30.0f, Mainmenu_Leader.getPosition().y - 25.0f);

	//Quit
	this->Quit_text.setString("Quit");
	this->Quit_text.setFont(font_Pixeboy);
	this->Quit_text.setFillColor(Color::White);
	this->Quit_text.setCharacterSize(1000);
	this->Quit_text.setOrigin(Quit_text.getLocalBounds().width / 2.0f, Quit_text.getLocalBounds().height / 2.0f);
	this->Quit_text.setPosition(Mainmenu_Quit.getPosition().x + 30.0f, Mainmenu_Quit.getPosition().y - 25.0f);
#pragma endregion
#pragma endregion

}

Mainmenu::~Mainmenu()
{
}

void Mainmenu::Update(RenderWindow& window,Event event, float deltatime)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

	this->PlayerName.setOrigin(PlayerName.getLocalBounds().width / 2.0f, PlayerName.getLocalBounds().height / 2.0f);

	if (IsNameInput == 1) {
		
		delaynow += deltatime;
		if (delaynow >= delayMax) {
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode == 8 && Name.getSize() > 0) Name.erase(Name.getSize() - 1);
				else if (event.text.unicode < 128 && Name.getSize() < 8 && event.text.unicode != 8) Name += static_cast<char>(event.text.unicode);
				PlayerName.setString(Name);
				delaynow = 0;
			}
			else if(Name.getSize()<8){
				Name += "_";
				PlayerName.setString(Name);
				Name.erase(Name.getSize() - 1);
			}
		}

		if (play_button.getGlobalBounds().contains(worldPos.x, worldPos.y))
		{
			this->play_button.setScale(1.1f, 1.1f);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && PlayerName.getString()!='_') {
				IsPlay = 1;
			}
		}
		else {
			this->play_button.setScale(1.f,1.f);
		}

		if (CloseInputNameButton.getGlobalBounds().contains(worldPos.x, worldPos.y))
		{
			this->CloseInputNameButton.setScale(1.1f, 1.1f);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				IsNameInput = 0;
				Name.clear(); PlayerName.setString(Name);
			} 
		}
		else {
			this->CloseInputNameButton.setScale(1.f, 1.f);
		}
		
	}

	Vector2f scaleButtonMenu = Vector2f(3.5f, 3.5f);
	Vector2f scaleTextMenu = Vector2f(0.05f, 0.05f);

	if (IsNameInput == 0) {
		if (Mainmenu_Play.getGlobalBounds().contains(worldPos.x, worldPos.y))
		{
			this->Mainmenu_Play.setScale(scaleButtonMenu * 1.1f);
			this->Play_text.setScale(scaleTextMenu * 1.1f);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) IsNameInput = 1;
		}
		else {
			this->Mainmenu_Play.setScale(scaleButtonMenu);
			this->Play_text.setScale(scaleTextMenu);
		}

		if (Mainmenu_Leader.getGlobalBounds().contains(worldPos.x, worldPos.y))
		{
			this->Mainmenu_Leader.setScale(scaleButtonMenu * 1.1f);
			this->Leader_text.setScale(scaleTextMenu * 1.1f);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) IsScore = 1;
		}
		else {
			this->Mainmenu_Leader.setScale(scaleButtonMenu);
			this->Leader_text.setScale(scaleTextMenu);
		}

		if (Mainmenu_Quit.getGlobalBounds().contains(worldPos.x, worldPos.y))
		{
			this->Mainmenu_Quit.setScale(scaleButtonMenu * 1.1f);
			this->Quit_text.setScale(scaleTextMenu * 1.1f);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) window.close();
		}
		else {
			this->Mainmenu_Quit.setScale(scaleButtonMenu);
			this->Quit_text.setScale(scaleTextMenu);
		}
	}
}

void Mainmenu::Draw(RenderWindow& window)
{
	window.clear(Color(150,150,150));
	window.setView(view);

	this->window->draw(wallpaper);

	//Text Block
	this->window->draw(Mainmenu_Play);
	this->window->draw(Mainmenu_Leader);
	this->window->draw(Mainmenu_Quit);
	this->window->draw(mainmenu_text);


	//Text
	this->window->draw(Play_text);
	this->window->draw(Leader_text);
	this->window->draw(Quit_text);

	if (IsNameInput == 1) {
		this->window->draw(InputName);
		this->window->draw(InputName_text);
		this->window->draw(PlayerName);
		this->window->draw(OnlyEight);
		this->window->draw(play_button);
		this->window->draw(CloseInputNameButton);
	}
	this->window->display();
}
