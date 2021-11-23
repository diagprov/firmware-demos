
CC=gcc
LD=gcc
CFLAGS=-Wall -fPIC -fPIE -pie
LDFLAGS=-Wall -fPIC -fPIE -pie
BUILD_DIR=build

C_SOURCES=asinine/src/asn1-oid.c \
	asinine/src/asn1-parser.c \
	asinine/src/asn1-types.c \
	asinine/src/x509-name.c \
	asinine/src/x509-path.c \
	asinine/src/x509-pubkey.c \
	asinine/src/x509.c \
	certlogic.c \
	main.c 
C_INCLUDES="-Iasinine/include"

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

default: prep $(BUILD_DIR)/certvuln

prep:
	mkdir -p $(BUILD_DIR)/asinine/src

$(BUILD_DIR)/certvuln: $(OBJECTS) | $(BUILD_DIR)
	$(LD) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(C_INCLUDES) -c $^ -o $@


