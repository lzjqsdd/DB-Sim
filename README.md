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
- [x] parse xml from config
- [x] boost library support
- [x] logging support
- [x] basic iterator develop
- [x] sample for every link
- [ ] train model for each node
- [ ] import ml model(trained by python and predict by c++)


# Usage
## Settings
- `config` privoid traffic network and evacuation demand with xml.
- `src` do simulation
    - `core` core code for simulation
    - `utils` some userdefined or 3rd necessary tools ,example parse xml tools
- `test` some test case for this project
- `data` train and test data

## build
```bash
cd ${PROJECT_DIR}
mkdir build
cd build
cmake ..
make
```

# Reference
- Papers To be add.
