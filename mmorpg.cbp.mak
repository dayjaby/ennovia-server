#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.137                       #
#------------------------------------------------------------------------------#


WORKDIR = %cd%

CC = gcc.exe
CXX = g++.exe
AR = ar.exe
LD = g++.exe
WINDRES = windres.exe

INC =  -Iinclude
CFLAGS =  -Wall -fexceptions
RESINC = 
LIBDIR =  -Lsrc
LIB =  -lluabind -lIrrlicht -lfreetype -lws2_32 -lmswsock -lboost_system-mgw44-mt-1_52 -lboost_serialization-mgw44-mt-1_52 C:\\libs\\lua\\lib\\lua5.1.dll
LDFLAGS = 

INC_RELEASE =  $(INC)
CFLAGS_RELEASE =  $(CFLAGS) -O2 -Wall -g
RESINC_RELEASE =  $(RESINC)
RCFLAGS_RELEASE =  $(RCFLAGS)
LIBDIR_RELEASE =  $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE =  $(LDFLAGS) -s
OBJDIR_RELEASE = obj\\Release
DEP_RELEASE = 
OUT_RELEASE = bin\\Release\\mmorpg.exe

INC_TEST =  $(INC)
CFLAGS_TEST =  $(CFLAGS)
RESINC_TEST =  $(RESINC)
RCFLAGS_TEST =  $(RCFLAGS)
LIBDIR_TEST =  $(LIBDIR)
LIB_TEST = $(LIB)
LDFLAGS_TEST =  $(LDFLAGS)
OBJDIR_TEST = .objs
DEP_TEST = 
OUT_TEST = mmorpg.exe

INC_RELEASE_SERVER =  $(INC)
CFLAGS_RELEASE_SERVER =  $(CFLAGS)
RESINC_RELEASE_SERVER =  $(RESINC)
RCFLAGS_RELEASE_SERVER =  $(RCFLAGS)
LIBDIR_RELEASE_SERVER =  $(LIBDIR)
LIB_RELEASE_SERVER = $(LIB)
LDFLAGS_RELEASE_SERVER =  $(LDFLAGS)
OBJDIR_RELEASE_SERVER = .objs
DEP_RELEASE_SERVER = 
OUT_RELEASE_SERVER = mmorpg.exe

OBJ_RELEASE = $(OBJDIR_RELEASE)\\src\\entities\\livingobject.o $(OBJDIR_RELEASE)\\src\\actions.o $(OBJDIR_RELEASE)\\src\\CGUITTFont.o $(OBJDIR_RELEASE)\\main.o $(OBJDIR_RELEASE)\\src\\registry.o $(OBJDIR_RELEASE)\\src\\position.o $(OBJDIR_RELEASE)\\src\\plugins\\GUIPlugin.o $(OBJDIR_RELEASE)\\src\\network\\server.o $(OBJDIR_RELEASE)\\src\\network\\proxies.o $(OBJDIR_RELEASE)\\src\\network\\message_server.o $(OBJDIR_RELEASE)\\src\\network\\message_client.o $(OBJDIR_RELEASE)\\src\\network\\connection.o $(OBJDIR_RELEASE)\\src\\map.o $(OBJDIR_RELEASE)\\src\\graphics.o $(OBJDIR_RELEASE)\\src\\game.o $(OBJDIR_RELEASE)\\src\\eventreceiver.o $(OBJDIR_RELEASE)\\src\\entity.o $(OBJDIR_RELEASE)\\src\\entities\\tile.o $(OBJDIR_RELEASE)\\src\\entities\\player.o $(OBJDIR_RELEASE)\\src\\entities\\object.o $(OBJDIR_RELEASE)\\src\\entities\\locatable.o $(OBJDIR_RELEASE)\\src\\objects.o

