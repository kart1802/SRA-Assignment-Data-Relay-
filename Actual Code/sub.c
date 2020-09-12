#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include<unistd.h>
#include<math.h>
#include <json-c/json.h>
#include <mosquitto.h>

void writing_in_file(const char* values, char* name){
    FILE *fp;
    fp = fopen(name,"a");
    if (fp == NULL)
    {
        printf("Could not open file");
        exit(1);
    }
    fprintf(fp,"%s\n", values);
    fclose(fp);
}

void writing_in_file2(int values, char* name){
    FILE *fp;
    fp = fopen(name,"a");
    if (fp == NULL)
    {
        printf("Could not open file");
        exit(1);
    }
    fprintf(fp,"%d\n", values);
    fclose(fp);
}


void parsed_data(char* message){
    struct json_object *parsed_json, *temp, *humidity, *pH, *air_pressure, *timestamp, *device_id, *distance, *switch_state;
    parsed_json = json_tokener_parse(message);
    printf("%s\n", json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));
    json_object_object_get_ex(parsed_json, "Device Id", &device_id);
    const char *id = json_object_get_string(device_id);
    printf("%s\n",id);
    json_object_object_get_ex(parsed_json, "Timestamp", &timestamp);
    const char *cur_time = json_object_get_string(timestamp);
    //printf("%s",cur_time);
    if (*id == '1'){
        json_object_object_get_ex(parsed_json, "Temperature", &temp);
        const char *temperature = json_object_get_string(temp);
        json_object_object_get_ex(parsed_json, "Humidity", &humidity);
        const char *Humidity = json_object_get_string(humidity);
        json_object_object_get_ex(parsed_json, "Air Pressure", &air_pressure);
        int ap = json_object_get_int(air_pressure);
        json_object_object_get_ex(parsed_json, "pH", &pH);
        const char *ph = json_object_get_string(pH);
        writing_in_file(temperature,"device1/temperature.txt");
        writing_in_file(Humidity,"device1/humidity.txt");
        writing_in_file2(ap,"device1/air_pressure.txt");
        writing_in_file(ph,"device1/ph.txt");
    }else{
        json_object_object_get_ex(parsed_json, "Distance", &distance);
        const char*dist = json_object_get_string(distance);
        json_object_object_get_ex(parsed_json, "Switch State", &switch_state);
        const char *ss = json_object_get_string(switch_state);
        writing_in_file(dist,"device2/distance.txt");
        writing_in_file(ss,"device2/switch_state.txt");
    }


}

void mosq_connect(struct mosquitto *mosq, void *obj, int a) {
	//printf("ID: %d\n", * (int *) obj);
	if(a) {
		printf("Error with result code: %d\n", a);
		exit(-1);
	}
	char* topic = "device/+";
	mosquitto_subscribe(mosq, NULL, topic, 1);
}

void mosq_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg) {
	parsed_data((char *)(msg->payload));
}

int main() {
	int a;

	mosquitto_lib_init();

	struct mosquitto *mosq;

	mosq = mosquitto_new("subscribe", true, NULL);
	mosquitto_connect_callback_set(mosq, mosq_connect);
	mosquitto_message_callback_set(mosq, mosq_message);

	a = mosquitto_connect(mosq, "localhost", 1883, 10);
	if(a) {
		printf("Could not connect to Broker with return code %d\n", a);
		return -1;
	}

	mosquitto_loop_start(mosq);
	printf("Press Enter to quit...\n");
	getchar();
	//mosquitto_loop_stop(mosq, true);

	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();

	return 0;
}
