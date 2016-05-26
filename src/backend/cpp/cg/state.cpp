#include "backend/cpp/cg/state.hpp"

uint switch_count = 0;

io::FileWriter module_fw{fopen("./module.txt", "w")};
io::FileWriter runtime_fw{fopen("./runtime.txt", "w")};
