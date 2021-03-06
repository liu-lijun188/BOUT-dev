
class BoutException;

#ifndef __BOUT_EXCEPTION_H__
#define __BOUT_EXCEPTION_H__

#include <exception>
#include <string>

#include "bout/format.hxx"

using std::string;

/// Throw BoutRhsFail with \p message if any one process has non-zero
/// \p status
void BoutParallelThrowRhsFail(int status, const char* message);

class BoutException : public std::exception {
public:
  BoutException(const char *, ...)
    BOUT_FORMAT_ARGS( 2, 3);
  BoutException(const std::string&);
  ~BoutException() override;

  const char* what() const noexcept override;
  void Backtrace();
protected:
  char *buffer = nullptr;
  static const int BUFFER_LEN = 1024; // Length of char buffer for printing
  int buflen; // Length of char buffer for printing
  string message;
#ifdef BACKTRACE
  static const unsigned int TRACE_MAX = 128;
  void *trace[TRACE_MAX];
  char **messages;
  int trace_size;
  mutable std::string _tmp;
#endif
  std::string BacktraceGenerate() const;
};

class BoutRhsFail : public BoutException {
public:
  BoutRhsFail(const char *, ...)
    BOUT_FORMAT_ARGS( 2, 3);
};

class BoutIterationFail : public BoutException {
public:
  BoutIterationFail(const char *, ...)
    BOUT_FORMAT_ARGS( 2, 3);
};

#endif
