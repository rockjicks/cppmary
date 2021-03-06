//
// Created by sooda on 16/6/12.
//
#include "modules/Phonemiser.cpp"
#include "modules/TextToMaryXml.cpp"
#include "modules/Tokenizer.cpp"
#include "modules/Prosody.cpp"
#include "modules/Pronunciation.cpp"
#include "modules/LabelGenerator.cpp"
#include "modules/HtsEngine.cpp"
#include "modules/InterModules.cpp"

#include "common/convertPinyin.cpp"
#include "common/MaryXml.cpp"
#include "common/util.cpp"
#include "common/JiebaSegment.cpp"
#include "common/Lexicon.cpp"
#include "common/ReferenceCounted.cpp"



#include "features/FeatureProcessorManager.cpp"
#include "features/GenericFeatureProcessors.cpp"
#include "features/Target.cpp"
#include "features/TargetElementNavigator.cpp"
#include "features/FeatureProcessor.cpp"
#include "features/TargetFeatureComputer.cpp"
#include "features/Allophone.cpp"
#include "features/AllophoneSet.cpp"
#include "features/LanguageFeatureProcessors.cpp"
#include "features/StringTranslator.cpp"
#include "features/PhoneTranslator.cpp"

#include "hts_engine/HTS_audio.c"
#include "hts_engine/HTS_engine.c"
#include "hts_engine/HTS_gstream.c"
#include "hts_engine/HTS_label.c"
#include "hts_engine/HTS_misc.c"
#include "hts_engine/HTS_model.c"
#include "hts_engine/HTS_pstream.c"
#include "hts_engine/HTS_sstream.c"
#include "hts_engine/HTS_vocoder.c"
