#include "Game.h"

Game::Game(int32_t width, int32_t height, std::string windowTitle)
{
	//{
	//	// Info: Code to create an asset file
	//	ResPacker::Dumper dmp("./assets.sndrpkg");
	//	for (auto entry : std::filesystem::directory_iterator("./assets")) {
	//		if(!entry.is_regular_file()) {
	//			continue;
	//		}
	//		ResPacker::ObjectType objType = ResPacker::ObjectType::None;
	//		if(entry.path().extension().string() == ".png"){
	//			objType = ResPacker::ObjectType::Image;
	//		}
	//		if (entry.path().extension().string() == ".ttf") {
	//			objType = ResPacker::ObjectType::Font;
	//		}
	//		if (entry.path().extension().string() == ".wav") {
	//			objType = ResPacker::ObjectType::Wave;
	//		}
	//		dmp.DumpFileBinary(entry.path().string(), entry.path().stem().string(), objType);
	//	}
	//}

	LoadOptions();

	assert(!GetWindowHandle());
	SetTargetFPS(60);
	SetConfigFlags(ConfigFlags::FLAG_MSAA_4X_HINT);
	InitWindow(width * Globals::Options.GUIScale, height * Globals::Options.GUIScale, windowTitle.c_str());
	InitAudioDevice();
	SetExitKey(KeyboardKey::KEY_NULL);

	Globals::Fonts::FontDefault = GetFontDefault();
	Globals::KeyboardManager = Keyboard();

	// 
	//Globals::SoundManagerInstance = new SoundManager(Globals::Options, Globals::Sounds::MainTheme);
	//Globals::SoundManagerInstance = std::make_shared<SoundManager>(Globals::Options, Globals::Sounds::MainTheme);
	Globals::KeyboardManager = Keyboard();

	Globals::GScoreFileHandlerInstance = std::make_unique<ScoreFileHandler>("./PlayerScores.bin");
	Globals::GScoreFileHandlerInstance->Load();


	{
		LoadAssets();
	}

	Globals::Colors::BackgroundColor = Color(20, 20, 30, 255);

	m_ScreenManager = new ScreenManager();

}

Game::~Game() noexcept
{
	assert(GetWindowHandle());
	CloseAudioDevice();
	CloseWindow();
	SaveOptions();
	Globals::GScoreFileHandlerInstance->Save();
}

bool Game::GameShouldClose() const
{
	return WindowShouldClose() or States::ForceClose;
}

