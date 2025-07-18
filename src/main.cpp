#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

enum class Spell {
    FireRune,
    WaterRune,
    WindRune,
    Steam,
    Flame,
    Tornado,
    Explosion
};

std::ostream& operator<<(std::ostream& os, const Spell& s) {
    switch (s) {
        case Spell::FireRune: return os << "FireRune";
        case Spell::WaterRune: return os << "WaterRune";
        case Spell::WindRune: return os << "WindRune";
        case Spell::Steam: return os << "Steam";
        case Spell::Flame: return os << "Flame";
        case Spell::Tornado: return os << "Tornado";
        case Spell::Explosion: return os << "Explosion";
        default: return os << "Unknown";
    }
}

const std::map<Spell, std::vector<Spell>> g_spellBook = {
    {Spell::Steam,     {Spell::FireRune, Spell::WaterRune}},
    {Spell::Flame,     {Spell::FireRune, Spell::FireRune}},
    {Spell::Tornado,   {Spell::WindRune, Spell::WindRune}},
    {Spell::Explosion, {Spell::Flame, Spell::Steam, Spell::Tornado}}
};

class SpellCrafter {
public:
    SpellCrafter(std::vector<Spell> inventory)
        : m_inventory(std::move(inventory)) {}

    bool canCraft(Spell target) {
        std::vector<Spell> copy = m_inventory;
        if (tryCraft(copy, target)) {
            m_inventory = copy;
            return true;
        }
        return false;
    }

private:
    std::vector<Spell> m_inventory;

    bool tryCraft(std::vector<Spell>& bag, Spell target) {
        // BEGIN IMPLEMEMTATION

        for(auto& spell:g_spellBook.at(target)) {
            auto it = std::find(bag.begin(), bag.end(), spell);

            if(it != bag.end()) {
                auto currentSpell = spell;
                bag.erase(it);
            }else if(spell == Spell::WaterRune || spell == Spell::FireRune || spell == Spell::WindRune) {
                return false;
            }else {
                if(!tryCraft(bag, spell)) return false;
            }
        }

        // END IMPLEMENTATION

        return true;
    }
};

int main() {
    SpellCrafter crafter({
        Spell::FireRune, Spell::FireRune, Spell::WaterRune,
        Spell::WindRune, Spell::WindRune
    });

    std::cout << std::boolalpha;
    std::cout << "Can craft Steam?      " << crafter.canCraft(Spell::Steam) << "\n";      // true
    std::cout << "Can craft Flame?      " << crafter.canCraft(Spell::Flame) << "\n";      // true
    std::cout << "Can craft Tornado?    " << crafter.canCraft(Spell::Tornado) << "\n";    // true
    std::cout << "Can craft Explosion?  " << crafter.canCraft(Spell::Explosion) << "\n";  // true
    std::cout << "Can craft Flame again?" << crafter.canCraft(Spell::Flame) << "\n";      // false
}

