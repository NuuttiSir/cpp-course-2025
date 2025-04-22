all: config_debug build run

config_debug:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

config_tests:
	cmake -S . -B build -DPIXELMANCY_BUILD_TESTS=ON

config_asan:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Asan

config_checks:
	cmake -S . -B build -DUSE_STATIC_ANALYZER="clang-tidy;cppcheck" -DPIXELMANCY_ENABLE_CHECKS=ON

config_formatting:
	cmake -S . -B build -DPIXELMANCY_ENABLE_FORMATTERS=ON	

config_release:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

config_fast_build:
	cmake -S . -B build -DPIXELMANCY_ENABLE_PCH=ON -DCMAKE_CXX_COMPILER_LAUNCHER=ccache -DCMAKE_C_COMPILER_LAUNCHER=ccache

build:
	cmake --build build -j

run:
	./build/standalone/PixelmancyExample -h

clean_test:
	cmake --build build/test --target clean -j

clean:
	cmake --build build --target clean

forced_clean:
	rm -rf build

t1:
	./build/tests/PixelmancyTests "[color] test Color distance*"

t1g:
	gdb --args ./build/tests/PixelmancyTests "[color] test Color distances*"

test: build
	./build/tests/PixelmancyTests

check: config_checks
	cmake --build build

check-format: config_formatting build
	cmake --build build --target format

fix-format: config_formatting build
	cmake --build build --target fix-format

compile_commands: all_config
	rm -f compile_commands.json
	ln -s build/compile_commands.json compile_commands.json

.PHONY: test build