OBJ_TEST = $(OBJDIR_TEST)\\src\\entities\\livingobject.o $(OBJDIR_TEST)\\src\\actions.o $(OBJDIR_TEST)\\src\\CGUITTFont.o $(OBJDIR_TEST)\\main.o $(OBJDIR_TEST)\\src\\registry.o $(OBJDIR_TEST)\\src\\position.o $(OBJDIR_TEST)\\src\\plugins\\GUIPlugin.o $(OBJDIR_TEST)\\src\\network\\server.o $(OBJDIR_TEST)\\src\\network\\proxies.o $(OBJDIR_TEST)\\src\\network\\message_server.o $(OBJDIR_TEST)\\src\\network\\message_client.o $(OBJDIR_TEST)\\src\\network\\connection.o $(OBJDIR_TEST)\\src\\map.o $(OBJDIR_TEST)\\src\\graphics.o $(OBJDIR_TEST)\\src\\game.o $(OBJDIR_TEST)\\src\\eventreceiver.o $(OBJDIR_TEST)\\src\\entity.o $(OBJDIR_TEST)\\src\\entities\\tile.o $(OBJDIR_TEST)\\src\\entities\\player.o $(OBJDIR_TEST)\\src\\entities\\object.o $(OBJDIR_TEST)\\src\\entities\\locatable.o $(OBJDIR_TEST)\\src\\objects.o

OBJ_RELEASE_SERVER = $(OBJDIR_RELEASE_SERVER)\\src\\entities\\livingobject.o $(OBJDIR_RELEASE_SERVER)\\src\\actions.o $(OBJDIR_RELEASE_SERVER)\\src\\CGUITTFont.o $(OBJDIR_RELEASE_SERVER)\\server.o $(OBJDIR_RELEASE_SERVER)\\src\\registry.o $(OBJDIR_RELEASE_SERVER)\\src\\position.o $(OBJDIR_RELEASE_SERVER)\\src\\plugins\\GUIPlugin.o $(OBJDIR_RELEASE_SERVER)\\src\\network\\server.o $(OBJDIR_RELEASE_SERVER)\\src\\network\\proxies.o $(OBJDIR_RELEASE_SERVER)\\src\\network\\message_server.o $(OBJDIR_RELEASE_SERVER)\\src\\network\\message_client.o $(OBJDIR_RELEASE_SERVER)\\src\\network\\connection.o $(OBJDIR_RELEASE_SERVER)\\src\\map.o $(OBJDIR_RELEASE_SERVER)\\src\\graphics.o $(OBJDIR_RELEASE_SERVER)\\src\\game.o $(OBJDIR_RELEASE_SERVER)\\src\\eventreceiver.o $(OBJDIR_RELEASE_SERVER)\\src\\entity.o $(OBJDIR_RELEASE_SERVER)\\src\\entities\\tile.o $(OBJDIR_RELEASE_SERVER)\\src\\entities\\player.o $(OBJDIR_RELEASE_SERVER)\\src\\entities\\object.o $(OBJDIR_RELEASE_SERVER)\\src\\entities\\locatable.o $(OBJDIR_RELEASE_SERVER)\\src\\objects.o

all: release test release_server

clean: clean_release clean_test clean_release_server

before_release: 
	cmd /c if not exist bin\\Release md bin\\Release
	cmd /c if not exist $(OBJDIR_RELEASE)\\src\\entities md $(OBJDIR_RELEASE)\\src\\entities
	cmd /c if not exist $(OBJDIR_RELEASE)\\src md $(OBJDIR_RELEASE)\\src
	cmd /c if not exist $(OBJDIR_RELEASE) md $(OBJDIR_RELEASE)
	cmd /c if not exist $(OBJDIR_RELEASE)\\src\\plugins md $(OBJDIR_RELEASE)\\src\\plugins
	cmd /c if not exist $(OBJDIR_RELEASE)\\src\\network md $(OBJDIR_RELEASE)\\src\\network

after_release: 

release: before_release out_release after_release

