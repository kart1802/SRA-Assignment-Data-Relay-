# ***SRA-Assignment-Data-Relay***

In this task, we had to get random data(as sensor data),place it in json format and send this message in the form of json string and also reducing it's size by compressing it, then receive from client side and parse the json to get actual data.

***
### Table of Contents
***

- [***SRA-Assignment-Data-Relay***](#sra-assignment-data-relay)
    - [Table of Contents](#table-of-contents)
    - [About Project](#about-project)
      - [Tech Stack :](#tech-stack-)
      - [File Structure :](#file-structure-)
    - [Getting Started](#getting-started)
      - [Prerequisites :](#prerequisites-)
      - [Installation :](#installation-)
    - [Usage](#usage)
    - [Results and Demo](#results-and-demo)
    - [Future Work](#future-work)
    - [Troubleshooting](#troubleshooting)
    - [Contributors](#contributors)
    - [Acknowledgement and Resources](#acknowledgement-and-resources)
  
***
### About Project
***


#### Tech Stack :

Used C language for coding, used json-c, mosquitto, pthread libraries

* [JSON-C](https://github.com/json-c/json-c)
* [Mosquitto](https://mosquitto.org/download/)

#### File Structure :
    .
    ├── Actual Code     # Containing the code related to project
    │   ├── pub.c       # Code related to publishing the JSON string
    │   └── sub.c       # Code related to subscribing, parsing, compressing the JSON string and storing in text files
    ├── Basic                    # Basic named folder
    │   ├── mqtt_pub.c            # Code related to basic of publishing the message using mosquitto
    │   ├── mqtt_sub.c          # Basic related to subscribing
    |   ├── prac_json.c           # Containing basic of creating json object and printing it
    │   ├── pthread.c           # Basic code related to threading 
    |   ├── test.c        # Code containing parsing of json
    |   ├── test.json             # containing sample json
    |   └── tp.c           # Very basic code for generating random values
    ├── device1             # Folder containing some text files
    |   ├── air_pressure.c    # Having air pressure data
    |   ├── ctemperature.c           # compressed temperature data
    |   ├── cph.c           # compressed pH data
    |   ├── chumidity.c           # compressed humidity data
    |   ├── humidity.c         # Having humidity data
    |   ├── ph.c           # Having pH data
    |   └── temperature.c          # Having temperature data
    ├── device2           # Folder containing some text files
    |   ├── cdistance.c    # compressed distance data
    |   ├── cswitch_state.c    # compressed switch_state data
    |   ├── distance.c    # Having distance data
    |   └── switch_state.c    # Having switch_state data
    │            
    ├── Hello.txt         # Nothing related to task
    ├── air_pressure - Notepad.png       # Image related to data of Air Pressure
    ├── device-1.png        # Image related to text files in device 1 folder
    ├── device-2.png        # Image related to text files in device 2 folder
    ├── kart folder.png     # Image related to files and folders present in main directory folder
    ├── sra-data-relay.mp4    # Video related to running of the code
    └── README.md 
    


***
### Getting Started
***

#### Prerequisites :

* [Codeblocks](http://www.codeblocks.org/) or any other IDE
* [Git](https://gitforwindows.org/) 
* [Github for making Repositories](https://github.com/)

>How to install these softwares
1. Click on the above "**CodeBlocks**" that will redirect you to the downloads section of Codeblocks website.
2. Click on the above "**Git**" that will redirect you to the website .
3. Click on the above "**Github for making Repositories**" that will redirect you to the website of github where you to first register yourself and then make repositories

* In WSL, enter the following <br>
1) For gcc installation
  
```sh
  sudo apt install gcc
  sudo apt update
  sudo apt upgrade
```
2) For Mosquitto
```sh  
  sudo apt-add-repository ppa:mosquitto-dev/mosquitto-ppa
  sudo apt-get update
  sudo apt mosquitto mosquitto-clients libmosquitto-dev
```
Checking the installation : If you have installed a binary package the broker should have been started automatically. If not, it can be started with a basic configuration:
```sh  
  mosquitto
```
Then use  "mosquitto_sub" to subscribe to a topic:
```sh  
  mosquitto_sub -t 'test/topic' -v
```
And use "mosquitto_pub" publish a message:
```sh  
  mosquitto_pub -t 'test/topic' -m 'Hello'
```
#### Installation :

If you want to take these files from our repository to your system , Clone our Repo by writing this code given below in your git bash

```sh
git clone https://github.com/kart1802/SRA-Assignment-Data-Relay-.git 
```

***
### Usage
***

Change the directory and go to Actual Code folder

Run the following Command to publish:
```sh
  gcc pub.c -o pub -lmosquitto -ljson-c -lpthread
  ./pub
```
Run the following Command to subscribe,parse and generate text files:
```sh
  gcc sub.c -o sub -lmosquitto -ljson-c 
  ./sub
```

***
### Results and Demo
***

![Result](https://github.com/kart1802/SRA-Assignment-Data-Relay-/blob/master/sra-data-relay.mp4) <br>

![Directory where device 1 and 2 folders are present](https://github.com/kart1802/SRA-Assignment-Data-Relay-/blob/master/kart%20folder.png) <br>

![Device1](https://github.com/kart1802/SRA-Assignment-Data-Relay-/blob/master/device-1.png) <br>

![Device2](https://github.com/kart1802/SRA-Assignment-Data-Relay-/blob/master/device-2.png) <br>

![Air pressure data for example](https://github.com/kart1802/SRA-Assignment-Data-Relay-/blob/master/air_pressure%20-%20Notepad.png)

***
### Future Work
***

* [x] Completed stage 0 by creating 50 bots
* [x] Completed stage 1 by parsing the data segregating it into multiple text files
* [ ] Need to complete compression of air pressure part
* [ ] Need to Decompress all to complete everything
* [ ] Need to add the frequency of 2 minute part



***
### Troubleshooting
***
* Had Segmentation Fault previously but now working fine

***
### Contributors
***
> Mentors

Mr. Omkar Bhilare 

   
> Members

Mr. [Karthik Swaminathan](https://github.com/kart1802) 

***
### Acknowledgement and Resources
***

* [SRA VJTI](http://sra.vjti.info/) Eklavya 2020
* Youtube Videos

* [Mosquitto site](https://mosquitto.org/api/files/mosquitto-h.html)

* [Json for c- 1](https://gist.github.com/alan-mushi/19546a0e2c6bd4e059fd)
* [Json for c - 2](https://json-c.github.io/json-c/json-c-0.10/doc/html/json__object_8h.html)

