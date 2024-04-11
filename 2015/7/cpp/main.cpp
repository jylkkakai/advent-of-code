#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

bool isNumber(std::string s) {
  if (s.find_first_of("0123456789") != std::string::npos) {
    return true;
  }
  return false;
}

void assign2Wire(std::string line, std::map<std::string, uint16_t> &circuit) {

  std::string din = line.substr(0, line.find(" "));
  std::string dout =
      line.substr(line.rfind(" ") + 1, line.length() - line.find(" "));
  std::map<std::string, uint16_t>::iterator ito = circuit.find(dout);
  if (ito == circuit.end()) {
    if (isNumber(din)) {
      circuit[dout] = std::stoi(din);
    } else {
      std::map<std::string, uint16_t>::iterator it = circuit.find(din);
      if (it != circuit.end()) {
        circuit[dout] = it->second;
      }
    }
  }
}

void logicAnd(std::string line, std::map<std::string, uint16_t> &circuit) {

  std::string dina = line.substr(0, line.find(" "));
  line = line.substr(line.find(" ") + 1, line.length() - line.find(" "));
  std::string dinb =
      line.substr(line.find(" ") + 1, line.find("-") - line.find(" ") - 2);
  std::string dout =
      line.substr(line.rfind(" ") + 1, line.length() - line.find(" "));
  // std::cout << dina << " " << dinb << " " << dout << std::endl;
  std::map<std::string, uint16_t>::iterator ito = circuit.find(dout);
  if (ito == circuit.end()) {
    if (isNumber(dina) && isNumber(dinb)) {
      circuit[dout] = std::stoi(dina) & std::stoi(dinb);
    } else {
      std::map<std::string, uint16_t>::iterator ita = circuit.find(dina);
      std::map<std::string, uint16_t>::iterator itb = circuit.find(dinb);

      if ((ita != circuit.end() && isNumber(dinb))) {
        circuit[dout] = ita->second & std::stoi(dinb);
      } else if (itb != circuit.end() && isNumber(dina)) {
        circuit[dout] = std::stoi(dina) & itb->second;
      } else if (ita != circuit.end() && itb != circuit.end()) {
        circuit[dout] = ita->second & itb->second;
      }
    }
  }
}
void logicOr(std::string line, std::map<std::string, uint16_t> &circuit) {

  std::string dina = line.substr(0, line.find(" "));
  line = line.substr(line.find(" ") + 1, line.length() - line.find(" "));
  std::string dinb =
      line.substr(line.find(" ") + 1, line.find("-") - line.find(" ") - 2);
  // std::cout << dina << " " << dinb << std::endl;
  std::string dout =
      line.substr(line.rfind(" ") + 1, line.length() - line.find(" "));
  std::map<std::string, uint16_t>::iterator ito = circuit.find(dout);
  if (ito == circuit.end()) {
    if (isNumber(dina) && isNumber(dinb)) {
      circuit[dout] = std::stoi(dina) | std::stoi(dinb);
    } else {
      std::map<std::string, uint16_t>::iterator ita = circuit.find(dina);
      std::map<std::string, uint16_t>::iterator itb = circuit.find(dinb);
      //
      // if ((ita != circuit.end() || isNumber(dina)) &&
      //     (itb != circuit.end() || isNumber(dinb))) {
      //   circuit[dout] = ita->second | itb->second;
      // }
      if ((ita != circuit.end() && isNumber(dinb))) {
        circuit[dout] = ita->second | std::stoi(dinb);
      } else if (itb != circuit.end() && isNumber(dina)) {
        circuit[dout] = std::stoi(dina) | itb->second;
      } else if (ita != circuit.end() && itb != circuit.end()) {
        circuit[dout] = ita->second | itb->second;
      }
    }
  }
}
void logicNot(std::string line, std::map<std::string, uint16_t> &circuit) {

  std::string dina =
      line.substr(line.find(" ") + 1, line.find("-") - line.find(" ") - 2);
  // line = line.substr(line.find(" ") + 1, line.length() - line.find(" "));
  // std::string dinb =
  //     line.substr(line.find(" ") + 1, line.find("-") - line.find(" ") -
  //     2);
  // std::cout << dina << "|" << std::endl;
  std::string dout =
      line.substr(line.rfind(" ") + 1, line.length() - line.find(" "));
  std::map<std::string, uint16_t>::iterator ito = circuit.find(dout);
  if (ito == circuit.end()) {
    if (isNumber(dina)) {
      circuit[dout] = ~std::stoi(dina);
    } else {
      std::map<std::string, uint16_t>::iterator ita = circuit.find(dina);

      if (ita != circuit.end()) {
        circuit[dout] = ~ita->second;
      }
    }
  }
}
void logicLshift(std::string line, std::map<std::string, uint16_t> &circuit) {

  std::string dina = line.substr(0, line.find(" "));
  line = line.substr(line.find(" ") + 1, line.length() - line.find(" "));
  std::string dinb =
      line.substr(line.find(" ") + 1, line.find("-") - line.find(" ") - 2);
  std::string dout =
      line.substr(line.rfind(" ") + 1, line.length() - line.find(" "));
  // std::cout << dina << " " << dinb << dout << std::endl;
  std::map<std::string, uint16_t>::iterator ito = circuit.find(dout);
  if (ito == circuit.end()) {
    if (isNumber(dina)) {
      circuit[dout] = std::stoi(dina) < std::stoi(dinb);
    } else {
      std::map<std::string, uint16_t>::iterator ita = circuit.find(dina);
      // std::map<std::string, uint16_t>::iterator itb =
      // circuit.find(dinb);

      if (ita != circuit.end()) {
        circuit[dout] = ita->second << std::stoi(dinb);
      }
    }
  }
}
void logicRshift(std::string line, std::map<std::string, uint16_t> &circuit) {

  std::string dina = line.substr(0, line.find(" "));
  line = line.substr(line.find(" ") + 1, line.length() - line.find(" "));
  std::string dinb =
      line.substr(line.find(" ") + 1, line.find("-") - line.find(" ") - 2);
  // std::cout << dina << " " << dinb << std::endl;
  std::string dout =
      line.substr(line.rfind(" ") + 1, line.length() - line.find(" "));
  std::map<std::string, uint16_t>::iterator ito = circuit.find(dout);
  if (ito == circuit.end()) {
    if (isNumber(dina)) {
      circuit[dout] = std::stoi(dina) >> std::stoi(dinb);
    } else {
      std::map<std::string, uint16_t>::iterator ita = circuit.find(dina);
      // std::map<std::string, uint16_t>::iterator itb =
      // circuit.find(dinb);

      if (ita != circuit.end()) {
        circuit[dout] = ita->second >> std::stoi(dinb);
      }
    }
  }
}
void executeLine(std::string line, std::map<std::string, uint16_t> &circuit) {
  // std::cout << line << std::endl;
  if (line.find("NOT") != std::string::npos) {
    logicNot(line, circuit);
  } else if (line.find("OR") != std::string::npos) {
    logicOr(line, circuit);
  } else if (line.find("AND") != std::string::npos) {
    logicAnd(line, circuit);
  } else if (line.find("LSHIFT") != std::string::npos) {
    logicLshift(line, circuit);
  } else if (line.find("RSHIFT") != std::string::npos) {
    logicRshift(line, circuit);
  } else {
    assign2Wire(line, circuit);
  }
}
int main() {
  std::cout << "Hello, World!" << std::endl;
  std::map<std::string, uint16_t> circuit;
  std::map<std::string, uint16_t>::iterator it;
  std::string line;
  std::vector<std::string> lines;
  std::string ex[] = {"123 -> x",    "456 -> y",        "x AND y -> d",
                      "x OR y -> e", "x LSHIFT 2 -> f", "y RSHIFT 2 -> g",
                      "NOT x -> h",  "NOT y -> i"};

  std::ifstream file("../input.txt");
  while (std::getline(file, line)) {
    lines.push_back(line);
  }
  int x = 0;
  while (circuit.find("a") == circuit.end()) {
    for (size_t j = 0; j < lines.size(); j++) {
      executeLine(lines[j], circuit);
    }
    x++;
  }
  for (std::map<std::string, uint16_t>::iterator it = circuit.begin();
       it != circuit.end(); it++) {
    std::cout << it->first << ":\t" << it->second << std::endl;
  }
  return 0;
}
