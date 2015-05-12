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

#include <stdio.h>
#include "libmasa/libmasa.hpp"
#include "config.h"
#include "OpenMPAligner.hpp"

/**
 * Header of Execution.
 */
#define HEADER 		PACKAGE_STRING"  -  OpenMP tool for huge sequences alignment"

int main ( int argc, char** argv ) {
	/*
	 * Calling the lib masa entry point. We must suplly an aligner isntance
	 * that will do the hard computational job.
	 */
	return libmasa_entry_point(argc, argv, new OpenMPAligner(new CPUBlockProcessor()), HEADER);
}
