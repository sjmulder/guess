/*
 * guess.c
 * Copyright (c) 2018, Sijmen J. Mulder <ik@sjmulder.nl>
 *
 * 'guess' is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * 'guess' is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with 'guess'. If not, see <https://www.gnu.org/licenses/>.
 */

#include <sys/syscall.h>

int syscall(int id, ...);

const char welcome[] = "Guessing game!\n\n> ";
const char low[] = "Too low.\n\n> ";
const char high[] = "Too high.\n\n> ";
const char correct[] = "Correct! Let's play another game.\n\n> ";

void
_start(void)
{
	unsigned char secret;
	char c;
	int guess;

	syscall(SYS_write, 1, welcome, sizeof(welcome)-1);
	syscall(SYS_getrandom, &secret, 1, 0);

	while (1) {

		guess = 0;
		while (1) {
			syscall(SYS_read, 0, &c, 1);
			if (c == '\n')
				break;
			if (c >= '0' && c <= '9')
				guess = guess * 10 + (c-'0');
		}

		if (guess < (int)secret)
			syscall(SYS_write, 1, &low, sizeof(low)-1);
		else if (guess > (int)secret)
			syscall(SYS_write, 1, &high, sizeof(high)-1);
		else {
			syscall(SYS_write, 1, &correct, sizeof(correct)-1);
			syscall(SYS_getrandom, &secret, 1, 0);
		}
	}
}
