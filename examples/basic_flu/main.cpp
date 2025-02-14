#include <xlamb/xlamb.hpp>
#include "model.hpp"

int main() {
    xlamb::Simulator sim;
    sim.bind(setup, simulate, report);
    return sim.run();

/* API PLANNING

    # in user main.cpp
    int main(int argc, char* argv[]) {
        xlamb::simulator app(argc, argv);
        return app.run(setup, simulate, report);
    }

    # xlamb::simulator::run() plan
      # read config files
      # read from database (single or batch)
      # set up/run simulation(s)
      # calculate metrics + save to file/database

*/
}