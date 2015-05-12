/*******************************************************************************
 *
 * Copyright (c) 2010-2015   Edans Sandes
 *
 * This file is part of MASA-OpenMP.
 * 
 * MASA-OpenMP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * MASA-OpenMP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with MASA-OpenMP.  If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

#include "OpenMPAligner.hpp"
#include <omp.h>

OpenMPAligner::OpenMPAligner(AbstractBlockProcessor* blockProcessor, BlockAlignerParameters* params)
		: AbstractBlockAligner(blockProcessor, params) {
	setPreferredSizes(0, omp_get_max_threads()*2);
}

OpenMPAligner::~OpenMPAligner() {
	// TODO Auto-generated destructor stub
}

void OpenMPAligner::scheduleBlocks(int grid_width, int grid_height) {
	for (int d = 0; (d < grid_height+grid_width+1) && mustContinue(); d++) {
		int bound = (d+1 < grid_width) ? d+1 : grid_width;
		#pragma omp parallel for schedule(dynamic,1)
		for (int bx=0; bx < bound; bx++) {
				int by=d-bx;
				if (by >= grid_height || !mustContinue()) continue;
				AbstractBlockAligner::alignBlock(bx, by);
		}
	}
}

void OpenMPAligner::alignBlock(int bx, int by, int i0, int j0, int i1, int j1) {
	/* The blocks in the top-most positions must read the first row */
	if (by == 0) {
		/* Receives the first row chunk [j0..j1] from the MASA-core */
		receiveFirstRow(row[bx], j1 - j0);
	}

	/* The blocks in the left-most positions must read the first column */
	if (bx == 0) {
		/* Puts the H[i-1][j-1] dependency in the first cell of the column. */
		col[by][0] = getFirstColumnTail();

		/* Receives the first column chunk from the MASA-core */
		receiveFirstColumn(col[by]+1, i1 - i0);
	}

	/*
	 * The processBlock function executes the SW/NW recurrence function
	 * for all the cells of this block.
	 * See the input/output parameters description in the function implementation.
	 */
	if (!mustContinue()) return; // MASA-core is telling to stop
	AbstractBlockAligner::processBlock(bx, by, i0, j0, i1, j1);

	/*
	 * Dispatch special rows with a minimum defined distance (getSpecialRowInterval()).
	 */
	if (isSpecialRow(by)) {
		#pragma omp critical
		{
			if (bx == 0) {
				/* The left-most blocks must send an extra cell to represent the
				 * very first column of the matrix. */
				cell_t first_cell = getFirstColumnTail();
				first_cell.f = -INF;
				dispatchRow(i1, &first_cell, 1);
			}
			dispatchRow(i1, row[bx], j1-j0); // Dispatch the special row.
		}
	}

	/*
	 * The right-most blocks must dispatch the last column to MASA.
	 */
	if (isSpecialColumn(bx)) {
		if (by == 0) {
			/* The left-most blocks must send an extra cell to represent the
			 * very first column of the matrix. */
			cell_t first_cell = getFirstRowTail();
			first_cell.f = -INF;
			dispatchColumn(j1, &first_cell, 1);
		}
		dispatchColumn(j1, col[by]+1, i1-i0);
	}

}

/*
 * Changes statistics in a safe way.
 */
void OpenMPAligner::increaseBlockStat(const bool pruned) {
	#pragma omp critical
	{
		AbstractBlockAligner::increaseBlockStat(pruned);
	}
}

/**
 * Prints the runtime parameters.
 * @param file handler to print out the statistics.
 * @see IAligner::printInitialStatistics
 */
void OpenMPAligner::printInitialStatistics(FILE* file) {
	AbstractBlockAligner::printInitialStatistics(file);
	fprintf(file, "OpenMP max threads: %d\n", omp_get_max_threads());
}
