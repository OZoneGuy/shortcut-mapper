NF = \033[0m
BOLD = \033[1m

# build project
cmake:
	@cmake --build build/

# Run test file Called Test{}.cpp
# Test%: cmake
# 	@echo -e "Testing \033[31m$(BOLD)$* $(NF)"
# 	@./build/tests/$@ --gtest_color=yes


# Generate required file for clangd lsp
clangd:
	cd build; cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
	ln -sf build/compile_commands.json .
