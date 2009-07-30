#ifndef SETTINGS_H
#define SETTINGS_H

#include <boost/program_options.hpp>
#include <string>

namespace ppa{

class Settings
{
//    boost::program_options::options_description desc;
    boost::program_options::variables_map vm;
public:
    Settings();
    int read_command_line_arguments(int argc, char *argv[]);

    bool is(std::string name) { return vm.count(name); }
    const boost::program_options::variable_value & get(const std::string & name) const { return vm[name]; }

    void info();
    boost::program_options::options_description desc;

    static int noise;
    static float resize_factor;
};

}
#endif // SETTINGS_H
