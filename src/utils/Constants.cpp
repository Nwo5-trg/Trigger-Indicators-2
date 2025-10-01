#include "Constants.hpp"

using namespace geode::prelude;

namespace Constants {
    void loadConstants() {
        auto path = string::pathToString(Mod::get()->getConfigDir() / "constants.json");
        if (!std::filesystem::exists(path)) return;

        std::ifstream file(path);
        auto parseJson = matjson::parse(file);
        if (!parseJson.isOk()) return;
        auto json = parseJson.unwrap();
        if (!json.isObject()) return;

        for (auto& [id, values] : json) {
            if (!setConstantsFunctions.contains(id)) continue;;
            if (!values.contains("value")) continue;
            auto& value = values["value"];
            setConstantsFunctions[id](value);
        }
    }

    void setColor(ccColor4F& constant, const matjson::Value& value) {
        if (!value.isArray()) return;
        auto col = value.asArray().unwrap();
        if (col.size() != 4) return;
        setFloat(constant.r, col[0]);
        setFloat(constant.g, col[1]);
        setFloat(constant.b, col[2]);
        setFloat(constant.a, col[3]);
    }
    void setInt(int& constant, const matjson::Value& value) {
        if (!value.isExactlyInt()) return;
        constant = value.asInt().unwrap();
    }
    void setUInt(int& constant, const matjson::Value& value) {
        if (!value.isExactlyUInt()) return;
        constant = value.asUInt().unwrap();
    }
    void setFloat(float& constant, const matjson::Value& value) {
        if (!value.isNumber()) return;
        constant = value.asDouble().unwrap();
    }
}