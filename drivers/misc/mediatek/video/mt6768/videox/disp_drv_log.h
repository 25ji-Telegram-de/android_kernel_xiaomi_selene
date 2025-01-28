/*
 * Copyright (C) 2015 MediaTek Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef __DISP_DRV_LOG_H__
#define __DISP_DRV_LOG_H__

#include "display_recorder.h"
#include "ddp_debug.h"
#ifdef CONFIG_MTK_AEE_FEATURE
#include "mt-plat/aee.h"
#endif

#define DISP_LOG_PRINT(level, sub_module, fmt, args...)			\
	dprec_logger_pr(DPREC_LOGGER_DEBUG, fmt, ##args)

#define DISPINFO(string, args...) ((void)0)
#define DISPMSG(string, args...) ((void)0)
#define DISPCHECK(string, args...) ((void)0)
#define DISPWARN(string, args...)					\
	do {								\
		dprec_logger_pr(DPREC_LOGGER_ERROR, string, ##args);	\
		pr_debug("[DISP][%s #%d]warn:"string,			\
				__func__, __LINE__, ##args); \
	} while (0)

#define DISPERR(string, args...)					\
	do {								\
		dprec_logger_pr(DPREC_LOGGER_ERROR, string, ##args);	\
		pr_debug("[DISP][%s #%d]ERROR:"string,			\
				__func__, __LINE__, ##args);		\
	} while (0)

#define DISPPR_FENCE(string, args...) ((void)0)
#define DISPDBG(string, args...) ((void)0)
#define DISPFUNC() ((void)0)
#define DISPFUNCSTART() ((void)0)
#define DISPFUNCEND() ((void)0)
#define DISPDBGFUNC() DISPFUNC()
#define DISPPR_HWOP(string, args...)

#ifdef CONFIG_MTK_AEE_AED
#ifdef CONFIG_MTK_AEE_FEATURE
#define disp_aee_print(string, args...) do {	\
	char disp_name[100];						\
	snprintf(disp_name, 100, "[DISP]"string, ##args); \
	aee_kernel_warning_api(__FILE__, __LINE__, \
		DB_OPT_DEFAULT | DB_OPT_MMPROFILE_BUFFER | \
		DB_OPT_DISPLAY_HANG_DUMP | DB_OPT_DUMP_DISPLAY, \
		disp_name, "[DISP] error"string, ##args);		\
	pr_debug("DISP error: "string, ##args);				\
} while (0)
#else
#define disp_aee_print(string, args...) do {				\
	char disp_name[100];						\
	snprintf(disp_name, 100, "[DISP]"string, ##args);		\
	pr_debug("DISP error: "string, ##args);				\
} while (0)
#endif

#ifdef CONFIG_MTK_AEE_FEATURE
#define disp_aee_db_print(string, args...) \
	do { \
		pr_debug("DISP error:"string, ##args);\
		aee_kernel_exception("DISP", "[DISP]error:%s, %d\n"\
			, __FILE__, __LINE__);\
	} while (0)
#else
#define disp_aee_db_print(string, args...) pr_debug("DISP error:"string, ##args)
#endif
#endif

#define _DISP_PRINT_FENCE_OR_ERR(is_err, string, args...)  ((void)0)

#endif /* __DISP_DRV_LOG_H__ */
