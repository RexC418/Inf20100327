#pragma once
#include <gui/Screen.hpp>
#include <Minecraft.hpp>
#include <entity/LocalPlayer.hpp>

struct BaseContainerMenu;
struct BaseContainerScreen: Screen
{
	BaseContainerMenu* field_50;
	//TODO maybe has constructor that takes field_50?
	virtual ~BaseContainerScreen() {
	}
	virtual void init() {
		Screen::init();
		this->minecraft->player->currentContainer = this->field_50;
	}
	virtual void tick() {
		Screen::tick();
		if (!this->minecraft->player->isAlive() || this->minecraft->player->isDead) {
			this->minecraft->player->closeContainer();
		}
	}
	virtual bool_t closeOnPlayerHurt() {
		return 1;
	}
};
