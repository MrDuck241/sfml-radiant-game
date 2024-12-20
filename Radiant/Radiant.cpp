/*
	Gra zrobiona przez twórcę: Przemek K.
	Gra oparta na retro grze "Radiant"
	Ostatnia aktualizacja kodu: 19.02.2024
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <time.h>

#include "Textures.h" //File with all textures and texture loader
#include "Position_class.hpp" //File with objects positions class
#include "Declarations.hpp" //File with mostly variables definitions and main functions like Exit()

using namespace std;
using namespace sf;

void AddShoot() {
	Sound1.loadFromFile("Sounds/blaster_1.mp3");
	ShootSound.setBuffer(Sound1);
	while (TurnOFFThreads.load() != true) {
		if (Shoot == true) {
			if (Timer1 >= ShootTime) {
				BulletPosition* bullet_position = new BulletPosition(ship_position.x + 50, ship_position.y);
				ship_bullets_positions.push_back(*bullet_position);
				delete bullet_position;
				if(ShootSoundPlay == true) ShootSound.play();
				Timer1 = 0;
			}

			if (enemy_positions.size() > 0) {
				if (Timer4 >= 2500) {
					for (int i = 0; i < enemy_positions.size(); i++) {
						EnemyBulletPosition* Enemybullet_position = new EnemyBulletPosition(enemy_positions.at(i).x + 50, enemy_positions.at(i).y);
						enemy_bullet_positions.push_back(*Enemybullet_position);
						delete Enemybullet_position;
					}
					Timer4 = 0;
				}
			}

			if (enemy_bullet_positions.size() > 0) {
				for (int i = 0; i < enemy_bullet_positions.size(); i++) {
					enemy_bullet_positions.at(i).y += 30;
				}
			}

			if (ship_bullets_positions.size() > 0) {
				for (int i = 0; i < ship_bullets_positions.size(); i++) {
					ship_bullets_positions.at(i).y -= 30;
				}
			}

			if (ship_bullets_positions.size() > 0) {
				if (ship_bullets_positions.at(0).y <= 50) {
					ship_bullets_positions.erase(ship_bullets_positions.begin());
				}
			}

			SleepGame(100);
			Timer1 = Timer1 + 100;
			Timer4 = Timer4 + 100;
		}
		if (Shoot == false) {
			std::unique_lock<std::mutex> lock(ShootMutex);
			std::cout << "Shooting stopped" << std::endl;
			ShootCondition.wait(lock, [] { return Shoot; });
		}
		if (TurnOFFThreads == true) break;
	}
}

void AddEnemy() {
	if (AddEnemys == true) {
		
		Stage++;

		if (Stage == 1) EnemyCount = Stages::STAGE1;
		else if (Stage == 2) EnemyCount = Stages::STAGE2;
		else if (Stage == 3) EnemyCount = Stages::STAGE3;
		else if (EndlessGameStarted == true) {
			EnemyCount += 10;
		}

		for (int i = 0; i < EnemyCount; i++) {
			int x = rand() % 1860 + 20;
			int y = rand() % 100 + 20;

			EnemyPosition* EnemyPos = new EnemyPosition(x, y);
			EnemyPos->tex = rand() % 3;
			enemy_positions.push_back(*EnemyPos);
			delete EnemyPos;
		}
		AddEnemys = false;
	}
}

void UpdateEnemys() {
	while (TurnOFFThreads.load() != true) {
		srand(time(NULL));
		int Way;

		if (UpdateEnemy == true && enemy_positions.size() > 0) {
			for (int i = 0; i < enemy_positions.size(); i++) {
				Way = rand() % 4;
				if (Way == 0 && enemy_positions.at(i).x + 25 < (WINDOW_SIZE_X - 50)) enemy_positions.at(i).x += 25;
				else if (Way == 2 && enemy_positions.at(i).x - 25 > 0) enemy_positions.at(i).x -= 25;
				else if (Way == 3 && enemy_positions.at(i).y + 25 < 400) enemy_positions.at(i).y += 25;
				else if (Way == 1 && enemy_positions.at(i).y - 25 > 0) enemy_positions.at(i).y -= 25;
			}
		}

		SleepGame(100);
		if (TurnOFFThreads == true) break;
	}
}

void START();

int main() {

	std::srand(time(NULL));

	RenderWindow window{ VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Radiant" };
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(60);
	window.clear(Color::Black);

	if (!LoadTextures()) ResourcesError();

	MainMusic.openFromFile("Sounds/BackMusic1.mp3");

	GamerLives.store(3);

	Shoot = true;
	AddEnemys = true;
	UpdateEnemy = true;
	SpawnPowerups = true;

	Stage = 0;

	START();

	Sprite background(background_texture);
	Sprite ship(ship_texture);

	ship.setPosition(900, 850);

	ship_position.x = static_cast<int>(ship.getPosition().x);
	ship_position.y = static_cast<int>(ship.getPosition().y);

	Sprite num1(zero_texture);
	Sprite num2(zero_texture);
	Sprite num3(zero_texture);
	Sprite num4(zero_texture);

	num1.setPosition(WINDOW_SIZE_X - 4 * zero_texture.getSize().x, 0);
	num2.setPosition(WINDOW_SIZE_X - 3 * zero_texture.getSize().x, 0);
	num3.setPosition(WINDOW_SIZE_X - 2 * zero_texture.getSize().x, 0);
	num4.setPosition(WINDOW_SIZE_X - 1 * zero_texture.getSize().x, 0);

	Sprite MainMenu(menu_background_texture);
	Sprite HeartsNumber(three_texture);
	Sprite Info1(lives_text);

	Info1.setPosition(1, 1);
	HeartsNumber.setPosition(1, 1 + lives_text.getSize().y);













	vector<int> toDelete;

	bool adde = true;

	bool drawEnd = false;
	bool WaitEnd = false;
	bool Showstart = true;
	bool wait = true;


	while (window.isOpen()) {
		if(ShowMenu) {
			window.setMouseCursorVisible(true);
			window.pollEvent(event);
			window.draw(MainMenu);

			window.display();
			if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition().x >= 749 && Mouse::getPosition().x <= 1140 && Mouse::getPosition().y >= 228 && Mouse::getPosition().y <= 345){
				ShowMenu = false;
				PlotGameStarted = true;
			}
			else if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition().x >= 748 && Mouse::getPosition().x <= 1151 && Mouse::getPosition().y >= 504 && Mouse::getPosition().y <= 675) {
				EndlessGameStarted = true;
				ShowMenu = false;
			}
			else if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition().x >= 755 && Mouse::getPosition().x <= 1146 && Mouse::getPosition().y >= 755 && Mouse::getPosition().y <= 897) {

					Shoot = false;
					exit(0);
			}

			SleepGame(10);
		}
		if (PlotGameStarted == true || EndlessGameStarted == true) {
			if (EndlessGameStarted != true) {
				if (Showstart == true) {
					window.setMouseCursorVisible(false);
					std::string Info[2] = 
					{
						{"Rok 2160. \nZiemie zaatakowaly niezidetyfikowane latające statki siejac zniszczenie na orbicie ziemskiej.\n Szwadron elitarnych pilotow wraz z kapitanem Rexem zostali\nwyslani aby zniszczyc wrogie obiekty i ocalic Ziemie"},
						{"Komandorze Rex. \nTutaj kapitan siodmej floty NSC. \nTwoim zadaniem jest zniszczyc wrogie obikety w okolicach Ksiezyca \nBez odioru"}

					};
					for (int i = 0; i < 2; i++) {
						RectangleShape* wsk = DrawRectangle(1400, 300, 260, 400);
						Text* wsk2 = DrawMessage(Info[i], 24, 270, 410);
						window.draw(background);
						window.draw(ship);

						window.draw(*wsk);
						window.draw(*wsk2);
						window.display();

						// Oczekiwanie na wciśnięcie klawisza
						bool keyPressed = false;
						while (!keyPressed) {
							while (window.pollEvent(event)) {
								if (event.type == Event::KeyPressed) {
									if (event.key.code == Keyboard::E) {
										keyPressed = true;
									}
								}
								else if (event.type == Event::Closed) {
									TurnOFFThreads.store(true);  HardExit(); window.close();
								}
							}
						}
						if (i != 1) keyPressed == false;
					}
					Shoot = true;
					ShootSoundPlay = true;
					MainMusic.play();
					ShootCondition.notify_all();
					Showstart = false;
				}
			}
			else {
				window.setMouseCursorVisible(false); Shoot = true; ShootSoundPlay = true;
				MainMusic.play(); }

			if (show_left == true) Timer2++;
			if (show_right == true) Timer3++;
			if (show_left == false && show_right == false) ship.setTexture(ship_texture);

			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					TurnOFFThreads.store(true);  HardExit(); window.close();
				}
				else if (event.type == Event::KeyPressed) {
					switch (event.key.code) {
					case Keyboard::Left: {
						if (ship.getPosition().x > 6) ship.setPosition(ship.getPosition().x - 6, ship.getPosition().y);
						ship.setTexture(ship_left);
						if (show_left == false) {
							show_left = true;
							show_right = false;
							Timer2 = 0;
							Timer3 = 0;
						}
					}break;

					case Keyboard::Right: {
						if (ship.getPosition().x < 1825) ship.setPosition(ship.getPosition().x + 6, ship.getPosition().y);
						ship.setTexture(ship_right);
						if (show_right == false) {
							show_right = true;
							show_left = false;
							Timer3 = 0;
							Timer2 = 0;
						}

					}break;
					}
				}
			}

			ship_position.x = static_cast<int>(ship.getPosition().x);
			ship_position.y = static_cast<int>(ship.getPosition().y);

			window.draw(background);
			window.draw(ship);


			window.draw(num4);
			window.draw(num3);
			window.draw(num2);
			window.draw(num1);

			if (GamerPoints >= 1000) Spoints = to_string(GamerPoints);
			else if (GamerPoints >= 100 && GamerPoints < 1000) Spoints = "0" + to_string(GamerPoints);
			else if (GamerPoints >= 10 && GamerPoints < 100) Spoints = "00" + to_string(GamerPoints);
			else if (GamerPoints >= 0 && GamerPoints < 10) Spoints = "000" + to_string(GamerPoints);

			ScoreBoardParts[0] = Spoints[0];
			ScoreBoardParts[1] = Spoints[1];
			ScoreBoardParts[2] = Spoints[2];
			ScoreBoardParts[3] = Spoints[3];


			for (int i = 0; i < 4; i++) {
				if (i == 0) NumTex(ScoreBoardParts[i], num1);
				if (i == 1) NumTex(ScoreBoardParts[i], num2);
				if (i == 2) NumTex(ScoreBoardParts[i], num3);
				if (i == 3) NumTex(ScoreBoardParts[i], num4);

			}

			if (ship_bullets_positions.size() > 0) {
				for (int i = 0; i < ship_bullets_positions.size(); i++) {
					Sprite* shoot = new Sprite(weapon_texture);
					shoot->setPosition(ship_bullets_positions.at(i).x, ship_bullets_positions.at(i).y);
					window.draw(*shoot);
					delete shoot;
				}
			}

			if (adde == true) AddEnemy();

			if (enemy_positions.size() > 0) {
				for (int i = 0; i < enemy_positions.size(); i++) {
					srand(time(NULL));

					if (Stage == 4) {
						Sprite* enemy = new Sprite(boss_1);
						enemy->setPosition(enemy_positions.at(i).x, enemy_positions.at(i).y);
						window.draw(*enemy);
						delete enemy;
					}
					else {
						if (enemy_positions.at(i).tex == 0) {
							Sprite* enemy = new Sprite(enemy_level_1_yellow_texture);
							enemy->setPosition(enemy_positions.at(i).x, enemy_positions.at(i).y);
							window.draw(*enemy);
							delete enemy;
						}
						else if (enemy_positions.at(i).tex == 1) {
							Sprite* enemy = new Sprite(enemy_level_1_green_texture);
							enemy->setPosition(enemy_positions.at(i).x, enemy_positions.at(i).y);
							window.draw(*enemy);
							delete enemy;
						}
						else if (enemy_positions.at(i).tex == 2) {
							Sprite* enemy = new Sprite(enemy_level_1_red_texture);
							enemy->setPosition(enemy_positions.at(i).x, enemy_positions.at(i).y);
							window.draw(*enemy);
							delete enemy;
						}
					}
				}
			}

			if (enemy_bullet_positions.size() > 0) {
				for (int i = 0; i < enemy_bullet_positions.size(); i++) {
					Sprite* shoot = new Sprite(enemy_plasma_gun_level_1);
					shoot->setPosition(enemy_bullet_positions.at(i).x, enemy_bullet_positions.at(i).y);
					window.draw(*shoot);
					delete shoot;
				}
			}
			if (SpawnPowerups == true) {
				if (Timer7 == 250) {
					Timer7 = 0;
					int which = rand() % 3 + 1;
					int x = rand() & 1500 + 300;
					int y = rand() & 200 + 80;
					PowerUpsPositions* powerup = new PowerUpsPositions(x, y, which);
					powerups_positions.push_back(*powerup);
					delete powerup;
				}
			}

			if (powerups_positions.size() > 0) {
				for (int i = 0; i < powerups_positions.size(); i++) {
					if (powerups_positions.at(i).type == 1) {
						Sprite* heart = new Sprite(heart_texture);
						heart->setPosition(powerups_positions.at(i).x, powerups_positions.at(i).y);
						window.draw(*heart);

						delete heart;
					}
					else if (powerups_positions.at(i).type == 2) {
						Sprite* rapid = new Sprite(rapid_fire_texture);
						rapid->setPosition(powerups_positions.at(i).x, powerups_positions.at(i).y);
						window.draw(*rapid);
						delete rapid;

					}
					else if (powerups_positions.at(i).type == 3) {
						Sprite* rapid = new Sprite(shield_texture);
						rapid->setPosition(powerups_positions.at(i).x, powerups_positions.at(i).y);
						window.draw(*rapid);
						delete rapid;

					}
				}
			}

			if (RapidFireEnabled == true && Timer5 == 200) {
				//stop = clock();
				//czas = static_cast<double>(stop - czas) / CLOCKS_PER_SEC;
				//if (czas >= 15) {
					RapidFireEnabled = false;
					ShootTime = NormalShootTime;
					Timer5 = 0;
				//}
			}

			if (powerups_positions.size() > 0) {
				for (int i = 0; i < powerups_positions.size(); i++) {
					powerups_positions.at(i).y += 5;
				}
			}

			if (powerups_positions.size() > 0) {
				for (int i = 0; i < powerups_positions.size(); i++) {
					if (ship.getPosition().x >= powerups_positions.at(i).x - 50 &&
						ship.getPosition().x <= powerups_positions.at(i).x + heart_texture.getSize().x + 50
						&&
						ship.getPosition().y >= powerups_positions.at(i).y - 50 &&
						ship.getPosition().y <= powerups_positions.at(i).y + heart_texture.getSize().y + 50
						&& powerups_positions.at(i).active == true) {
						//
						// Lives++;
						if (powerups_positions.at(i).type == 1)
						{
							GamerLives.store(GamerLives.load() + 1);
							powerups_positions.at(i).active = false;
							PowerupsToDelete.push_back(i);
						}
						else if (powerups_positions.at(i).type == 2) {
							if (RapidFireEnabled) Timer5 = 0;
							else RapidFireEnabled = true;
							//start = clock();
							cout << "Rapid fire" << endl;
							ShootTime = RapidShootTime;
						}
					}
				}
			}

			if (RapidFireEnabled == true) {
				Timer5++;
			}

			string j = to_string(GamerLives.load());
			NumTex(j, HeartsNumber);

			window.draw(Info1);
			window.draw(HeartsNumber);

			if (PowerupsToDelete.size() > 0) {
				for (int i = 0; i < PowerupsToDelete.size(); i++) {
					powerups_positions.erase(powerups_positions.begin() + i);
				}
				PowerupsToDelete.clear();
			}

			if (enemy_positions.size() > 0) {
				for (int i = 0; i < enemy_positions.size(); i++) {
					for (int a = 0; a < ship_bullets_positions.size(); a++) {

						if (ship_bullets_positions.at(a).x >= enemy_positions.at(i).x &&
							ship_bullets_positions.at(a).x <= enemy_positions.at(i).x + enemy_level_1_yellow_texture.getSize().x &&
							ship_bullets_positions.at(a).y <= enemy_positions.at(i).y + enemy_level_1_yellow_texture.getSize().y &&
							ship_bullets_positions.at(a).active == true) {
							toDelete.push_back(i);
							ship_bullets_positions.at(a).active = false;
							GamerPoints += 5;
							GamerPointsBuffer += 5;
						}
					}


				}
				sort(toDelete.begin(), toDelete.end());
				if (toDelete.size() > 0) {
					for (int i = toDelete.size() - 1; i >= 0; i--) {
						enemy_positions.erase(enemy_positions.begin() + toDelete[i]);

					}
				}
				toDelete.clear();
			}
			
			vector<int> EnemyBulletsToDelete;

			if (enemy_bullet_positions.size() > 0) {
				for (int i = 0; i < enemy_bullet_positions.size(); i++) {
					if (
						enemy_bullet_positions.at(i).x >= ship.getPosition().x &&
						enemy_bullet_positions.at(i).x <= ship.getPosition().x + ship_texture.getSize().x
						&&
						enemy_bullet_positions.at(i).y >= ship.getPosition().y &&
						enemy_bullet_positions.at(i).y <= ship.getPosition().y + ship_texture.getSize().y
						&& enemy_bullet_positions.at(i).active == true
						) {
						enemy_bullet_positions.at(i).active = false;
						EnemyBulletsToDelete.push_back(i);
						GamerLives.store(GamerLives.load() - 1);
					}
				}
			}

			if (enemy_bullet_positions.size() > 0) {
				for (int i = 0; i < enemy_bullet_positions.size(); i++) {
					if (enemy_bullet_positions.at(i).y > 1000) 	EnemyBulletsToDelete.push_back(i);
				}
			}

			if (EnemyBulletsToDelete.size() > 0) {
				for (int i = 0; i < EnemyBulletsToDelete.size(); i++) {
					EnemyBulletsToDelete.erase(EnemyBulletsToDelete.begin() + i);
				}
			}



			if (Timer2 == 10) { show_left = false; Timer2 = 0; }
			if (Timer3 == 10) { show_right = false; Timer3 = 0; }

			if (enemy_positions.size() == 0) UpdateEnemy = false;

			if (GamerLives.load() == 0) {

				TurnOFFThreads.store(true);
				ShootSound.pause(); MainMusic.pause();
				window.close();
			}
			if (EndlessGameStarted != true) {
				if (Stage == 3 && enemy_positions.size() == 0) {
					TurnOFFThreads.store(true);


					 drawEnd = true; 

					WaitEnd = true;
				}
				if (drawEnd == true) {
					enemy_bullet_positions.clear();
					enemy_positions.clear();
					ship_bullets_positions.clear();
					adde = false;
					SpawnPowerups = false;
					RectangleShape *won_info = DrawRectangle(700, 300, 600, 400);
					Font f1;
					f1.loadFromFile("Hibo.otf");
					Text *t2 = DrawMessage("Dobra robota komandorze Rex! \nCaly sektor jest oczyszczony z wrogow. \nWracaj do bazy", 24, 610, 410);

					MainMusic.pause();

					Sound WinSound;
					SoundBuffer WinSoundBuffer;
					WinSoundBuffer.loadFromFile("Sounds/WinSound.wav");
					WinSound.setBuffer(WinSoundBuffer);
					//WinSound.play();
					//WinSound.pause();
					window.draw(*won_info);
					window.draw(*t2);
					WinGameSound = true;
					drawEnd = false;
				}
			}
			window.display();
			if (WaitEnd == true) {

				if (WinGameSound == true) {

					WinGameSound = false;
				}
				//SleepGame(2000);
				//WinSound.stop();
				while (window.pollEvent(event)) {
					if (event.type == Event::KeyPressed) {
						if (event.key.code == Keyboard::E) {
							window.close();
							exit(0);
						}
					}
					SleepGame(50);
				}
			}
			if (enemy_positions.size() == 0) {
				AddEnemys = true; UpdateEnemy = true;
			}
			Timer7++;
			SleepGame(30);
		}
	}

	return 0;
}

void START() {
	thread Shooting(AddShoot);
	thread Updating(UpdateEnemys);

	Shooting.detach();
	Updating.detach();
}