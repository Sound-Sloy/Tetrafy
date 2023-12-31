#pragma once
#include <raylib.h>
#include "Keyboard.h"
#include "AnimatedSprite.h"
#include "Options.h"
#include "SoundManager.h"

namespace Globals {

	namespace Fonts {
		inline Font FontDefault;
	}
	inline Font TetrisFont; 
	inline Font TetrisFontBig; 
	inline Font TetrisFontMedium; 
	inline Keyboard KeyboardManager;
	inline SoundManager* SoundManagerInstance;
	
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
	}

	namespace Colors {
		inline Color BackgroundColor;
	}

	inline OptionsS Options;

	inline uint32_t HighScore = 0;
}
