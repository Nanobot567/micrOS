# ----------------------------
# Makefile Options
# ----------------------------

NAME = MICROS
ICON = icon.png
DESCRIPTION = "micrOS v1.1d"
COMPRESSED = YES
ARCHIVED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
