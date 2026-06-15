#pragma once

#include <string>
#include <vector>

// Forward declaration only — SaveManager just calls through a MapComponent*
// it's handed; it doesn't own or construct one.
class MapComponent;

// ============================================================
//  SaveManager
//  Snapshots/restores the existing singletons (CharacterManager,
//  Inventory, GameFlags, Party composition, current map/unlocks)
//  to/from Assets/Saves/slotN.sav using the project's existing
//  |-delimited text convention.
//
//  Design notes:
//  - loadFromSlot mutates existing Character objects in place (via the
//    float& getters and StatsModule setters) rather than replacing them,
//    so shared_ptrs held by Party/CombatState/etc. stay valid. This means
//    an in-game load from the pause menu doesn't require recreating
//    TravelState.
//  - Map/unlock state needs a live MapComponent to apply directly. If
//    loadFromSlot is called with map == nullptr (loading from the main
//    menu, before any TravelState exists), the map state is stashed as
//    "pending" — TravelState's constructor should call
//    applyPendingMapState() right after building its MapComponent.
// ============================================================

class SaveManager
{
public:
    static SaveManager& getInstance()
    {
        static SaveManager instance;
        return instance;
    }

    SaveManager(const SaveManager&) = delete;
    SaveManager& operator=(const SaveManager&) = delete;

    static constexpr int maxSlots = 10;

    // Writes the current game state to Assets/Saves/slotN.sav.
    // `map` should be the active TravelState's MapComponent (saving is
    // only reachable from the pause menu, so this should never be null
    // in practice — but the call is guarded anyway).
    bool saveToSlot(int slot, MapComponent* map);

    // Reads Assets/Saves/slotN.sav and restores it into the existing
    // singletons. `map` may be null (main-menu load) — see class comment.
    // Returns false if the slot doesn't exist or can't be opened; in that
    // case nothing is mutated.
    bool loadFromSlot(int slot, MapComponent* map);

    // Lightweight peek at a slot's [META] + character levels for the slot
    // picker UI. Doesn't touch any singletons.
    struct SlotSummary
    {
        bool exists = false;
        std::string location;
        std::string timestamp;
        int partyLevel = 0; // highest character level found in the save
    };
    SlotSummary getSlotSummary(int slot) const;

    // True if loadFromSlot stashed map/unlock state because no
    // MapComponent was available at load time.
    bool hasPendingMapState() const { return this->pendingMapStateValid; }

    // Applies and clears any pending map/unlock state. Safe to call even
    // if there's nothing pending (no-op). Call this from TravelState's
    // constructor right after constructing its MapComponent.
    void applyPendingMapState(MapComponent* map);

private:
    SaveManager() = default;

    std::string slotPath(int slot) const;

    bool pendingMapStateValid = false;
    std::string pendingMapId;
    std::vector<std::string> pendingUnlockedMapIds;
};