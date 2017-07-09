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

#ifndef CPU_H
#define CPU_H

/* Copyright daemon32 2017 */
struct cpu_tsc_struct
{
	int returnval;
	int returnval_vmexit;
	unsigned long long avg;
	unsigned long long vmexit_avg;
} cpu_tsc_avg;

static inline unsigned long long rdtsc_diff();
static inline unsigned long long rdtsc_diff_vmexit();
/* End Copyright daemon32 2017 */

void cpu_rdtsc();
void cpu_rdtsc_force_vmexit();

#endif