out_release: $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LDFLAGS_RELEASE) $(LIBDIR_RELEASE) $(OBJ_RELEASE) $(LIB_RELEASE) -o $(OUT_RELEASE)

$(OBJDIR_RELEASE)\\src\\entities\\livingobject.o: src\\entities\\livingobject.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\entities\\livingobject.cpp -o $(OBJDIR_RELEASE)\\src\\entities\\livingobject.o

$(OBJDIR_RELEASE)\\src\\actions.o: src\\actions.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\actions.cpp -o $(OBJDIR_RELEASE)\\src\\actions.o

$(OBJDIR_RELEASE)\\src\\CGUITTFont.o: src\\CGUITTFont.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\CGUITTFont.cpp -o $(OBJDIR_RELEASE)\\src\\CGUITTFont.o

$(OBJDIR_RELEASE)\\main.o: main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c main.cpp -o $(OBJDIR_RELEASE)\\main.o

$(OBJDIR_RELEASE)\\src\\registry.o: src\\registry.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\registry.cpp -o $(OBJDIR_RELEASE)\\src\\registry.o

$(OBJDIR_RELEASE)\\src\\position.o: src\\position.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\position.cpp -o $(OBJDIR_RELEASE)\\src\\position.o

$(OBJDIR_RELEASE)\\src\\plugins\\GUIPlugin.o: src\\plugins\\GUIPlugin.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\plugins\\GUIPlugin.cpp -o $(OBJDIR_RELEASE)\\src\\plugins\\GUIPlugin.o

$(OBJDIR_RELEASE)\\src\\network\\server.o: src\\network\\server.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\network\\server.cpp -o $(OBJDIR_RELEASE)\\src\\network\\server.o

$(OBJDIR_RELEASE)\\src\\network\\proxies.o: src\\network\\proxies.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\network\\proxies.cpp -o $(OBJDIR_RELEASE)\\src\\network\\proxies.o

$(OBJDIR_RELEASE)\\src\\network\\message_server.o: src\\network\\message_server.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\network\\message_server.cpp -o $(OBJDIR_RELEASE)\\src\\network\\message_server.o

$(OBJDIR_RELEASE)\\src\\network\\message_client.o: src\\network\\message_client.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\network\\message_client.cpp -o $(OBJDIR_RELEASE)\\src\\network\\message_client.o

$(OBJDIR_RELEASE)\\src\\network\\connection.o: src\\network\\connection.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\network\\connection.cpp -o $(OBJDIR_RELEASE)\\src\\network\\connection.o

$(OBJDIR_RELEASE)\\src\\map.o: src\\map.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\map.cpp -o $(OBJDIR_RELEASE)\\src\\map.o

$(OBJDIR_RELEASE)\\src\\graphics.o: src\\graphics.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\graphics.cpp -o $(OBJDIR_RELEASE)\\src\\graphics.o

$(OBJDIR_RELEASE)\\src\\game.o: src\\game.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\game.cpp -o $(OBJDIR_RELEASE)\\src\\game.o

$(OBJDIR_RELEASE)\\src\\eventreceiver.o: src\\eventreceiver.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\eventreceiver.cpp -o $(OBJDIR_RELEASE)\\src\\eventreceiver.o

$(OBJDIR_RELEASE)\\src\\entity.o: src\\entity.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\entity.cpp -o $(OBJDIR_RELEASE)\\src\\entity.o

$(OBJDIR_RELEASE)\\src\\entities\\tile.o: src\\entities\\tile.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\entities\\tile.cpp -o $(OBJDIR_RELEASE)\\src\\entities\\tile.o

$(OBJDIR_RELEASE)\\src\\entities\\player.o: src\\entities\\player.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\entities\\player.cpp -o $(OBJDIR_RELEASE)\\src\\entities\\player.o

$(OBJDIR_RELEASE)\\src\\entities\\object.o: src\\entities\\object.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\entities\\object.cpp -o $(OBJDIR_RELEASE)\\src\\entities\\object.o

