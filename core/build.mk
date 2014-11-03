
OBJECTS = $(addprefix build/,$(SOURCES:.c=.o))

all: build/$(TARGET)

build/$(TARGET): $(OBJECTS)
	@echo $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

build/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c $< -o $@

build/%.o : $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -rvf build
