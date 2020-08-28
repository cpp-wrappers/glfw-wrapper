#include <cxx_exec/environment.hpp>
#include <string>
#include <vector>
#include "clap/gnu_clap.hpp"
#include "cxx_exec/build/configuration.hpp"
#include "cxx_exec/build/build.hpp"
#include "cxx_exec/environment.hpp"

using namespace std;
using namespace filesystem;

void exec(vector<string> args) {
    string conf_name;

    gnu::clap{}.value("configuration", conf_name).parse(args);

    auto cc = environment::cxx_compile_command_builder();
    cc.std(gcc_like_driver::cxx20);
    cc.include({"include", "../unified-math/include"});
    configuration::by_name(conf_name).apply(cc);

    path build_conf = path{"build"}/conf_name;
    path objects = build_conf/"objects";

    source_set{}.include("src", ".cpp")
        .compile_to_objects(objects, cc)
        .to_thin_static_lib(build_conf, "glfw-wrapper");
}