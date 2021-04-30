/*
 *PURPOSE: des_inputs will be a client to des_controller. Will have a connection with des_controller and will be sending a Person object to des_controller depending on the user input
 *NAME: 		des_inputs.c
 *CREATED ON: 	2021-03-10
 *AUTHORS:		Johnathan Slaunwhite and Federico Fonseca
 */
//#include "D:\QNX\Workspaces\cst8244_assign1\des_controller\src\des.h"
#include "../../des_controller/src/des.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>

pid_t serverPid; /* controller pid storage var */
Person person; /* Person structure defined in des.h */
Display display; /* response from the controller, struct defined in des.h */
int coid; /* return from connect attach  */
int personId;
int weight;

int main(int argc, char **argv) {
	personId = 0;
	weight = 0;

	/*Phase I*/

	/*get des_controller PID from command-line arguments*/
	if (argc != 2) {/*if not valid amount of arguments*/
		perror("Not a valid amount of arguments");
		exit(EXIT_FAILURE);
	}
	serverPid = atoi(argv[1]);

	/*Connect to a communication channel created by des_controller*/
	coid = ConnectAttach(ND_LOCAL_NODE, serverPid, 1, _NTO_SIDE_CHANNEL, 0);
	if (coid == -1) {/*If error*/
		perror("Error during ConnectAttach()");
		exit(EXIT_FAILURE);
	}

	/*Phase II*/
	while (1) {/*infinite loop*/
		char desEvent[12];/*stores event*/
		printf(
				"Enter the device (ls= left scan, rs= right scan, ws= weight scale, lo =left open, ro=right open, lc =left closed, rc = right closed , gru = guard right unlock, grl = guard right lock, gll=guard left lock,glu = guard left unlock)\n");/*output menu for user*/
		scanf("%s", &desEvent);/*store user input*/
		if (strcmp(desEvent, "ls") == 0) {/*if left scan*/
			/*take person ID from user and set struct */
			/*Taking ID from user and setting the person struct to be sent*/
			printf("Enter person ID: \n");
			scanf("%d", &personId);
			person.person_id = personId;
			person.direction = 0;
			person.state_holder = (int) INPUT_LS;/*set state of LS in person struct from input*/
		} else if (strcmp(desEvent, "rs") == 0) {/*if right scan*/
			/*Taking ID from user and setting the person struct to be sent*/
			printf("Enter person ID: \n");
			scanf("%d", &personId);
			person.person_id = personId;
			person.direction = 1;
			person.state_holder = (int) INPUT_RS;/*set state of RS in person struct from input*/
		} else if (strcmp(desEvent, "ws") == 0) {
			/*Taking weight from user and setting the person struct to be sent*/
			printf("Enter weight: \n");
			scanf("%d", &weight);
			person.weight = weight;
			person.state_holder = (int) INPUT_WS;/*set state of WS in person struct from input*/
		} else if (strcmp(desEvent, "lo") == 0) {
			person.state_holder = (int) INPUT_LO;/*set state of LO in person struct from input*/
		} else if (strcmp(desEvent, "ro") == 0) {
			person.state_holder = (int) INPUT_RO;/*set state of RO in person struct from input*/
		} else if (strcmp(desEvent, "lc") == 0) {
			person.state_holder = (int) INPUT_LC;/*set state of LC in person struct from input*/
		} else if (strcmp(desEvent, "rc") == 0) {
			person.state_holder = (int) INPUT_RC;/*set state of RC in person struct from input*/
		} else if (strcmp(desEvent, "gru") == 0) {
			person.state_holder = (int) INPUT_GRU;/*set state of GRU in person struct from input*/
		} else if (strcmp(desEvent, "grl") == 0) {
			person.state_holder = (int) INPUT_GRL;/*set state of GRL in person struct from input*/
		} else if (strcmp(desEvent, "gll") == 0) {
			person.state_holder = (int) INPUT_GLL;/*set state of GLL in person struct from input*/
		} else if (strcmp(desEvent, "glu") == 0) {
			person.state_holder = (int) INPUT_GLU;/*set state of GLU in person struct from input*/
		} else if (strcmp(desEvent, "exit") == 0) {
			printf("Exiting");
			break;/*break out of infinite loop*/
		} else {
			person.state_holder = 144;
		}

		/*person.state_holder=desEvent;*/

		/*possible error dsfgjkuehgiuersbgheriug*/
		if (MsgSend(coid, &person, sizeof(person), &display, sizeof(display))
				== -1) {
			printf("msg send inputs error \n");
			exit(EXIT_FAILURE);
		}

	}

	/*Phase III*/
	/*Detach from communication channel with des_controller*/
	ConnectDetach(coid);

	return EXIT_SUCCESS;
}
