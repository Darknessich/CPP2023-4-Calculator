set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable (Calculator 
  "main.cpp"
  "Calculator.cpp" 
  "Calculator.h"  
  "Operators/Operator.h"
  "Operators/StandardOps.h" 
  "DllReader.h" "DllReader.cpp")