Build examples

emcc main.cpp -std=c++11 -s WASM=1 -O3 -o main.js

emcc main.cpp -std=c++11 -s WASM=1 -O3 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']" -o main.js

emrun --no_browser --port 8080 .