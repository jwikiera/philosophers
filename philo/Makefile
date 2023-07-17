NAME					:= philo

UNAME_S					:= $(shell uname -s)

ifeq ($(UNAME_S),Linux)
  FRAMEWORK				:=
  LINUX_LIBS			:=
  LINUX_INCLUDES		:= -I/usr/include
  OS_FLAG				:= -D LINUX
else
  FRAMEWORK				:=
  LINUX_LIBS			:=
  LINUX_INCLUDES		:=
  OS_FLAG				:= -D OSX
endif

ifndef addressoff
	FSANADDRESS			:= -fsanitize=address
else
	FSANADDRESS			:=
endif

ifndef leakoff
	FSANLEAK			:= -fsanitize=leak
else
	FSANLEAK			:=
endif

ifdef santhread
	FSANTHREAD			:= -fsanitize=thread
else
	FSANTHREAD			:=
endif

ifndef fsanitizeoff
	FSANITIZE			:= -fno-omit-frame-pointer -fstack-protector-all $(FSANADDRESS) $(FSANLEAK) $(FSANTHREAD)
else
	FSANITIZE			:=
endif

ifdef DEBUG
	DEVFLAGS			:= -ggdb $(FSANITIZE)
	OPTFLAG				:= -O0
else
	DEVFLAGS			:=
	OPTFLAG				:= -O3
endif

CC						:= cc
CFLAGS					:= -Wall -Wextra -Werror -pedantic $(OPTFLAG) $(DEVFLAGS) $(OS_FLAG) -pthread
RM						:= rm -f

LIB_DIRECTORY			:= ./libs/

INCLUDE_DIR				:= ./includes/

# lm: default math lib
LIBRARIES				:= -L. $(FRAMEWORK) $(LINUX_LIBS)
INCLUDES				:= -I$(INCLUDE_DIR) $(LINUX_INCLUDES)

SOURCES_DIRECTORY		:= ./sources/
SOURCES_LIST			:= main.c\
							validate_args.c\
							util.c\
							util2.c\
							str_is_int.c\
							ph_atoi_l.c\
							strlcat.c\
							strtrim.c\
							init_struct.c\
							init_sophers.c\
							atoi.c\
							log.c\
							get_fork_status.c\
							mysleep.c\
							mutex_getters.c\
							philo_funcs.c\
							philo_funcs2.c\
							philo_routine.c\
							main_funcs.c\
							free_everything.c\
							init_struct2.c
HEADER_LIST				:= philo.h
HEADER_FILES			:= $(addprefix $(INCLUDE_DIR), $(HEADER_LIST))

OBJECTS_DIRECTORY		:= objects/
OBJECTS_LIST			:= $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS					:= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))


.PHONY: all clean fclean re docker_build docker_run docker_clean

all: $(NAME)

bonus: all

$(OBJECTS_DIRECTORY):
	mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@



$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS) $(HEADER_FILES)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBRARIES) $(INCLUDES) -o $(NAME)


clean:
	rm -rf $(OBJECTS_DIRECTORY)
	rm -rf *.dSYM


clean_philosophers:
	rm -rf $(OBJECTS_DIRECTORY)
	rm -rf *.dSYM


fclean: clean
	rm -f $(NAME)

docker_build:
	docker build -t $(NAME) .

docker_run:
	docker run -it $(NAME)

docker_clean:
	docker system prune -a --volumes

re: fclean all

re_philo: clean_philosophers all

norm:
	norminette includes/ sources/

funcs: $(NAME)
	@echo "Functions used in $(NAME):"
	nm -u $(NAME)
