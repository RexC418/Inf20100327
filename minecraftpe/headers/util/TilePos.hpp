#pragma once
#include <_types.h>
#include <stdlib.h>
#include <bitset>
struct TilePos{
	int32_t x, y, z;

	bool_t operator<(const TilePos& a2) const {
		return 981131 * this->y + 8976890 * this->x + this->z < (uint32_t) ((981131 * a2.y + 8976890 * a2.x + a2.z));
	}
	//inlined in std::_Hashtable<TilePos,std::pair<TilePos const,TileEntity *>,std::allocator<std::pair<TilePos const,TileEntity *>>,std::_Select1st<std::pair<TilePos const,TileEntity *>>,std::equal_to<TilePos>,std::hash<TilePos>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,true,false,true>::_M_find_before_node(uint,TilePos const&,uint)
	bool_t operator==(const TilePos& a2) const {
		return this->x == a2.x && this->y == a2.y && this->z == a2.z;
	}
};

namespace std {
	template<>
	struct hash<TilePos>
	{
		//i hate c++ so much
		size_t operator()(const TilePos& a2) const noexcept {
			return 0xEF88B * a2.y + 0x88F9FA * a2.x + a2.z;
		}
	};
}

