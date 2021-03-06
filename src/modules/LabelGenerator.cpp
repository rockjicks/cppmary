//
// Created by sooda on 16/6/27.
//

#include "modules/LabelGenerator.h"
#include "common.h"

namespace cppmary {
    LabelGenerator::LabelGenerator(std::shared_ptr<FeatureProcessorManager> manager, std::shared_ptr<TargetFeatureComputer> featureComputer, std::vector<std::string> featureName, std::vector<std::string> featureAlias, std::shared_ptr<PhoneTranslator> phoneTranslator) {
        name_ = "LabelGenerator";
        manager_ = manager;
        featureComputer_ = featureComputer;
        featureName_ = featureName;
        featureAlias_ = featureAlias;
        phoneTranslator_ = phoneTranslator;
    }
    LabelGenerator::~LabelGenerator() {
    }

    std::string LabelGenerator::process(const std::string& input) {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_string(input.c_str());
        phone_boundary_walker tw;
        doc.traverse(tw);
        std::vector<Target> targets = createTargetWithPauses(tw.nodes_, "_");
        std::string label = "";
        for (int i = 0; i < targets.size(); i++) {
            Target target = targets[i];
            std::map<std::string, std::pair<int, std::string> > detail;
            std::vector<int> features = featureComputer_->computeFeatureVector(target, &detail);
//            std::cout << target.getName() << "\t" ;
//            std::map<std::string, std::pair<int, std::string> >::iterator iter;
//            for (iter = detail.begin(); iter != detail.end(); iter++) {
//                std::cout << iter->first << " " << iter->second.first << " " << iter->second.second << std::endl;
//            }
//            std::cout << std::endl << std::endl;
            //construct label string
            //need to repalce trickyphone, repalce punc, replace tobi
            std::string prevPrevPhone = detail["prev_prev_phone"].second;
            std::string prevPhone = detail["prev_phone"].second;
            std::string phone = detail["phone"].second;
            std::string nextPhone = detail["next_phone"].second;
            std::string nextNextPhone = detail["next_next_phone"].second;

            if (phoneTranslator_ != NULL) {
                prevPrevPhone = phoneTranslator_->replaceTrickyPhones(prevPrevPhone);
                prevPhone = phoneTranslator_->replaceTrickyPhones(prevPhone);
                phone = phoneTranslator_->replaceTrickyPhones(phone);
                nextPhone = phoneTranslator_->replaceTrickyPhones(nextPhone);
                nextNextPhone = phoneTranslator_->replaceTrickyPhones(nextNextPhone);
            }

            label = label + prevPrevPhone + "^" + prevPhone + "-" + phone + "+" + nextPhone + "=" + nextNextPhone + "|";
            for (int i = 0; i < featureName_.size(); i++) {
                std::string featureName = featureName_[i];
                std::string featureAlias = featureAlias_[i];
                std::map<std::string, std::string>::iterator iter;
                std::map<std::string, std::pair<int, std::string> >::iterator detail_iterator;
                detail_iterator = detail.find(featureName);
                std::string featureValue;
                if (detail_iterator != detail.end()) {
                    featureValue = detail[featureName].second;
                    if (featureName == "sentence_punc" || featureName == "prev_punctuation" || featureName == "next_punctuation") {
                        featureValue = phoneTranslator_->replacePunc(featureValue);
                    } else if (featureName.find("tobi_") != std::string::npos) {
                        featureValue = phoneTranslator_->replaceToBI(featureValue);
                    }
                } else {
                    XLOG(ERROR) << featureName << " has no feature processor";
                    featureValue = "0";
                }
                label = label + "|" + featureAlias + "=" + featureValue;
            }
            label = label + "||\n";
        }
        XLOG(INFO) << label;
        return label;
    }


    std::vector<Target> LabelGenerator::createTargetWithPauses(std::vector<pugi::xml_node> segmentsAndPauses,
                                               std::string pauseSymbol) {
        std::vector<Target> targets;
        if (segmentsAndPauses.size() == 0) {
            return targets;
        }
        //TODO: add final boundary
        for (int i = 0; i < segmentsAndPauses.size(); i++) {
            pugi::xml_node seg = segmentsAndPauses[i];
            std::string phone = seg.attribute("p").as_string();
            if (phone == "") {
                phone = pauseSymbol;
            }
            Target temp(phone, seg);
            targets.push_back(temp);
        }
        return targets;
    }
}
