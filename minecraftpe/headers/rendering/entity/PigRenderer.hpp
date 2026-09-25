#pragma once
#include <rendering/entity/MobRenderer.hpp>
#include <entity/Pig.hpp>
#include <rendering/model/PigModel.hpp>

struct PigRenderer: MobRenderer
{
	PigRenderer(Model* a2, float a3) :
			MobRenderer(a2, a3) {
		this->setArmor(new PigModel(0.5));
	}

	virtual ~PigRenderer() {
		Model* armouwur = this->getArmor();
		if (armouwur) delete armouwur;
	}
	virtual int32_t prepareArmor(Mob* a2, int32_t a3, float a4) {
		if (!((Pig*) (a2))->hasSaddle() || a3 > 0) return -1;

		this->bindTexture("mob/saddle.png");
		return 1;
	}
};
