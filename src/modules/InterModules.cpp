//
// Created by sooda on 16/6/30.
//

#include <modules/InterModules.h>

namespace cppmary {
    InterModules::InterModules() { }
    InterModules::~InterModules() {
        XLOG(INFO) << "deconstruct module " << name_;
    }
}