$(OBJDIR_RELEASE)\\src\\entities\\locatable.o: src\\entities\\locatable.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\entities\\locatable.cpp -o $(OBJDIR_RELEASE)\\src\\entities\\locatable.o

$(OBJDIR_RELEASE)\\src\\objects.o: src\\objects.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\objects.cpp -o $(OBJDIR_RELEASE)\\src\\objects.o

clean_release: 
	cmd /c del /f $(OBJ_RELEASE) $(OUT_RELEASE)
	cmd /c rd bin\\Release
	cmd /c rd $(OBJDIR_RELEASE)\\src\\entities
	cmd /c rd $(OBJDIR_RELEASE)\\src
	cmd /c rd $(OBJDIR_RELEASE)
	cmd /c rd $(OBJDIR_RELEASE)\\src\\plugins
	cmd /c rd $(OBJDIR_RELEASE)\\src\\network

before_test: 
	cmd /c if not exist $(OBJDIR_TEST)\\src\\entities md $(OBJDIR_TEST)\\src\\entities
	cmd /c if not exist $(OBJDIR_TEST)\\src md $(OBJDIR_TEST)\\src
	cmd /c if not exist $(OBJDIR_TEST) md $(OBJDIR_TEST)
	cmd /c if not exist $(OBJDIR_TEST)\\src\\plugins md $(OBJDIR_TEST)\\src\\plugins
	cmd /c if not exist $(OBJDIR_TEST)\\src\\network md $(OBJDIR_TEST)\\src\\network

after_test: 

test: before_test out_test after_test

out_test: $(OBJ_TEST) $(DEP_TEST)
	$(LD) $(LDFLAGS_TEST) $(LIBDIR_TEST) $(OBJ_TEST) $(LIB_TEST) -o $(OUT_TEST)

$(OBJDIR_TEST)\\src\\entities\\livingobject.o: src\\entities\\livingobject.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\entities\\livingobject.cpp -o $(OBJDIR_TEST)\\src\\entities\\livingobject.o

$(OBJDIR_TEST)\\src\\actions.o: src\\actions.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\actions.cpp -o $(OBJDIR_TEST)\\src\\actions.o

$(OBJDIR_TEST)\\src\\CGUITTFont.o: src\\CGUITTFont.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\CGUITTFont.cpp -o $(OBJDIR_TEST)\\src\\CGUITTFont.o

$(OBJDIR_TEST)\\main.o: main.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c main.cpp -o $(OBJDIR_TEST)\\main.o

$(OBJDIR_TEST)\\src\\registry.o: src\\registry.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\registry.cpp -o $(OBJDIR_TEST)\\src\\registry.o

$(OBJDIR_TEST)\\src\\position.o: src\\position.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\position.cpp -o $(OBJDIR_TEST)\\src\\position.o

$(OBJDIR_TEST)\\src\\plugins\\GUIPlugin.o: src\\plugins\\GUIPlugin.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\plugins\\GUIPlugin.cpp -o $(OBJDIR_TEST)\\src\\plugins\\GUIPlugin.o

$(OBJDIR_TEST)\\src\\network\\server.o: src\\network\\server.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\network\\server.cpp -o $(OBJDIR_TEST)\\src\\network\\server.o

$(OBJDIR_TEST)\\src\\network\\proxies.o: src\\network\\proxies.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\network\\proxies.cpp -o $(OBJDIR_TEST)\\src\\network\\proxies.o

$(OBJDIR_TEST)\\src\\network\\message_server.o: src\\network\\message_server.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\network\\message_server.cpp -o $(OBJDIR_TEST)\\src\\network\\message_server.o

$(OBJDIR_TEST)\\src\\network\\message_client.o: src\\network\\message_client.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\network\\message_client.cpp -o $(OBJDIR_TEST)\\src\\network\\message_client.o

