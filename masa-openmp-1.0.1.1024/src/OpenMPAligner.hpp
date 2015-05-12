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

#ifndef OPENMP_ALIGNER_HPP_
#define OPENMP_ALIGNER_HPP_

#include "libmasa/libmasa.hpp"

class OpenMPAligner : public AbstractBlockAligner {
public:
	OpenMPAligner(AbstractBlockProcessor* blockProcessor = NULL, BlockAlignerParameters* params = NULL);
	virtual ~OpenMPAligner();
	virtual void printInitialStatistics(FILE* file);

protected:
	virtual void scheduleBlocks(int grid_width, int grid_height);
	virtual void alignBlock(int bx, int by, int i0, int j0, int i1, int j1);

	virtual void increaseBlockStat(const bool pruned);
};

#endif /* OPENMP_ALIGNER_HPP_ */
