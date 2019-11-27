Build examples

emcc hello.cpp -std=c++11 -s WASM=1 -O3 -o hello.js
emcc external.cpp -std=c++11 -s WASM=1 -O3 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']" -o external.js
emcc webgl.cpp -std=c++11 -s WASM=1 -O3 -o webgl.js

emrun --no_browser --port 8080 .