#include <cstdlib>
#include <iostream>
#include <dirent.h>

int main(int argc, char *argv[]) {
  struct dirent *pDirent;
  DIR *pDir;

  // Ensure correct argument count.
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <dirname>\n";
    return EXIT_FAILURE;
  }

  // Ensure we can open directory.
  pDir = opendir(argv[1]);
  if (pDir == NULL) {
    std::cout << "Cannot open directory '" << argv[1] << "'\n";
    return 1;
  }

  // Process each entry.
  while ((pDirent = readdir(pDir)) != NULL) {
    std::cout << "[" << pDirent->d_name << "]\n" ;
    /* std::cout << "\t- <" << pDirent->d_ino << ">\n" ;
    std::cout << "\t- <" << pDirent->d_off << ">\n" ;
    std::cout << "\t- <" << pDirent->d_reclen << ">\n" ;
    std::cout << "\t- <" << pDirent->d_type << ">\n" ; */
  }

  // Close directory and exit.
  closedir(pDir);
  return EXIT_SUCCESS;
}
