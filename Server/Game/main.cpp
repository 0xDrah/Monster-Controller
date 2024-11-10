## add

#ifdef __ENABLE_MONSTER_CONTROLLER__
#include "MonsterController.hpp"
#endif

## After

	DSManager dsManager;

## Add

#ifdef __ENABLE_MONSTER_CONTROLLER__
	CMonsterController MonsterController;
#endif