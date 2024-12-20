#include "Position_class.hpp"
#include "Declarations.hpp"

#include <mutex>
#include <condition_variable>

void AddShoot() {
	while (TurnOFFThreads.load() != true) {
		if (Shoot == true) {
			if (Timer1 >= ShootTime) {
				BulletPosition* bullet_position = new BulletPosition(ship_position.x + 50, ship_position.y);
				ship_bullets_positions.push_back(*bullet_position);
				delete bullet_position;
				if (ShootSoundPlay == true) ShootSound.play();
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
		//	std::cout << "Shooting stopped" << std::endl;
			ShootCondition.wait(lock, [] { return Shoot; });
		}
		if (TurnOFFThreads == true) break;
	}
}