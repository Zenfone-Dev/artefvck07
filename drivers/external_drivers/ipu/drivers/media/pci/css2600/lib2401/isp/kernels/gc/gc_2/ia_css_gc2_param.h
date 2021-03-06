/*
 * Support for Intel Camera Imaging ISP subsystem.
 *
 * Copyright (c) 2010 - 2014 Intel Corporation. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#ifndef __IA_CSS_GC2_PARAM_H
#define __IA_CSS_GC2_PARAM_H

#include "type_support.h"
/* Extend GC1 */
#include "gc/gc_1.0/ia_css_gc_param.h"
#include "csc/csc_1.0/ia_css_csc_param.h"

#ifndef PIPE_GENERATION
#if defined(IS_VAMEM_VERSION_1)
#define SH_CSS_ISP_RGB_GAMMA_TABLE_SIZE IA_CSS_VAMEM_1_RGB_GAMMA_TABLE_SIZE
#elif defined(IS_VAMEM_VERSION_2)
#define SH_CSS_ISP_RGB_GAMMA_TABLE_SIZE IA_CSS_VAMEM_2_RGB_GAMMA_TABLE_SIZE
#else
#error "Undefined vamem version"
#endif

#else
/* For pipe generation, the size is not relevant */
#define SH_CSS_ISP_RGB_GAMMA_TABLE_SIZE 0
#endif

/* This should be vamem_data_t, but that breaks the pipe generator */
struct sh_css_isp_rgb_gamma_vamem_params {
	uint16_t gc[SH_CSS_ISP_RGB_GAMMA_TABLE_SIZE];
};

#endif /* __IA_CSS_GC2_PARAM_H */
