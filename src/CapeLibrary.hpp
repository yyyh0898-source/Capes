
#pragma once

#include <algorithm>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace bedrock::capes {

struct Cape {
    std::string id;
    std::string name;
    std::string texture_path;
    std::string source;
    bool available = false;
};

class CapeLibrary {
public:
    CapeLibrary() {
        add({"classic", "Classic Cape",
             "textures/capes/classic",
             "local_resource_pack", true});

        add({"crimson", "Crimson Cape",
             "textures/capes/crimson",
             "local_resource_pack", true});

        add({"midnight", "Midnight Cape",
             "textures/capes/midnight",
             "local_resource_pack", true});

        add({"emerald", "Emerald Cape",
             "textures/capes/emerald",
             "local_resource_pack", true});
    }

    void add(Cape cape) {
        if (cape.id.empty())
            return;

        const auto id = cape.id;
        capes_[id] = std::move(cape);
    }

    bool remove(const std::string& id) {
        if (equipped_ == id)
            equipped_.clear();

        return capes_.erase(id) != 0;
    }

    std::vector<Cape> list() const {
        std::vector<Cape> result;
        result.reserve(capes_.size());

        for (const auto& entry : capes_)
            result.push_back(entry.second);

        std::sort(result.begin(), result.end(),
            [](const Cape& a, const Cape& b) {
                return a.name < b.name;
            });

        return result;
    }

    std::optional<Cape> find(
        const std::string& id) const {

        const auto it = capes_.find(id);

        if (it == capes_.end())
            return std::nullopt;

        return it->second;
    }

    bool equip(const std::string& id) {
        const auto it = capes_.find(id);

        if (it == capes_.end() ||
            !it->second.available) {
            return false;
        }

        equipped_ = id;
        return true;
    }

    void unequip() {
        equipped_.clear();
    }

    std::optional<Cape> equipped() const {
        if (equipped_.empty())
            return std::nullopt;

        return find(equipped_);
    }

private:
    std::unordered_map<std::string, Cape> capes_;
    std::string equipped_;
};

} // namespace bedrock::capes
