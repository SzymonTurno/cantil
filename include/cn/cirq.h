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
 * @file cn/cirq.h
 *
 * @brief Doubly linked circular list.
 *
 * This header file provides data types, functions and macros that define and
 * operate on doubly linked circular lists.
 *
 *
 * Features
 * --------
 *
 * - Intrusive.
 *
 *
 * Glossary
 * --------
 *
 * | Term | Description                 |
 * | ---- | --------------------------- |
 * | cirq | doubly linked circular list |
 *
 *
 * Usage
 * -----
 *
 * @code
 * typedef SomeData MyData;
 *
 * CN_CIRQ(struct MyCirq, MyData);
 *
 * void push(struct MyCirq** headp, MyData data)
 * {
 *     struct MyCirq* entry = malloc(sizeof(*entry));
 *
 *     *cn_graph_data(entry) = data;
 *     *headp = cn_cirq_ins(*headp, entry);
 * }
 * @endcode
 */

#ifndef CN_CIRQ_H
#define CN_CIRQ_H

#include "cn/graph.h"

/* @cond */
#define _CN_CIRQ_INS(cirq, entry, pos, ...)                                    \
	(cn_graph_recast(                                                      \
		cn_vxcirq_ins(                                                 \
			cn_graph_cast(cirq), cn_graph_cast(entry), (pos)),     \
		(entry)))

#define _CN_CIRQ_REM(cirqp, pos, ...)                                          \
	(cn_graph_recast(cn_vxcirq_rem(cn_adjl_cast(cirqp), (pos)), *(cirqp)))
/* @endcond */

/**
 * @def CN_CIRQ(name, type)
 *
 * @brief Define the *cirq*.
 *
 * @param[in] name The name of the type used for the *cirq*.
 * @param[in] type The type of the data held by @a name.
 *
 * This macro will define a compound type (must be struct or union) @a name,
 * a type for a *cirq* entry that holds the data of the type @a type.
 */
#define CN_CIRQ(name, type) CN_GRAPH(name, 2, type)

/**
 * @def cn_cirq_ins(cirq, ...)
 *
 * @brief Insert, at the given position, an entry into the *cirq*.
 *
 * A call cn_cirq_ins(cirq, entry, pos) will insert the @a entry into the @a
 * cirq at the @a pos. To insert at the head use 0 for the @a pos and to insert
 * at the tail use -1 for the @a pos. The argument @a pos is optional and by
 * default it equals -1.
 *
 * @return The new head.
 *
 * @note Compile with the GNU extension to enable a type check for the @a cirq.
 */
#define cn_cirq_ins(cirq, ...) _CN_CIRQ_INS((cirq), __VA_ARGS__, -1, )

/**
 * @def cn_cirq_rem(...)
 *
 * @brief Remove, at the given position, an entry from the *cirq*.
 *
 * A call cn_cirq_rem(cirqp, pos) will remove an entry from the @a cirqp at the
 * @a pos and will return the removed entry. To remove from the head use 0 for
 * the @a pos and to remove from the tail use -1 for the @a pos. The argument
 * @a pos is optional and by default it equals 0.
 *
 * @return The removed entry.
 *
 * @note Compile with the GNU extension to enable a type check for the @a cirqp.
 */
#define cn_cirq_rem(...) _CN_CIRQ_REM(__VA_ARGS__, 0, )

#endif /* CN_CIRQ_H */
