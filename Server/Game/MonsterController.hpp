#include "../../common/service.h"
#ifdef __ENABLE_MONSTER_CONTROLLER__
#include "../../common/singleton.h"

#include "char.h"
#include "constants.h"

#include <unordered_set>
#include <unordered_map>
#include <array>
#include <optional>

namespace MonsterControllerNS {
    enum eCounterTypes : uint8_t {
        MONSTER_COUNTER_STONES,
        MONSTER_COUNTER_BOSS,
        MONSTER_COUNTER_KING,
        MONSTER_COUNTER_MAX_NUM
    };

    using aMonsterCounter = std::array<std::unordered_set<uint32_t>, eCounterTypes::MONSTER_COUNTER_MAX_NUM>;
    using mMonsterCounter = std::unordered_map<uint16_t, aMonsterCounter>;

    std::optional<eCounterTypes> GetCounterType(const uint32_t& vnum);
};

class CMonsterController : public singleton<CMonsterController> {
    public:
        CMonsterController() = default;
        virtual ~CMonsterController() = default;

        void SendCounter(CHARACTER* ch) const;
        void BroadcastCounter(uint16_t index) const;
        void HandleCounter(CHARACTER* ch, uint16_t index, bool remove = false);

        size_t RequestCounter(uint16_t index, MonsterControllerNS::eCounterTypes type) const noexcept;

    private:
        MonsterControllerNS::mMonsterCounter monsterCounter_;
};
#endif
