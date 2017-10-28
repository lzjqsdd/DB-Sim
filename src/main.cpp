#include <iostream>
#include <cstdio>

#include "./core/agent.h"
#include "./core/link.h"
#include "./core/node.h"
#include "./core/config.h"

#include "./utils/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

int main()
{
    cout << "fight!!!" << endl;

    //load config
    XMLDocument doc;
    doc.LoadFile("../config/path.xml");

    XMLElement * pathListElement = doc.FirstChildElement("pathlist");

    XMLElement * pathElement= pathListElement->FirstChildElement("path");

    XMLElement *linkElement = pathElement->FirstChildElement("link");

    XMLElement *speedElement = linkElement->FirstChildElement("maxspeed");

    XMLText* speedNode = speedElement->FirstChild()->ToText();

    printf("speed is : %s\n",speedNode->Value());
    //build network
    //init evacuation demand
    //do simulation per step
    //calc time
}
