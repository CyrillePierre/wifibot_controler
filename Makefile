# Activation/Désactivation du mode
# de débuggage
DEBUG   = yes

# Répertoire des fichiers
SRC_DIR  = src
OBJ_DIR	 = bin

# Divers
MAKE	= make --no-print-directory
DEPFILE	= .depends
RM		= rm -rf
SHELL	= bash

# Règle de compilation
CXX     = g++-4.6
VERSION = -std=c++0x
CFLAGS  = -Wall -Wextra
LDFLAGS = -lpthread
EXEC	= wifibot_controler

ifeq ($(DEBUG), yes)
CFLAGS += -g -O0 #-pg
else
CFLAGS += -O2
endif

CFLAGS += $(VERSION)

### MEMO ###
#   $@  :   nom de la cible
#   $<  :   nom de la première dépendance
#   $^  :   liste des dépendances
#   $+  :   liste des dépendances sans doublons 
#   $?  :   liste des dépendances plus récente que la cible

.SUFFIXES: .cpp .hpp .o

SUBDIRS = $(shell find $(SRC_DIR) -type d | grep -v '\.\w')
OBJ_DIRS = $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SUBDIRS))

SRC	= $(foreach sdir,$(SUBDIRS),$(wildcard $(sdir)/*.cpp))
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

INCOPT = $(addprefix -I, $(SUBDIRS))

vpath %.cpp $(SUBDIRS)

define make-goal
$1/%.o : %.cpp
	@echo -e "\e[01;39mCompilation de $$<...\e[01;31m"
	@if ! $(CXX) $(CFLAGS) $(INCOPT) -c $$< -o $$@; then \
		echo -en "\E[00m"; false; fi
endef


.PHONY : all clean depends check_dirs

all : check_dirs $(EXEC)

# Création des commandes de compilation pour chaque répertoire
$(foreach sdir,$(OBJ_DIRS),$(eval $(call make-goal,$(sdir))))

$(EXEC) : $(OBJ)
	@echo -e "\e[01;39mCompilation du programme $(EXEC)..."
	@echo -en "\e[01;31m"
	@if ! $(CXX) $+ -o $@ $(LDFLAGS) ; then echo -en "\e[00m" ; false ; fi
	@echo -e "\e[01;32m\nCompilation terminée avec succes !";
	@echo -e "\e[00m";

check_dirs : $(OBJ_DIRS)

$(OBJ_DIRS) :
	@mkdir -p $@

clean : 
	$(RM) $(OBJ_DIR) $(EXEC)

dep : $(SRC)
	@$(CXX) $(VERSION) $(INCOPT) -MM $+ \
		| sed -r 's|^(\S*:\s)($(SRC_DIR)/)(\S*/)?|$(OBJ_DIR)/\3\1\2\3|' > $(DEPFILE)

sinclude $(DEPFILE)
