/* $Id$
 *
 * category.h
 * 
 * Copyright 2001-2002, Meiosys SA (www.meiosys.com). All rights reserved.
 * Copyright 2001-2002, Cedric Le Goater <legoater@meiosys.com>. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef log4c_category_h
#define log4c_category_h

/**
 * @file category.h
 *
 * @brief central class in the log4c package. 
 * 
 * One of the distintive features of log4j (and hence log4c) are
 * hierarchical categories and their evaluation.
 *
 **/   

#include <stdio.h>
#include <stdarg.h>
#include <log4c/defs.h>
#include <log4c/priority.h>
#include <log4c/location_info.h>

__LOG4C_BEGIN_DECLS

struct __log4c_appender;
struct __log4c_category;

/**
 * log4c category class 
 **/
typedef struct __log4c_category	log4c_category_t;

/**
 * Instantiate a log4c_category_t with name @a name. This method
 * does not set priority of the category which is by default @c
 * LOG4C_PRIORITY_NOTSET.
 * 
 * @param a_name The name of the category to retrieve.
 **/
extern log4c_category_t* log4c_category_get(const char* a_name);

/**
 * Constructor for a log4c_category_t.
 *
 * @param a_name the category name
 * @returns a log4c_category object
 * @warning this method should not be called directly. You should use the
 * log4c_category_get() method in order to preserve the categories
 * hierarchy.
 **/
extern log4c_category_t* log4c_category_new(const char* a_name);

/**
 * Destructor for a log4c_category_t.
 *
 * @param a_category the log4c_category_t object
 **/
extern void log4c_category_delete(log4c_category_t* a_category);

/**
 * Return the category name.
 * @param a_category the log4c_category_t object
 * @returns the category name.
 */       
extern const char* log4c_category_get_name(const log4c_category_t* a_category);

/**
 * Returns the Appender for this log4c_category_t, or NULL if no Appender has
 * been set.
 * @param a_category the log4c_category_t object
 * @returns The Appender.
 **/
extern const struct __log4c_appender* log4c_category_get_appender(
    const log4c_category_t* a_category);

/**
 * Get the additivity flag for this log4c_category_t..
 *
 * @param a_category the log4c_category_t object
 * @return the category additivity
 **/
extern int log4c_category_get_additivity(const log4c_category_t* a_category);

/**
 * Returns the assigned Priority, if any, for this log4c_category_t.
 * @param a_category the log4c_category_t object
 * @return Priority - the assigned Priority, can be LOG4C_PRIORITY_NOTSET
 **/
extern int log4c_category_get_priority(const log4c_category_t* a_category);

/**
 * Starting from this category, search the category hierarchy for a set
 * priority and return it. Otherwise, return the priority of the root
 * category.
 *
 * @param a_category the log4c_category_t object
 *
 * @todo the log4c_category_t is designed so that this method executes as
 * quickly as possible. It could even be faster if the set priority was
 * propagated through the children hierarchy of a category.
 **/
extern int log4c_category_get_chainedpriority(const log4c_category_t* a_category);

/**
 * Sets a new appender for this category.
 *
 * @param a_category the log4c_category_t object
 * @param a_appender the new category appender
 * @return the previous category appender
 **/
extern const struct __log4c_appender* log4c_category_set_appender(
    log4c_category_t* a_category,
    struct __log4c_appender* a_appender);
/**
 * Sets a new priority of this category.
 *
 * @param a_category the log4c_category_t object
 * @param a_priority the new priority to set. Use LOG4C_PRIORITY_NOTSET to
 * let the category use its parents priority as effective priority.
 * @return the previous category priority
 **/
extern int log4c_category_set_priority(log4c_category_t* a_category,
                                       int a_priority);

/**
 * Sets a new additivity flag for this category.
 *
 * @param a_category the log4c_category_t object
 * @param a_additivity the new category additivity
 * @return the previous category additivity
 **/
extern int log4c_category_set_additivity(log4c_category_t* a_category,
                                         int a_additivity);
/**
 * prints the log4c_category_t object on a stream
 *
 * @param a_category the log4c_category_t object
 * @param a_stream The stream
 **/ 
extern void log4c_category_print(const log4c_category_t* a_category, FILE* a_stream); 

/** 
 * Returns true if the chained priority of the log4c_category_t is equal to
 * or higher than given priority.
 * @param a_category the log4c_category_t object
 * @param a_priority The priority to compare with.
 * @returns whether logging is enable for this priority.
 **/
static inline int log4c_category_is_priority_enabled(const log4c_category_t* a_category,
						     int a_priority)
{
    return log4c_category_get_chainedpriority(a_category) >= a_priority;
}

/**
 * Return true if the category will log messages with priority @c
 * LOG4C_PRIORITY_FATAL.
 *
 * @param a_category the log4c_category_t object
 * @returns Whether the category will log.
 **/ 
static inline int log4c_category_is_fatal_enabled(const log4c_category_t* a_category)
{	
    return log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_FATAL); 
}
 