$(OBJDIR_TEST)\\src\\network\\connection.o: src\\network\\connection.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\network\\connection.cpp -o $(OBJDIR_TEST)\\src\\network\\connection.o

$(OBJDIR_TEST)\\src\\map.o: src\\map.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\map.cpp -o $(OBJDIR_TEST)\\src\\map.o

$(OBJDIR_TEST)\\src\\graphics.o: src\\graphics.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\graphics.cpp -o $(OBJDIR_TEST)\\src\\graphics.o

$(OBJDIR_TEST)\\src\\game.o: src\\game.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\game.cpp -o $(OBJDIR_TEST)\\src\\game.o

$(OBJDIR_TEST)\\src\\eventreceiver.o: src\\eventreceiver.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\eventreceiver.cpp -o $(OBJDIR_TEST)\\src\\eventreceiver.o

$(OBJDIR_TEST)\\src\\entity.o: src\\entity.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\entity.cpp -o $(OBJDIR_TEST)\\src\\entity.o

$(OBJDIR_TEST)\\src\\entities\\tile.o: src\\entities\\tile.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\entities\\tile.cpp -o $(OBJDIR_TEST)\\src\\entities\\tile.o

$(OBJDIR_TEST)\\src\\entities\\player.o: src\\entities\\player.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\entities\\player.cpp -o $(OBJDIR_TEST)\\src\\entities\\player.o

$(OBJDIR_TEST)\\src\\entities\\object.o: src\\entities\\object.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\entities\\object.cpp -o $(OBJDIR_TEST)\\src\\entities\\object.o

$(OBJDIR_TEST)\\src\\entities\\locatable.o: src\\entities\\locatable.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\entities\\locatable.cpp -o $(OBJDIR_TEST)\\src\\entities\\locatable.o

$(OBJDIR_TEST)\\src\\objects.o: src\\objects.cpp
	$(CXX) $(CFLAGS_TEST) $(INC_TEST) -c src\\objects.cpp -o $(OBJDIR_TEST)\\src\\objects.o

clean_test: 
	cmd /c del /f $(OBJ_TEST) $(OUT_TEST)
	cmd /c rd $(OBJDIR_TEST)\\src\\entities
	cmd /c rd $(OBJDIR_TEST)\\src
	cmd /c rd $(OBJDIR_TEST)
	cmd /c rd $(OBJDIR_TEST)\\src\\plugins
	cmd /c rd $(OBJDIR_TEST)\\src\\network

before_release_server: 
	cmd /c if not exist $(OBJDIR_RELEASE_SERVER)\\src\\entities md $(OBJDIR_RELEASE_SERVER)\\src\\entities
	cmd /c if not exist $(OBJDIR_RELEASE_SERVER)\\src md $(OBJDIR_RELEASE_SERVER)\\src
	cmd /c if not exist $(OBJDIR_RELEASE_SERVER) md $(OBJDIR_RELEASE_SERVER)
	cmd /c if not exist $(OBJDIR_RELEASE_SERVER)\\src\\plugins md $(OBJDIR_RELEASE_SERVER)\\src\\plugins
	cmd /c if not exist $(OBJDIR_RELEASE_SERVER)\\src\\network md $(OBJDIR_RELEASE_SERVER)\\src\\network

after_release_server: 

release_server: before_release_server out_release_server after_release_server

out_release_server: $(OBJ_RELEASE_SERVER) $(DEP_RELEASE_SERVER)
	$(LD) $(LDFLAGS_RELEASE_SERVER) $(LIBDIR_RELEASE_SERVER) $(OBJ_RELEASE_SERVER) $(LIB_RELEASE_SERVER) -o $(OUT_RELEASE_SERVER)

$(OBJDIR_RELEASE_SERVER)\\src\\entities\\livingobject.o: src\\entities\\livingobject.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\entities\\livingobject.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\entities\\livingobject.o

