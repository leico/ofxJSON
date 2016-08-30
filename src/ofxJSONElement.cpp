#include "ofxJSONElement.h"


ofxJSONElement::ofxJSONElement()
{
}


ofxJSONElement::ofxJSONElement(const Json::Value& v): Json::Value(v)
{
}


ofxJSONElement::ofxJSONElement(const std::string& jsonString)
{
    parse(jsonString);
}


ofxJSONElement::~ofxJSONElement()
{
}


bool ofxJSONElement::parse(const std::string& jsonString)
{
    Json::Reader reader;

    if (!reader.parse( jsonString, *this ))
    {
        ofLogError("ofxJSONElement::parse") << "Unable to parse string: " << reader.getFormattedErrorMessages();
        return false;
    }

    return true;
}


bool ofxJSONElement::open(const string& filename)
{
    if (filename.find("http://") == 0 || filename.find("https://") == 0)
    {
        return openRemote(filename);
    }
    else
    {
        return openLocal(filename);
    }
}


bool ofxJSONElement::openLocal(const std::string& filename)
{
    ofBuffer buffer = ofBufferFromFile(filename);

    Json::Reader reader;

    if (!reader.parse(buffer.getText(), *this))
    {
        ofLogError("ofxJSONElement::openLocal") << "Unable to parse " << filename << ": " << reader.getFormattedErrorMessages();
        return false;
    }
    else
    {
        return true;
    }
}


bool ofxJSONElement::openRemote(const std::string& filename)
{
    std::string result = ofLoadURL(filename).data.getText();

    Json::Reader reader;

    if (!reader.parse(result, *this))
    {
        ofLogError("ofxJSONElement::openRemote") << "Unable to parse " << filename << ": " << reader.getFormattedErrorMessages();
        return false;
    }

    return true;
}


bool ofxJSONElement::save(const std::string& filename, bool pretty) const
{
    ofFile file;

    if (!file.open(filename, ofFile::WriteOnly))
    {
        ofLogError("ofxJSONElement::save") << "Unable to open " << file.getAbsolutePath() << ".";
        return false;
    }

    if (pretty)
    {
        Json::StyledWriter writer;
        file << writer.write( *this ) << endl;
    } else {
        Json::FastWriter writer;
        file << writer.write( *this ) << endl;
    }

    ofLogVerbose("ofxJSONElement::save") << "JSON saved to " << file.getAbsolutePath() << ".";

    file.close();

    return true;
}


std::string ofxJSONElement::getRawString(bool pretty) const
{
    std::string raw;

    if (pretty)
    {
        Json::StyledWriter writer;
        raw = writer.write(*this);
    }
    else
    {
        Json::FastWriter writer;
        raw = writer.write(*this);
    }

    return raw;
}

std::string ofxJSONElement::toString(Json::ValueType type)
{
    switch (type)
    {
        case Json::nullValue:
            return "null";
        case Json::intValue:
            return "integer";
        case Json::uintValue:
            return "unsigned integer";
        case Json::realValue:
            return "double";
        case Json::stringValue:
            return "string";
        case Json::booleanValue:
            return "boolean";
        case Json::arrayValue:
            return "array";
        case Json::objectValue:
            return "object";
        default:
            ofLogError("ofxJSONElement::toString") << "Unknown Json::ValueType.";
            return "unknown";
    }
}



/* ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| *
 * ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| *
 * |||   Convert Series   |||||||||||||||||||||||||||||||||||||||| *
 * ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| *
 * ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */

/* =============================================================== *
 * const ofxJSONElement Convert(const ofPoint &data);              *
 * =============================================================== */
const ofxJSONElement ofxJSONElement :: Convert(const ofPoint& data){
  ofxJSONElement json;

  json["x"] = data.x;
  json["y"] = data.y;
  json["z"] = data.z;

  return json;
}

/* =============================================================== *
 * const ofxJSONElement Convert(const ofVec2f &data);              *
 * =============================================================== */
const ofxJSONElement ofxJSONElement :: Convert(const ofVec2f& data){
  ofxJSONElement json;

  json["x"] = data.x;
  json["y"] = data.y;

  return json;
}

/* =============================================================== *
 * const ofxJSONElement Convert(const ofRectangle &data);          *
 * =============================================================== */
const ofxJSONElement ofxJSONElement :: Convert(const ofRectangle& data){
  ofxJSONElement json;

  json["x"]      = data.x;
  json["y"]      = data.y;
  json["width"]  = data.width;
  json["height"] = data.height;

  return json;
}

