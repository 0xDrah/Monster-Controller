## Add

#ifdef __ENABLE_MONSTER_CONTROLLER__
#include "MonsterController.hpp"
#endif

## After

void CHARACTER_MANAGER::DestroyCharacter(LPCHARACTER ch)
{
	if (!ch)
		return;

	auto it = m_map_pkChrByVID.find(ch->GetVID());
	if (it == m_map_pkChrByVID.end()) {
		sys_err("[CHARACTER_MANAGER::DestroyCharacter] <Factor> %d not found", (long)(ch->GetVID()));
		return;
	}

## Add

#ifdef __ENABLE_MONSTER_CONTROLLER__
	if (!ch->IsPC() && MonsterControllerNS::GetCounterType(ch->GetRaceNum()))
		CMonsterController::instance().HandleCounter(ch, ch->GetMapIndex(), true);
#endif