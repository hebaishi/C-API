#include "wsa_lib.h"
#include <string.h>

//TODO create a log file method

/**
 * Connect to a WSA through the specified interface method \b intf_method,
 * and communicate control commands in the given \b protocol format
 *
 * @param dev - the WSA device structure to be connected/establised.
 * @param protocol - The standard for control commands communication to the
 * WSA. \n Currently supported protocols are: SCPI, CLI(?).
 * @param intf_method - The interface method to the WSA. \n
 * Possible methods: \n
 * - With LAN, use: "TCPIP::<Ip address of the WSA>::HISLIP" \n
 * - With USB, use: "USB" (check if supported with the WSA version used)
 * 
 * @return 0 on success, or a negative number on error.
 * TODO: define ERROR values with associated messages....
 */
int32_t wsa_connect(struct wsa_device *dev, char *protocol, char *intf_method)
{
	struct wsa_device wsa_dev;
	int32_t result = 0;
	char *temp_str;
	const char* wsa_addr;

	// When the cmd protocol is SCPI:
	if (strncmp(protocol, SCPI, 4) == 0) {
		// if it's a TCPIP connection, get the address
		if(strstr(intf_method, "TCPIP") != NULL) {
			if ((temp_str = strstr(intf_method, "::")) == NULL) {
				printf("ERROR: Invalid TCPIP string \"%s\".\n", intf_method);
				return -1;
			}

			// TODO: there might be a danger here...
			wsa_addr = strtok(temp_str, "::");
		}

		// Can't determine connection method from the interface string
		else {
			printf(" ERROR: Interface method is not recognized/valid!\n");
			return -1;
		}
	}

	// When the command protocol is not supported/recognized
	else {
		printf("Error: Command protocol not supported/recognized!");
		return -1;
	}

	result = start_client(wsa_addr);

	dev = &wsa_dev;

	return result;
}


/**
 * Close the device connection if one is started, stop any existing data 
 * capture, and perform any necessary clean ups.
 *
 * @param dev - The WSA device structure to be closed.
 *
 * @return 0 on success, or a negative number on error.
 */
int32_t wsa_close(struct wsa_device dev)
{
	return 0;
}


/**
 * Open a file or print the help commands information associated with the 
 * WSA used.
 *
 * @param dev - The WSA device structure from which the help information 
 * will be provided.
 *
 * @return 0 on success, or a negative number on error.
 */
int32_t wsa_help(struct wsa_device dev)
{
	// Open the generic SCPI for now
	if(_popen("ThinkRF SCPI DS 101202.pdf", "r") == NULL) {
		printf("ERROR: Failed to opent the SCPI file.\n");
		return -1;
	}
	return 0;
}


/**
 * Send the control command string to the WSA device specified by \b dev. 
 * The commands format must be written according to the specified protocol 
 * in wsa_connect().
 *
 * @param dev - The WSA device structure from which the command is sent to
 * @param command - The control command string written in the format specified 
 * by the protocol in wsa_connect()
 *
 * @return 0 on success, or a negative number on error.
 */
int32_t wsa_send_command(struct wsa_device dev, char *command)
{
	return 0;
}


/**
 * Send query command to the WSA device specified by \b dev. The
 * commands format must be written according to the specified protocol 
 * in wsa_connect().
 *
 * @param dev - The WSA device structure from which the query is sent to
 * @param command - The query command string written in the format specified 
 * by the protocol in wsa_connect()
 *
 * @return The result stored in a wsa_resp struct format.
 */
struct wsa_resp wsa_send_query(struct wsa_device dev, char *command)
{
	struct wsa_resp result;

	return result;
}


//TODO: Determine if string should be returned instead.
/**
 * Querry the WSA for any error
 *
 * @param dev - The WSA device structure from which the error query is sent to
 *
 * @return 0 on success, or a negative number on error.
 */
int32_t wsa_query_error(struct wsa_device dev)
{
	return 0;
}


// this one need better design base on SCPI?
/**
 *
 * @param dev - The WSA device structure from which the command is sent to.
 * @param header - A wsa_frame_header structure of information for the frame.
 * @param i_buf - The unscaled, signed integer I data buffer with size 
 * specified by the frame_size.
 * @param q_buf - The unscaled, signed integer Q data buffer with size 
 * specified by the frame_size.
 * @param frame_size - The number of samples (i.e. {I, Q} sample pairs) to be 
 * captured per frame.
 *
 * @return Number of samples read on success, or a negative number on error.
 */
int32_t wsa_read_data(struct wsa_device *dev, struct wsa_frame_header *header, 
				 int32_t *i_buf, int32_t *q_buf, uint32_t frame_size)
{
	return 0;
}
