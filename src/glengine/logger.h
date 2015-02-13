#ifndef LOGGER_H
#define LOGGER_H

#include <log4cpp/Category.hh>

#ifdef __FILENAME__
#define LOGGED_FROM __FILENAME__ << ":" << __LINE__ << " "
#else
#include <string.h>
#define LOGGED_FROM                                                \
  (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) \
      << ":" << __LINE__ << " "
#endif

#define DEBUG() log4cpp::Category::getRoot().debugStream() << LOGGED_FROM
#define EMERGENCY() log4cpp::Category::getRoot().emergStream() << LOGGED_FROM
#define ALERT() log4cpp::Category::getRoot().alertStream() << LOGGED_FROM
#define CRITICAL() log4cpp::Category::getRoot().critStream() << LOGGED_FROM
#define ERROR() log4cpp::Category::getRoot().errorStream() << LOGGED_FROM
#define WARNING() log4cpp::Category::getRoot().warnStream() << LOGGED_FROM
#define NOTICE() log4cpp::Category::getRoot().noticeStream() << LOGGED_FROM
#define INFO() log4cpp::Category::getRoot().infoStream() << LOGGED_FROM

#endif  // LOGGER_H
