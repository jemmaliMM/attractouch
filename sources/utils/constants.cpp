#include "utils/constants.h"

namespace AT {

    Constants::Constants()
    {
        XML::Constants *xmlConstants = NULL;
        try {
            xmlConstants = XML::constants("content/constants.xml").release();
        } catch(xml_schema::Exception& ex) {
            std::cout << ex << std::endl;
            throw;
        }

        if(xmlConstants != NULL) {
            fingerRadius = xmlConstants->fingerRadius();
            firstLevel = xmlConstants->firstLevel();
        }
    }

    Constants& Constants::Instance()
    {
        static Constants instance;
        return instance;
    }
}