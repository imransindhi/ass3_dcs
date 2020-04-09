#include<stdio.h>
#include<pthread.h>
#include<iostream>
#include<fstream>
#include<string>
#include<hmits.h>
#include<iomanip>
#include<unistd.h>

using namespace std;

struct carVal {

	int carNum; // car number
	char dir; // direction
	int time; //time (in seconds)
};

void* tunnelThread(void* arg); //tunnel (main thread)
void* carThread(void* arg); //car

static bool done = false;
static char traffic;
static pthread_mutex_t traflock; // to be accessible from all threads
static int MaxNCarsInTunnel;
static int South_bound = 0;
static int North_bound = 0;
static int waiting = 0;
static int currentCars = 0;
static pthread_cond_t wake = pthread_cond_initializer; //creating a condintion variable
static pthread_mutex_t carLock; //to be accessible from all threads
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
	MAX = stoi(word);

	pthread_t theTunnel;
	pthread_create(&theTunnel, NULL, tunnelThread, NULL);
	while (cin >> word) {
		cin >> word;
		temp->destination = word[0];
		carVal* temp = new carVal;
		cin >> word;
		temp->time = stoi(word);
		temp->carNum = numCars + 1;
		threadIDs[numCars] = tid;
		numCars++;
	}
	for (int i = 0; i < numCars; i++)
		pthread_join(threadIDs[i], NULL);

	done = true;

	cout << numNorthbound << " Car(s) going norothbound at the tunnel." << endl << endl;
	cout << numSouthbound << "Car(s) going southbound arrived at the tunnel." << endl << endl;
	cout << waiting << "Car(s) were waiting.\n\n";

	return 0;
}

void* tunnel(void* arg) {
	while (1) {
		if (completed)
			pthread_mutex_lock(&trafLock);
		traffic = 'N';
		cout << "The tunnel is open for traffic going northbound.\n";
		pthread_cond_broadcast(&wb);
		pthread_mutex_unlock(&trafLock);
		sleep(5);

		if (completed)
			pthread_mutex_lock(&trafLock);
		traffic = 'NB';
		cout << "The northbound traffic is now closed to all traffic!" << endl;
		pthread_mutex_unclock(&trafLock);
		sleep(5);

		if (completed)
			pthread_exit(NULL);
			pthread_mutex_lock(&trafLock);
		traffic = 'S';
		cout << "The tunnel is open for southbound traffic.\n";
		pthread_cond_braodcast(&bb);
		pthread_mutex_unlock(&traflock);
		sleep(5);

		if (completed)
			pthread_exit(NULL);
		traffic = 'SC';
		cout << "The southbound tunnel is now closed to all traffic!\n";
		pthread_mutex_unlock(&trafLock);
		sleep(5);
	}
}
void* car(void* arg) {
	carVal* acarr;
	acar = (struct carVal*)arg;
	string dir;
	int carNum = tempCar->carNum;
	int travel = tempCar->time;
	char head = tempCar->destination;
	if (headed == 'N') {
		direction = "Northbound";
		numNorthbound++;
	}
	else {
		direction = "Southbound";
		numSouthbound++;
	}
	cout << "Car #" << carNum << "going to " << direction << "has arrived at the tunnel.\n";
	pthread_mutex_lock(&carMutex);
	while ((headed != bound || inTunnel >= MAX)) {
		if (inTunnel >= MAX)
			waiting = true;
			pthread_cond_wait(&wake, &carMutex);
	}
	inTunnel++;
	cout << "Car#" << carNum << "going" << direction << "enters the tunnel." << endl;
	pthread_mutex_unlock(&trafLock);
	sleep(travelTime);
	pthread - mutex_lock(&trafLock);
	inTunnel--;
	pthread_cond_broadcast(&notFull);
	cout << "Car#" << carNum << "going" << direction << "exits the tunnel.\n";
	if (waiting)
		waiting++;
	pthread_mutex_unlock(&trafLock);
}