
ifeq ($(PLATFORM),AVR)
include $(HALDIR)/core/avr/build.mk
else
$(error Unknown platform $(PLATFORM)!)
endif

OBJECTS = $(addprefix build/,$(SOURCES:.c=.o))

all: build/$(TARGET)

build/$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

build/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(INCLUDES) $(CCFLAGS) -c $< -o $@

build/%.o : $(HALDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(INCLUDES) $(CCFLAGS) -c $< -o $@

clean:
	rm -rvf build
