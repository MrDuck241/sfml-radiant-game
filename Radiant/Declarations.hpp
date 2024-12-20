#include <SFML/Audio.hpp>

#define DEBUG(info) cout<<info<<endl;
#define SleepGame(value) std::this_thread::sleep_for(std::chrono::milliseconds(value));

#define WINDOW_SIZE_X 1920
#define WINDOW_SIZE_Y 1000

bool Shoot{ false };
bool ShowEnemy{ false };
bool UpdateEnemy{ false };
bool AddEnemys{ false };
bool ShootSoundPlay{ false };
bool WinGameSound{ false };
bool show_left{ false };
bool show_right{ false };
bool EndlessGameStarted{ false };
bool PlotGameStarted{ false };
bool RapidFireEnabled{ false };
bool ShowMenu{ true };
bool SpawnPowerups{ false };

std::string Spoints;
std::string ScoreBoardParts[4];

std::vector<BulletPosition> ship_bullets_positions;
std::vector<EnemyPosition> enemy_positions;
std::vector<EnemyBulletPosition> enemy_bullet_positions;
std::vector<PowerUpsPositions> powerups_positions;

std::vector<int> PowerupsToDelete;

int EnemyCount{ 0 };
int Stage{ 0 };
int WeaponLevel{ 0 };
int GamerPoints{ 0 };
int GamerPointsBuffer{ 0 };
int Timer1{ 0 };
int Timer2{ 0 };
int Timer3{ 0 };
int Timer4{ 0 };
int Timer5{ 0 };
int Timer7{ 0 };

const int NormalShootTime = 1000;
const int RapidShootTime = 400;
int ShootTime{NormalShootTime};

atomic<bool> TurnOFFThreads(false);
atomic<int> GamerLives(0);

std::mutex ShootMutex;

std::condition_variable ShootCondition;

sf::Music MainMusic;

sf::Sound ShootSound;

sf::SoundBuffer Sound1;

sf::Event event;

enum Stages {
	STAGE0 = 0,
	STAGE1 = 5,
	STAGE2 = 10,
	STAGE3 = 15,
	STAGE4 = 1
};

void HardExit() {
	Shoot = false;
	exit(0);
}

void ResourcesError() {
	runtime_error("Unable to open game resources");
}