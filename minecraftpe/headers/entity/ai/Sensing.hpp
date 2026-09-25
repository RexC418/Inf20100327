#pragma once
#include <entity/Mob.hpp>
#include <set>
struct Mob;
struct Entity;

struct Sensing
{
	Mob* holder;
	std::set<int32_t> _canSee;
	std::set<int32_t> _cannotSee;
	Sensing(Mob* a2) {
		this->holder = a2;
	}

	bool_t canSee(Entity* a2) {
		bool_t r;
		int32_t eid = a2->entityId;
		if (this->_canSee.find(eid) == this->_canSee.end()) {
			if (this->_cannotSee.find(eid) == this->_cannotSee.end()) {
				r = this->holder->canSee(a2);
				if (r) {
					this->_canSee.insert(eid);
				} else {
					this->_cannotSee.insert(eid);
				}
			} else {
				return 0;
			}
		} else {
			return 1;
		}
		return r;
	}
};
