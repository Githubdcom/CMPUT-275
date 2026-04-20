#include <string>
#include <iostream>
#include <sstream>
#include "myMap.h"
using namespace std;
// The below typedef statements (in conjunction with preprocessor macros)
// will define the type keytype to be one of (int,string,float) and
// the type valtype to be one of (int,string,float) so this can be compiled
// with different combinations of KTYPE and VTYPE preprocessor defines to
// build different test harnesses for different types.
typedef
#if KTYPE == 0
int
#elif KTYPE == 1
std::string
#elif KTYPE == 2
float
#endif
keytype;

typedef
#if VTYPE == 0
int
#elif VTYPE == 1
std::string
#elif VTYPE == 2
float
#endif
valtype;


int main() {
  Map<keytype, valtype> map;
  char cmd;
  while (cin >> cmd) {
    switch(cmd) {
      case 's': { // Set value
        // after s there should be a K k and a V v entered into the input stream
        // This then performs
        // map[k] = v;
        keytype key;
        valtype val;
        cin >> key;
        cin >> val;
        map[key] = val;
        break;
      }
      case 'r': { // Read value
        // after r there should be a K k entered into the input stream
        // This performs map[k] and prints out the result.
        // If the key k exists in the map then the resultant value v should
        // be printed, if it doesn't then the key k is added to the map
        // with a default constructed v, and as such that default constructed
        // v will be printed (and the map is mutated).
        keytype key;
        cin >> key;
        cout << map[key] << endl;
        break;
      }
      case 'f': { // Apply the map like a fn
        // after r there should be a K k entered into the input stream
        // This performs map(k) and prints out the result.
        // If the key k exists in the map then the resultant value v should
        // be printed, if it doesn't then a default constructed V should be printed
        // but the map should NOT be mutated.
        keytype key;
        cin >> key;
        cout << map(key) << endl;
        break;
      }
      case 'p': { // Print the contents using the iterator
        // Use this to determine if your index operator and function call operator
        // are correctly mutating (and not mutating) the map! As well as to
        // test if your iterator is implemented correctly.
        stringstream out;
        out << "{";
        for (auto key : map) {
          if (out.str() != "{") out << ", ";
          out << key << ":" << map(key);
        }
        out << "}";
        cout << out.str() << endl;
        break;
      }
      case 'q': {
        // Test cases should end with q, this
        // terminates the program.
        return 0;
      }
    }
  }
}
