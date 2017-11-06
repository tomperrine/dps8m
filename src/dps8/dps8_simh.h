/*
 Copyright (c) 2007-2013 Michael Mondy
 Copyright 2012-2016 by Harry Reed
 Copyright 2013-2016 by Charles Anthony

 All rights reserved.

 This software is made available under the terms of the
 ICU License -- ICU 1.8.1 and later.
 See the LICENSE file at the top-level directory of this distribution and
 at https://sourceforge.net/p/dps8m/code/ci/master/tree/LICENSE
 */

extern DEVICE scu_dev;

#ifdef ISOLTS
#define isISOLTS (currentRunningCpuIdx != 0)
#else
#if 0 // CPU1 only
#define isISOLTS (currentRunningCpuIdx != 0)
#else // Any CPU
#define isISOLTS true
#endif
#endif

#ifdef SPEED
#define if_sim_debug(dbits, dptr) if ((0))

#else
      // ((dptr != & cpu_dev) || currentRunningCpuIdx == 1) && 

#define if_sim_debug(dbits, dptr) \
  if ( \
      sim_deb && \
      isISOLTS && \
      (((dptr)->dctrl & (dbits)) || (dbits) == 0) && \
      ((dptr != & cpu_dev) || ((1 << currentRunningCpuIdx) & dbgCPUMask)) && \
      ((dptr != & cpu_dev) || sim_deb_segno == NO_SUCH_SEGNO || sim_deb_segno == cpu . PPR . PSR) && \
      ((dptr != & cpu_dev) || sim_deb_ringno == NO_SUCH_RINGNO || sim_deb_ringno == cpu . PPR. PRR) && \
      ((dptr != & cpu_dev) || (! sim_deb_bar) || (! TST_I_NBAR)) && \
      cpu.cycleCnt >= sim_deb_start && \
      (sim_deb_stop == 0 || cpu.cycleCnt < sim_deb_stop) && \
      (sim_deb_mme_cntdwn == 0) && \
      ((dptr != & cpu_dev) | (((dbits) & DBG_TRACE) ? (sim_deb_skip_cnt ++ >= sim_deb_skip_limit) : (sim_deb_skip_cnt >= sim_deb_skip_limit))) \
    ) 
#endif

#ifndef THREADZ
#define dps8_sim_debug _sim_debug
#endif

#undef sim_debug
#ifdef THREADZ
#define sim_debug(dbits, dptr, ...) \
  if_sim_debug((dbits), dptr) \
    dps8_sim_debug ((dbits), dptr, DBG_CTR, __VA_ARGS__); \
  else \
    (void) 0
#else
#define sim_debug(dbits, dptr, ...) \
  if_sim_debug((dbits), dptr) \
    dps8_sim_debug ((dbits), dptr, __VA_ARGS__); \
  else \
    (void) 0
#endif

/* scp Debug flags */

#define DBG_TRACE       (1U << 0)    ///< instruction trace
#define DBG_MSG         (1U << 1)    ///< misc output

#define DBG_REGDUMPAQI  (1U << 2)    ///< A/Q/IR register dump
#define DBG_REGDUMPIDX  (1U << 3)    ///< index register dump
#define DBG_REGDUMPPR   (1U << 4)    ///< pointer registers dump
//#define DBG_REGDUMPADR  (1U << 5)    ///< address registers dump
#define DBG_REGDUMPPPR  (1U << 6)    ///< PPR register dump
#define DBG_REGDUMPDSBR (1U << 7)    ///< descritptor segment base register dump
#define DBG_REGDUMPFLT  (1U << 8)    ///< C(EAQ) floating-point register dump

//#define DBG_REGDUMP     (DBG_REGDUMPAQI | DBG_REGDUMPIDX | DBG_REGDUMPPR | DBG_REGDUMPADR | DBG_REGDUMPPPR | DBG_REGDUMPDSBR | DBG_REGDUMPFLT)
#define DBG_REGDUMP     (DBG_REGDUMPAQI | DBG_REGDUMPIDX | DBG_REGDUMPPR | DBG_REGDUMPPPR | DBG_REGDUMPDSBR | DBG_REGDUMPFLT)

