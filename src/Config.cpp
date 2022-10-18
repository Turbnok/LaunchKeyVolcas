#include <Config.hpp>
#include <yaml-cpp/yaml.h>
#include <midi.hpp>
#include <fstream>

MidiChannel
Config::keyChannel = MidiChannel::CH1;

YAML::Node
Config::config = YAML::LoadFile("config.yml");

void
Config::init(){
    Config::keyChannel = static_cast<MidiChannel>(config["KEYS_CHANNEL"].as<int>());
}

void
Config::setAsInt(std::string pKey, int pValue){
    config[pKey] = pValue;
    std::ofstream fout("config.yml");
    fout <<  Config::config; 
}

int
Config::getAsInt(std::string pKey){
     //   std::cout << "Last logged in: " << config["hop"].as<int>() << "\n";
     return config[pKey].as<int>();// = pValue;
    
 }