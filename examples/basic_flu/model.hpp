// DO NOT REMOVE XLAMB INCLUDE
#include <xlamb/xlamb.hpp>

// PLACE NECESSARY INCLUDES HERE
#include <unordered_map>

//------------------------------------------------------------------------------
// Place model-specific code below to be called in xlamb simulator fucntions.
//------------------------------------------------------------------------------

enum class Strain {
    FLU,
    NUM_STRAINS
};

struct Pathogen {
    Strain strain;
    float pr_exposure;
};

struct Susceptibility {
    std::unordered_map<Strain, float> baseline_susceptibility;
    std::unordered_map<Strain, float> current_susceptibility;
};

struct Infection {
    size_t time;
    Strain strain;
};

struct InfectionHistory {
    bool has_been_infected() { return inf_hist.size() > 0; }
    std::vector<Infection> inf_hist;
};

void generate_synth_pop(xlamb::Context& context, const size_t pop_size) {
    for (size_t i = 0; i < pop_size; ++i) {
        auto p = context.create_entity("person_" + std::to_string(i));
        auto& s = p.add_component<Susceptibility>();
        s.baseline_susceptibility[Strain::FLU] = 1.0;
        s.current_susceptibility[Strain::FLU]  = 1.0;

        p.add_component<InfectionHistory>();
    }
}

void attempt_infection_given_exposure(xlamb::Context& context, Susceptibility& s, InfectionHistory& ih, const size_t time) {
    auto rng = context.get_rng();
    const auto current_suscep = s.current_susceptibility[Strain::FLU];

    if (rng->unif("def") < static_cast<double>(current_suscep)) {
        ih.inf_hist.push_back({time, Strain::FLU});
        s.current_susceptibility[Strain::FLU] = 0.0;
    }
}

void transmission(xlamb::Context& context, const size_t time) {
    auto rng = context.get_rng();
    const double pr_exp = context.get_entity("flu_pathogen").get_component<Pathogen>().pr_exposure;

    for (auto [ent, s, ih] : context.each_entity_with<Susceptibility, InfectionHistory>()) {
        if (rng->unif("def") < pr_exp) {
            attempt_infection_given_exposure(context, s, ih, time);
        }
    }
}

void tally_infections_by_vax(xlamb::Context& context) {
    size_t num_infections = 0;
    for (const auto [ent, s, ih] : context.each_entity_with<Susceptibility, InfectionHistory>()) {
        const auto infected   = ih.has_been_infected();
        if (infected) num_infections++;
    }

    XLAMB_INFO("Number of infections:   {}", num_infections);
}

//------------------------------------------------------------------------------
// XLAMB SIMULATOR FUNCTIONS: DO NOT ALTER FUNCTION ARGUMENTS
//
// Place model-specific code inside these functions.
//
// setup() is designed for running code that is necessary to setup a simulation
// or that needs to be run before the simulation time-steps begin.
//
// simulate() holds the main simulation loop and should be used to run code that
// needs to be executed each time step.
//
// report() should be used to cleanup after a simulation (if necessary) and to
// calculate user-desired metrics to be saved in CSV/SQLite.
//------------------------------------------------------------------------------

void setup(xlamb::Context& context) {
    auto rng = context.get_rng();
    rng->create_generator("def");
    rng->set_seed("def", 0);

    auto flu = context.create_entity("flu_pathogen");
    flu.add_component<Pathogen>(Strain::FLU, 0.01);

    generate_synth_pop(context, 100);
}

void simulate(xlamb::Context& context) {
    for (size_t time = 0; time < 200; ++time) {
        transmission(context, time);
    }
}

void report(xlamb::Context& context) {
    tally_infections_by_vax(context);
}