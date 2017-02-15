#include "tests.h"

int main(int argc, char** argss){
  Tester tester;
  if(tester.begin() != 0){
    Base.errorReport();
  }
  tester.end();
  return Base.getErrors();
}