/**
 * Return true if the category will log messages with priority @c
 * LOG4C_PRIORITY_ALERT.
 *
 * @param a_category the log4c_category_t object
 * @returns Whether the category will log.
 **/ 
static inline int log4c_category_is_alert_enabled(const log4c_category_t* a_category) 
{	
    return log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_ALERT); 
}
 
/**
 * Return true if the category will log messages with priority @c
 * LOG4C_PRIORITY_CRIT.
 *
 * @param a_category the log4c_category_t object
 * @returns Whether the category will log.
 **/ 
static inline int log4c_category_is_crit_enabled(const log4c_category_t* a_category) 
{	
    return log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_CRIT); 
}
 
/**
 * Return true if the category will log messages with priority @c
 * LOG4C_PRIORITY_ERROR.
 *
 * @param a_category the log4c_category_t object
 * @returns Whether the category will log.
 **/ 
static inline int log4c_category_is_error_enabled(const log4c_category_t* a_category) 
{	
    return log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_ERROR); 
}
 
/**
 * Return true if the category will log messages with priority @c
 * LOG4C_PRIORITY_WARN.
 *
 * @param a_category the log4c_category_t object
 * @returns Whether the category will log.
 **/ 
static inline int log4c_category_is_warn_enabled(const log4c_category_t* a_category) 
{	
    return log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_WARN); 
}
 
/**
 * Return true if the category will log messages with priority @c
 * LOG4C_PRIORITY_NOTICE.
 *
 * @param a_category the log4c_category_t object
 * @returns Whether the category will log.
 **/ 
static inline int log4c_category_is_notice_enabled(const log4c_category_t* a_category) 
{	
    return log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_NOTICE); 
}
 
/**
 * Return true if the category will log messages with priority @c
 * LOG4C_PRIORITY_INFO.
 *
 * @param a_category the log4c_category_t object
 * @returns Whether the category will log.
 **/ 
static inline int log4c_category_is_info_enabled(const log4c_category_t* a_category) 
{	
    return log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_INFO); 
}
 
/**
 * Return true if the category will log messages with priority @c
 * LOG4C_PRIORITY_DEBUG.
 *
 * @param a_category the log4c_category_t object
 * @returns Whether the category will log.
 **/ 
static inline int log4c_category_is_debug_enabled(const log4c_category_t* a_category) 
{	
    return log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_DEBUG); 
}
 
/**
 * Return true if the category will log messages with priority @c
 * LOG4C_PRIORITY_TRACE.
 *
 * @param a_category the log4c_category_t object
 * @returns Whether the category will log.
 **/ 
static inline int log4c_category_is_trace_enabled(const log4c_category_t* a_category) 
{	
    return log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_TRACE); 
}
 
/**
 * @internal
 **/
extern void __log4c_category_vlog(const log4c_category_t* a_category, 
				  const log4c_location_info_t* a_locinfo, 
				  int a_priority,
				  const char* a_format, 
				  va_list a_args);

/**
 * @internal
 *
 * @bug the log4c_location_info_t object is not set correctly. A macro is
 * needed.
 **/
static inline void log4c_category_vlog(const log4c_category_t* a_category, 
				       int a_priority,
				       const char* a_format, 
				       va_list a_args)
{
    const log4c_location_info_t locinfo = LOG4C_LOCATION_INFO_INITIALIZER;

    __log4c_category_vlog(a_category, &locinfo, a_priority, a_format, a_args);
}

/** 
 * Log a message with the specified priority.
 * @param a_category the log4c_category_t object
 * @param a_priority The priority of this log message.
 * @param a_format Format specifier for the string to write 
 * in the log file.
 * @param ... The arguments for a_format 
 **/  
static inline void log4c_category_log(const log4c_category_t* a_category,
				      int a_priority,
				      const char* a_format,
				      ...)
{
    if (log4c_category_is_priority_enabled(a_category, a_priority)) {
	va_list va;
	va_start(va, a_format);
	log4c_category_vlog(a_category, a_priority, a_format, va);
	va_end(va);
    }
}

/** 
 * Log a message with fatal priority.
 * @param a_category the log4c_category_t object
 * @param a_format Format specifier for the string to write 
 * in the log file.
 * @param ... The arguments for a_format 
 **/  
static inline void log4c_category_fatal(const log4c_category_t* a_category,
					const char* a_format,
					...)
{
    if (log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_FATAL)) {
	va_list va;
	va_start(va, a_format);
	log4c_category_vlog(a_category, LOG4C_PRIORITY_FATAL, a_format, va);
	va_end(va);
    }
}

/** 
 * Log a message with alert priority.
 * @param a_category the log4c_category_t object
 * @param a_format Format specifier for the string to write 
 * in the log file.
 * @param ... The arguments for a_format 
 **/  
