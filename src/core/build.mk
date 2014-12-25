
ifeq ($(PLATFORM),AVR)
include $(OSDIR)/core/avr/build.mk
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

build/%.o : $(OSDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(INCLUDES) $(CCFLAGS) -c $< -o $@

clean:
	rm -rvf build
