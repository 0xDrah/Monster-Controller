## Add

#ifdef __ENABLE_MONSTER_CONTROLLER__
#include "MonsterController.hpp"
#endif

## After

	ch->Show(ch->GetMapIndex(), pos.x, pos.y, pos.z);
	ch->ReviveInvisible(5);

## Add

#ifdef __ENABLE_MONSTER_CONTROLLER__
	CMonsterController::instance().SendCounter(ch);
#endif
