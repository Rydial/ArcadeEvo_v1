############################# System Dependencies ##############################

# Windows OS
ifeq ($(OS), Windows_NT)

endif


# Linux
ifeq ($(shell uname), Linux)

    # Commands
	CLEAR				:= clear
	MKDIR				:= mkdir -p
	RM					:= rm -dfr
	PRINT				:= printf
	TIMESTAMP			:= $(shell date -u +%Y-%m-%d_%I-%M-%S)


    # Functions
	listparents			 = $(foreach d,										   \
							$1,												   \
							$(if $(filter $2,$(d:/=)),						   \
								,											   \
								$(call listparents,$(dir $(d:/=)),$2)) $d)
    rfind 				 = $(foreach d,										   \
							$(wildcard $(1:=/*)),							   \
							$(call rfind,$d,$2) $(filter $(subst *,%,$2),$d))


    # Built-in Compile Variables
	C					:= gcc
	CFLAGS				:= 
	CXX					:= g++
    CXXFLAGS			+= -std=c++20 -Wall -Wextra -pedantic -Werror


    # User-Defined Compile Variables
    DEBUG				:= -g -O0 -fsanitize=address -fsanitize=undefined
	LIBS				:= -lSDL2
	RELEASE				:= -O2 -DNDEBUG


    # Environment Variables
	ENV					:= 

endif


# Mac OS
ifeq ($(shell uname), Darwin)

    # Commands
	CLEAR				:= clear
	MKDIR				:= mkdir -p
	RM					:= rm -dfr
	PRINT				:= printf
	TIMESTAMP			:= $(shell date -u +%Y-%m-%d_%I-%M-%S)


    # Functions
	listparents			 = $(foreach d,										   \
							$1,												   \
							$(if $(filter $2,$(d:/=)),						   \
								,											   \
								$(call listparents,$(dir $(d:/=)),$2)) $d)
    rfind 				 = $(foreach d,										   \
							$(wildcard $(1:=/*)),							   \
							$(call rfind,$d,$2) $(filter $(subst *,%,$2),$d))


    # Built-in Compile Variables
	C					:= gcc
	CFLAGS				:= 
	CXX					:= g++
    CXXFLAGS			+= -std=c++20 -Wall -Wextra -pedantic -Werror


    # User-Defined Compile Variables
    DEBUG				:= -g -O0 -fsanitize=address -fsanitize=undefined
	LIBS				+= -lSDL2main -lSDL2
	RELEASE				:= -O2 -DNDEBUG


    # Environment Variables
	ENV					:= MallocNanoZone=0

endif

################################## Constants ###################################

# Characters
NULL					:= 
SPACE					:= $(NULL) $(NULL)
NEWLINE					:= \n
TAB						:= \t
BACKSPACE				:= \b


# Color
DEFAULT					:= \033[0m
WHITE					:= \033[38;5;15m
YELLOW					:= \033[38;5;226m
ORANGE					:= \033[38;5;208m
RED						:= \033[38;5;196m
GREEN					:= \033[38;5;46m

################################### Functions ##################################

# Print Message to Standard Output
#
# Parameters: 1) Prefix    2) Message    3) Suffix
define print

	$(PRINT) "$(1)$(2)$(DEFAULT)$(3)"

endef


# Print Parenthesized Message to Standard Output
#
# Parameters: 1) Prefix    2) Message    3) Suffix
define printp

	$(PRINT) "$(1)$(WHITE)[ $(2)$(WHITE) ]$(DEFAULT)$(3)"

endef


# Print Empty Line (Newline Character) to Standard Output
define println

	$(PRINT) "$(NEWLINE)"

endef

################################# Directories ##################################

BUILDDIR				:= bin
LIBDIR					:= lib
LOGDIR					:= log
RLSDIR					:= out
SRCDIR					:= src

############################## Compile Variables ###############################

SRC						:= $(call rfind, $(SRCDIR),	*.cpp)					   \
						   $(call rfind, $(LIBDIR),	*.cpp *.c)

BUILD_FOLDERS			:= $(BUILDDIR)/										   \
						   $(addprefix $(BUILDDIR)/,$(sort $(dir $(SRC))))
DEPENDS					:= $(addprefix $(BUILDDIR)/,						   \
							$(filter %.d,$(SRC:.c=.d))						   \
							$(filter %.d,$(SRC:.cpp=.d)))
ERRLOG					:= $(LOGDIR)/err.log
EXEC					:= $(RLSDIR)/$(TIMESTAMP).exe
INCLUDES				:= $(addprefix -I,									   \
						       $(sort $(call listparents, $(sort $(dir $(call  \
							       rfind,$(LIBDIR),*.h *.hpp))),$(LIBDIR)))	   \
		      				   $(sort $(call listparents, $(sort $(dir $(call  \
							   	   rfind,$(SRCDIR),*.h *.hpp))),$(SRCDIR))))
LIBS					:= $(addprefix -L,$(sort $(dir $(call rfind,		   \
							$(LIBDIR), 										   \
							*.a *.so)))) $(LIBS)
MAIN					:= $(BUILDDIR)/main.exe
OBJS					:= $(addprefix $(BUILDDIR)/,						   \
							$(filter %.o,$(SRC:.c=.o))						   \
							$(filter %.o,$(SRC:.cpp=.o)))

################################ Default Target ################################

default: --clear
	@$(call print,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(WHITE)Please specify a target. Use '					   \
		$(BACKSPACE)$(GREEN)make help										   \
		$(BACKSPACE)$(WHITE)' for a list of commands.,						   \
		$(BACKSPACE)$(NEWLINE)$(NEWLINE))

############################### Private Targets ################################

--clear:
	@$(CLEAR)


--errlog: $(LOGDIR)
	@$(NULL) > $(ERRLOG)

ifeq (,$(wildcard $(ERRLOG)))

	@$(call printp,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(GREEN)Error Log Setup,								   \
		$(BACKSPACE)$(NEWLINE))

endif

################################### Targets ####################################

.PHONY: clean debug fullclean help release run test


clean: --clear
	@$(RM) $(MAIN) $(BUILDDIR)/$(SRCDIR)

	@$(call printp,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(GREEN)Compiled Files Removed,							   \
		$(BACKSPACE)$(NEWLINE)$(NEWLINE))


debug: --clear $(BUILD_FOLDERS) --errlog $(OBJS)
	@$(CXX) $(CXXFLAGS) $(DEBUG) $(INCLUDES) $(filter %.o,$^) $(LIBS)		   \
		-o $(MAIN)															   \
		2>> $(ERRLOG); [ $$? -eq 0 ]										   \
	&& 	(																	   \
		$(PRINT) "$(NEWLINE)$(WHITE)[ "										&& \
		$(PRINT) "$(GREEN)Program Compiled"									&& \
		$(PRINT) "$(WHITE) ] [ "											&& \
		$(PRINT) "$(YELLOW)DEBUG"											&& \
		$(PRINT) "$(WHITE) ]$(DEFAULT)$(NEWLINE)$(NEWLINE)")				   \
	||	(																	   \
		$(PRINT) "$(NEWLINE)$(WHITE)[ "										&& \
		$(PRINT) "$(RED)Missing Object Files"								&& \
		$(PRINT) "$(WHITE) ]$(DEFAULT)$(NEWLINE)$(NEWLINE)")


fullclean: --clear
	@$(RM) $(BUILDDIR) $(RLSDIR) $(LOGDIR)

	@$(call printp,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(GREEN)Program Directory Cleaned,						   \
		$(BACKSPACE)$(NEWLINE)$(NEWLINE))

fc: fullclean


help: --clear
	@$(call printp,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(GREEN)Command List,									   \
		$(BACKSPACE)$(NEWLINE))

	@$(call print,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(YELLOW)clean$(TAB)$(TAB)		   						   \
		$(BACKSPACE)$(WHITE) : Delete compiled and debug files.				   \
		$(BACKSPACE)$(NEWLINE))
	
	@$(call print,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(YELLOW)debug$(TAB)$(TAB)		   						   \
		$(BACKSPACE)$(WHITE) : Compile program in DEBUG mode.				   \
		$(BACKSPACE)$(NEWLINE))

	@$(call print,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(YELLOW)fullclean$(TAB)				   				   \
		$(BACKSPACE)$(WHITE) : Restore directory to default state.			   \
		$(BACKSPACE)$(NEWLINE))

	@$(call print,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(YELLOW)help$(TAB)$(TAB)		   						   \
		$(BACKSPACE)$(WHITE) : Show list of make commands.					   \
		$(BACKSPACE)$(NEWLINE))
	
	@$(call print,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(YELLOW)release$(TAB)$(TAB)		   					   \
		$(BACKSPACE)$(WHITE) : Compile program in RELEASE mode.				   \
		$(BACKSPACE)$(NEWLINE))

	@$(call print,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(YELLOW)run$(TAB)$(TAB)		   						   \
		$(BACKSPACE)$(WHITE) : Run compiled program.						   \
		$(BACKSPACE)$(NEWLINE))

	@$(call print,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(YELLOW)test$(TAB)$(TAB)		   						   \
		$(BACKSPACE)$(WHITE) : A test command.								   \
		$(BACKSPACE)$(NEWLINE)$(NEWLINE))


release: --clear $(RLSDIR) --errlog
	@$(CXX) $(CXXFLAGS) $(RELEASE) $(INCLUDES) $(SRC) $(LIBS)		   		   \
		-o $(EXEC)															   \
		2>> $(ERRLOG); [ $$? -eq 0 ]										   \
	&& 	(																	   \
		$(PRINT) "$(NEWLINE)$(WHITE)[ "										&& \
		$(PRINT) "$(GREEN)Program Compiled"									&& \
		$(PRINT) "$(WHITE) ] [ "											&& \
		$(PRINT) "$(YELLOW)RELEASE"											&& \
		$(PRINT) "$(WHITE) ]$(DEFAULT)$(NEWLINE)$(NEWLINE)")				   \
	||	(																	   \
		$(PRINT) "$(NEWLINE)$(WHITE)[ "										&& \
		$(PRINT) "$(RED)Program Compile Failed"								&& \
		$(PRINT) "$(WHITE) ]$(DEFAULT)$(NEWLINE)$(NEWLINE)")


run: --clear --errlog

ifeq (,$(wildcard $(MAIN)))

	@$(call printp,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(RED)Executable Not Found,								   \
		$(BACKSPACE)$(NEWLINE)$(NEWLINE))

else

	@$(call printp,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(GREEN)Program Started,								   \
		$(BACKSPACE)$(NEWLINE))

	@$(ENV) ./$(MAIN) 2>> $(ERRLOG) || true

	@$(call printp,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(GREEN)Program Finished,								   \
		$(BACKSPACE)$(NEWLINE)$(NEWLINE))

endif


test: --clear
	@echo $(LIBS)
	@$(call printp,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(GREEN)Test Complete,									   \
		$(BACKSPACE)$(NEWLINE)$(NEWLINE))

########################### Compilation Dependencies ###########################

$(BUILD_FOLDERS):
	@$(MKDIR) $(BUILD_FOLDERS)

	@$(call printp,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(GREEN)Build Folder Setup,								   \
		$(BACKSPACE)$(NEWLINE))


$(LOGDIR):
	@$(MKDIR) $(LOGDIR)

	@$(call printp,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(GREEN)Log Folder Setup,								   \
		$(BACKSPACE)$(NEWLINE))


$(RLSDIR):
	@$(MKDIR) $(RLSDIR)

	@$(call printp,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(GREEN)Release Folder Setup,							   \
		$(BACKSPACE)$(NEWLINE))

-include $(DEPENDS)

$(BUILDDIR)/%.o: %.cpp
	@$(call print,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(ORANGE)$<$(SPACE)										   \
		$(BACKSPACE)$(YELLOW)==>$(SPACE)									   \
		$(BACKSPACE)$(DEFAULT)$(NULL))

	@$(CXX) $(CXXFLAGS) $(DEBUG) $(INCLUDES) -MMD -MP -c $<					   \
		-o $@																   \
		2>> $(ERRLOG)														   \
	&& 	(																	   \
		$(PRINT) "$(BACKSPACE)$(BACKSPACE)$(BACKSPACE)$(BACKSPACE)"			&& \
		$(PRINT) "$(GREEN)==> "												&& \
		$(PRINT) "$(ORANGE)$@"												&& \
		$(PRINT) "$(DEFAULT)$(NEWLINE)")				 					   \
	|| 	(																	   \
		$(PRINT) "$(BACKSPACE)$(BACKSPACE)$(BACKSPACE)$(BACKSPACE)"			&& \
		$(PRINT) "$(RED)==> "												&& \
		$(PRINT) "$(ORANGE)$@"												&& \
		$(PRINT) "$(DEFAULT)$(NEWLINE)")				 					   \


$(BUILDDIR)/%.o: %.c
	@$(call print,															   \
		$(BACKSPACE)$(NEWLINE),												   \
		$(BACKSPACE)$(ORANGE)$<$(SPACE)										   \
		$(BACKSPACE)$(YELLOW)==>$(SPACE)									   \
		$(BACKSPACE)$(DEFAULT)$(NULL))

	@$(C) $(CFLAGS) $(DEBUG) $(INCLUDES) -MMD -MP -c $<						   \
		-o $@																   \
		2>> $(ERRLOG)														   \
	&& 	(																	   \
		$(PRINT) "$(BACKSPACE)$(BACKSPACE)$(BACKSPACE)$(BACKSPACE)"			&& \
		$(PRINT) "$(GREEN)==> "												&& \
		$(PRINT) "$(ORANGE)$@"												&& \
		$(PRINT) "$(DEFAULT)$(NEWLINE)")				 					   \
	|| 	(																	   \
		$(PRINT) "$(BACKSPACE)$(BACKSPACE)$(BACKSPACE)$(BACKSPACE)"			&& \
		$(PRINT) "$(RED)==> "												&& \
		$(PRINT) "$(ORANGE)$@"												&& \
		$(PRINT) "$(DEFAULT)$(NEWLINE)")
