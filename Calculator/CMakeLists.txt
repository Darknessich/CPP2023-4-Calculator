set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable (Calculator 
  "main.cpp"
  "Calculator.cpp" 
  "Calculator.h"
  
  "Operators/Operator.h"
  "Operators/StandardOps.h" 
  "Operators/StandardOps.cpp"
  
  "Logics/Loader.h" 
  "Logics/Loader.cpp"    
  "Logics/Parser.h"   
  "Logics/Parser.cpp"  
  "Logics/Validator.h" 
  "Logics/Validator.cpp"  
  "Logics/Flipper.h"
  "Logics/Flipper.cpp"
  "Logics/Solver.h" 
  "Logics/Solver.cpp")