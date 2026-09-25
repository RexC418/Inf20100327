#pragma once
#include <_types.h>
#include <map>
struct ItemInstance;
struct FurnaceRecipes
{
	static FurnaceRecipes* instance;

	std::map<int32_t, ItemInstance> recipes;

	FurnaceRecipes();
	void addFurnaceRecipe(int32_t, const ItemInstance&);
	static FurnaceRecipes* getInstance();
	void getRecipes() const; //TODO prob different type, but it is empty so cant really guess
	ItemInstance getResult(int32_t) const;
	bool_t isFurnaceItem(int32_t) const;
	static void teardownFurnaceRecipes();
};
