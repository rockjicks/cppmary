//
// Created by sooda on 16/6/27.
//

#ifndef CPPMARY_LABELGENERATOR_H
#define CPPMARY_LABELGENERATOR_H
#include "features.h"

namespace cppmary {
    class LabelGenerator : public InterModules {
    public:
        LabelGenerator(FeatureProcessorManager* manager, TargetFeatureComputer* featureComputer, const std::string& featureMapName);
        virtual ~LabelGenerator();
        virtual std::string process(std::string input);
        std::vector<Target> createTargetWithPauses(std::vector<pugi::xml_node> segmentsAndPauses,
                                                   std::string pauseSymbol);
    private:
        FeatureProcessorManager *manager_;
        TargetFeatureComputer *featureComputer_;
        std::vector<std::string> featureName_;
        std::vector<std::string> featureAlias_;
    };
}

#endif //CPPMARY_LABELGENERATOR_H