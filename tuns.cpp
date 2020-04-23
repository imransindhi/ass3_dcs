#include<iostream> //has cout and cin function
#include<iomanip> //set funcitons
#include<pthread.h> //linux function used in threading programs
#include<stdlib.h> //standard library
#include<stdio.h> //tells the compiler to put the standard input of stdio
#include<string> //string functions
#include<unistd.h> //provides access to the POSIX opereating system
#include<queue> //standard template library
#include<sstream> //standard streaming library

using namespace std;

    static pthread_mutex_t mylock;
    static pthread_cond_t ok = PTHREAD_COND_INITIALIZER;
    int numberOfCarsInTunnel = 0;
    int numberOfCarsWaiting = 0;

struct carVal {

	int carNum; //car number
	char direction; //direction
	int travelTime; //time taken for the car to pass through the tunnel

};

void* tunnel(void* arg); //tunnel thread
void* car(void* arg); //car thread

static bool completed = false;

static char traffic;

static int maxNumCarsInTunnel; //maximum number of cars that can be in the tunnel
static int Southbound = 0; //number of cars going Southbound
static int Northbound = 0; //number of cars going northbound
static int waiting = 0; //number of cars waiting to enter the tunnel

int main() {

	static int inTunnel = 0; //number of cars in the tunnel
	pthread_cond_t cold = PTHREAD_COND_INITIALIZER;

	int totalCars = 0;
	pthread_t cartid[128];
	pthread_mutex_init(&mylock, NULL);

	string word;
	cin >> word;
	maxNumCarsInTunnel = stoi(word);

	pthread_t tunnelID;
	pthread_create(&tunnelID, NULL, tunnel, NULL);
	while (cin >> word)
	{
		sleep(stoi(word)); //sleep function's first appearance
		cin >> word;
		carVal* temp = new carVal;
		temp->direction = word[0];
		cin >> word;
		temp->travelTime = stoi(word);
		temp->carNum = totalCars + 1;
		pthread_t tid;
		pthread_create(&tid, NULL, car, (void*)temp);
		cartid[totalCars] = tid;
		totalCars++;
	}
	for (int i = 0; i < totalCars; i++)
		pthread_join(cartid[i], NULL);

	completed = true;

	cout << Northbound << "Car(s) going northbound are at the tunnel.\n\n";
	cout << Southbound << "Car(s) going southbound are at the tunnel.\n\n";
	cout << waiting << "Car(s) are waiting.\n\n";

}

void* inTunnel(void* arg)
{
	while (1) {

		//northbound tunnel open
		if (completed)
			pthread_exit(NULL);
		pthread_mutex_lock(&mylock);
		traffic = 'N';
		cout << "The tunnel is open and is going northbound!\n\n";
		pthread_cond_broadcast(&ok);
		pthread_mutex_unlock(&mylock);
		sleep(3);

		if (completed)
			pthread_exit(NULL);
		pthread_mutex_lock(&mylock);
		traffic = 'C'; //closed going northbound
		cout << "The northbound traffic is now closed to all traffic!" << endl << endl; //northbound tunnel closed
		pthread_mutex_unlock(&mylock);
		sleep(3);

		if (completed)
			pthread_exit(NULL);
		pthread_mutex_lock(&mylock);
		traffic = 'S';
		cout << "The tunnel is open and is going southbound!\n\n"; //southbound tunnel open
		pthread_cond_broadcast(&ok);
		sleep(3);


		if (completed)
			pthread_mutex_lock(&mylock);
		traffic = 'U'; //Unavailable going southbound
		cout << "The southbound tunnel is now closed to all traffic!" << endl << endl; //southbound tunnel closed
		pthread_mutex_unlock(&mylock);
		sleep(3);
	}
}

//car thread
void* car(void* arg)
{
	carVal* acar;
	acar = (struct carVal*) arg;
	int carNo = acar->carNum;
	char bound = acar->direction;//direction of traffic
	bool waiting = false; //wait/delay
	int travelTime = acar->travelTime; //time should be measured in seconds

	if (bound == 'N') {

		Northbound++;
		pthread_mutex_lock(&mylock);
		cout << "Car#" << carNo << "going Northbound arrives at the tunnel." << endl << endl;
		while (traffic != 'N') {
			pthread_cond_wait(&ok, &mylock);
			if (inTunnel >= maxNumCarsInTunnel) {
				waiting = true;
				pthread_cond_wait(&ok, &mylock);
			}
		}
		inTunnel++;
		cout << "Car#" << carNo << " going Northbound enters the tunnel.\n\n";
		pthread_mutex_unlock(&mylock);
		sleep(travelTime);
		pthread_mutex_lock(&mylock);
		inTunnel--;
		pthread_cond_broadcast(&ok);
		cout << "Car#" << carNo << " going Northbound exits the tunnel\n\n";
		if (waiting)
			waiting++;
		pthread_mutex_unlock(&mylock);
	}
	else {
		Southbound++;
		pthread_mutex_lock(&mylock);
		cout << "Car#" << carNo << " going Southbound arrives at the tunnel." << endl << endl;
		while (traffic != 'S')
		{
			pthread_cond_wait(&ok, &mylock);
				if (inTunnel >= maxNumCarsInTunnel) {
					waiting = true;
					pthread_cond_wait(&ok, &mylock);

				}
		}
		while (inTunnel >= maxNumCarsInTunnel)
		{
			waiting = true;
			pthread_cond_wait(&ok, &mylock);
			if (traffic != 'S')
				pthread_cond_wait(&ok, &mylock);
		}
		inTunnel++;
		cout << "Car #" << carNo << " going Southbound enters the tunnel.\n\n";
		pthread_mutex_unlock(&mylock);
		sleep(travelTime);
		pthread_mutex_lock(&mylock);
		inTunnel--;
		pthread_cond_broadcast(&ok);
		cout << "Car #" << carNo << " going to Southbound exits the tunnel.\n\n";
		if (waiting)
			waiting++;
		pthread_mutex_unlock(&mylock);
	}
}
