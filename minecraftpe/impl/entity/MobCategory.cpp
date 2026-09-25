#include <entity/MobCategory.hpp>
#include <tile/material/Material.hpp>

MobCategory MobCategory::monster(1, 10, 20, 0);
MobCategory MobCategory::creature(2, 10, 15, 1);
MobCategory MobCategory::waterCreature(3, 5, 10, 1);
int32_t MobCategory::numValues = 3;
MobCategory* MobCategory::values[] = {
	&MobCategory::monster, &MobCategory::creature, &MobCategory::waterCreature};

void MobCategory::initMobCategories(void){
	MobCategory::monster.material = Material::air;
	MobCategory::creature.material = Material::air;
	MobCategory::waterCreature.material = Material::water;
}
