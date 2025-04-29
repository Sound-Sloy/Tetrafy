#pragma once
#include <raylib.h>
#include "Keyboard.h"
#include "AnimatedSprite.h"
#include "Options.h"
#include "SoundManager.h"
#include "ScoreFileHandler.h"
#include "AnimatedBackground.h"

namespace Globals {

	namespace Fonts {
		inline Font FontDefault;
	}
	inline Font TetrisFont; 
	inline Font TetrisFontBig; 
	inline Font TetrisFontMedium; 
	inline Keyboard KeyboardManager;
	inline std::shared_ptr<SoundManager> SoundManagerInstance;
	inline std::unique_ptr<AnimatedBackground> GAnimatedBackgroundInstance;

	inline int32_t BaseWindowSizeX = 738;
	inline int32_t BaseWindowSizeY = 800;

	inline std::vector<std::string> GUIScales = {"1.0", "1.1", "1.2", "1.3", "1.4", "1.5"};
	inline std::unordered_map<float, size_t> GUIScaleToIndexMap = { {1.f, 0}, {1.1f, 1}, {1.2f,2}, {1.3f, 3}, {1.4f, 4}, {1.5f, 5} };

	inline std::unique_ptr<ScoreFileHandler> GScoreFileHandlerInstance;

	namespace Animations {
		//inline Animation TeeAnimation;
		//inline Animation ElAnimation;
		//inline Animation JayAnimation;
		//inline Animation StraightAnimation;
		//inline Animation SquareAnimation;
		//inline Animation LeftZigZagAnimation;
		//inline Animation RightZigZagAnimation;
		inline Animation CellBlinkingAnimation;
		inline Animation CellDisolveAnimation;
	}

	namespace Sounds {
		inline Music MainTheme;
		inline Sound SolidifySound;
		inline Sound HoverSound;
		inline Sound ClickSound;
	}

	namespace Textures {
		inline Texture2D SwitchOn;
		inline Texture2D SwitchOff;
		inline Texture2D SliderBase;
		inline Texture2D SliderHighlight;
		inline Texture2D SliderHandle;
		inline Texture2D OptionsActive;
		inline Texture2D OptionsHovered;
		inline Texture2D OptionsClicked;
		inline Texture2D OptionsInactive;
		inline Texture2D HotkeyFocus;
		inline Texture2D HotkeyActive;
		inline Texture2D HotkeyInactive;
		inline Texture2D HotkeyClicked;
		inline Texture2D HotkeyHovered;
	}

	namespace Colors {
		inline Color BackgroundColor;
	}

	inline OptionsS Options;
}
