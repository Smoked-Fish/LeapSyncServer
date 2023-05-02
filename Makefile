CC=g++
CFLAGS=-Wall -Wextra -g3 -Iinclude -Iinclude/ViGEm -std=gnu++17
LDFLAGS=-lws2_32 -Llib -lViGEmClient -lstdc++ -lsetupapi
SRC=src/main.cpp src/decode.cpp src/gamepad.cpp
OBJ=$(SRC:src/%.cpp=obj/%.o)
EXE=bin/LeapSyncServer.exe
UPX=tools/upx.exe
RC=app.rc
RES=obj/app.res

.PHONY: all clean

all: directories $(EXE)

$(EXE): $(OBJ) $(RES)
	@echo "Linking objects and resources into executable..."
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) > /dev/null 2>&1
	@cp lib/ViGEmClient.dll bin
	@echo "Build completed!"

obj/%.o: src/%.cpp
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(RES): $(RC)
	@echo "Compiling resource file..."
	@windres $(RC) -O coff -o $@

compress: $(EXE)
	@echo "Compressing $(EXE) and bin/ViGEmClient.dll..."
	@$(UPX) --best $(EXE)
	@$(UPX) --best bin/ViGEmClient.dll
	@echo "Compression completed!"

clean:
	@echo "Cleaning up..."
	@rm -rf obj bin
	@echo "Cleanup completed!"

directories:
	@mkdir -p obj bin