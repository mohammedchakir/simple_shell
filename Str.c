#include "main.h"

	
	_strcpy(err, datash->av[0]);

	_strcat(err, ": ");

	_strcat(err, count);

	_strcat(err, msg2);

	_strcat(err, msg);

	_strcat(err, msg3);

	_strcat(err, "\0");
	write(STDERR_FILENO, err, lenght);
	free(err);
	free(count);



}



