#pragma once
#include <yaml-cpp/yaml.h>
#include <midi.hpp>
// #include <ScreenState.hpp>
// #include <Screen.hpp>
// #include <Sequencer.hpp>


class Config
{
    public:
		static void setAsInt(std::string pKey, int pValue);
        static int getAsInt(std::string pKey);
        static void init();
        //YAML::Node get(std::string pKey);
        static MidiChannel keyChannel;
		    static YAML::Node config; 
    private:
};
