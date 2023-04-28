CC=g++
CFLAGS=-Wall -Wextra -g3 -Iinclude -Iinclude/ViGEm -std=gnu++17
LDFLAGS=-lws2_32 -Llib -lViGEmClient -lstdc++ -lsetupapi
SRC=src/main.cpp src/decode.cpp src/gamepad.cpp
OBJ=$(SRC:src/%.cpp=obj/%.o)
EXE=bin/LeapSyncServer.exe
UPX=tools/upx.exe

$(EXE): $(OBJ)
	@echo "Linking objects into executable..."
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) > /dev/null 2>&1
	@cp lib/ViGEmClient.dll bin
	@echo "Build completed!"

obj/%.o: src/%.cpp
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

compress: $(EXE)
	@echo "Compressing $(EXE) and bin/ViGEmClient.dll..."
	@$(UPX) --best $(EXE)
	@$(UPX) --best bin/ViGEmClient.dll
	@echo "Compression completed!"

clean:
	@echo "Cleaning up..."
	@rm -f $(OBJ) $(EXE)
	@echo "Cleanup completed!"