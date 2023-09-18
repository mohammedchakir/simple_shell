#include "main.h"

	
	_strcp(err, datash->av[0]);

	_strconcat(err, ": ");

	_strcat(err, count);

	_strcat(err, msg2);

	_strcat(err, msg);

	_strcat(err, msg3);

	_strccc(err, "\0");

	write(STDERR_FILENO, err, lenght);

	free(err);

	free(count);



}



