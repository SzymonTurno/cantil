/*
BSD 3-Clause License

Copyright (c) 2025, Szymon Turno

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * @file cantil/vertex.h
 *
 * @see cn/vertex.h
 */

#ifndef CANTIL_VERTEX_H
#define CANTIL_VERTEX_H

#include "cn/vertex.h"

/** @see cn_vx_get() */
#define vx_get cn_vx_get

/** @see cn_vx2adjl() */
#define vx2adjl cn_vx2adjl

/** @see cn_adjl2vx() */
#define adjl2vx cn_adjl2vx

/** @see cn_vxlist_ins() */
#define vxlist_ins cn_vxlist_ins

/** @see cn_vxlist_rem() */
#define vxlist_rem cn_vxlist_rem

/** @see cn_vxcirq_ins() */
#define vxcirq_ins cn_vxcirq_ins

/** @see cn_vxcirq_rem() */
#define vxcirq_rem cn_vxcirq_rem

#endif /* CANTIL_VERTEX_H */
