//
// Created by sooda on 16/6/15.
//

#ifndef CPPMARY_TARGETFEATURECOMPUTER_H
#define CPPMARY_TARGETFEATURECOMPUTER_H
#include <vector>
#include "FeatureProcessorManager.h"
#include "FeatureProcessor.h"
#include <memory>

namespace cppmary {
    class TargetFeatureComputer {
    public:
        TargetFeatureComputer(std::shared_ptr<FeatureProcessorManager> manager, std::string featuresProcessorNames);
        TargetFeatureComputer(std::shared_ptr<FeatureProcessorManager> manager, std::vector<std::string> featureNamesVec);
        void init(std::shared_ptr<FeatureProcessorManager> manager, std::vector<std::string> featureNamesVec);
        ~TargetFeatureComputer();
        //Feature vector 暂时用std::vector<int>保存
        std::vector<int> computeFeatureVector(Target target, std::map<std::string, std::pair<int, std::string> > *detail = NULL);
        std::string toStringValue(std::vector<int> featureVector);
        std::string getFeatureValue(int processorIndex, int feature);
    private:
        std::vector<std::shared_ptr<FeatureProcessor> > processor_;
    };

}

#endif //CPPMARY_TARGETFEATURECOMPUTER_H
