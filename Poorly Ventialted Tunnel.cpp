#include<stdio.h>
#include<pthread.h>
#include<iostream>
#include<fstream>
#include<string>
#include<hmits.h>
#include<iomanip>
#include<unistd.h>
#include<time.h>

using namespace std;

struct carVal {
	int numCars; // number of cars
	int carNum; // car number
	char dir; // direction
	int travelTime; //time (in seconds)
};

void* tunnelThread(void* arg); //tunnel (main thread)
void* carThread(void* arg); //car

static bool done = false;
static char traffic;
static pthread_mutex_lock traflock; //to be accessible from all threads
static pthread_mutex_unlock traflock; // to be accessible from all threads
static int maxNCarsInTunnel;
static int numSouthbound = 0; //number of cars going southbound
static int numNorthbound = 0; //number of cars going northbound
static int waiting = 0; //number of cars waiting to enter the tunnel
static int inTunnel = 0; // number of cars in the tunnel
static pthread_cond_t wake = pthread_cond_initializer; //creating a condintion variable
static pthread_mutex_lock carLock; //to be accessible from all threads
static pthread_mutex_unlock carLock; //to be accessible from all threads
static pthread_cond_t wb = pthread_cond_initializer;
static pthread_cond_t bb = pthread_cond_initializer;
static pthread_cond_t notFull = pthread_cond_initializer;

ifstream file;
ofstream output;

int main() {

	int numCars = 0;
	pthread_t threadIDs[256];
	pthread_mutex_init(&carMutex, NULL);

	string word;
	cin >> word;
	maxNCarsInTunnel = stoi(word);

	pthread_t theTunnel;
	pthread_create(&theTunnel, NULL, tunnelThread, NULL);
	while (cin >> word) {
		cin >> word;
		temp->dir = word[0]; //direction the car is going
		carNum* temp = new carNum;
		cin >> word;
		temp->time = stoi(word);
		temp->carNum = numCars + 1;
		threadIDs[numCars] = tid;
		numCars++;
	}
	for (int i = 0; i < numCars; i++)
		pthread_join(threadIDs[i], NULL);

	done = true;

	cout << numNorthbound << " Car(s) going northbound at the tunnel.\n\n";
	cout << numSouthbound << "Car(s) going southbound arrived at the tunnel.\n\n";
	cout << waiting << "Car(s) were waiting.\n\n";

	return 0;
}

void* tunnel(void* arg) {
	while (1) {
		if (done)
			pthread_mutex_lock traflock;
		traffic = 'N';
		cout << "The tunnel is open for traffic going northbound!\n\n";
		pthread_cond_t wb;
		pthread_mutex_unlock trafLock;
		sleep(5);

		if (done)
			pthread_mutex_lock trafLock;
		traffic = 'NB';
		cout << "The northbound traffic is now closed to all traffic!" << endl <<endl;
		pthread_mutex_unlock trafLock;
		sleep(5);

		if (done)
			pthread_exit(NULL);
			pthread_mutex_lock trafLock;
		traffic = 'S';
		cout << "The tunnel is open for southbound traffic!\n\n";
		pthread_cond_t bb;
		pthread_mutex_unlock traflock;
		sleep(5);

		if (done)
			pthread_exit(NULL);
		traffic = 'SC';
		cout << "The southbound tunnel is now closed to all traffic!" << endl << endl;
		pthread_mutex_unlock trafLock;
		sleep(5);
	}
}
void* car(void* arg) {
	carNum* acar;
	acar = (struct carNum*)arg;
	string dir; //dir stands for direction
	int carNum = tempCar->carNum;
	int travelTime = tempCar->travelTime; //time measured in seconds
	char dir = tempCar->dir; //direction
	if (dir == 'N') {
		dir = "Northbound";
		numNorthbound++;
	}
	else {
		dir = "Southbound";
		numSouthbound++;
	}
	cout << "Car #" << carNum << "going to " << dir << "has arrived at the tunnel.\n";
	pthread_mutex_lock(&carMutex); 
	while ((dir != Northbound || inTunnel >= maxNCarsInTunnel)) {
		if (inTunnel >= maxNCarsInTunnel)
			waiting = true;
			pthread_cond_wait(&wake, &carMutex);
	}
	while ((dir != Southbound || inTunnel >= maxNCarsInTunnel)) {
		if (inTunnel >= maxNCarsInTunnel)
			waiting = true;
		pthread_cond_wait(&wake, &carMutex);
	}
	inTunnel++;
	cout << "Car" << carNum << "going" << dir << "entering the tunnel." << endl;
	pthread_mutex_unlock trafLock;
	sleep(travelTime);
	pthread_mutex_lock trafLock;
	inTunnel--;
	static pthread_cond_t notFull;
	cout << "Car" << carNum << "going" << dir << "is exiting the tunnel.\n";
	if (waiting)
		waiting++;
	pthread_mutex_unlock trafLock;
}