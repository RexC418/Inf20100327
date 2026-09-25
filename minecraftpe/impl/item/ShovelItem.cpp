#include <item/ShovelItem.hpp>
#include <tile/Tile.hpp>

//</3 DiggerItem::DiggerItem(int,int,Item::Tier const&,std::vector<Tile *> const&) according to 0.7.2
//c++ is def the most evil language ever
ShovelItem::ShovelItem(int32_t a2, const Item::Tier& tier)
	: DiggerItem(a2, 1, tier, {}) {
	std::vector<Tile*> v9;
	//this cast is very important to compile into the same thing as vanilla -
	//without this cast it does not turn into std::vector<Tile *>::_M_emplace_back_aux<Tile *>
	//*truly magical language*
	v9.push_back((Tile*) Tile::grass);
	v9.push_back(Tile::dirt);
	v9.push_back(Tile::sand);
	v9.push_back(Tile::gravel);
	v9.push_back(Tile::topSnow);
	v9.push_back(Tile::snow);
	v9.push_back(Tile::clay);
	v9.push_back(Tile::farmland);
	this->setTiles(v9);
	//i wonder why didnt mojang use this->setTiles({...}) - maybe it is somehow related to the old versions that used
	//non c++11 std(stlport)?
	//okie now a different question - why didnt mojang use DiggerItem(a2, tier, {...}) if they had it since at least 0.7.2 </3
}

bool_t ShovelItem::canDestroySpecial(const Tile* a2) const {
	return a2 == Tile::topSnow || a2 == Tile::snow;
}
