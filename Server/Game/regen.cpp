## Add

#ifdef __ENABLE_MONSTER_CONTROLLER__
#include "MonsterController.hpp"
#endif


## Compare

static void regen_spawn(LPREGEN regen, bool bOnce)
{
	DWORD	num;
	DWORD	i;

	num = (regen->max_count - regen->count);

	if (!num)
		return;

	for (i = 0; i < num; ++i)
	{
		LPCHARACTER ch = NULL;

		if (regen->type == REGEN_TYPE_ANYWHERE)
		{
			ch = CHARACTER_MANAGER::instance().SpawnMobRandomPosition(regen->vnum, regen->lMapIndex);

			if (ch) {
				++regen->count;
			
#ifdef __ENABLE_MONSTER_CONTROLLER__
				if (MonsterControllerNS::GetCounterType(ch->GetRaceNum()).has_value())
					CMonsterController::instance().HandleCounter(ch, ch->GetMapIndex());
#endif
			}
		}
		else if (regen->sx == regen->ex && regen->sy == regen->ey)
		{
			ch = CHARACTER_MANAGER::instance().SpawnMob(regen->vnum,
					regen->lMapIndex,
					regen->sx,
					regen->sy,
					regen->z_section,
					false,
					regen->direction == 0 ? number(0, 7) * 45 : (regen->direction - 1) * 45);

			if (ch) {
				++regen->count;

#ifdef __ENABLE_MONSTER_CONTROLLER__
				if (MonsterControllerNS::GetCounterType(ch->GetRaceNum()).has_value())
					CMonsterController::instance().HandleCounter(ch, ch->GetMapIndex());
#endif
			}
		}
		else
		{
			if (regen->type == REGEN_TYPE_MOB)
			{
				ch = CHARACTER_MANAGER::Instance().SpawnMobRange(regen->vnum, regen->lMapIndex, regen->sx, regen->sy, regen->ex, regen->ey, true, regen->is_aggressive, regen->is_aggressive );

				if (ch) {
					++regen->count;
					
#ifdef __ENABLE_MONSTER_CONTROLLER__
					if (MonsterControllerNS::GetCounterType(ch->GetRaceNum()).has_value())
						CMonsterController::instance().HandleCounter(ch, ch->GetMapIndex());
#endif
				}
			}
			else if (regen->type == REGEN_TYPE_GROUP)
			{
				if (CHARACTER_MANAGER::Instance().SpawnGroup(regen->vnum, regen->lMapIndex, regen->sx, regen->sy, regen->ex, regen->ey, bOnce ? NULL : regen, regen->is_aggressive)) {
					++regen->count;
				}
			}
			else if (regen->type == REGEN_TYPE_GROUP_GROUP)
			{
				if (CHARACTER_MANAGER::Instance().SpawnGroupGroup(regen->vnum, regen->lMapIndex, regen->sx, regen->sy, regen->ex, regen->ey, bOnce ? NULL : regen, regen->is_aggressive))
					++regen->count;
			}
		}

		if (ch && !bOnce)
			ch->SetRegen(regen);
	}
}