// DO NOT REMOVE XLAMB INCLUDE
#include <xlamb/xlamb.hpp>

// PLACE NECESSARY INCLUDES HERE
#include <unordered_map>
#include <random>

//------------------------------------------------------------------------------
// Place model-specific code below to be called in xlamb simulator fucntions.
//------------------------------------------------------------------------------

std::default_random_engine rng(0);
std::uniform_real_distribution<> unif(0.0, 1.0);

enum class Strain {
    FLU,
    NUM_STRAINS
};

enum class VaccinationStatus {
    VAXD,
    UNVAXD,
    NUM_VAX_STATUSES
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

struct Vaccination {
    size_t time;
    std::unordered_map<Strain, float> efficacy;
};

struct VaccinationHistory {
    bool is_vaccinated() { return vax_hist.size() > 0; }
    std::vector<Vaccination> vax_hist;
};

void generate_synth_pop(xlamb::Context& context, const size_t pop_size) {
    for (size_t i = 0; i < pop_size; ++i) {
        auto p = context.create_entity("person_" + std::to_string(i));
        auto& s = p.add_component<Susceptibility>();
        s.baseline_susceptibility[Strain::FLU] = 1.0;
        s.current_susceptibility[Strain::FLU]  = 1.0;

        p.add_component<InfectionHistory>();
        p.add_component<VaccinationHistory>();
    }
}

void random_vaccination_campaign(xlamb::Context& context, const double pr_vax, const Vaccination& vax) {
    for (auto [ent, vh, s] : context.each_entity_with<VaccinationHistory, Susceptibility>()) {
        if (unif(rng) < pr_vax) {
            vh.vax_hist.push_back(vax);
            s.current_susceptibility.at(Strain::FLU) *= 1 - vax.efficacy.at(Strain::FLU);
        }
    }
}

void attempt_infection_given_exposure(Susceptibility& s, InfectionHistory& ih, const size_t time) {
    const auto current_suscep = s.current_susceptibility[Strain::FLU];
    if (unif(rng) < static_cast<double>(current_suscep)) {
        ih.inf_hist.push_back({time, Strain::FLU});
        s.current_susceptibility[Strain::FLU] = 0.0;
    }
}

void transmission(xlamb::Context& context, const size_t time) {
    const double pr_exp = context.get_entity("flu_pathogen").get_component<Pathogen>().pr_exposure;
    for (auto [ent, s, ih] : context.each_entity_with<Susceptibility, InfectionHistory>()) {
        if (unif(rng) < pr_exp) {
            attempt_infection_given_exposure(s, ih, time);
        }
    }
}

void tally_infections_by_vax(xlamb::Context& context) {
    std::unordered_map<VaccinationStatus, size_t> inf_ledger;
    inf_ledger[VaccinationStatus::VAXD]   = 0;
    inf_ledger[VaccinationStatus::UNVAXD] = 0;
    for (const auto [ent, s, ih, vh] : context.each_entity_with<Susceptibility, InfectionHistory, VaccinationHistory>()) {
        const auto vaccinated = vh.is_vaccinated();
        const auto infected   = ih.has_been_infected();
        if (infected) {
            if (vaccinated) {
                inf_ledger[VaccinationStatus::VAXD]++;
            } else {
                inf_ledger[VaccinationStatus::UNVAXD]++;
            }
        }
    }

    XLAMB_INFO("Num vax infs:   {}", inf_ledger[VaccinationStatus::VAXD]);
    XLAMB_INFO("Num unvax infs: {}", inf_ledger[VaccinationStatus::UNVAXD]);
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
    auto flu = context.create_entity("flu_pathogen");
    flu.add_component<Pathogen>(Strain::FLU, 0.01);

    generate_synth_pop(context, 100);

    auto vax = Vaccination();
    vax.efficacy[Strain::FLU] = 0.5;

    random_vaccination_campaign(context, 0.5, vax);
}

void simulate(xlamb::Context& context) {
    for (size_t time = 0; time < 200; ++time) {
        transmission(context, time);
    }
}

void report(xlamb::Context& context) {
    tally_infections_by_vax(context);
}