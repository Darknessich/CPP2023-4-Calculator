set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable (Calculator 
  "main.cpp"
  "Calculator.cpp" 
  "Calculator.h"  
  "Operators/Operator.h"
  "Operators/StandardOps.h" 
  "Loader.h" 
  "Loader.cpp" 
  "Solver.h" 
  "Solver.cpp"
 "Parser.cpp" "Parser.h"  )