#define DBG_ADDRMOD     (1U << 9)    ///< follow address modifications
#define DBG_APPENDING   (1U << 10)   ///< follow appending unit operations
#define DBG_TRACEEXT    (1U << 11)   ///< extended instruction trace
#define DBG_WARN        (1U << 12)   
#define DBG_DEBUG       (1U << 13)   
#define DBG_INFO        (1U << 14)   
#define DBG_NOTIFY      (1U << 15)   
#define DBG_SIM_USES_16 (1U << 16)
#define DBG_SIM_USES_17 (1U << 17)
#define DBG_SIM_USES_18 (1U << 18)
#define DBG_ERR         (1U << 19)   
#define DBG_ALL (DBG_NOTIFY | DBG_INFO | DBG_ERR | DBG_DEBUG | DBG_WARN | \
                 DBG_ERR | DBG_TRACE )
#define DBG_FAULT       (1U << 20)  ///< follow fault handling
#define DBG_INTR        (1U << 21)  // follow interrupt handling
#define DBG_CORE        (1U << 22)
#define DBG_CYCLE       (1U << 23)
#define DBG_CAC         (1U << 24)
#define DBG_FINAL       (1U << 25)
#define DBG_AVC         (1U << 26)

// Abort codes, used to sort out longjmp's back to the main loop.
// Codes > 0 are simulator stop codes
// Codes < 0 are internal aborts
// Code  = 0 stops execution for an interrupt check (XXX Don't know if I like 
// this or not)
// XXX above is not entirely correct (anymore).


//#define SCPE_OK    0
#define STOP_STOP   1
#define STOP_BKPT   2


// not really STOP codes, but get returned from instruction loops
#define CONT_TRA    -1  // encountered a transfer instruction; don't bump PPR.IC
#define CONT_DIS    -2  // instruction was a DIS 
#define CONT_XEC    -3  // instruction was a XEC or XED 

//
// mask entry flags
//  MTAB_XTD extended entry
//  MTAB_VDV valid for devices
//  MTAB_VUN valid for units
//  MTAB_VALO takes a value (optional)
//  MTAB_VALR takes a value (required)
//  MTAB_NMO valid only in named SHOW
//  MTAB_NC do not convert option value to upper case
//  MTAB_SHP SHOW parameter takes optional value 
 
// Requires a value, DEV and DEVn both work, not in "show"
#define MTAB_unit_value      MTAB_XTD | MTAB_VUN | MTAB_VDV | MTAB_NMO | MTAB_VALR
// Requires a value, DEVn, not in "show"
#define MTAB_unitonly_value      MTAB_XTD | MTAB_VUN | MTAB_NMO | MTAB_VALR
// Requires a value, DEV and DEVn both work, in "show"
#define MTAB_unit_value_show MTAB_XTD | MTAB_VUN | MTAB_VDV | MTAB_VALR
// Requires a value, DEV only, not in "show"
#define MTAB_dev_value     MTAB_XTD | MTAB_VDV | MTAB_NMO | MTAB_VALR
// No value, DEV only, in "show"
#define MTAB_dev_novalue     MTAB_XTD | MTAB_VDV 

// End of list marker
#define MTAB_eol { 0, 0, NULL, NULL, 0, 0, NULL, NULL }

extern uint32 sim_brk_summ, sim_brk_types, sim_brk_dflt;
extern FILE *sim_deb;
#ifdef THREADZ
void dps8_sim_debug (uint32 dbits, DEVICE* dptr, unsigned long long cnt, const char* fmt, ...)
#ifdef __GNUC__
  __attribute__ ((format (printf, 4, 5)))
#endif
;
#endif
#define sim_warn(format, ...) _sim_err (format, ##__VA_ARGS__)
#define sim_err(format, ...) { _sim_err (format, ##__VA_ARGS__); longjmp (cpu.jmpMain, JMP_STOP); }
