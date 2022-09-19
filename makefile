NAME		= pipex
SRCFILES	= main.c
OBJDIR		= obj

$(NAME) all:

all $(OBJ):
	$(CC) -o $@ $^

OBJ			= $(addprefix obj/, $(SRCFILES:.c=.o))

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) -c $(CFLAGS) $(INC) -o $@ $^

clean:
	rm -rf $(OBJDIR)

fclean clean:
	rm -rf $(NAME)

re:
	make fclean
	make
