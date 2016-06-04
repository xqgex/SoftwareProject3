#include "SPLogger.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//File open mode
#define SP_LOGGER_OPEN_MODE "w"

// Global variable holding the logger
SPLogger logger = NULL;

struct sp_logger_t {
	FILE* outputChannel; // The logger file
	bool isStdOut; // Indicates if the logger is stdout
	SP_LOGGER_LEVEL level; // Indicates the level
};

// Creates and initializes the logger
SP_LOGGER_MSG spLoggerCreate(const char* filename, SP_LOGGER_LEVEL level) {
	if (logger != NULL) { // Already defined
		return SP_LOGGER_DEFINED;
	}
	logger = (SPLogger) malloc(sizeof(*logger));
	if (logger == NULL) { // Allocation failure
		return SP_LOGGER_OUT_OF_MEMORY;
	}
	logger->level = level; // Set the level of the logger
	if (filename == NULL) { // In case the filename is not set use stdout
		logger->outputChannel = stdout;
		logger->isStdOut = true;
	} else { // Otherwise open the file in write mode
		logger->outputChannel = fopen(filename, SP_LOGGER_OPEN_MODE);
		if (logger->outputChannel == NULL) { // Open failed
			free(logger);
			logger = NULL;
			return SP_LOGGER_CANNOT_OPEN_FILE;
		}
		logger->isStdOut = false;
	}
	return SP_LOGGER_SUCCESS;
}

// Closes are frees all resources of the logger
void spLoggerDestroy() {
	if (!logger) {
		return;
	}
	if (!logger->isStdOut) {// Close file only if not stdout
		fclose(logger->outputChannel);
	}
	free(logger);//free allocation
	logger = NULL;
}

// Prints error messages at leves {Error, Warning, Info, Debug}
SP_LOGGER_MSG spLoggerPrintError(const char* msg, const char* file, const char* function, const int line) {
	char out[4096];
	if (logger == NULL) { // If the logger is undefined
			return SP_LOGGER_UNDIFINED;
	}
	if ( (msg==NULL)||(file==NULL)||(function==NULL)||(line<0) ) { // If any of msg or file or function are null or line is negative
		return SP_LOGGER_INVAlID_ARGUMENT;
	}
	out = "---ERROR---" + "\n- file: " + file + "\n- function: " + function + "\n- line: " + line + "\n- message: " + msg;
	return spLoggerPrintMsg(out);
}

// Prints warnning messages at levels {Warning, Info, Debug}
SP_LOGGER_MSG spLoggerPrintWarning(const char* msg, const char* file, const char* function, const int line) {
	char out[4096];
	if (logger == NULL) { // If the logger is undefined
			return SP_LOGGER_UNDIFINED;
	}
	if ( (msg==NULL)||(file==NULL)||(function==NULL)||(line<0) ) { // If any of msg or file or function are null or line is negative
		return SP_LOGGER_INVAlID_ARGUMENT;
	}
	if (logger->level != SP_LOGGER_ERROR_LEVEL) {
		out = "---WARNING---" + "\n- file: " + file + "\n- function: " + function + "\n- line: " + line + "\n- message: " + msg;
		return spLoggerPrintMsg(out);
	} else {
		return SP_LOGGER_SUCCESS;
	}
}

// Prints info messages at levels {Info, Debug}
SP_LOGGER_MSG spLoggerPrintInfo(const char* msg) {
	char out[4096];
	if (logger == NULL) { // If the logger is undefined
			return SP_LOGGER_UNDIFINED;
	}
	if (msg==NULL) { // If msg is null
		return SP_LOGGER_INVAlID_ARGUMENT;
	}
	if ( (logger->level == SP_LOGGER_INFO_WARNING_ERROR_LEVEL)||(logger->level == SP_LOGGER_DEBUG_INFO_WARNING_ERROR_LEVEL) ) {
		out = "---INFO---" + "\n- message: " + msg;
		return spLoggerPrintMsg(out);
	} else {
		return SP_LOGGER_SUCCESS;
	}
}

// Prints debug messages at level {Debug}
SP_LOGGER_MSG spLoggerPrintDebug(const char* msg, const char* file, const char* function, const int line) {
	char out[4096];
	if (logger == NULL) { // If the logger is undefined
			return SP_LOGGER_UNDIFINED;
	}
	if ( (msg==NULL)||(file==NULL)||(function==NULL)||(line<0) ) { // If any of msg or file or function are null or line is negative
		return SP_LOGGER_INVAlID_ARGUMENT;
	}
	if (logger->level == SP_LOGGER_DEBUG_INFO_WARNING_ERROR_LEVEL) {
		out = "---DEBUG---" + "\n- file: " + file + "\n- function: " + function + "\n- line: " + line + "\n- message: " + msg;
		return spLoggerPrintMsg(out);
	} else {
		return SP_LOGGER_SUCCESS;
	}
}

// Prints the exact message at any level (Without formatting)
SP_LOGGER_MSG spLoggerPrintMsg(const char* msg) {
	if (logger == NULL) { // If the logger is undefined
			return SP_LOGGER_UNDIFINED;
	}
	if (msg==NULL) { // If msg is null
		return SP_LOGGER_INVAlID_ARGUMENT;
	}
	printf(msg);
	fflush(stdout);
	return SP_LOGGER_SUCCESS;
	// TODO \/
	// * SP_LOGGER_WRITE_FAIL			- If Write failure occurred
}
