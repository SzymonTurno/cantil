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
 * @file cn/vertex.h
 *
 * @brief Vertex.
 */

#ifndef CN_VERTEX_H
#define CN_VERTEX_H

#include <stddef.h>

#ifndef OPTIMIZE_VX

#define OPTIMIZE_VX 0

#endif /* OPTIMIZE_VX */

#define CN_VX_MEMCHECK(v)                                                      \
	do {                                                                   \
		if (!OPTIMIZE_VX && !v) {                                      \
			cn_vx_error(__LINE__);                                 \
			return NULL;                                           \
		}                                                              \
	} while (0)

struct CnVertex {
	struct CnVertex* adjl[1];
};

void cn_vx_error(int line);

static inline struct CnVertex*
cn_vx_get(struct CnVertex* v, size_t edge, int pos)
{
	struct CnVertex* p = NULL;

	CN_VX_MEMCHECK(v);
	while (pos-- && (p = v->adjl[edge]))
		v = p;
	return v;
}

static inline struct CnVertex*
cn_vxlist_ins(struct CnVertex* list, struct CnVertex* entry, int pos)
{
	const size_t next = 0;
	struct CnVertex* adjl[] = {list};
	struct CnVertex* v = cn_vx_get((struct CnVertex*)adjl, next, pos);

	CN_VX_MEMCHECK(entry);
	entry->adjl[next] = v->adjl[next];
	v->adjl[next] = entry;
	return adjl[next];
}

static inline struct CnVertex* cn_vxlist_rem(struct CnVertex** list, int pos)
{
	const size_t next = 0;
	struct CnVertex* ret = NULL;
	struct CnVertex* v = cn_vx_get((struct CnVertex*)list, next, pos);

	ret = v->adjl[next];
	v->adjl[next] = ret->adjl[next];
	return ret;
}

static inline struct CnVertex*
cn_vxcirq_ins(struct CnVertex* cirq, struct CnVertex* entry, int pos)
{
	const size_t next = 0;
	const size_t prev = 1;
	struct CnVertex* v = NULL;

	CN_VX_MEMCHECK(entry);
	if (!cirq) {
		entry->adjl[next] = entry;
		entry->adjl[prev] = entry;
		return entry;
	}

	if (pos > 0)
		v = cn_vx_get(cirq, next, pos);
	else if (pos < -1)
		v = cn_vx_get(cirq, prev, -(pos + 1));
	else
		v = cirq;
	entry->adjl[next] = v;
	entry->adjl[prev] = v->adjl[prev];
	v->adjl[prev] = entry;
	entry->adjl[prev]->adjl[next] = entry;
	return pos ? cirq : entry;
}

static inline struct CnVertex* cn_vxcirq_rem(struct CnVertex** cirqp, int pos)
{
	const size_t next = 0;
	const size_t prev = 1;
	struct CnVertex* ret = NULL;

	CN_VX_MEMCHECK(cirqp);
	CN_VX_MEMCHECK(*cirqp);
	ret = *cirqp;
	if (pos > 0)
		ret = cn_vx_get(ret, next, pos);
	else if (pos < 0)
		ret = cn_vx_get(ret, prev, -pos);
	ret->adjl[next]->adjl[prev] = ret->adjl[prev];
	ret->adjl[prev]->adjl[next] = ret->adjl[next];
	if (ret == ret->adjl[next])
		*cirqp = NULL;
	else if (ret == *cirqp)
		*cirqp = ret->adjl[next];
	return ret;
}

#endif /* CN_VERTEX_H */
