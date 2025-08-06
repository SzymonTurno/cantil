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
 * @file cn/list.h
 *
 * @brief Singly linked list.
 *
 * This header file provides data types, functions and macros that define and
 * operate on singly linked lists.
 *
 *
 * Features
 * --------
 *
 * - Intrusive.
 *
 *
 * Usage
 * -----
 *
 * @code
 * typedef SomeData MyData;
 *
 * CN_LIST(struct MyList, MyData);
 *
 * void push(struct MyList** listp, MyData data)
 * {
 *     struct MyList* entry = malloc(sizeof(*entry));
 *
 *     *cn_graph_data(entry) = data;
 *     *listp = cn_list_ins(*listp, entry);
 * }
 * @endcode
 */

#ifndef CN_LIST_H
#define CN_LIST_H

#include "cn/graph.h"

/* @cond */
#define _CN_LIST_INS(list, entry, pos, ...)                                    \
	(cn_graph_recast(                                                      \
		cn_vxlist_ins(                                                 \
			cn_graph_cast(list), cn_graph_cast(entry), (pos)),     \
		(entry)))

#define _CN_LIST_REM(listp, pos, ...)                                          \
	(cn_graph_recast(cn_vxlist_rem(cn_adjl_cast(listp), (pos)), *(listp)))
/* @endcond */

/**
 * @def CN_LIST(name, type)
 *
 * @brief Define the list.
 *
 * @param[in] name The name of the type used for the list.
 * @param[in] type The type of the data held by @a name.
 *
 * This macro will define a compound type (must be struct or union) @a name,
 * a type for a list entry that holds the data of the type @a type.
 */
#define CN_LIST(name, type) CN_GRAPH(name, 1, type)

/**
 * @def cn_list_foreach(type, i, listp)
 *
 * @brief Traverse the list.
 *
 * Traverse the list of type @a type referenced by @a listp in the forward
 * direcion, assigning every entry in turn to @a i.
 */
#define cn_list_foreach(type, i, listp) cn_graph_foredge(type, i, listp, 0)

/**
 * @def cn_list_ins(list, ...)
 *
 * @brief Insert, at the given position, an entry into the list.
 *
 * A call cn_list_ins(list, entry, pos) will insert the @a entry into the @a
 * list at the @a pos. To insert at the head use 0 for the @a pos and to insert
 * at the tail use -1 for the @a pos. The argument @a pos is optional and by
 * default it equals 0.
 */
#define cn_list_ins(list, ...) _CN_LIST_INS((list), __VA_ARGS__, 0, )

/**
 * @def cn_list_rem(...)
 *
 * @brief Remove, at the given position, an entry from the list.
 *
 * A call cn_list_rem(listp, pos) will remove an entry from the @a listp at the
 * @a pos and will return the removed entry. To remove from the head use 0 for
 * the @a pos and to remove from the tail use -1 for the @a pos. The argument
 * @a pos is optional and by default it equals 0.
 *
 * @return The removed entry.
 */
#define cn_list_rem(...) _CN_LIST_REM(__VA_ARGS__, 0, )

#endif /* CN_LIST_H */
