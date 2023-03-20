// MAIN

/**
 * @file main.cc
 * @author Celeste Luis Díaz (alu0101321660@ull.edu.es)
 * @brief Programa cliente
 *  ** Compilar utilizando el comando: make
 *  ** Ejecutar utilizando el comando: make run
 *  ** Limpiar utilizando el comando: make clean
 * @version 0.1
 * @date 2023-02-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>

#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <map>
#include <fstream>
#include <stack>

#include "../include/bigint.h"

std::vector<std::string> readData(std::string filename);
int getBase(std::string line);

template<size_t Base>
void processData(std::vector<std::pair<std::string, BigInt<Base>>> &board, std::string data);

template<size_t Base>
int getIndexOfKey(std::vector<std::pair<std::string, BigInt<Base>>> &board, std::string key);

template<size_t Base>
bool checkKey(std::vector<std::pair<std::string, BigInt<Base>>> &board, std::string key);

template <size_t Base>
void printBoard(std::vector<std::pair<std::string, BigInt<Base>>> &board, std::ofstream &fileout);

int main() {

    const int baseHex = 16;
    const int baseDecimal = 10;
    const int baseOctal = 8;
    const int baseBinary = 2;

    std::vector<std::string> data = readData("P1_B10.txt");
    int base = getBase(data[0]);

    switch (base) {
        
        case 10:
            {
                std::vector<std::pair<std::string, BigInt<baseDecimal>>> board;
                for (int i = 1; i < data.size(); i++) {
                    processData<baseDecimal>(board, data[i]);
                }
                std::ofstream fileout("output.txt");
                printBoard<baseDecimal>(board, fileout);
                fileout.close();
                break;
            }
        case 2: 
            {
                std::vector<std::pair<std::string, BigInt<baseBinary>>> board;
                for (int i = 1; i < data.size(); i++) {
                    processData<baseBinary>(board, data[i]);
                }
                std::ofstream fileout("output.txt");
                printBoard<baseBinary>(board, fileout);
                fileout.close();
                break;
            }

        case 8:
            {
                std::vector<std::pair<std::string, BigInt<baseOctal>>> board;
                for (int i = 1; i < data.size(); i++) {
                    processData<baseOctal>(board, data[i]);
                }
                std::ofstream fileout("output.txt");
                printBoard<baseOctal>(board, fileout);
                fileout.close();
                break;
            }

        case 16:
            {
                std::vector<std::pair<std::string, BigInt<baseHex>>> board;
                for (int i = 1; i < data.size(); i++) {
                    processData<baseHex>(board, data[i]);
                }
                std::ofstream fileout("output.txt");
                printBoard<baseHex>(board, fileout);
                fileout.close();
                break;
            }
        default:
            std::cout << "Base not supported" << std::endl;
            break;
    }
    return 0;
}

std::vector<std::string> readData(std::string filename) {
    std::ifstream filein(filename);
    std::vector<std::string> data;
    std::string line;
    while (std::getline(filein, line)) {
        data.push_back(line);
    }
    return data;
}

int getBase(std::string line) {
    line.erase(0, line.find("=") + 1);
    // Delete spaces
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    return std::stoi(line);
}

template<size_t Base>
void processData(std::vector<std::pair<std::string, BigInt<Base>>> &board, std::string data) {
    std::string key = data.substr(0, data.find("=") - 1);

    // Introducir en un vector todos los tokens despues del =
    std::vector<std::string> tokens;
    std::istringstream iss(data.substr(data.find("=") + 1));
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }

    std::stack<std::string> stack;

    if (tokens.size() == 1) {
        BigInt<Base> value(tokens[0]);
        board.push_back(std::make_pair(key, value));
    } else {
        for (int i = 0; i < tokens.size();++i) {
            if (tokens[i] == "+") {
                BigInt<Base> value1 = board[getIndexOfKey(board, stack.top())].second;
                stack.pop();
                BigInt<Base> value2 = board[getIndexOfKey(board, stack.top())].second;
                stack.pop();
                BigInt<Base> result = value1 + value2;

                if (checkKey(board, key)) {
                    board[getIndexOfKey(board, key)].second = result;
                } else {
                    board.push_back(std::make_pair(key, result));
                }

                stack.push(board[getIndexOfKey(board, key)].first);
                
            } else if (tokens[i] == "-") {
                BigInt<Base> value1 = board[getIndexOfKey(board, stack.top())].second;
                stack.pop();
                BigInt<Base> value2 = board[getIndexOfKey(board, stack.top())].second;
                stack.pop();
                BigInt<Base> result = value1 - value2;

                if (checkKey(board, key)) {
                    board[getIndexOfKey(board, key)].second = result;
                } else {
                    board.push_back(std::make_pair(key, result));
                }

                stack.push(board[getIndexOfKey(board, key)].first);
                
            } else if (tokens[i] == "*")  {
                BigInt<Base> value1 = board[getIndexOfKey(board, stack.top())].second;
                stack.pop();
                BigInt<Base> value2 = board[getIndexOfKey(board, stack.top())].second;
                stack.pop();
                BigInt<Base> result = value1 * value2;

                if (checkKey(board, key)) {
                    board[getIndexOfKey(board, key)].second = result;
                } else {
                    board.push_back(std::make_pair(key, result));
                }

                stack.push(board[getIndexOfKey(board, key)].first);

            } else {
                stack.push(tokens[i]);
            }
            // Imprimir la pila
            std::cout << "Stack: [ ";
            std::stack<std::string> temp = stack;
            while (!temp.empty()) {
                std::cout << temp.top() << " ";
                temp.pop();
            }
            std::cout << "]" << std::endl;
        }
    }
}

template<size_t Base>
int getIndexOfKey(std::vector<std::pair<std::string, BigInt<Base>>> &board, std::string key) {
    for (int i = 0; i < board.size(); i++) {
        if (board[i].first == key) {
            return i;
        }
    }
    return -1;
}

template <size_t Base>
bool checkKey(std::vector<std::pair<std::string, BigInt<Base>>> &board, std::string key) {
    for (int i = 0; i < board.size(); i++) {
        if (board[i].first == key) {
            return true;
        }
    }
    return false;
}

template <size_t Base>
void printBoard(std::vector<std::pair<std::string, BigInt<Base>>> &board, std::ofstream &fileout) {
    for (int i = 0; i < board.size(); i++) {
        fileout << board[i].first << " => " << board[i].second << std::endl;
    }
}

