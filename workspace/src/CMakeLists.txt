INCLUDE_DIRECTORIES("${PROJECT_INCLUDE_DIR}")

SET(COMMON_SRCS 
	Mundo.cpp 
	Esfera.cpp
	Plano.cpp
	Raqueta.cpp
	Vector2D.cpp
	)
				
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)

# 1. Ejecutable del juego principal
ADD_EXECUTABLE(tenis tenis.cpp ${COMMON_SRCS})
TARGET_LINK_LIBRARIES(tenis glut GL GLU)

# 2. Ejecutable del logger (FIFO)
add_executable(logger logger.cpp)

# 3. Ejecutable del bot autónomo (Memoria proyectada con mmap)
add_executable(bot bot.cpp Esfera.cpp Raqueta.cpp Plano.cpp Vector2D.cpp)
TARGET_LINK_LIBRARIES(bot glut GL GLU)
