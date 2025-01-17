RAYLIB_PATH ?= C:\raylib\raylib
BUILD_MODE  ?= RELEASE
CXX          = g++
CFLAGS       = -c -std=c++17 -Wall -I$(RAYLIB_PATH)\src -Iexternal -DPLATFORM_DESKTOP
ifeq ($(BUILD_MODE), RELEASE)
    CFLAGS += -s -O2
else
    CFLAGS += -g3 -O0 -DDEBUG
endif

LDFLAGS = -static -L$(RAYLIB_PATH)\src -lraylib -lopengl32 -lgdi32 -lwinmm
objects =	main.o \
			Player.o \
			MotiveCreature.o \
			global_resources.o \
			GameWorld.o \
			ScreenManager.o \
			Button.o \
			ButtonBuilder.o \
			Menu.o \
			MainMenu.o \
			SettingsMenu.o \
			AboutMenu.o \
			PauseMenu.o \
			GameOverMenu.o \
			Timer.o \
			Enemy.o \
			EnemyBlock.o \
			EnemiesManager.o \
			PlayersManager.o \
			MenusBackgroundEffects.o \
			AudioManager.o \
			ColorsManager.o \
			resource.o

ifeq ($(BUILD_MODE), DEBUG)
	objects += Logger.o
endif

Dodgy_Blocks: $(objects)
	$(CXX) $(objects) -o Dodgy_Blocks $(LDFLAGS)

main.o: src/main.cpp src/global_resources.hpp src/Singleton.hpp
	$(CXX) src/main.cpp $(CFLAGS)

Player.o: src/Player.cpp src/Player.hpp src/MotiveCreature.hpp src/ScreenManager.hpp src/global_resources.hpp
	$(CXX) src/Player.cpp $(CFLAGS)

MotiveCreature.o:	src/MotiveCreature.cpp src/MotiveCreature.hpp \
					src/ScreenManager.hpp \
					src/global_resources.hpp \
					src/Logger.hpp
	$(CXX) src/MotiveCreature.cpp $(CFLAGS)

global_resources.o: src/global_resources.cpp src/global_resources.hpp \
					src/Singleton.hpp \
					src/GameWorld.hpp \
					src/ScreenManager.hpp \
					src/MainMenu.hpp \
					src/SettingsMenu.hpp \
					src/AboutMenu.hpp \
					src/PauseMenu.hpp \
					src/GameOverMenu.hpp \
					src/Timer.hpp \
					src/EnemiesManager.hpp \
					src/PlayersManager.hpp \
					src/types.hpp \
					src/Logger.hpp \
					src/MenusBackgroundEffects.hpp \
					src/AudioManager.hpp \
					src/ColorsManager.hpp
	$(CXX) src/global_resources.cpp $(CFLAGS)

GameWorld.o:	src/GameWorld.cpp src/GameWorld.hpp \
				src/Player.hpp \
				src/MotiveCreature.hpp \
				src/global_resources.hpp \
				src/Menu.hpp \
				src/Singleton.hpp \
				src/Logger.hpp
	$(CXX) src/GameWorld.cpp $(CFLAGS)

ScreenManager.o: src/ScreenManager.cpp src/ScreenManager.hpp
	$(CXX) src/ScreenManager.cpp $(CFLAGS)

Button.o: src/Button.cpp src/Button.hpp src/global_resources.hpp
	$(CXX) src/Button.cpp $(CFLAGS)

ButtonBuilder.o: src/ButtonBuilder.cpp src/ButtonBuilder.hpp src/Button.hpp
	$(CXX) src/ButtonBuilder.cpp $(CFLAGS)

Menu.o: src/Menu.cpp src/Menu.hpp src/Button.hpp
	$(CXX) src/Menu.cpp $(CFLAGS)

MainMenu.o: src/MainMenu.cpp src/MainMenu.hpp \
			src/ButtonBuilder.hpp \
			src/Menu.hpp \
			src/Button.hpp \
			src/global_resources.hpp
	$(CXX) src/MainMenu.cpp $(CFLAGS)

SettingsMenu.o: src/SettingsMenu.cpp src/SettingsMenu.hpp \
			src/ButtonBuilder.hpp \
			src/Menu.hpp \
			src/Button.hpp \
			src/global_resources.hpp
	$(CXX) src/SettingsMenu.cpp $(CFLAGS)

AboutMenu.o: src/AboutMenu.cpp src/AboutMenu.hpp \
			src/ButtonBuilder.hpp \
			src/Menu.hpp \
			src/Button.hpp \
			src/global_resources.hpp
	$(CXX) src/AboutMenu.cpp $(CFLAGS)

PauseMenu.o:	src/PauseMenu.cpp src/PauseMenu.hpp \
				src/ButtonBuilder.hpp \
				src/Menu.hpp \
				src/Button.hpp \
				src/global_resources.hpp
	$(CXX) src/PauseMenu.cpp $(CFLAGS)

GameOverMenu.o: src/GameOverMenu.cpp src/GameOverMenu.hpp \
				src/ButtonBuilder.hpp \
				src/Menu.hpp \
				src/Button.hpp \
				src/global_resources.hpp
	$(CXX) src/GameOverMenu.cpp $(CFLAGS)

Timer.o: src/Timer.cpp src/Timer.hpp src/global_resources.hpp
	$(CXX) src/Timer.cpp $(CFLAGS)

Enemy.o:	src/Enemy.cpp src/Enemy.hpp \
			src/global_resources.hpp \
			src/Logger.hpp
	$(CXX) src/Enemy.cpp $(CFLAGS)

EnemyBlock.o: src/EnemyBlock.cpp src/EnemyBlock.hpp \
				src/global_resources.hpp \
				src/Enemy.hpp \
				src/MotiveCreature.hpp \
				src/Player.hpp \
				src/Logger.hpp
	$(CXX) src/EnemyBlock.cpp $(CFLAGS)

EnemiesManager.o:	src/EnemiesManager.cpp src/EnemiesManager.hpp \
					src/EnemyBlock.hpp \
					src/Enemy.hpp \
					src/global_resources.hpp \
					src/Logger.hpp
	$(CXX) src/EnemiesManager.cpp $(CFLAGS)

PlayersManager.o: 	src/PlayersManager.cpp src/PlayersManager.hpp \
					src/global_resources.hpp \
					src/Player.hpp
	$(CXX) src/PlayersManager.cpp $(CFLAGS)

Logger.o: src/Logger.cpp src/Logger.hpp
	$(CXX) src/Logger.cpp $(CFLAGS)

MenusBackgroundEffects.o:	src/MenusBackgroundEffects.cpp src/MenusBackgroundEffects.hpp \
							src/global_resources.hpp \
							src/Logger.hpp
	$(CXX) src/MenusBackgroundEffects.cpp $(CFLAGS)

AudioManager.o:	src/AudioManager.cpp src/AudioManager.hpp
	$(CXX) src/AudioManager.cpp $(CFLAGS)

ColorsManager.o: src/ColorsManager.cpp src/ColorsManager.hpp
	$(CXX) src/ColorsManager.cpp $(CFLAGS)

resource.o: resource.rc
	windres resource.rc -o resource.o

############## ASSISTANT TOOLS ##############

# pass the name of the cpp file as a parameter to get a rule of depenedencies using the -MM flag
depsOfSource	?= src/main.cpp
get_deps:
	$(CXX) src/$(depsOfSource) -MM $(CFLAGS)

clean:
	del $(objects)