static inline void log4c_category_alert(const log4c_category_t* a_category,
					const char* a_format,
					...)
{
    if (log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_ALERT)) {
	va_list va;
	va_start(va, a_format);
	log4c_category_vlog(a_category, LOG4C_PRIORITY_ALERT, a_format, va);
	va_end(va);
    }
}

/** 
 * Log a message with crit priority.
 * @param a_category the log4c_category_t object
 * @param a_format Format specifier for the string to write 
 * in the log file.
 * @param ... The arguments for a_format 
 **/  
static inline void log4c_category_crit(const log4c_category_t* a_category,
				       const char* a_format,
				       ...)
{
    if (log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_CRIT)) {
	va_list va;
	va_start(va, a_format);
	log4c_category_vlog(a_category, LOG4C_PRIORITY_CRIT, a_format, va);
	va_end(va);
    }
}

/** 
 * Log a message with error priority.
 * @param a_category the log4c_category_t object
 * @param a_format Format specifier for the string to write 
 * in the log file.
 * @param ... The arguments for a_format 
 **/  
static inline void log4c_category_error(const log4c_category_t* a_category,
					const char* a_format,
					...)
{
    if (log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_ERROR)) {
	va_list va;
	va_start(va, a_format);
	log4c_category_vlog(a_category, LOG4C_PRIORITY_ERROR, a_format, va);
	va_end(va);
    }
}

/** 
 * Log a message with warn priority.
 * @param a_category the log4c_category_t object
 * @param a_format Format specifier for the string to write 
 * in the log file.
 * @param ... The arguments for a_format 
 **/  
static inline void log4c_category_warn(const log4c_category_t* a_category,
				       const char* a_format,
				       ...)
{
    if (log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_WARN)) {
	va_list va;
	va_start(va, a_format);
	log4c_category_vlog(a_category, LOG4C_PRIORITY_WARN, a_format, va);
	va_end(va);
    }
}

/** 
 * Log a message with notice priority.
 * @param a_category the log4c_category_t object
 * @param a_format Format specifier for the string to write 
 * in the log file.
 * @param ... The arguments for a_format 
 **/  
static inline void log4c_category_notice(const log4c_category_t* a_category,
					 const char* a_format,
					 ...)
{
    if (log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_NOTICE)) {
	va_list va;
	va_start(va, a_format);
	log4c_category_vlog(a_category, LOG4C_PRIORITY_NOTICE, a_format, va);
	va_end(va);
    }
}

/** 
 * Log a message with info priority.
 * @param a_category the log4c_category_t object
 * @param a_format Format specifier for the string to write 
 * in the log file.
 * @param ... The arguments for a_format 
 **/  
static inline void log4c_category_info(const log4c_category_t* a_category,
				       const char* a_format,
				       ...)
{
    if (log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_INFO)) {
	va_list va;
	va_start(va, a_format);
	log4c_category_vlog(a_category, LOG4C_PRIORITY_INFO, a_format, va);
	va_end(va);
    }
}

/** 
 * Log a message with debug priority.
 * @param a_category the log4c_category_t object
 * @param a_format Format specifier for the string to write 
 * in the log file.
 * @param ... The arguments for a_format 
 **/  
static inline void log4c_category_debug(const log4c_category_t* a_category,
					const char* a_format,
					...)
{
    if (log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_DEBUG)) {
	va_list va;
	va_start(va, a_format);
	log4c_category_vlog(a_category, LOG4C_PRIORITY_DEBUG, a_format, va);
	va_end(va);
    }
}

/** 
 * Log a message with trace priority.
 * @param a_category the log4c_category_t object
 * @param a_format Format specifier for the string to write 
 * in the log file.
 * @param ... The arguments for a_format 
 **/  
static inline void __log4c_category_trace(const log4c_category_t* a_category,
					  const char* a_format,
					  ...)
{
    if (log4c_category_is_priority_enabled(a_category, LOG4C_PRIORITY_TRACE)) {
	va_list va;
	va_start(va, a_format);
	log4c_category_vlog(a_category, LOG4C_PRIORITY_TRACE, a_format, va);
	va_end(va);
    }
}

#ifdef __GNUC__
#  define log4c_category_trace(a_category, a_format, ...) \
    __log4c_category_trace(a_category, log4c_location "\n" a_format, ##__VA_ARGS__ )
#else
#  define log4c_category_trace __log4c_category_trace
#endif

/**
 * Helper macro to define static categories.
 *
 * @param a_category the log4c_category_t pointer name
 * @param a_name the category name
 * @warning needs GCC support
 **/
#ifdef __GNUC__
#   define log4c_category_define(a_category, a_name) \
static log4c_category_t* a_category = NULL; \
static void __attribute__ ((constructor)) __log4c_init_category##a_category(void) \
{ a_category = log4c_category_get(a_name); }
#else
#   define log4c_category_define(a_category, a_name)
#endif

/**
 * @internal
 **/
struct __sd_factory;
extern struct __sd_factory* log4c_category_factory;

__LOG4C_END_DECLS

#endif
