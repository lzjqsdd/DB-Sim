                         +------------------------------------------------+
                         |       ______           __  __________________  |
                         |      / ____/___ ______/ /_/ ____/_  __/ ____/  |
                         |     / /_  / __ `/ ___/ __/ __/   / / / __/     |
                         |    / __/ / /_/ (__  ) /_/ /___  / / / /___     |
                         |   /_/    \__,_/____/\__/_____/ /_/ /_____/     |
                         +------------------------------------------------+

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
## Framework
- [x] parse xml from config
- [x] boost library support
- [x] logging support
- [x] basic iterator develop
- [x] xgboost,randomforest c++ support
- [x] refacting fete manage
- [x] refacting config manage 

## Model
- [x] poolnum -> buffernum
- [x] buffernum -> outflow
- [x] sample for every link and node
- [x] add pool and buffer sample
- [x] train model for each node
- [x] import ml model(trained by python and predict by c++)


## Plans
### V0.1.3
- [ ] add param configure for better tune.
- [x] add super-dest-point process


### V0.1.4
- [x] add [poolnum -> buffernum] Model
- [x] finished basic iteration for simulation.


### V0.1.5
- [ ] add 2out->1in intersection analysis

### V0.1.6
- [ ] add rotary island intersection analysis

### To Be Continue~

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
