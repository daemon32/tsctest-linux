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

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "cpu.h"
#include "types.h"

/* Copyright Alberto Ortega 2015, 2016 */
static inline unsigned long long rdtsc_diff() {
	unsigned long long ret, ret2;
	unsigned eax, edx;
	__asm__ volatile("rdtsc" : "=a" (eax), "=d" (edx));
	ret  = ((unsigned long long)eax) | (((unsigned long long)edx) << 32);
	__asm__ volatile("rdtsc" : "=a" (eax), "=d" (edx));
	ret2  = ((unsigned long long)eax) | (((unsigned long long)edx) << 32);
	return ret2 - ret;
}

static inline unsigned long long rdtsc_diff_vmexit() {
	unsigned long long ret, ret2;
	unsigned eax, edx;
	__asm__ volatile("rdtsc" : "=a" (eax), "=d" (edx));
	ret  = ((unsigned long long)eax) | (((unsigned long long)edx) << 32);
	/* vm exit forced here. it uses: eax = 0; cpuid; */
	__asm__ volatile("cpuid" : /* no output */ : "a"(0x00));
	/**/
	__asm__ volatile("rdtsc" : "=a" (eax), "=d" (edx));
	ret2  = ((unsigned long long)eax) | (((unsigned long long)edx) << 32);
	return ret2 - ret;
}

void cpu_rdtsc() {
	int i;
	unsigned long long avg = 0;
	for (i = 0; i < 10; i++) {
		avg = avg + rdtsc_diff();
		usleep(5000);
	}
	avg = avg / 10;
	cpu_tsc_avg.avg = avg;
	(avg < 750 && avg > 0) ? (cpu_tsc_avg.returnval = FALSE) : (cpu_tsc_avg.returnval = TRUE);
	return;
}

void cpu_rdtsc_force_vmexit() {
	int i;
	unsigned long long avg = 0;
	for (i = 0; i < 10; i++) {
		avg = avg + rdtsc_diff_vmexit();
		usleep(5000);
	}
	avg = avg / 10;
	cpu_tsc_avg.vmexit_avg = avg;
	(avg < 1000 && avg > 0) ? (cpu_tsc_avg.returnval_vmexit = FALSE) : (cpu_tsc_avg.returnval_vmexit = TRUE);
	return;
}
/* End Copyright Alberto Ortega */
