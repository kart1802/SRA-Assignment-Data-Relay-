#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include<unistd.h>
#include<math.h>
#include <json-c/json.h>
#include<mosquitto.h>
#include <pthread.h>

char* cur_time(){
    time_t rawtime;
    time ( &rawtime );
    return asctime (localtime ( &rawtime ));
}

char* device1(){

    float t = (rand()%150)-40+0.75*((float)rand()/RAND_MAX);
    float h= (rand()%100)+0.75*((float)rand()/RAND_MAX);
    int air_pressure= (rand()%298)+3;
    float ph = (rand()%14)+((float)rand()/RAND_MAX);
    //char* timestamp = cur_time();
    //printf("%s",timestamp);
    char temp[20],humidity[30],pH[10];
    sprintf(temp,"%.2f",t);
    sprintf(humidity,"%.3f",h);
    sprintf(pH,"%.1f",ph);

    struct json_object *jobj;
    char* device_id = "1";
    jobj = json_object_new_object();
    json_object_object_add(jobj, "Device Id", json_object_new_string(device_id));
    json_object_object_add(jobj, "Timestamp", json_object_new_string(cur_time()));
    json_object_object_add(jobj, "Temperature", json_object_new_string(temp));
	json_object_object_add(jobj, "Humidity", json_object_new_string(humidity));
	json_object_object_add(jobj, "Air Pressure", json_object_new_int(air_pressure));
	json_object_object_add(jobj, "pH", json_object_new_string(pH));

	char* json_to_string = (char *)json_object_to_json_string(jobj);
	//size_t i = strlen(json_to_string);
	printf("%s\n",json_to_string);
	return json_to_string;
}

char* device2(){

    float dist = (rand()%100)+0.75*((float)rand()/RAND_MAX);
    char* switch_state;
    int n= rand()%2;
    if (n==0){
        switch_state = "OFF";
    }else{
        switch_state = "ON";
    }
    char distance[20];
    sprintf(distance,"%.2f",dist);
    struct json_object *jobj;
    char* device_id = "2";
    jobj = json_object_new_object();
    json_object_object_add(jobj, "Device Id", json_object_new_string(device_id));
    json_object_object_add(jobj, "Distance", json_object_new_string(distance));
    json_object_object_add(jobj, "Switch State", json_object_new_string(switch_state));

	char* json_to_string = (char *)json_object_to_json_string(jobj);
	printf("%s\n",json_to_string);
	return json_to_string;
}

void* device1_mosquitto(void * arg){
    char str[200];
    int len;
    //char* length = device1();
    int a;
    //sleep(0.5);
    struct mosquitto *mosq;
    mosquitto_threaded_set(mosq,true);
    strcpy(str, device1());
    mosq = mosquitto_new(NULL, true, NULL);
    len = strlen(str);
    char* topic = "device/first";
    a = mosquitto_connect_async(mosq, "localhost", 1883, 60);
    if( a != 0){
        printf("Client could not connect to broker! Error Code: %d\n", a);
        mosquitto_destroy(mosq);
    }
    //printf("We are now connected to the broker!\n");

    mosquitto_publish(mosq, NULL, topic, len, str, 1, false);
    //printf("%d",len);
    mosquitto_loop_start(mosq);
    mosquitto_disconnect(mosq);
    pthread_exit(NULL);
}

void* device2_mosquitto(void * arg){
    char str[200];
    int len;
    //char* length = device1();
    int a;

    struct mosquitto *mosq;
    mosquitto_threaded_set(mosq,true);
    strcpy(str, device2());
    mosq = mosquitto_new(NULL, true, NULL);
    len = strlen(str);
    char* topic = "device/second";
    a = mosquitto_connect_async(mosq, "localhost", 1883, 60);
    if( a != 0){
        printf("Client could not connect to broker! Error Code: %d\n", a);
        mosquitto_destroy(mosq);
    }
    //printf("We are now connected to the broker!\n");

    mosquitto_publish(mosq, NULL, topic, len, str, 1, false);
    //printf("%d",len);
    mosquitto_loop_start(mosq);
    mosquitto_disconnect(mosq);
    pthread_exit(NULL);
}

int main(){
    pthread_t thread_id[50];
    for(int i=0;i<50;i++){
            if(i<30){
                sleep(0.5);
                pthread_create(&thread_id[i], NULL, device1_mosquitto, NULL);
            }else{
                sleep(0.5);
                pthread_create(&thread_id[i], NULL, device2_mosquitto, NULL);
            }
    }
    for(int i=0;i<50;i++){
        pthread_join(thread_id[i], NULL);
    }
    return 0;
}