void Game::Tick()
{
	if(States::Flags::ForceReloadAssets) {
		States::Flags::ForceReloadAssets = false;
		UnloadAssets();
		LoadAssets();
	}

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

void Game::LoadAssets()
{
	ResPacker::Loader loader("./assets.sndrpkg");

	loader.LoadAllRaw();

	Globals::TetrisFont = loader.LoadAsFont("font", ".ttf", 28 * Globals::Options.GUIScale);
	Globals::TetrisFontBig = loader.LoadAsFont("font", ".ttf", 72 * Globals::Options.GUIScale);
	Globals::TetrisFontMedium = loader.LoadAsFont("font", ".ttf", 20 * Globals::Options.GUIScale);
	std::string guiScaleSuffix = Globals::GUIScales.at(Globals::GUIScaleToIndexMap.at(Globals::Options.GUIScale));

	Globals::Animations::CellBlinkingAnimation = { loader.LoadAsTexture2D("cellblinkanim_" + guiScaleSuffix, ".png"), 20,
		{
			{0 * floor(32 * Globals::Options.GUIScale), 0, floor(32 * Globals::Options.GUIScale), floor(32 * Globals::Options.GUIScale)},
			{1 * floor(32 * Globals::Options.GUIScale), 0, floor(32 * Globals::Options.GUIScale), floor(32 * Globals::Options.GUIScale)},
			{2 * floor(32 * Globals::Options.GUIScale), 0, floor(32 * Globals::Options.GUIScale), floor(32 * Globals::Options.GUIScale)},
			{3 * floor(32 * Globals::Options.GUIScale), 0, floor(32 * Globals::Options.GUIScale), floor(32 * Globals::Options.GUIScale)},
			{4 * floor(32 * Globals::Options.GUIScale), 0, floor(32 * Globals::Options.GUIScale), floor(32 * Globals::Options.GUIScale)},
			{5 * floor(32 * Globals::Options.GUIScale), 0, floor(32 * Globals::Options.GUIScale), floor(32 * Globals::Options.GUIScale)},
			{6 * floor(32 * Globals::Options.GUIScale), 0, floor(32 * Globals::Options.GUIScale), floor(32 * Globals::Options.GUIScale)},
			{7 * floor(32 * Globals::Options.GUIScale), 0, floor(32 * Globals::Options.GUIScale), floor(32 * Globals::Options.GUIScale)},
			{8 * floor(32 * Globals::Options.GUIScale), 0, floor(32 * Globals::Options.GUIScale), floor(32 * Globals::Options.GUIScale)},
			{9 * floor(32 * Globals::Options.GUIScale), 0, floor(32 * Globals::Options.GUIScale), floor(32 * Globals::Options.GUIScale)},
		},
		{0,0} };
	Globals::Animations::CellDisolveAnimation = { loader.LoadAsTexture2D("celldisolveanim_" + guiScaleSuffix, ".png"), 18,
	{
		{0 * floor(32 * Globals::Options.GUIScale), 0, floor(32 * Globals::Options.GUIScale), floor(32 * Globals::Options.GUIScale)},
		{1 * floor(32 * Globals::Options.GUIScale), 0, floor(32 * Globals::Options.GUIScale), floor(32 * Globals::Options.GUIScale)},
		{2 * floor(32 * Globals::Options.GUIScale), 0, floor(32 * Globals::Options.GUIScale), floor(32 * Globals::Options.GUIScale)},
		{3 * floor(32 * Globals::Options.GUIScale), 0, floor(32 * Globals::Options.GUIScale), floor(32 * Globals::Options.GUIScale)},
		{4 * floor(32 * Globals::Options.GUIScale), 0, floor(32 * Globals::Options.GUIScale), floor(32 * Globals::Options.GUIScale)},
		{5 * floor(32 * Globals::Options.GUIScale), 0, floor(32 * Globals::Options.GUIScale), floor(32 * Globals::Options.GUIScale)},
	},
	{0,0} };

	Globals::Sounds::MainTheme = loader.LoadAsMusicStream("themesong", ".mp3");
	Globals::Sounds::SolidifySound = loader.LoadAsSound("solidifysound", ".wav");
	Globals::Sounds::HoverSound = loader.LoadAsSound("hoversound", ".wav");
	Globals::Sounds::ClickSound = loader.LoadAsSound("clicksound", ".wav");

	Globals::Textures::SwitchOn = loader.LoadAsTexture2D("switchon_" + guiScaleSuffix, ".png");
	Globals::Textures::SwitchOff = loader.LoadAsTexture2D("switchoff_" + guiScaleSuffix, ".png");
	Globals::Textures::SliderBase = loader.LoadAsTexture2D("sliderbase_" + guiScaleSuffix, ".png");
	Globals::Textures::SliderHighlight = loader.LoadAsTexture2D("sliderhighlight_" + guiScaleSuffix, ".png");
	Globals::Textures::SliderHandle = loader.LoadAsTexture2D("sliderhandle_" + guiScaleSuffix, ".png");
	Globals::Textures::OptionsActive = loader.LoadAsTexture2D("options_normal_" + guiScaleSuffix, ".png");
	Globals::Textures::OptionsHovered = loader.LoadAsTexture2D("options_hovered_" + guiScaleSuffix, ".png");
	Globals::Textures::HotkeyFocus = loader.LoadAsTexture2D("hotkey_focus_" + guiScaleSuffix, ".png");
	Globals::Textures::HotkeyActive = loader.LoadAsTexture2D("hotkey_active_" + guiScaleSuffix, ".png");
	Globals::Textures::OptionsClicked = Globals::Textures::OptionsHovered;
	Globals::Textures::OptionsInactive = Globals::Textures::OptionsActive;
	Globals::Textures::HotkeyInactive = Globals::Textures::HotkeyActive;
	Globals::Textures::HotkeyHovered = Globals::Textures::HotkeyActive;
	Globals::Textures::HotkeyClicked = Globals::Textures::HotkeyActive;

	Globals::SoundManagerInstance = std::make_shared<SoundManager>(Globals::Options, Globals::Sounds::MainTheme);

	Globals::GAnimatedBackgroundInstance = std::make_unique<AnimatedBackground>();
}
void Game::UnloadAssets()
{
	UnloadFont(Globals::TetrisFont);
	UnloadFont(Globals::TetrisFontBig);
	UnloadFont(Globals::TetrisFontMedium);
	UnloadTexture(Globals::Animations::CellBlinkingAnimation.Atlas);
	//Globals::Animations::CellDisolveAnimation = { loader.LoadAsTexture2D("celldisolveanim", ".png"), 18, { {0, 0, 32, 32}, {32, 32, 32, 32}, {64, 64, 32, 32}, {96, 96, 32, 32}, {128, 128, 32, 32}, {160, 160, 32, 32} }, {0,0} };
	UnloadTexture(Globals::Animations::CellDisolveAnimation.Atlas);
	UnloadMusicStream(Globals::Sounds::MainTheme);
	UnloadSound(Globals::Sounds::SolidifySound);
	UnloadSound(Globals::Sounds::HoverSound);
	UnloadSound(Globals::Sounds::ClickSound);

	UnloadTexture(Globals::Textures::SwitchOn);
	UnloadTexture(Globals::Textures::SwitchOff);
	UnloadTexture(Globals::Textures::SliderBase);
	UnloadTexture(Globals::Textures::SliderHighlight);
	UnloadTexture(Globals::Textures::SliderHandle);
	UnloadTexture(Globals::Textures::OptionsActive);
	UnloadTexture(Globals::Textures::OptionsHovered);
	UnloadTexture(Globals::Textures::HotkeyFocus);
	UnloadTexture(Globals::Textures::HotkeyActive);
	Globals::Textures::OptionsClicked = Globals::Textures::OptionsHovered;
	Globals::Textures::OptionsInactive = Globals::Textures::OptionsActive;
	Globals::Textures::HotkeyInactive = Globals::Textures::HotkeyActive;
	Globals::Textures::HotkeyHovered = Globals::Textures::HotkeyActive;
	Globals::Textures::HotkeyClicked = Globals::Textures::HotkeyActive;
}

void Game::Update()
{
	float deltaTime = GetFrameTime();
	Globals::GAnimatedBackgroundInstance->Update(deltaTime);
	Globals::SoundManagerInstance->Update();
	m_ScreenManager->Update(deltaTime);
}

void Game::Draw()
{
	ClearBackground(Globals::Colors::BackgroundColor);
	Globals::GAnimatedBackgroundInstance->Draw();
	m_ScreenManager->Draw();
}