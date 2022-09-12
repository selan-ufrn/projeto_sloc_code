/*!
 * @file main.cpp
 * @description
 * This program implements a single line of code count for C/C++ programs.
 * @author	Add your name here
 * @date	September, 9th 2022.
 * @remark On 2022-09-9 changed ...
 */
#include <algorithm>
#include <array>
#include <cstdlib>
#include <dirent.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <vector>
using std::map;
#include <string>
using std::string;
#include <string_view>
#include <optional>

//== Enumerations

/// This enumeration lists all the supported languages.
enum lang_type_e {
  C = 0,  //!< C language
  CPP,    //!< C++ language
  H,      //!< C/C++ header
  HPP,    //!< C++ header
  UNDEF,  //!< Undefined type.
};

//== Class/Struct declaration

/// Integer type for counting lines.
using count_t = unsigned long;
/// Stores the file information we are collecting.
class FileInfo {
 public:
  string filename;     //!< the filename.
  lang_type_e type;    //!< the language type.
  count_t n_blank;     //!< # of blank lines in the file.
  count_t n_comments;  //!< # of comment lines.
  count_t n_loc;       //!< # lines of code.
  count_t n_lines;     //!< # of lines.

 public:
  /// Ctro.
  FileInfo(const string &fn = "",
           lang_type_e t = UNDEF,
           count_t nb = 0,
           count_t nc = 0,
           count_t nl = 0,
           count_t ni = 0)
      : filename{ fn }, type{ t }, n_blank{ nb }, n_comments{ nc }, n_loc{ nl }, n_lines{ ni } {
    /* empty*/
  }
};

/// The running options provided via CLI.
struct RunningOpt {
  string input_name;  //!< This might be a filename or a directory.
};

//== Aux functions

// trim from left
inline std::string ltrim(const std::string &s, const char *t = " \t\n\r\f\v") {
  std::string clone{ s };
  clone.erase(0, clone.find_first_not_of(t));
  return clone;
}
// trim from right
inline std::string rtrim(const std::string &s, const char *t = " \t\n\r\f\v") {
  // TODO
  return s;
}
// trim from left & right
inline std::string trim(const std::string &s, const char *t = " \t\n\r\f\v") {
  // TODO
  return s;
}

/// Returns true if file exists and can be opened.
bool file_exists(const string &str) {
  std::ifstream fs{ str };
  return fs.is_open();
}


//== Main entry

int main(int argc, char *argv[]) {
  // RunningOpt runop = parse_cmd_line(argc, argv);
  // auto src_files = list_of_src_files(runop.input_name);
  // auto database = count_lines(src_files);
  // show_info(database);

  return EXIT_SUCCESS;
}
