#include <xlamb/xlamb.hpp>

#include <unordered_map>
#include <random>

enum class Strain {
    FLU,
    NON_FLU,
    NUM_STRAINS
};

struct Pathogen {
    Strain strain;
    float pr_exposure;
};

struct Susceptibility {
    Susceptibility() {
        baseline_susceptibility[Strain::FLU]     = 1.0;
        baseline_susceptibility[Strain::NON_FLU] = 1.0;
        current_susceptibility[Strain::FLU]      = 1.0;
        current_susceptibility[Strain::NON_FLU]  = 1.0;
    };
    std::unordered_map<Strain, float> baseline_susceptibility;
    std::unordered_map<Strain, float> current_susceptibility;
};

struct Infection {
    size_t time;
    Strain strain;
};

struct InfectionHistory {
    std::vector<Infection> inf_hist;
};

struct Vaccination {
    size_t time;
    std::unordered_map<Strain, float> efficacy;
};

struct VaccinationHistory {
    std::vector<Vaccination> vax_hist;
};

int main() {
    std::default_random_engine rng(0);
    std::uniform_real_distribution<> unif(0.0, 1.0);

    xlamb::Simulator simulator;
    auto& context = simulator.context;

    auto flu = context.create_entity("flu_pathogen");
    flu.add_component<Pathogen>(Strain::FLU, 0.01);

    auto nflu = context.create_entity("nonflu_pathogen");
    nflu.add_component<Pathogen>(Strain::NON_FLU, 0.001);

    for (int i = 0; i < 10; ++i) {
        auto p = context.create_entity("person_" + std::to_string(i));
        p.add_component<Susceptibility>();
        p.add_component<InfectionHistory>();
        p.add_component<VaccinationHistory>();
    }

    auto vax = Vaccination();
    vax.efficacy[Strain::FLU]     = 0.5;
    vax.efficacy[Strain::NON_FLU] = 0.0;

    auto people_to_be_vaxd = context.view_entities_with<VaccinationHistory, Susceptibility>();
    for (auto ent : people_to_be_vaxd) {
        if (unif(rng) < 0.5) {
            auto [vh, s] = people_to_be_vaxd.get(ent);
            vh.vax_hist.push_back(vax);
            s.current_susceptibility.at(Strain::FLU) *= vax.efficacy.at(Strain::FLU);
            s.current_susceptibility.at(Strain::NON_FLU) *= vax.efficacy.at(Strain::NON_FLU);
        }
    }

    auto synth_pop = context.view_entities_with<Susceptibility>();
    for (auto ent : synth_pop) {
        auto [s] = synth_pop.get(ent);
        const auto curr_suscep = s.current_susceptibility.at(Strain::FLU);
        XLAMB_TRACE("entity flu suscep = {}", curr_suscep);
    }

    auto pathogens = context.view_entities_with<Pathogen>();
    for (auto ent : pathogens) {
        auto [path] = pathogens.get(ent);
        auto strain = (path.strain == Strain::FLU) ? "flu" : "non_flu";
        XLAMB_TRACE("pathogen {}: Pr(exposure) = {}", strain, path.pr_exposure);
    }

/* API PLANNING

    # in user main.cpp
    int main(int argc, char* argv[]) {
        xlamb::simulator app(argc, argv);
        return app.run();
    }

    # xlamb::simulator::run() plan
      # read config files
      # read from database (single or batch)
      # set up/run simulation(s)
      # calculate metrics + save to file/database

*/

    return EXIT_SUCCESS;
}