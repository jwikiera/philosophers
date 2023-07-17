NAME					:= philo_bonus

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
	FSANITIZE			:= -fno-omit-frame-pointer -fstack-protector-all $(FSANADDRESS) $(FSANTHREAD) # $(FSANLEAK)
else
	FSANITIZE			:=
endif

ifdef DEBUG
	DEVFLAGS			:= -ggdb $(FSANITIZE)
	OPTFLAG				:= -O0
else
	DEVFLAGS			:=
	OPTFLAG				:= -O0
endif

CC						:= cc
CFLAGS					:= -Wall -Wextra -Werror -pedantic -pthread $(OPTFLAG) $(DEVFLAGS) $(OS_FLAG)
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
							atoi.c\
							itoa.c\
							log.c\
							mysleep.c\
							philo_funcs.c\
							philo_routine.c\
							main_funcs.c\
							panic_exit.c\
							death_checker.c\
							mutex_get_set.c\
							solo_routine.c\
							sem_wrappers.c

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
