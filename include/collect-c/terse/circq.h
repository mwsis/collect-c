/* /////////////////////////////////////////////////////////////////////////
 * File:    collect-c//terse/circq.h
 *
 * Purpose: Circular-queue container terse api.
 *
 * Created: 5th February 2025
 * Updated: 7th February 2025
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <collect-c/circq.h>


/* /////////////////////////////////////////////////////////////////////////
 * terse-form macros
 */

#define CLC_CQ_F_USE_STACK_ARRAY                            COLLECT_C_CIRCQ_F_USE_STACK_ARRAY
#define CLC_CQ_F_OVERWRITE_FRONT_WHEN_FULL                  COLLECT_C_CIRCQ_F_OVERWRITE_FRONT_WHEN_FULL

#define CLC_CQ_define_empty                                 COLLECT_C_CIRCQ_define_empty
#define CLC_CQ_define_on_stack                              COLLECT_C_CIRCQ_define_on_stack
#define CLC_CQ_define_on_stack_with_cb                      COLLECT_C_CIRCQ_define_on_stack_with_callback

#define CLC_CQ_is_empty                                     COLLECT_C_CIRCQ_is_empty
#define CLC_CQ_len                                          COLLECT_C_CIRCQ_len
#define CLC_CQ_spare                                        COLLECT_C_CIRCQ_spare
#define CLC_CQ_at                                           COLLECT_C_CIRCQ_at
#define CLC_CQ_element_index                                COLLECT_C_CIRCQ_element_index
#define CLC_CQ_push_by_ref                                  COLLECT_C_CIRCQ_push_by_ref
#define CLC_CQ_push_by_value                                COLLECT_C_CIRCQ_push_by_value
#define CLC_CQ_pop_back                                     COLLECT_C_CIRCQ_pop_back
#define CLC_CQ_pop_front                                    COLLECT_C_CIRCQ_pop_front
#define CLC_CQ_clear                                        COLLECT_C_CIRCQ_clear


#define clc_cq_allocate_storage                             collect_c_cq_allocate_storage
#define clc_cq_free_storage                                 collect_c_cq_free_storage
#define clc_cq_push_by_ref                                  collect_c_cq_push_by_ref
#define clc_cq_clear                                        collect_c_cq_clear
#define clc_cq_pop_from_back_n                              collect_c_cq_pop_from_back_n
#define clc_cq_pop_from_front_n                             collect_c_cq_pop_from_front_n



/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#pragma once


/* ///////////////////////////// end of file //////////////////////////// */