$(OBJDIR_RELEASE_SERVER)\\src\\actions.o: src\\actions.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\actions.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\actions.o

$(OBJDIR_RELEASE_SERVER)\\src\\CGUITTFont.o: src\\CGUITTFont.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\CGUITTFont.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\CGUITTFont.o

$(OBJDIR_RELEASE_SERVER)\\server.o: server.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c server.cpp -o $(OBJDIR_RELEASE_SERVER)\\server.o

$(OBJDIR_RELEASE_SERVER)\\src\\registry.o: src\\registry.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\registry.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\registry.o

$(OBJDIR_RELEASE_SERVER)\\src\\position.o: src\\position.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\position.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\position.o

$(OBJDIR_RELEASE_SERVER)\\src\\plugins\\GUIPlugin.o: src\\plugins\\GUIPlugin.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\plugins\\GUIPlugin.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\plugins\\GUIPlugin.o

$(OBJDIR_RELEASE_SERVER)\\src\\network\\server.o: src\\network\\server.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\network\\server.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\network\\server.o

$(OBJDIR_RELEASE_SERVER)\\src\\network\\proxies.o: src\\network\\proxies.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\network\\proxies.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\network\\proxies.o

$(OBJDIR_RELEASE_SERVER)\\src\\network\\message_server.o: src\\network\\message_server.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\network\\message_server.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\network\\message_server.o

$(OBJDIR_RELEASE_SERVER)\\src\\network\\message_client.o: src\\network\\message_client.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\network\\message_client.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\network\\message_client.o

$(OBJDIR_RELEASE_SERVER)\\src\\network\\connection.o: src\\network\\connection.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\network\\connection.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\network\\connection.o

$(OBJDIR_RELEASE_SERVER)\\src\\map.o: src\\map.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\map.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\map.o

$(OBJDIR_RELEASE_SERVER)\\src\\graphics.o: src\\graphics.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\graphics.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\graphics.o

$(OBJDIR_RELEASE_SERVER)\\src\\game.o: src\\game.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\game.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\game.o

$(OBJDIR_RELEASE_SERVER)\\src\\eventreceiver.o: src\\eventreceiver.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\eventreceiver.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\eventreceiver.o

$(OBJDIR_RELEASE_SERVER)\\src\\entity.o: src\\entity.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\entity.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\entity.o

$(OBJDIR_RELEASE_SERVER)\\src\\entities\\tile.o: src\\entities\\tile.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\entities\\tile.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\entities\\tile.o

$(OBJDIR_RELEASE_SERVER)\\src\\entities\\player.o: src\\entities\\player.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\entities\\player.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\entities\\player.o

$(OBJDIR_RELEASE_SERVER)\\src\\entities\\object.o: src\\entities\\object.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\entities\\object.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\entities\\object.o

$(OBJDIR_RELEASE_SERVER)\\src\\entities\\locatable.o: src\\entities\\locatable.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\entities\\locatable.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\entities\\locatable.o

$(OBJDIR_RELEASE_SERVER)\\src\\objects.o: src\\objects.cpp
	$(CXX) $(CFLAGS_RELEASE_SERVER) $(INC_RELEASE_SERVER) -c src\\objects.cpp -o $(OBJDIR_RELEASE_SERVER)\\src\\objects.o

clean_release_server: 
	cmd /c del /f $(OBJ_RELEASE_SERVER) $(OUT_RELEASE_SERVER)
	cmd /c rd $(OBJDIR_RELEASE_SERVER)\\src\\entities
	cmd /c rd $(OBJDIR_RELEASE_SERVER)\\src
	cmd /c rd $(OBJDIR_RELEASE_SERVER)
	cmd /c rd $(OBJDIR_RELEASE_SERVER)\\src\\plugins
	cmd /c rd $(OBJDIR_RELEASE_SERVER)\\src\\network

.PHONY: before_release after_release clean_release before_test after_test clean_test before_release_server after_release_server clean_release_server
