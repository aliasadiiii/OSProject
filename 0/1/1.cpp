#include <pthread.h>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

char* id_to_string(int thread_id) {
    static char temp_str[1000];
    snprintf(temp_str,1000,"(%d)",thread_id);
    return temp_str;
}

void* run(void* ptr) {
    cout << "Start Job: " << (char *) ptr << ' ' << (long long) pthread_self() << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "End Job: " << (char *) ptr << ' ' << (long long) pthread_self() << endl;
    return NULL;
}

int main() {
    pthread_t t[100];
    char* id[100];
    for(int i = 0; i < 100; i ++) {
        id[i] = new char[1000];
        strcpy(id[i], id_to_string(i+1));
        int it = pthread_create(&t[i], NULL, run, (void*) id[i]);
        this_thread::sleep_for(chrono::milliseconds(2000));
    }

    for(int i = 0; i < 100; i ++) {
        pthread_join(t[i], NULL);
        delete id[i];
    }

    cout << "End Process" << endl;
    return 0;
}
