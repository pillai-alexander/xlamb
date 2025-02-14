#include <xlamb/simulator.hpp>

#include <xlamb/context.hpp>

namespace xlamb {

void Simulator::bind(std::function<void(xlamb::Context&)> f_setup,
                     std::function<void(xlamb::Context&)> f_sim,
                     std::function<void(xlamb::Context&)> f_report) {
    setup    = f_setup;
    simulate = f_sim;
    report   = f_report;
}

int Simulator::run() {
    setup(context);
    simulate(context);
    report(context);

    return EXIT_SUCCESS;
}

} // namespace xlamb