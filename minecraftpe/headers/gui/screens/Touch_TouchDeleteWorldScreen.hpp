#pragma once
#include <gui/screens/ConfirmScreen.hpp>
#include <level/LevelSummary.hpp>

namespace Touch {
	struct TouchDeleteWorldScreen: ConfirmScreen
	{
		LevelSummary levelSummary;

		TouchDeleteWorldScreen(const LevelSummary&);

		virtual ~TouchDeleteWorldScreen() {
		}
		virtual void postResult(bool_t);
	};
}
