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
 * @file cn/graph.h
 *
 * @brief Graph.
 */

#ifndef CN_GRAPH_H
#define CN_GRAPH_H

#include "cn/vertex.h"
#include <stdint.h>

#ifdef __STRICT_ANSI__
#define CN_TYPEOF(var) void*
#else
#define CN_TYPEOF(var) __typeof__(var)
#endif

#define CN_GRAPH(name, deg, type)                                              \
	name                                                                   \
	{                                                                      \
		struct CnVertex* cantil_adj_list[deg];                         \
		type cantil_graph_data;                                        \
	}

#define cn_adjl_cast(graphp)                                                   \
	(0 ? (*(graphp))->cantil_adj_list : (struct CnVertex**)(graphp))

#define cn_graph_cast(graph)                                                   \
	(0 ? (struct CnVertex*)(graph)->cantil_adj_list                        \
	   : (struct CnVertex*)(graph))

#define cn_graph_recast(vp, graph)                                             \
	(0 ? (CN_TYPEOF(graph))(intptr_t)((graph)->cantil_adj_list &&          \
	                                  (vp)->adjl)                          \
	   : ((CN_TYPEOF(graph))(vp)))

#define cn_graph_data(graph) (&(graph)->cantil_graph_data)

#define cn_graph_foredge(type, i, graphp, edge)                                \
	for (type** i = graphp; *i; i = (type**)&(*i)->cantil_adj_list[edge])

#endif /* CN_GRAPH_H */
