.ONESHELL:

include_flags := -Llibs -Iincludes -Iserver
flags := $(include_flags) -fdiagnostics-color=always
special_flags := -pipe#-O2 -Wall 
special_flags_optimized := -pipe -O0 #-march=native# -Wall 
libs := -lccd -lenet64 -lws2_32 -lwinmm

obj := \
	compiled/server.o \
	compiled/entity.o \
	compiled/net.o \
	compiled/vec.o \
	compiled/kvad.o \
	compiled/vector.o \

src := \
	server/server.c \
	server/entities/entity.c \
	includes/vec.c \
	includes/qdtree/kvad.c \
	includes/vector.c \

headers := \
	server/structs.h \
	server/player/player_t.h \
	server/entities/entity.h \
	server/entities/entity_t.h \
	server/net/net.h \
	server/net/net_t.h \
	includes/vec.h \
	includes/qdtree/kvad.h \
	includes/vector.h \

server_: $(obj)
	gcc -o builds/server.exe $(obj) $(flags) $(libs) $(special_flags)

compiled/vec.o: includes/vec.c $(headers)
	gcc -c includes/vec.c -o compiled/vec.o $(include_flags) $(libs)

compiled/vector.o: includes/vector.c $(headers)
	gcc -c includes/vector.c -o compiled/vector.o $(include_flags) $(libs)

compiled/kvad.o: includes/qdtree/kvad.c $(headers)
	gcc -c includes/qdtree/kvad.c -o compiled/kvad.o $(include_flags) $(libs)

compiled/server.o: server/server.c $(headers)
	gcc -c server/server.c -o compiled/server.o $(include_flags) $(libs)

compiled/entity.o: server/entities/entity.c $(headers)
	gcc -c server/entities/entity.c -o compiled/entity.o $(include_flags) $(libs)

compiled/net.o: server/net/net.c $(headers)
	gcc -c server/net/net.c -o compiled/net.o $(include_flags) $(libs)


# builds/imorter.exe: 
# 	gcc importer/import.c $(special_flags_optimized) -o builds/imorter.exe
# full:
# import_: importer/import.c
# 	gcc importer/import.c $(special_flags) -o builds/imorter.exe
# 	builds/imorter.exe

# uptodate: $()

run: server_
	cd ./builds && \
	server.exe

opt:
	gcc $(flags) $(src) $(libs) $(special_flags_optimized) -o builds/server.exe
	cd ./builds && \
	server.exe