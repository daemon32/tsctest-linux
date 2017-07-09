/*    This file is part of tsctest-linux.
 *
 *    tsctest-linux is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    tsctest-linux is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with tsctest-linux.  If not, see <http://www.gnu.org/licenses/>.
*/

/* Copyright 2017 daemon32 */

#include <stdio.h>
#include "cpu.h"
#include "types.h"

int main(int argc, char *argv[])
{
	unsigned long long ret_cpu_rdtsc,
			   ret_cpu_rdtsc_vmexit;

	if(argc > 1 && argv[1][0] == 'v')
		goto vmexit;

	printf("Testing rdtsc variance...\n");
	cpu_rdtsc();
	if(cpu_tsc_avg.returnval == TRUE)
		printf("cpu_rdtsc() == TRACED!\n");
	else
		printf("cpu_rdtsc() == OK!\n");
	ret_cpu_rdtsc = cpu_tsc_avg.avg;
	printf("avg == %llu ticks\n\n", ret_cpu_rdtsc);

vmexit:
	printf("Testing rdtsc variance after vmexit...\n");
	cpu_rdtsc_force_vmexit();
	if(cpu_tsc_avg.returnval_vmexit == TRUE)
		printf("cpu_rdtsc_force_vmexit() == TRACED!\n");
	else
		printf("cpu_rdtsc_force_vmexit() == OK!\n");
	ret_cpu_rdtsc_vmexit = cpu_tsc_avg.vmexit_avg;
	printf("avg_vmexit == %llu ticks\n", ret_cpu_rdtsc_vmexit);

	return 0;
}
