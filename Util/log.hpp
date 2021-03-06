#ifndef UTIL_LOG_HPP
#define UTIL_LOG_HPP

#include <string>
#include <iostream>
#include <fstream>
#include "../IACS.h"
#include "prefixedoutstream.hpp"
#include "nulloutstream.hpp"

namespace util{

/**
 * Provides a convenient way to give formatted output.
 *
 * The Log class has four members which can be used in the same way ostreams can
 * be used:
 *
 *  - Log::Debug
 *  - Log::Info
 *  - Log::Warn
 *  - Log::Fatal
 *
 * Each of these will prefix a tag to the output (for easy filtering), and the
 * fatal output will terminate the program when a newline is encountered.  An
 * example is given below.
 *
 * @code
 * Log::Info << "Checking a condition." << std::endl;
 * if (!someCondition())
 *   Log::Warn << "someCondition() is not satisfied!" << std::endl;
 * Log::Info << "Checking an important condition." << std::endl;
 * if (!someImportantCondition())
 * {
 *   Log::Fatal << "someImportantCondition() is not satisfied! Terminating.";
 *   Log::Fatal << std::endl;
 * }
 * @endcode
 *
 * Any messages sent to Log::Debug will not be shown when compiling in non-debug
 * mode.  Messages to Log::Info will only be shown when the --verbose flag is
 * given to the program (or rather, the CLI class).
 *
 * @see PrefixedOutStream, NullOutStream, CLI
 */
class Log
{
 public:
  /**
   * Checks if the specified condition is true.
   * If not, halts program execution and prints a custom error message.
   * Does nothing in non-debug mode.
   */
  static void Assert(bool condition,
                     const std::string& message = "Assert Failed.");

  /**
   * MLPACK_EXPORT is required for global variables, so that they are properly
   * exported by the Windows compiler.
   */

  // We only use PrefixedOutStream if the program is compiled with debug
  // symbols.
#ifdef DEBUG
  static util::PrefixedOutStream Debug;
#else
  //Dumps debug output into the bit nether regions.
  static util::NullOutStream Debug;
#endif

  //! Prints informational messages if --verbose is specified, prefixed with
  //! [INFO ].
  static  util::PrefixedOutStream Info;

  static  util::PrefixedOutStream Output;

  //! Prints warning messages prefixed with [WARN ].
  static  util::PrefixedOutStream Warn;

  //! Prints fatal messages prefixed with [FATAL], then terminates the program.
  static  util::PrefixedOutStream Fatal;

  static  util::PrefixedOutStream Error;
  //! Reference to cout, if necessary.
  static  std::ostream& cout;
  static  std::ofstream fcout;
};

}; // namespace mlpack

#endif
