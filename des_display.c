//#include "D:\QNX\Workspaces\cst8244_assign1\des_controller\src\des.h"
//#include "D:\QNX\Workspaces\cst8244_assign1\des_controller\src\des.h"
#include "../../des_controller/src/des.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/neutrino.h>

Person person;
int chid;
int rcvid;

int main(void) {
	/*Display the pid for des_display*/
	printf("des_display PID: %d\n", getpid());

	Display display;

	/*Create a communication channel*/
	chid = ChannelCreate(0);
	if (chid == -1) {/*If error creating the communication channel*/
		perror("Error creating the communication channel in the des_display");
		exit(EXIT_FAILURE);
	}

	while (1) {/*infinite loop*/
		/*Call MsgReceive to get object from controller*/
		rcvid = MsgReceive(chid, &person, sizeof(person), NULL);
		if (rcvid == -1) {
			perror("Error receiving message from controller in des_display");
			exit(EXIT_FAILURE);
		}

		/*Display to user which state is the program currently in*/
		if (person.state_holder == INPUT_LS) {
			printf("%s %d\n", outMessage[OUT_LS], person.person_id);
		} else if (person.state_holder == INPUT_RS) {
			printf("%s %d\n", outMessage[OUT_RS], person.person_id);
		} else if (person.state_holder == INPUT_WS) {
			printf("%s %d\n", outMessage[OUT_WS], person.weight);
		} else if (person.state_holder == INPUT_LO) {
			printf("%s\n", outMessage[OUT_LO]);
		} else if (person.state_holder == INPUT_RO) {
			printf("%s\n", outMessage[OUT_RO]);
		} else if (person.state_holder == INPUT_LC) {
			printf("%s\n", outMessage[OUT_LC]);
		} else if (person.state_holder == INPUT_RC) {
			printf("%s\n", outMessage[OUT_RC]);
		} else if (person.state_holder == INPUT_GRU) {
			printf("%s\n", outMessage[OUT_GRU]);
		} else if (person.state_holder == INPUT_GRL) {
			printf("%s\n", outMessage[OUT_GRL]);
		} else if (person.state_holder == INPUT_GLL) {
			printf("%s\n", outMessage[OUT_GLL]);
		} else if (person.state_holder == INPUT_GLU) {
			printf("%s\n", outMessage[OUT_GLU]);
		} else if (person.state_holder == INPUT_EXIT) {
			printf("%s \n", outMessage[OUT_EXIT]);
		} else {
			printf("Invalid input\n");
		}

		if (person.state_holder != STATE_EXIT) {
			/*Reply to the controller using MsgReply*/
			MsgReply(rcvid, EOK, &display, sizeof(display));
		} else {
			/*if STATE_EXIT is the state, break from loop*/
			break;
		}

	}

	ChannelDestroy(chid);
	return EXIT_SUCCESS;
}
