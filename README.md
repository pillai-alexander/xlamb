# xlamb
e**X**tensible **L**azy **A**gent-based **M**odel **B**uilder

![linux](https://github.com/pillai-alexander/xlamb/actions/workflows/linux.yml/badge.svg)


## Goal: basic framework for rapid development of user-configurable and user-scriptable agent-based (or individual-based) simulation models in C++
**High-level goals**

- core "engine" that handles reading parameters, performing the simulation, and writing desired metrics
- performant storage of simulation elements via ECS-like architecture
- user-defined parameters and metrics in configuration files
- user-scriptable model elements and metric calculations
  - define entities and components
  - define logic of systems
  - define what data is stored and how desired metrics are calculated and returned
- core library should have no notion of model-specific behaviors
  - no person class (or other model-specific agent)
  - no library hard-coded logic (how transmission is defined, how metrics are calculated)

## Dependencies

- [GSL](https://www.gnu.org/software/gsl/) (must be installed on user's system)
- [EnTT](https://github.com/skypjack/entt) (automatically built into xlamb library)
- [spdlog](https://github.com/gabime/spdlog) (automatically built into xlamb library)