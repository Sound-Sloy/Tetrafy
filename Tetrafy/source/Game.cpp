#include "Game.h"

Game::Game(int32_t width, int32_t height, std::string windowTitle)
{
	LoadOptions();

	assert(!GetWindowHandle());
	SetTargetFPS(60);
	SetConfigFlags(ConfigFlags::FLAG_MSAA_4X_HINT);
	InitWindow(width, height, windowTitle.c_str());
	InitAudioDevice();
	SetExitKey(KeyboardKey::KEY_NULL);

	//Globals::ScreenManagerInstance = (uintptr_t)&m_ScreenManager;

	Globals::Fonts::FontDefault = GetFontDefault();

	Globals::TetrisFont = LoadFontEx("./assets/TitanOne-Regular.ttf", 28, nullptr, 256);
	Globals::TetrisFontBig = LoadFontEx("./assets/TitanOne-Regular.ttf", 72, nullptr, 256);
	Globals::TetrisFontMedium = LoadFontEx("./assets/TitanOne-Regular.ttf", 20, nullptr, 256);
	Globals::KeyboardManager = Keyboard();
	Globals::SoundManagerInstance = new SoundManager(Globals::Options, Globals::Sounds::MainTheme);

	//Globals::Animations::TeeAnimation = { LoadTexture("./assets/teeanim.png"), 10, { {0, 0, 32, 32}, {32, 32, 32, 32}, {64, 64, 32, 32}, {96, 96, 32, 32}, {128, 128, 32, 32}, {160, 160, 32, 32}, {192, 192, 32, 32} }, {0,0} };
	//Globals::Animations::ElAnimation = { LoadTexture("./assets/elanim.png"), 10, { {0, 0, 32, 32}, {32, 32, 32, 32}, {64, 64, 32, 32}, {96, 96, 32, 32}, {128, 128, 32, 32}, {160, 160, 32, 32}, {192, 192, 32, 32} }, {0,0} };
	//Globals::Animations::JayAnimation = { LoadTexture("./assets/jayanim.png"), 10, { {0, 0, 32, 32}, {32, 32, 32, 32}, {64, 64, 32, 32}, {96, 96, 32, 32}, {128, 128, 32, 32}, {160, 160, 32, 32}, {192, 192, 32, 32} }, {0,0} };
	//Globals::Animations::StraightAnimation = { LoadTexture("./assets/straightanim.png"), 10, { {0, 0, 32, 32}, {32, 32, 32, 32}, {64, 64, 32, 32}, {96, 96, 32, 32}, {128, 128, 32, 32}, {160, 160, 32, 32}, {192, 192, 32, 32} }, {0,0} };
	//Globals::Animations::SquareAnimation = { LoadTexture("./assets/oanim.png"), 10, { {0, 0, 32, 32}, {32, 32, 32, 32}, {64, 64, 32, 32}, {96, 96, 32, 32}, {128, 128, 32, 32}, {160, 160, 32, 32}, {192, 192, 32, 32} }, {0,0} };
	//Globals::Animations::LeftZigZagAnimation = { LoadTexture("./assets/leftanim.png"), 10, { {0, 0, 32, 32}, {32, 32, 32, 32}, {64, 64, 32, 32}, {96, 96, 32, 32}, {128, 128, 32, 32}, {160, 160, 32, 32}, {192, 192, 32, 32} }, {0,0} };
	//Globals::Animations::RightZigZagAnimation = { LoadTexture("./assets/rightanim.png"), 10, { {0, 0, 32, 32}, {32, 32, 32, 32}, {64, 64, 32, 32}, {96, 96, 32, 32}, {128, 128, 32, 32}, {160, 160, 32, 32}, {192, 192, 32, 32} }, {0,0} };
	Globals::Animations::CellBlinkingAnimation = { LoadTexture("./assets/cellblinkanim.png"), 15, { {0, 0, 32, 32}, {32, 32, 32, 32}, {64, 64, 32, 32}, {96, 96, 32, 32}, {128, 128, 32, 32}, {160, 160, 32, 32}, {192, 192, 32, 32}, {224, 224, 32, 32}, {256, 256, 32, 32} }, {0,0} };
	Globals::Animations::CellDisolveAnimation = { LoadTexture("./assets/celldisolveanim.png"), 5, { {0, 0, 32, 32}, {32, 32, 32, 32}, {64, 64, 32, 32}, {96, 96, 32, 32}, {128, 128, 32, 32}, {160, 160, 32, 32} }, {0,0} };

	Globals::Sounds::MainTheme = LoadMusicStream("./assets/maintheme.mp3");
	Globals::Sounds::SolidifySound = LoadSound("./assets/solidify.wav");
	Globals::Sounds::HoverSound = LoadSound("./assets/hover.wav");
	Globals::Sounds::ClickSound = LoadSound("./assets/click.wav");

	Globals::Textures::SwitchOn = LoadTexture("./assets/switchon.png");
	Globals::Textures::SwitchOff = LoadTexture("./assets/switchoff.png");
	Globals::Textures::SliderBase = LoadTexture("./assets/sliderbase.png");
	Globals::Textures::SliderHighlight = LoadTexture("./assets/sliderhighlight.png");
	Globals::Textures::SliderHandle = LoadTexture("./assets/sliderhandle.png");
	Globals::Textures::OptionsActive = LoadTexture("./assets/options_normal.png");
	Globals::Textures::OptionsHovered = LoadTexture("./assets/options_hovered.png");
	Globals::Textures::OptionsClicked = Globals::Textures::OptionsHovered;
	Globals::Textures::OptionsInactive = Globals::Textures::OptionsActive;
	Globals::Textures::HotkeyFocus = LoadTexture("./assets/hotkey_focus.png");
	Globals::Textures::HotkeyActive = LoadTexture("./assets/hotkey_active.png");
	Globals::Textures::HotkeyInactive = Globals::Textures::HotkeyActive;
	Globals::Textures::HotkeyHovered = Globals::Textures::HotkeyActive;
	Globals::Textures::HotkeyClicked = Globals::Textures::HotkeyActive;

	Globals::Colors::BackgroundColor = Color(20, 20, 30, 255);

	m_ScreenManager = new ScreenManager();
}

Game::~Game() noexcept
{
	assert(GetWindowHandle());
	CloseAudioDevice();
	CloseWindow();
	SaveOptions();
}

bool Game::GameShouldClose() const
{
	return WindowShouldClose() or States::ForceClose;
}

void Game::Tick()
{
	BeginDrawing();
	Update();
	Draw();
	EndDrawing();
}

void Game::LoadOptions() {
	if (!FileExists("./settings.json")) {
		return;
	}
	std::ifstream in("./settings.json");
	nlohmann::json content = nlohmann::json::parse(in);
	Globals::Options = content;
}

void Game::SaveOptions() {
	nlohmann::json data = Globals::Options;
	std::ofstream out("./settings.json");
	out << std::setw(4) << data << std::endl;
}

void Game::Update()
{
	float deltaTime = GetFrameTime();
	Globals::SoundManagerInstance->Update();
	m_ScreenManager->Update(deltaTime);
	//this->m_Board.Update(deltaTime);
}

void Game::Draw()
{
	ClearBackground(Globals::Colors::BackgroundColor);
	m_ScreenManager->Draw();
	//m_Board.Draw();
}