//
// Created by sooda on 16/6/8.
//

#ifndef CPPMARY_MARYXML_H
#define CPPMARY_MARYXML_H
#include "pugixml/pugixml.hpp"
#include <string>

namespace cppmary {
    struct xml_string_writer : pugi::xml_writer {
        std::string result;
        virtual void write(const void *data, size_t size) {
            result.append(static_cast<const char *>(data), size);
        }
    };
    class MaryXml {
    public:
        static std::string getMaryXmlHeaderWithLocale(std::string locale);
        static std::string saveDoc2String(const pugi::xml_document& doc);
        static void appendChild(pugi::xml_node doc, std::string childName);
        static bool hasAttribute(const pugi::xml_node& node, const std::string& attributeName);
        static bool isAncestor(pugi::xml_node ancestor, pugi::xml_node node);
        static pugi::xml_node getAncestor(pugi::xml_node node, std::string ancestorName);
        static pugi::xml_node getClosetAncestorWithAttribute(pugi::xml_node node, std::string ancestorName, std::string attributeName);
        static pugi::xml_node closestCommonAncestor(pugi::xml_node first, pugi::xml_node last);
        static pugi::xml_node encloseNodesWithNewElement(pugi::xml_node first, pugi::xml_node last, std::string newElementName);


    };
}


#endif //CPPMARY_MARYXML_H
