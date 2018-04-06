
# Model predictive control
A Model Predictive Controller is used to drive a car around a simulated track at 50 mph.

## Model
A simple kinematic model bicycle model was used for setting up motion cconstraints in the optimizer. The equations are as follows:

![Model](imgs/eq1.png)


## Pre-processing
The waypoints provided by the simulator were transformed relative to the car. Lines `129 to 139` in `main.cpp` describe this simple euclidean transform.

## Polynomial fitting
The target way point are used to fit a polynomial through them. This polynomial allows us to generate continuous estimations of our target cross-track and heading errors.

## Timestep selection
The controller uses the `IPOPT` package to solve for the optimal control inputs by propagating the system model forward for a specified time horizon. The numbers were selected after trial and error. A 1s "look ahead" with time-step of 10s was found to be sufficient. Very high lookahead values caused performance problems on low-spec virtual machine. Very low lookahead values on the other hand, caused instabilities around sharp turns. 

## Lag compensation
Lag compensation was achieved by propagating the state forward by estimating the system state around the time the actuator command would actually be given. This was done using the dyammic model of the system and current throttle and steering value. Ideally, the acceleration of the vehicle should be used here but throttle is used as an approximation to it. Line `145 - 152` implement this case. The performance was tested for 100ms of lag.

## Tuning
Tuning was performed by an educated trial and error. High weightage was given to cross-track and heading errors. This however, caused osciallations. To prevent them the weightage to the actuation magnitude and change is actuation magnitudes was increased. The final weight values are as follows:

```
// Weights for the cost function
#define W_CTE 1000      // Cross track error
#define W_EPSI 1000     // Heading error
#define W_V 1           // Velocity error
#define W_DELTA 50000   // Steering angle command
#define W_A 50          // Throttle command 
#define W_DDELTA 500000 // Change in steering angle 
#define W_DA 10         // Change in throttle 
```

## Dependencies
* cmake >= 3.5
* make >= 4.1(mac, linux), 3.81(Windows)
* gcc/g++ >= 5.4
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `install-mac.sh` or `install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.

* **Ipopt and CppAD:** Please refer to [this document](https://github.com/udacity/CarND-MPC-Project/blob/master/install_Ipopt_CppAD.md) for installation instructions.
* [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page). This is already part of the repo so you shouldn't have to worry about it.
* Simulator. You can download these from the [releases tab](https://github.com/udacity/self-driving-car-sim/releases).
* Not a dependency but read the [DATA.md](./DATA.md) for a description of the data sent back from the simulator.


## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./mpc`.

