# Nom de l'exécutable final
EXEC = detecteur

# Répertoire source et includes
SRC_DIR = src
INC_DIR = include

# Tous les fichiers sources
SRCS = \
	$(SRC_DIR)/main.cpp \
	$(SRC_DIR)/image.cpp \
	$(SRC_DIR)/hough_polaire.cpp \
	$(SRC_DIR)/detection_contours.cpp \
	$(SRC_DIR)/bresenham.cpp \
	$(SRC_DIR)/suppression_doublons.cpp

# Fichiers objets générés
OBJS = $(SRCS:.cpp=.o)

# Commande de compilation
CXX = g++
CXXFLAGS = -I$(INC_DIR) -std=c++17 -Wall

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(EXEC)
