//
// Created by sooda on 16/6/16.
//

#include "pugixml/pugixml.hpp"
#include "features/LanguageFeatureProcessors.h"
#include "common/util.h"

namespace cppmary {
    Phone::Phone(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> segmentNavigator) :
            FeatureProcessor(name, possibleValues, segmentNavigator) {
    }

    Phone::~Phone() { }

    int Phone::process(Target target) {
        pugi::xml_node segment = navigator_->getElement(target);
        int pauseValue = translator_.getValue("_");
        if (segment.empty()) {
            //can get pausesymbol here?
            return pauseValue;
        }
        if (strcmp(segment.name(), "ph")) {
            return pauseValue;
        }
        std::string ph = segment.attribute("p").as_string();
        if (!translator_.contain(ph)) {
            //what does this mean?
            return translator_.getValue("0");
        }
        return translator_.getValue(ph);
    }

    /*
     * pos
     */
    Pos::Pos(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> wordNavigator) :
            FeatureProcessor(name, possibleValues, wordNavigator) {
    }

    Pos::~Pos() {}

    int Pos::process(Target target) {
        pugi::xml_node word = navigator_->getElement(target);
        if (word.empty()) {
            return 0;
        }
        std::string pos = word.attribute("pos").as_string();
        if (pos.empty()) {
            return 0;
        }
        pos = trim(pos);
        return translator_.getValue(pos);
    }

    /*
     * Zhtone
     */

    Zhtone::Zhtone(std::string name, std::vector<std::string> possibleValues, std::shared_ptr<TargetElementNavigator> navigator) :
        FeatureProcessor(name, possibleValues, navigator) {
    }

    Zhtone::~Zhtone() {}

    int Zhtone::process(Target target) {
        pugi::xml_node syllable = navigator_->getElement(target);
        if (syllable.empty()) {
            return 0;
        }
        std::string tone = syllable.attribute("zhtone").as_string();
        if (tone.empty()) {
            return 0;
        }
        return translator_.getValue(tone);
    }

}

