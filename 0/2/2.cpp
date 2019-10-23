#include <pthread.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

using namespace std;

struct ThreadArgs {
    char* message;
    ofstream* fout;

    ThreadArgs(char* m, ofstream* f) {
        message = m;
        fout = f;
    }
};

char* id_to_string(int thread_id) {
    static char temp_str[1000];
    snprintf(temp_str,1000,"(%d)",thread_id);
    return temp_str;
}

void* run(void* ptr) {
    ThreadArgs* ta = (ThreadArgs*) ptr;

    *ta->fout << "Start Job: " << (char *) ta->message << ' ' << (long long) pthread_self() << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    *ta->fout << "End Job: " << (char *) ta->message << ' ' << (long long) pthread_self() << endl;

    return NULL;
}

int main() {
    ofstream fout("process_output");
    pthread_t t[100];
    ThreadArgs* args[100];
    for(int i = 0; i < 100; i ++) {
        char* id = new char[1000];
        strcpy(id, id_to_string(i+1));
        args[i] = new ThreadArgs(id, &fout);
        int it = pthread_create(&t[i], NULL, run, (void*) args[i]);
        this_thread::sleep_for(chrono::milliseconds(2000));
    }

    for(int i = 0; i < 100; i ++) {
        pthread_join(t[i], NULL);
        delete args[i]->message;
        delete args[i];
    }

    fout.close();
    cout << "End Process" << endl;
    return 0;
}
