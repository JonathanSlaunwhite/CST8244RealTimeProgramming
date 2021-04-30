/*
 * des.h
 *
 *  Created on: Feb 14, 2021
 *      Author: hurdleg
 */


#ifndef DES_H_
#define DES_H_


//#ifndef DOOR_ENTRY_SYSTEM_H_
//#define DOOR_ENTRY_SYSTEM_H_

#define NUM_STATES 13	// where n = number of states in your finite state machine (FSM)


typedef void *(*ControllerState)();

typedef enum {
//TODO :: to see the list of //TODOS, Window > Show View > Tasks
	//TODO :: assign an enum value, one for each state
	STATE_START = 0,
	STATE_LS = 1,
	STATE_RS = 2,
	STATE_WS = 3,
	STATE_LO = 4,
	STATE_RO = 5,
	STATE_LC = 6,
	STATE_RC = 7,
	STATE_GRU = 8,
	STATE_GRL = 9,
	STATE_GLL = 10,
	STATE_GLU = 11,
	STATE_EXIT = 12
} State;

#define NUM_INPUTS 12	// where n equals the number of input commands that drive the FSM. // From the assignment specification, notice the prompt. Each command, ls, rs, etc. // Count those...
typedef enum {//TODO :: assign an enum value, one for each input command
	INPUT_LS = 0,
	INPUT_RS = 1,
	INPUT_WS = 2,
	INPUT_LO = 3,
	INPUT_RO = 4,
	INPUT_LC = 5,
	INPUT_RC = 6,
	INPUT_GRU = 7,
	INPUT_GRL = 8,
	INPUT_GLL = 9,
	INPUT_GLU = 10,
	INPUT_EXIT = 11
} Input;

const char *inMessage[NUM_INPUTS] = {//TODO :: each input command. For example, "ls"
		"ls",
		"rs",
		"ws",
		"lo",
		"ro",
		"lc",
		"rc",
		"gru",
		"grl",
		"gll",
		"glu",
		"exit"};

//double check ME KINDA UNSURE *******************************************************
#define NUM_OUTPUTS 13	// where n equals the number of output messages from the FSM.
typedef enum {//TODO :: assign an enum value, one for each output message from the FSM
	OUT_START = 0,
	OUT_LS = 1,
	OUT_RS = 2,
	OUT_WS = 3,
	OUT_LO = 4,
	OUT_RO = 5,
	OUT_LC = 6,
	OUT_RC = 7,
	OUT_GRU = 8,
	OUT_GRL = 9,
	OUT_GLL = 10,
	OUT_GLU = 11,
	OUT_EXIT = 12
	} Output;

	const char *outMessage[NUM_OUTPUTS] = {
	    //TODO :: each output message. For example, "Person opened left door"

	     "Waiting for someone to scan.",
	     "Person has scanned from left door with the ID: ",
	     "Person has scanned from right door with the ID: ",
	     "Person has been weighed, weight: ",
	     "The left door has been opened.",
	     "The right door has been opened.",
	     "The left door has been closed.",
	     "The right door has been closed.",
	     "The guard has unlocked the right door.",
	     "The guard has locked the right door.",
	     "The guard has locked the left door.",
	     "The guard has unlocked the left door.",
	     "Program has exited."

	};

// inputs client sends a Person struct to its server, the controller
typedef struct {
	//TODO :: fields for person's ID (int), weight (int), direction (inbound or outbound),
	//	and some way to remember what state the Person is in. Suppose the Person in "Left Scan" state.
	//	You need a way to represent that.

	int person_id;
	int weight;
	int direction;
	int state_holder;//somehow remember state person is in.

} Person;

// controller client sends a Display struct to its server, the display
typedef struct {
	//TODO :: fields for the output message and the Person. For the output message, I used an int, which
	//	is the index into the outMessages array. That way I don't pass strings in my messages.
	//	The Person field is needed, as some output message require information from the Person.
	//	Specifically, those messages that display the Person's ID and weight.

	int msg_array;
	Person person;


} Display;

#endif /* DOOR_ENTRY_SYSTEM_H_ */

