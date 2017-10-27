# FETE
A data driven and  queue-based simulation tool for FastETE 

# Goals
calculate evacuation time faster and  more accurately

# Methods
-  build basic iterator model[FETE Framework]
-  build ml model
-  data driven model integration
-  Experiment

# TODOLISTS
- [ ] parse xml from config
- [ ] basic iterator develop
- [ ] import ml model


# Usage
## Settings
- `config` privoid traffic network and evacuation demand with xml.
- `src` do simulation
    - `core` core code for simulation
    - `utils` some userdefined or 3rd necessary tools ,example parse xml toos
- `test` some test case for this project

## build
```bash
cd ${PROJECT_DIR}
mkdir build
cd build
cmake ..
make
```

# Reference
