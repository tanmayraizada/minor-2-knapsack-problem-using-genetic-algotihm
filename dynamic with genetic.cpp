ś// C++ program to implement Knapsack Problem
// using Genetic Algorithm 

#include <bits/stdc++.h> 
using namespace std; 


#define POPULATION_SIZE 200
#define MAX_ITER 100
#define CAPACITY 100


const string GENES ="01";



typedef struct nd{
    float w;
    float p;
}A;


array<A,100> OBJ{ 2.965,3.115,0.292,3.83,3.098,3.345,3.52,0.425,2.321,1.644,1.062,0.302,1.304,3.178,0.226,1.844,2.302,1.124,2.525,1.195,3.338,0.941,3.991,0.565,2.518,4.166,0.477,1.486,2.349,3.326,0.239,4.217,1.441,4.425,1.959,3.442,2.769,0.479,2.77,0.089,1.026,3.822,4.285,2.32,0.912,3.415,3.068,3.204,3.442,0.592,3.303,1.779,0.437,2.293,2.335,2.945,0.371,1.715,4.421,1.623,0.04,4.65,0.84,1.471,2.988,1.702,3.816,0.756,1.084,1.585,4.74,1.014,4.31,4.024,3.324,0.222,1.351,0.304,2.329,4.784,4.791,4.535,1.562,0.227,1.827,2.8,2.075,2.189,4.505,1.495,3.802,4.536,0.057,3.545,4.91,3.035,4.151,3.726,2.695,0.234,4.214,1.347,1.238,3.524,4.274,3.466,2.649,0.625,2.673,3.881,0.408,1.376,3.416,0.873,0.506,4.146,3.664,2.571,0.247,3.168,2.969,2.953,1.616,3.017,1.497,1.526,4.955,4.551,4.155,1.562,3.689,2.281,2.899,3.83,4.708,2.173,1.208,2.356,1.701,3.872,0.15,2.099,4.151,3.556,1.875,4.648,2.701,0.538,2.218,2.939,2.61,0.187,4.795,3.129,2.107,0.204,3.558,0.974,4.746,2.712,2.527,3.434,3.897,4.329,2.263,3.604,1.501,2.375,0.96,2.105,1.246,0.013,3.107,0.396,3.559,4.973,3.947,0.172,0.51,1.165,2.014,2.023,0.255,1.808,0.152,1.265,2.003,3.7,2.229,1.748,0.325,4.746,4.085,4.212,2.988,0.26,2.815,4.479,2.625,2.678 };

 
int random_num(int start, int end) 
{ 
	int range = (end-start)+1; 
	int random_int = start+(rand()%range); 
	return random_int; 
} 


char mutated_genes() 
{ 
	int len = GENES.size(); 
	int r = random_num(0, len-1); 
	return GENES[r]; 
} 

string create_gnome() 
{ 
	int len = OBJ.size(); 
	string gnome = ""; 
	for(int i = 0;i<len;i++) 
		gnome += mutated_genes(); 
	return gnome; 
} 


class Individual 
{ 
public: 
	string chromosome; 
	int fitness; 
	Individual(string chromosome); 
	Individual mate(Individual parent2); 
	int cal_fitness(); 
}; 

Individual::Individual(string chromosome) 
{ 
	this->chromosome = chromosome; 
	fitness = cal_fitness(); 
}; 


Individual Individual::mate(Individual par2) 
{ 
	
	string child_chromosome = ""; 

	int len = chromosome.size(); 
	for(int i = 0;i<len;i++) 
	{ 
		
		float p = random_num(0, 100)/100; 

		
		
		if(p < 0.45) 
			child_chromosome += chromosome[i]; 

		
		else if(p < 0.90) 
			child_chromosome += par2.chromosome[i]; 

		
		else
			child_chromosome += mutated_genes(); 
	} 
 
	return Individual(child_chromosome); 
}; 



int Individual::cal_fitness() 
{ 
	int len = OBJ.size(); 
	float fitness = 0; 
	float volume = 0;
	char b[0];
	 for(int j = 0;j<len;j++) 
        	{ 
        	   
            	b[0]=chromosome[j];
	            int x = atoi(b);
        		fitness = fitness + ((OBJ[j].p)*x);
        		volume = volume + (x*(OBJ[j].w));
         	}

	if(volume>CAPACITY)
	{
	     fitness=0;
         volume=0;
	    while(1)
	    { 
	        int i=random_num(0,len-1);
	        fitness=0;
            volume=0;
	        
	        this->chromosome[i]='0';
	        for(int j = 0;j<len;j++) 
        	{ 
            	b[0]=chromosome[j];
	            int x = atoi(b);
        		fitness = fitness + ((OBJ[j].p)*x);
        		volume = volume + (x*(OBJ[j].w));
         	}
         	if(volume<=CAPACITY)
         	  break;
	    }
	}


	return fitness;	 
}; 


bool operator<(const Individual &ind1, const Individual &ind2) 
{ 
	return ind1.fitness < ind2.fitness; 
} 

int main() 
{ 
	srand((unsigned)(time(0))); 

	
	int generation = 0; 

	vector<Individual> population; 

	
	for(int i = 0;i<POPULATION_SIZE;i++) 
	{ 
	   
	   
	          string gnome = create_gnome(); 
	
	
		          population.push_back(Individual(gnome));
		
		
	   

		 
	} 

	while(generation<MAX_ITER) 
	{ 
		
		sort(population.begin(), population.end()); 

     
		vector<Individual> new_generation; 

		
		int s = (10*POPULATION_SIZE)/100; 
		for(int i = (POPULATION_SIZE-s);i<POPULATION_SIZE;i++) 
			new_generation.push_back(population[i]); 

	
		s = (90*POPULATION_SIZE)/100; 
		for(int i = (POPULATION_SIZE-s);i<POPULATION_SIZE;i++) 
		{ 
			int r = random_num(POPULATION_SIZE/2, POPULATION_SIZE-1); 
			Individual parent1 = population[r]; 
			r = random_num(POPULATION_SIZE/2, POPULATION_SIZE-1); 
			Individual parent2 = population[r]; 
			 
		
			    Individual offspring = parent1.mate(parent2);
		
			        new_generation.push_back(offspring);
		
			 
			 
		} 
		sort(new_generation.begin(), new_generation.end());
		population = new_generation; 
		cout<< "Generation: " << generation << "\t"; 
		cout<< "Cromosome: "<< population[POPULATION_SIZE-1].chromosome <<"\t"; 
		cout<< "Profit: "<< population[POPULATION_SIZE-1].fitness << "\n"; 

		generation++; 
	} 
	cout<< "maximum Profit: "<< population[POPULATION_SIZE-1].fitness << "\n"; 
} 

