#include "stdafx.h"
#ifdef __ENABLE_MONSTER_CONTROLLER__
#include "MonsterController.hpp"
#include "mob_manager.h"
#include "desc.h"
#include "desc_manager.h"
#include "buffer_manager.h"

namespace MonsterControllerNS {
    std::optional<eCounterTypes> GetCounterType(const uint32_t& vnum) {
        if (vnum == 0) return std::nullopt;

        auto pMobData = CMobManager::Instance().Get(vnum);
        if (!pMobData) return std::nullopt;

        static const std::unordered_map<uint8_t, eCounterTypes> mMonsterValidator = {
            {MOB_RANK_BOSS, eCounterTypes::MONSTER_COUNTER_BOSS},
            {MOB_RANK_KING, eCounterTypes::MONSTER_COUNTER_KING}
        };

        if (pMobData->m_table.bType == CHAR_TYPE_MONSTER) {
            auto fIT = mMonsterValidator.find(pMobData->m_table.bRank);
            if (fIT != mMonsterValidator.end())
                return fIT->second;
        }

        if (pMobData->m_table.bType == CHAR_TYPE_STONE)
            return eCounterTypes::MONSTER_COUNTER_STONES;

        return std::nullopt;
    }
};

void CMonsterController::SendCounter(CHARACTER* ch) const {
    if (!ch) return;

    for (const auto key : {MonsterControllerNS::eCounterTypes::MONSTER_COUNTER_STONES, MonsterControllerNS::eCounterTypes::MONSTER_COUNTER_BOSS}) {
        ch->ChatPacket(CHAT_TYPE_COMMAND, "MonsterControllerCRegister %d %d", key, RequestCounter(ch->GetMapIndex(), key));
    }
}

void CMonsterController::BroadcastCounter(uint16_t index) const {
    const auto& clientSet = DESC_MANAGER::instance().GetClientSet();
    for (const auto& desc : clientSet) {
        if (desc->GetCharacter() && desc->GetCharacter()->GetMapIndex() == index) {
            SendCounter(desc->GetCharacter());
        }
    }
}

void CMonsterController::HandleCounter(CHARACTER* ch, uint16_t index, bool remove) {
    if (!ch) return;

    auto [unsetIT, inserted] = monsterCounter_.try_emplace(index, MonsterControllerNS::aMonsterCounter());

    auto counterType = MonsterControllerNS::GetCounterType(ch->GetRaceNum());
    if (!counterType) return;

    auto& counterSet = unsetIT->second.at(counterType.value());

    if (!remove) {
        counterSet.insert(ch->GetVID());
    } else {
        counterSet.erase(ch->GetVID());
    }

    BroadcastCounter(index);
}

size_t CMonsterController::RequestCounter(uint16_t index, MonsterControllerNS::eCounterTypes type) const noexcept {
    auto fIT = monsterCounter_.find(index);
    if (fIT == monsterCounter_.end()) return 0;

    return fIT->second.at(type).size();
}
#endif
