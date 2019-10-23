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
    pthread_exit(NULL);
    return NULL;
}

int main() {
    freopen("out.txt", "w", stdout);

    for(int i = 1; i <= 100; i ++) {
        pthread_t t1;
        char* id = id_to_string(i);
        int it = pthread_create(&t1, NULL, run, (void*) id);
        pthread_join(t1, NULL);
        //this_thread::sleep_for(chrono::milliseconds(2000));
    }
    cout << "End Process" << endl;
    return 0;
}
