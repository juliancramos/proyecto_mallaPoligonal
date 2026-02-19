#ifndef _SISTEMA_H
#define _SISTEMA_H

#include <string>
#include <vector>
class Sistema {

public:
  static std::vector<std::string> separarComando(const std::string &entrada);

  static void ayuda(const std::string &comando);
};
#endif