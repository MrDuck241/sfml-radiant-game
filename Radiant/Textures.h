#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

typedef const float& DrawVariable;

const string FontPath{ "Hibo.otf" };

sf::Texture background_texture;
sf::Texture menu_background_texture;

sf::Texture weapon_texture;

sf::Texture ship_texture;
sf::Texture ship_left;
sf::Texture ship_right;

sf::Texture enemy_level_1_yellow_texture;
sf::Texture enemy_plasma_gun_level_1;
sf::Texture enemy_level_1_green_texture;
sf::Texture enemy_level_1_red_texture;

sf::Texture boss_1;

sf::Texture heart_texture;
sf::Texture rapid_fire_texture;
sf::Texture shield_texture;

sf::Texture zero_texture;
sf::Texture one_texture;
sf::Texture two_texture;
sf::Texture three_texture;
sf::Texture four_texture;
sf::Texture five_texture;
sf::Texture six_texture;
sf::Texture seven_texture;
sf::Texture eight_texture;
sf::Texture nine_texture;
sf::Texture lives_text;

sf::Texture won_info;

bool LoadTextures() {

	if (lives_text.loadFromFile("Images/Info_models/Lives.png") &&
		won_info.loadFromFile("Images/Info_models/won_info.png") &&

		zero_texture.loadFromFile("Images/Numbers/zero.png") &&
		one_texture.loadFromFile("Images/Numbers/one.png") &&
		two_texture.loadFromFile("Images/Numbers/two.png") &&
		three_texture.loadFromFile("Images/Numbers/three.png") &&
		four_texture.loadFromFile("Images/Numbers/four.png") &&
		five_texture.loadFromFile("Images/Numbers/five.png") &&
		six_texture.loadFromFile("Images/Numbers/six.png") &&
		seven_texture.loadFromFile("Images/Numbers/seven.png") &&
		eight_texture.loadFromFile("Images/Numbers/eight.png") &&
		nine_texture.loadFromFile("Images/Numbers/nine.png") &&

		enemy_level_1_red_texture.loadFromFile("Images/Enemy_models/Enemy_level_1_red.png") &&
		enemy_plasma_gun_level_1.loadFromFile("Images/Weapon_models/enemy_plasma_gun_level_1.png") &&
		enemy_level_1_green_texture.loadFromFile("Images/Enemy_models/Enemy_level_1_green.png") &&
		enemy_level_1_yellow_texture.loadFromFile("Images/Enemy_models/Enemy_level_1_yellow.png") &&
		boss_1.loadFromFile("Images/Enemy_models/boss_1.png") &&

		background_texture.loadFromFile("Images/Background/background_1.png") &&
		menu_background_texture.loadFromFile("Images/Background/MenuBackground.png") &&

		weapon_texture.loadFromFile("Images/Weapon_models/plasma_gun_level_1.png") &&

		ship_texture.loadFromFile("Images/Ship_models/Ship_1.png") &&
		ship_left.loadFromFile("Images/Ship_models/Ship_1_Left.png") &&
		ship_right.loadFromFile("Images/Ship_models/Ship_1_Right.png") &&
		
		heart_texture.loadFromFile("Images/Powerups_models/Heart.png") &&
		rapid_fire_texture.loadFromFile("Images/Powerups_models/Rapid.png") &&
		shield_texture.loadFromFile("Images/Powerups_models/Shield.png"))
		return true;

		else return false;

}

void NumTex(const std::string num, sf::Sprite& obj) {
	if (num == "0") obj.setTexture(zero_texture);
	if (num == "1") obj.setTexture(one_texture);
	if (num == "2") obj.setTexture(two_texture);
	if (num == "3") obj.setTexture(three_texture);
	if (num == "4") obj.setTexture(four_texture);
	if (num == "5") obj.setTexture(five_texture);
	if (num == "6") obj.setTexture(six_texture);
	if (num == "7") obj.setTexture(seven_texture);
	if (num == "8") obj.setTexture(eight_texture);
	if (num == "9") obj.setTexture(nine_texture);
}

//DrawVariable = const float&;

sf::RectangleShape* DrawRectangle(DrawVariable SIZE_X, DrawVariable SIZE_Y, DrawVariable POZ_X, DrawVariable POZ_Y) {
	sf::RectangleShape* Message = new sf::RectangleShape();

	Message->setSize(sf::Vector2f{SIZE_X, SIZE_Y});
	Message->setPosition(POZ_X, POZ_Y);
	Message->setFillColor(sf::Color::Blue);

	return Message;
}

sf::Text* DrawMessage(const std::string& TextValue, DrawVariable FontSize, DrawVariable POZ_X, DrawVariable POZ_Y) {
	sf::Font *MessageFont = new sf::Font;
	MessageFont->loadFromFile(FontPath);

	sf::Text *MessageText = new sf::Text;
	MessageText->setFont(*MessageFont);
	MessageText->setCharacterSize(FontSize);
	MessageText->setString(TextValue);
	MessageText->setPosition(POZ_X, POZ_Y);

	return MessageText;
}