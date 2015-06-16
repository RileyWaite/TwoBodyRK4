#include "headers/vecManip.hpp"
#include "headers/RK4.hpp"
#include <fstream>
#include <iostream>

#define G -6.67384e-11
#define M 5.972e24
#define MOON_SPEED 7545.6867982406
#define PERIOD 5828.8

std::vector<double> moonFunc(std::vector<double> pos, std::vector<double> vel, double t){
  	
 	std::vector<double> dvdt(3);
  	
  	for(int i(0);i<3;++i) dvdt[i]=0;
 	
 	double r = mag(pos);
 	double accel = G*M/(r*r*r);
  	
 	dvdt[0] = accel * pos[0];
  	dvdt[1] = accel * pos[1];
 	dvdt[2] = accel * pos[2];
  	
  	return dvdt;
}

int main(int argc, char **argv){

	std::vector<double> pos(3), vel(3), posNew(3), velNew(3);
	
	double t = 0.0, dt = 0.2;
	
	long double counter = 0.0;
	
	std::ofstream fout("SystemStates.txt");
	
	if(argc != 8){
		std::cout << "Incorrect number of command line parameters\n";
		std::cout << "Correct command line: ./propagation posX posY posZ velX velY velZ numOrbits\n";
		std::exit(1);
	}
	
	pos[0] = atof(argv[1]);
	pos[1] = atof(argv[2]);
	pos[2] = atof(argv[3]);
	
	vel[0] = atof(argv[4]);
	vel[1] = atof(argv[5]);
	vel[2] = atof(argv[6]);
	
	unsigned int numOrbits = atof(argv[7]);
	
	//pos = {7e6, 0, 0};
	//vel = {0, MOON_SPEED, 0};
	
	while(1){
	
 		if(counter >= (PERIOD / dt) * numOrbits){
  			fout.close();
  			break;
  		}

                evaluate(moonFunc, pos, vel, t, dt, posNew, velNew);
		
                fout <<  posNew[0] << '\t' << posNew[1] << '\t' << posNew[2] << "\t0\t0\t0\t"
			<< velNew[0] << '\t' << velNew[1] <<  '\t' << velNew[2] << '\n';
	
		for(int i = 0; i < 3; ++i){
			pos[i] = posNew[i];
			vel[i] = velNew[i];
		}
		
                counter++;
        }

        return 0;
	
}